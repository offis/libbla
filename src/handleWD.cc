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
 * handleWD.cc
 *
 *  Created on: 11.09.2018
 *      Author: friederike bruns
 */
#include "../include/handleWD.h"

handleWD::handleWD():
	wdTi(IntcInstance),tickrate_(COUNTS_PER_SECOND / ::sysx::si::seconds) {

}
void wdTiHandleIntr() {
	auto &Instan = handleWD::Inst();
	Instan.wdTihandleIntr();
}

handleWD& handleWD::Inst() {
	static handleWD Instan;
	return Instan;
}

/*
 * Called when interrupt occurred
 */
void handleWD::wdTihandleIntr() {
	timeOver = true;
}


/*
 * starts the private timer so an interrupt occurs after certain duration
 */
void handleWD::waitFor(time_type dur) {
	timeOver = false;
	wdTi.startWdTi(toTicks(dur ));
	while (timeOver != true) {
		asm volatile("wfi");
	}

}
