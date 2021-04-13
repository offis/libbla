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
 * priTimer.h
 *
 *  Created on: 10.09.2018
 *      Author: fried
 */

#ifndef PRITIMER_H_INCLUDED_
#define PRITIMER_H_INCLUDED_

#include "xparameters.h"
#include "xscutimer.h"
#include "xscugic.h"
#include "xil_exception.h"
#include "xil_printf.h"
#include <stdio.h>
#include "xTime_l.h"
#include <iostream>

/************************** Constant Definitions *****************************/

/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are only defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#define TIMER_DEVICE_ID		XPAR_XSCUTIMER_0_DEVICE_ID
#define INTC_DEVICE_ID		XPAR_SCUGIC_SINGLE_DEVICE_ID
#define TIMER_IRPT_INTR		XPAR_SCUTIMER_INTR




/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/
class priTimer {

public:
	priTimer(XScuGic& Gic);
	void startPriTi(XTime dur);
	static void TimerIntrHandler(void *CallBackRef);
	int TimerSetupIntrSystem(XScuGic *IntcInstancePtr,
			XScuTimer *TimerInstancePtr, u16 TimerIntrId);
	void TimerDisableIntrSystem(XScuGic *IntcInstancePtr,
			XScuTimer *TimerInstancePtr, u16 TimerIntrId);

private:
	XScuTimer TimerInstance; /* Cortex A9 Scu Private Timer Instance */
	XScuGic& IntcInstance; /* Interrupt Controller Instance */

};
#endif // PRITIMER_H_INCLUDED_

