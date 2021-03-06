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
 * betBm.h
 *
 *  Created on: 01.08.2018
 *      Author: fried
 */

#ifndef BETBM_H_INCLUDED_
#define BETBM_H_INCLUDED_

/************************** Function Prototypes ******************************/
#include "macros2.h"
#include "time.h"
#include "timer.h"
#include "petBm.h"
#include "fetBm.h"

class betBm {


public:
  using time_type = sysx::units::time_type;
  betBm(time_type const& duration, int id);
  ~betBm();

private:
  const unsigned id_;
  time_type start_, end_;
  const int causal_id_;

};

#endif // BETBM_H_INCLUDED_

