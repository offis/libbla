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
 * petBm.h
 *
 *  Created on: 08.07.2019
 *      Author: iyarza
 */

#ifndef PETBM_H_INCLUDED_
#define PETBM_H_INCLUDED_

/************************** Function Prototypes ******************************/

#include "time.h"
#include "timer.h"
#include "initPlatform.h"
#include "trace.h"
#include "macros2.h"


class petBm
{

public:
  using time_type = sysx::units::time_type;
  petBm(time_type const& duration, int id);
  ~petBm();
  static void addBudget(time_type duration);
  static time_type getBudget();
  static time_type getStart();
  static bool is_active();

private:
  const unsigned id_;
  time_type start_, end_, petBudget_;
  const int causal_id_;
  static petBm* petBlock_;
};

#endif // PETBM_H_INCLUDED_
