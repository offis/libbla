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
 * watchdogTimer.cc
 *
 *  Created on: 28.06.2018
 *      Author: friederike bruns
 */
#include "../include/watchdogTimer.h"

extern void wdTiHandleIntr();

watchdog::watchdog(XScuGic& Gic) :
		IntcInstance(Gic) {
	int Status;
	XScuWdt_Config *ConfigPtr;
	/*
	 * Initialize the ScuWdt driver.
	 */
	ConfigPtr = XScuWdt_LookupConfig(WDT_DEVICE_ID);

	/*
	 * This is where the virtual address would be used, this example
	 * uses physical address.
	 */
	Status = XScuWdt_CfgInitialize(&WdtInstance, ConfigPtr,
			ConfigPtr->BaseAddr);
	/*
	 * Put the watchdog timer in timer mode.
	 */
	XScuWdt_SetTimerMode(&WdtInstance);
	/*
	 * Connect the device to interrupt subsystem so that interrupts
	 * can occur.
	 */
	WdtSetupIntrSystem(&IntcInstance, &WdtInstance);
}

void watchdog::startWdTi(XTime dur) {
	/*
	 * Load the watchdog counter register.
	 */
	XScuWdt_LoadWdt(&WdtInstance, dur);

	/*
	 * Start the ScuWdt device.
	 */
	XScuWdt_Start(&WdtInstance);
}


void watchdog::WdtSetupIntrSystem(XScuGic *IntcInstancePtr,
		XScuWdt *WdtInstancePtr) {
	int Status;
	u32 Reg;

	XScuGic_Config *IntcConfig;
	/*
	 * Initialize the interrupt controller driver so that it is ready to
	 * use.
	 */
	IntcConfig = XScuGic_LookupConfig(INTC_DEVICE_ID);

	Status = XScuGic_CfgInitialize(IntcInstancePtr, IntcConfig,
			IntcConfig->CpuBaseAddress);

	Xil_ExceptionInit();

	/*
	 * Connect the interrupt controller interrupt handler to the hardware
	 * interrupt handling logic in the processor.
	 */
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
			(Xil_ExceptionHandler) XScuGic_InterruptHandler, IntcInstancePtr);

	/*
	 * Connect the device driver handler that will be called when an
	 * interrupt for the device occurs, the handler defined above performs
	 * the specific interrupt processing for the device.
	 */
	Status = XScuGic_Connect(IntcInstancePtr, WDT_IRPT_INTR,
			(Xil_ExceptionHandler) WdtIntrHandler, (void *) WdtInstancePtr);

	/*
	 * Enable the watchdog interrupts for timer mode.
	 */
	Reg = XScuWdt_GetControlReg(WdtInstancePtr);
	XScuWdt_SetControlReg(WdtInstancePtr, Reg | XSCUWDT_CONTROL_IT_ENABLE_MASK);

	/*
	 * Enable the interrupt for the device.
	 */
	XScuGic_Enable(IntcInstancePtr, WDT_IRPT_INTR);

	/*
	 * Enable interrupts in the Processor.
	 */
	Xil_ExceptionEnable();

}


void watchdog::WdtIntrHandler(void *CallBackRef) {
	wdTiHandleIntr();
}


void watchdog::WdtDisableIntrSystem(XScuGic *IntcInstancePtr) {
	/*
	 * Disconnect and disable the interrupt for the Wdt.
	 */
	XScuGic_Disconnect(IntcInstancePtr, WDT_IRPT_INTR);

}
