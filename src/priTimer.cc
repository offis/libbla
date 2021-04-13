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
 
 #include"../include/priTimer.h"
/*
 * The following variables are shared between non-interrupt processing and
 * interrupt processing such that they must be global.
 */
extern void priTiHandleIntr();


priTimer::priTimer(XScuGic& Gic) :
				IntcInstance(Gic) {
	int Status;
	XScuTimer_Config *ConfigPtr;

	/*
	 * Initialize the Scu Private Timer driver.
	 */
	ConfigPtr = XScuTimer_LookupConfig(TIMER_DEVICE_ID);

	/*
	 * This is where the virtual address would be used, this example
	 * uses physical address.
	 */
	Status = XScuTimer_CfgInitialize(&TimerInstance, ConfigPtr,
			ConfigPtr->BaseAddr);

	/*
	 * Connect the device to interrupt subsystem so that interrupts
	 * can occur.
	 */
	Status = TimerSetupIntrSystem(&IntcInstance, &TimerInstance,
			TIMER_IRPT_INTR);

	/*
	 * Enable Auto reload mode.
	 */
	XScuTimer_EnableAutoReload(&TimerInstance);

}

void priTimer::startPriTi(XTime dur) {

	/*
	 * Load the timer counter register.
	 */
	XScuTimer_LoadTimer(&TimerInstance, dur);

	/*
	 * Start the timer counter and then wait for it
	 * to timeout a number of times.
	 */
	XScuTimer_Start(&TimerInstance);

}


int priTimer::TimerSetupIntrSystem(XScuGic *IntcInstancePtr,
		XScuTimer *TimerInstancePtr, u16 TimerIntrId) {
	int Status;

	XScuGic_Config *IntcConfig;

	/*
	 * Initialize the interrupt controller driver so that it is ready to
	 * use.
	 */
	IntcConfig = XScuGic_LookupConfig(INTC_DEVICE_ID);
	if (NULL == IntcConfig) {
		return XST_FAILURE;
	}

	Status = XScuGic_CfgInitialize(IntcInstancePtr, IntcConfig,
			IntcConfig->CpuBaseAddress);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	Xil_ExceptionInit();

	/*
	 * Connect the interrupt controller interrupt handler to the hardware
	 * interrupt handling logic in the processor.
	 */
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_IRQ_INT,
			(Xil_ExceptionHandler) XScuGic_InterruptHandler, IntcInstancePtr);

	/*
	 * Connect the device driver handler that will be called when an
	 * interrupt for the device occurs, the handler defined above performs
	 * the specific interrupt processing for the device.
	 */
	Status = XScuGic_Connect(IntcInstancePtr, TIMER_IRPT_INTR,
			(Xil_ExceptionHandler) TimerIntrHandler, (void *) &TimerInstance);
	if (Status != XST_SUCCESS) {
		return Status;
	}

	/*
	 * Enable the interrupt for the device.
	 */
	XScuGic_Enable(IntcInstancePtr, TIMER_IRPT_INTR);

	/*
	 * Enable the timer interrupts for timer mode.
	 */
	XScuTimer_EnableInterrupt(&TimerInstance);

	/*
	 * Enable interrupts in the Processor.
	 */
	Xil_ExceptionEnable();

	return XST_SUCCESS;
}


void priTimer::TimerIntrHandler(void *CallBackRef) {

	priTiHandleIntr();

}


void priTimer::TimerDisableIntrSystem(XScuGic *IntcInstancePtr,
		XScuTimer *TimerInstancePtr, u16 TimerIntrId) {
	/*
	 * Disconnect and disable the interrupt for the Timer.
	 */
	XScuTimer_Stop(TimerInstancePtr);
	XScuGic_Disconnect(IntcInstancePtr, TIMER_IRPT_INTR);
}
