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
 * trace.h
 *
 * Created on: 21.06.2019
 *     Author: irune
 *  Edited on: 08.07.2019
 *     Author: irune
 */

#ifndef TRACE_H_INCLUDED_
#define TRACE_H_INCLUDED_

#include "time.h"
#include "memory.h"
#include "timer.h"
#include "macros2.h"
#include <vector>
#include "embxx/container/StaticQueue.h"


class traceSingleton{
  public:
    using time_type = sysx::units::time_type;
    static traceSingleton& getInstance();
    void output();
    void FET_entry_trace(int id, int causal_id_, time_type instant);
    void FET_exit_trace(int id, int causal_id_, time_type instant);
    void BET_entry_trace(int id, int causal_id_, time_type instant);
    void BET_pentry_trace(int id, int causal_id_, time_type instant);
    void BET_exit_trace(int id, int causal_id_, time_type instant);
    void PET_entry_trace(int id, int causal_id_, time_type instant);
    void PET_exit_trace(int id, int causal_id_, time_type instant);
    void switchingTime();
    static int cnt, cntPet, cntPnet, counter;
#ifdef TRACEON
    static std::vector<std::string> hierarchy;
#endif//TRACEON
    static time_type startTimeL1;
    static time_type startTimeL2;

  private:
    traceSingleton();
    traceSingleton(traceSingleton const&);
    void operator = (traceSingleton const&);
#ifdef TRACEON
    std::ostream myfile_;
    void print(std::string id, time_type instant);
#endif//TRACEON
};

#endif //TRACE_H_INCLUDED_
