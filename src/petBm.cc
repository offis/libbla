 /*
 * Copyright (c) 2018-2020 OFFIS Institute for Information Technology
 *                          Oldenburg, Germany
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 /*
 * petBm.cc
 *
 *  Created on: 08.07.2019
 *      Author: iyarza
 */

#include "../include/petBm.h"

petBm* petBm::petBlock_;

/*
 * Called when PET block starts and saves its context
 * puts block in queue
 */
petBm::petBm(time_type const& duration, int id)
  : id_(id)
  , start_(timer::getTime())
  , end_(timer::getTime() + duration)
  , petBudget_(0_ms)
  , causal_id_(traceSingleton::cnt)
{
  traceSingleton::getInstance().PET_entry_trace(id_, causal_id_, start_);
  assert(!petBm::is_active() && "Just one PET block allowed!");
  petBlock_ = this;
  traceSingleton::cnt++;
  traceSingleton::cntPet++;

}

/*
 * Called when PET block ends
 * waits for interrupt and then deletes PET context
 */
petBm::~petBm(){
  auto now = timer::getTime();
  auto &initP = initPlatform::Inst();
  if (now > end_) {
    printf("PET Block %i overflow!\n", id_);
    assert(false && "block overflow");
  } else {
	  initP.waitFor(end_ - now);
  }
  petBlock_ = NULL;
  traceSingleton::getInstance().PET_exit_trace(id_, causal_id_, timer::getTime());
#ifdef  TRACEON
  traceSingleton::hierarchy.pop_back();
#endif //TRACEON

}

/*
 * Updates budget within PET
 */
void
petBm::addBudget(time_type duration){
  petBlock_->petBudget_ = duration;
}

/*
 * Returns budget within PET
 */
petBm::time_type
petBm::getBudget(){
  return petBlock_->petBudget_;
}

/*
 * Returns active PET ID
 */
bool
petBm::is_active(){
  return (petBlock_ != NULL);
}

/*
 * Returns PET start time
 */
petBm::time_type
petBm::getStart(){
  return petBlock_->start_;
}

