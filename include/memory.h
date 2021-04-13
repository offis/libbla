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
#define MEMORY_H_INCLUDED_

/************************** Function Prototypes ******************************/
#include "boost/core/noncopyable.hpp"
#include "time.h"
#include "macros2.h"
#include <vector>



class memory: public boost::noncopyable {

public:

	static memory& getInstance();
#ifdef TRACEON
    void output();
    void switchingTime();
    struct body
    {
        std::string identity;
        double times;
    };

    struct body bodies[100];
    double switchingTimes[10];
#else
void output(){}
struct body
   {   };

   struct body bodies[10];
#endif //TRACEON

private:
	memory();


};

#endif // MEMORY_H_INCLUDED_

