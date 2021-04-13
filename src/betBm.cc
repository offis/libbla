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
 * betBm.cc
 *
 *  Created on: 01.08.2018
 *      Author: friederike bruns
 */

#include "../include/betBm.h"


/*
 * Called when BET block starts
 * gets budget for that block and puts it in the queue
 */
betBm::betBm(time_type const &duration, int id) :
		id_(id), start_(timer::getTime()), end_(fetBm::is_active() ? timer::getTime() + duration - fetBm::getBudget() : timer::getTime() + duration + petBm::getBudget())
, causal_id_(traceSingleton::cnt) {
	 traceSingleton::getInstance().BET_entry_trace(id_, causal_id_, start_);
	  traceSingleton::getInstance().BET_pentry_trace(id_, causal_id_, fetBm::is_active() ? fetBm::getStart() : petBm::getStart());
	  assert(petBm::is_active() && "BET can only be used within PET block!");
	  traceSingleton::cnt++;
}

/*
 * Called when BET block ends
 * computes and updates budget for other blocks
 * gets block out of queue
 */
betBm::~betBm() {
	auto now = timer::getTime();

	  if (now > end_) {
	    printf("BET Block %i Overflow!\n", id_);
	    assert(false && "block overflow");
	  } else {
	    auto rem = end_ - now;
	    fetBm::is_active() ? fetBm::addBudget(rem) : petBm::addBudget(rem);
	  }
	  traceSingleton::getInstance().BET_exit_trace(id_, causal_id_, timer::getTime());
#ifdef TRACEON
	  traceSingleton::hierarchy.pop_back();
#endif //TRACEON
}


