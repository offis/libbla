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
#include "../include/memory.h"

memory::memory(){

}

memory& memory::getInstance() {
	static memory Instan;
	return Instan;
}
#ifdef TRACEON
void memory::output(){
	int counting = 0;
	  for(int i = 0; i < 100; i++){
		  std::cout << bodies[i].identity << bodies[i].times << " " << "ms \n";
		  //printf("%s %d ms \n",bodies[i].identity,bodies[i].times);
		  // if(i > 0 && i % 3 == 0 && i % 6 != 0){
			 //  switchingTimes[counting] = bodies[i].times - bodies[i-1].times;
			  // printf("Switching Time: %f \n",switchingTimes[counting]);
			//   counting++;
			   //printf("Compute Time: %d %d\n",mem.bodies[counter-2].times, mem.bodies[counter-3].times);
		   //}
	  }

}
void memory::switchingTime(){
	auto &mem = memory::getInstance();
	double average;
	for(int i=0; i < 10 ;i++){
		average += switchingTimes[i];
	}
	average /= 10;
	printf("Average Switching Time: %f ms\n",average);
}
#endif //TRACEON
