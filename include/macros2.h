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

#include <iostream>
#define TRACEON //redefine Trace to do nothing and turn off printf if not defined
#ifndef TRACEON
	#define printf(fmt, ...) (0)
#endif


//  text	   data	    bss	    dec	    hex	filename
// 505507	   4408	  29704	 539619	  83be3	test.elf
//text	   data	    bss	    dec	    hex	filename
 //504635	   4408	  29704	 538747	  8387b	test.elf
//text	   data	    bss	    dec	    hex	filename
// 504203	   4408	  29704	 538315	  836cb	test.elf