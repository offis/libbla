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
 * Example for Flight Controller CPU1
 *
 *  Created on: 11.09.2018
 *      Author: friederike bruns
 */

#include "../include/bla.h"


/*
 * Main can be changed by the user to annotate his code with FETs and BETs
 */
class CPUOne{
	void testingCPUOne(){


auto &initP = initPlatform::Inst();
auto &trac = traceSingleton::getInstance();

BLOCK_PET(2.1_ms){
			BLOCK_FET(0.55_ms){
			}
			BLOCK_FET(0.02_ms){
			}
			BLOCK_FET(0.02_ms) {
			}
			BLOCK_FET(0.55_ms){
				BLOCK_BET(0.08_ms){
				}
				BLOCK_BET(0.1_ms){
				}
				BLOCK_BET(0.14_ms){
				}
			}
			BLOCK_FET(0.02_ms){
			}
		}
	trac.output();
	}

};
