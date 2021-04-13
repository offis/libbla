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
 * watchdogTimer.h
 *
 *  Created on: 28.06.2018
 *      Author: fried
 */

#ifndef WATCHDOG_H_INCLUDED_
#define WATCHDOG_H_INCLUDED_

#include "xparameters.h"
#include "xTime_l.h"
#include "xscuwdt.h"
#include "xscugic.h"
#include "xil_exception.h"
#include <stdio.h>
/************************** Constant Definitions *****************************/

/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are only defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#define WDT_DEVICE_ID		XPAR_SCUWDT_0_DEVICE_ID
#define INTC_DEVICE_ID		XPAR_SCUGIC_SINGLE_DEVICE_ID
#define WDT_IRPT_INTR		XPAR_SCUWDT_INTR

class watchdog {

public:
	watchdog(XScuGic& Gic);
	void startWdTi(XTime dur);
	static void WdtIntrHandler(void *CallBackRef);
	void WdtSetupIntrSystem(XScuGic *IntcInstancePtr, XScuWdt *WdtInstancePtr);
	void WdtDisableIntrSystem(XScuGic *IntcInstancePtr);

private:
	XScuWdt WdtInstance; /* Cortex SCU Private WatchDog Timer Instance */
	XScuGic& IntcInstance; /* Interrupt Controller Instance */

};
#endif // WATCHDOG_H_INCLUDED_

