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
 * timer.h
 *
 *  Created on: 04.07.2018
 *      Author: fried
 */

#ifndef TIMER_H_INCLUDED_
#define TIMER_H_INCLUDED_

/************************** Function Prototypes ******************************/

#include "xTime_l.h"
#include "time.h"

#include "boost/core/noncopyable.hpp"

#include "xparameters.h"



class timer: public boost::noncopyable {

public:

	using time_type = sysx::units::time_type;
	using frequency_type = sysx::units::frequency_type;

	static time_type getTime();
	static timer& Instance();

private:
	timer();
	frequency_type tickrate_;
	time_type fromTicks(XTime time) {
		return 1.0 * time / tickrate_;

		}

};

#endif // TIMER_H_INCLUDED_

