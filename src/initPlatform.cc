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
 * initPlatform.cc
 *
 *  Created on: 11.09.2018
 *      Author: friederike bruns
 */
#include "../include/initPlatform.h"

initPlatform::initPlatform():
	priTi(IntcInstance),tickrate_(COUNTS_PER_SECOND / ::sysx::si::seconds) {

}
void priTiHandleIntr() {
	auto &Instan = initPlatform::Inst();
	Instan.handleIntr();
}

initPlatform& initPlatform::Inst() {
	static initPlatform Instan;
	return Instan;
}

/*
 * Called when interrupt occurred
 */
void initPlatform::handleIntr() {
	timeOver = true;
}


/*
 * starts the private timer so an interrupt occurs after certain duration
 */
void initPlatform::waitFor(time_type dur) {
	timeOver = false;
	priTi.startPriTi(toTicks(dur));
	while (timeOver != true) {
		asm volatile("wfi");
	}

}
