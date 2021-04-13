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
 * initPlatform.h
 *
 *  Created on: 11.09.2018
 *      Author: fried
 */

#ifndef INITPLATFORM_H_INCLUDED_
#define INITPLATFORM_H_INCLUDED_

/************************** Function Prototypes ******************************/
#include "time.h"
#include "priTimer.h"
#include "boost/core/noncopyable.hpp"
#include <iostream>
#define PRITIOVERHEAD 0.00004_s //sekunden
//0.00007859974_s
class initPlatform: public boost::noncopyable {

public:
	using time_type = sysx::units::time_type;
	using frequency_type = sysx::units::frequency_type;
	static initPlatform& Inst();
	void handleIntr();
	void init(int count);
	void waitFor(time_type dur);
	XScuGic IntcInstance; /* Interrupt Controller Instance */

private:
	initPlatform();
	priTimer priTi;
	bool timeOver = false;
	time_type fromTicks(XTime time) {
		return 1.0 * time / tickrate_;
	}

	XTime toTicks(time_type time) {
	    return time * tickrate_;
	}
	frequency_type tickrate_;

};

#endif // INITPLATFORM_H_INCLUDED_

