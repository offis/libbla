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
 * trace.cc
 *
 *  Created on: 21.06.2019
 *      Author: irune
 *   Edited on: 08.07.2019
 *      Author: irune
 */

#include "../include/trace.h"

#include <sstream>
#include <iomanip>


int traceSingleton::cnt;
int traceSingleton::cntPet;
int traceSingleton::cntPnet;
int traceSingleton::counter;
sysx::units::time_type traceSingleton::startTimeL1;
sysx::units::time_type traceSingleton::startTimeL2;
#ifdef TRACEON
std::vector<std::string> traceSingleton::hierarchy;
std::vector<std::string> traces;

//#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))

traceSingleton::traceSingleton()
: myfile_(NULL)

{
 // myfile_.open("traces.txt")
	myfile_.rdbuf(std::cout.rdbuf());;
  cnt = 0;
  cntPet = -1;
  cntPnet = 0;
  counter = 0;
  startTimeL1 = timer::getTime();
  startTimeL2 = timer::getTime();
}

traceSingleton& traceSingleton::getInstance()
{
  static traceSingleton instance;
  return instance;
}




void traceSingleton::print(std::string id, time_type instant){
 auto &mem = memory::getInstance();
  double time_ns = static_cast<double>(instant / ::sysx::si::milliseconds);
  for (int i = 0; i < (hierarchy.size() - 1); i++)  {
	  mem.bodies[counter].identity =  mem.bodies[counter].identity +  hierarchy.at(i) + ".";
  }
   mem.bodies[counter].identity = mem.bodies[counter].identity + " " + id + " " ;
   mem.bodies[counter].times = time_ns;
  counter++;

}

void traceSingleton::output(){
	auto &mem = memory::getInstance();
	mem.output();
	//mem.switchingTime();
}

void traceSingleton::FET_entry_trace(int id, int causal_id_, time_type instant)
{
  std::ostringstream oss;
  oss << "FET_" << id;
  hierarchy.push_back(oss.str());
  oss << ".Entry " << causal_id_;
  print(oss.str(), instant);
}

void traceSingleton::FET_exit_trace(int id, int causal_id_, time_type instant)
{
  std::ostringstream oss;
  oss << "FET_" << id << ".Exit " << causal_id_;
  print(oss.str(), instant);
}

void traceSingleton::BET_entry_trace(int id, int causal_id_, time_type instant)
{
  std::ostringstream oss;
  oss << "BET_" << id;
  hierarchy.push_back(oss.str());
  oss << ".Entry " << causal_id_;
  print(oss.str(), instant);
}

void traceSingleton::BET_pentry_trace(int id, int causal_id_, time_type instant)
{
  std::ostringstream oss;
  oss << "BET_" << id << ".PEntry " << causal_id_;
  print(oss.str(), instant);
}

void traceSingleton::BET_exit_trace(int id, int causal_id_, time_type instant)
{
  std::ostringstream oss;
  oss << "BET_" << id << ".Exit " << causal_id_;
  print(oss.str(), instant);
}

void traceSingleton::PET_entry_trace(int id, int causal_id_, time_type instant)
{
  std::ostringstream oss;
  oss << "PET_" << id;
  hierarchy.push_back(oss.str());
  oss << ".Entry " << causal_id_;
  print(oss.str(), instant);
}

void traceSingleton::PET_exit_trace(int id, int causal_id_, time_type instant)
{
  std::ostringstream oss;
  oss << "PET_" << id << ".Exit " << causal_id_;
  print(oss.str(), instant);
}


#else
	traceSingleton::traceSingleton(){	}

	traceSingleton& traceSingleton::getInstance()
	{
	  static traceSingleton instance;
	  return instance;
	}
	void traceSingleton::output(){}
	void traceSingleton::FET_entry_trace(int id, int causal_id_, time_type instant)	{	}
	void traceSingleton::FET_exit_trace(int id, int causal_id_, time_type instant)	{	}
	void traceSingleton::BET_entry_trace(int id, int causal_id_, time_type instant)	{	}
	void traceSingleton::BET_pentry_trace(int id, int causal_id_, time_type instant){	}
	void traceSingleton::BET_exit_trace(int id, int causal_id_, time_type instant)	{	}
	void traceSingleton::PET_entry_trace(int id, int causal_id_, time_type instant)	{	}
	void traceSingleton::PET_exit_trace(int id, int causal_id_, time_type instant)	{	}
#endif //TRACEON
