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
 * fetBm.cc
 *
 *  Created on: 07.07.2018
 *      Author: friederike bruns
 */

#include "../include/fetBm.h"
static embxx::container::StaticQueue<fetBm*,27> fetBlocks_;
#define FETOVERHEAD 0.00000358599_s
/*
 * Called when FET block starts and saves its context
 * puts block in queue
 */
fetBm::fetBm(time_type const &duration, int id):
		id_(id),start_(timer::getTime()), end_(timer::getTime() + duration - 0.00000358599_s), fetBudget_(0_ms), causal_id_(traceSingleton::cnt) {
	traceSingleton::getInstance().FET_entry_trace(id_, causal_id_, start_);
	  assert(petBm::is_active() && "FET can only be used within PET block!");
	 // fetBlocks_.push_back(this);
	  fetBlocks_.pushBack(this);
	  traceSingleton::cnt++;
}

/*
 * Called when FET block ends
 * waits for interrupt and then deletes FET context
 */
fetBm::~fetBm() {
	auto now = timer::getTime();
	auto &initP = initPlatform::Inst();
	  if (now > end_) {
	    printf("FET Block %i overflow!\n", id_);
	    assert(false && "block overflow");
	  } else {
		initP.waitFor(end_ - now);
	  }

	  //fetBlocks_.pop_back();
	  fetBlocks_.popBack();
	  traceSingleton::getInstance().FET_exit_trace(id_, causal_id_, timer::getTime());
#ifdef TRACEON
	  traceSingleton::hierarchy.pop_back();
#endif

}

/*
 * Updates BET budget
 */
void fetBm::addBudget(time_type duration) {
	auto *this_block_ = fetBlocks_.back();
	this_block_->fetBudget_ = duration;
}

/*
 * Returns BET Budget
 */
fetBm::time_type fetBm::getBudget() {
	auto *this_block_ = fetBlocks_.back();
	return this_block_->fetBudget_;
}

/*
 * Returns active FET ID
 */
bool fetBm::is_active() {
  return !fetBlocks_.empty();
}
/*
 * Returns active FET start time
 */
fetBm::time_type fetBm::getStart() {
	auto *this_block_ = fetBlocks_.back();
	return this_block_->start_;
}

