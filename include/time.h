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

#ifndef TIME_H_INCLUDED_
#define TIME_H_INCLUDED_

#include "macros.h"
#include <boost/units/quantity.hpp>
#include <boost/units/scale.hpp>
#include <boost/units/units_fwd.hpp>

#include <boost/units/io.hpp>

#include <boost/units/base_units/si/second.hpp>
#include <boost/units/systems/si/prefixes.hpp>
#include <boost/units/systems/si/time.hpp>
#include <boost/units/systems/si/frequency.hpp>

namespace sysx {
namespace units {

using boost::units::quantity;
namespace si = boost::units::si;

using time_type = quantity<si::time, double>;
using frequency_type = quantity<si::frequency>;

} // namespace units
} // namespace sysx

namespace sysx {
namespace si {

using units::si::micro;
using units::si::milli;
using units::si::nano;

using units::si::seconds;
using units::si::time;
using units::si::frequency;

namespace /* anonymous */ {

#define SYSX_UNITS_SCALED_CONSTANT_(Unit, Name, Scale)                         \
  static const ::sysx::units::quantity<Unit> SYSX_IMPL_UNUSED_(                \
      SYSX_IMPL_CONCAT_(Scale, Name))(1.0 * Scale * Name)

SYSX_UNITS_SCALED_CONSTANT_(time, seconds, nano);
SYSX_UNITS_SCALED_CONSTANT_(time, seconds, micro);
SYSX_UNITS_SCALED_CONSTANT_(time, seconds, milli);

#undef SYSX_UNITS_SCALED_CONSTANT_

} // anonymous namespace

} // namespace si
} // namespace sysx

// ADL only operates on argument types, so we need to define these convenience
// operators outside of the sysx namespace

#define SYSX_LITERAL_FUNC_(Suffix, ArgTy, Type)                                \
  inline sysx::units::time_type operator"" Suffix(ArgTy val) {                 \
    return sysx::units::time_type(static_cast<double>(val) * Type);            \
  }

#define SYSX_UNITS_LITERAL_(Suffix, Type)                                      \
  SYSX_LITERAL_FUNC_(Suffix, long double, Type)                                \
  SYSX_LITERAL_FUNC_(Suffix, unsigned long long, Type)

// The following definition provides literal operators for specifying the time
// in a convenient manner.  Example: Use 2_s to define a duration of 2 seconds.

SYSX_UNITS_LITERAL_(_ns, sysx::si::nanoseconds)
SYSX_UNITS_LITERAL_(_us, sysx::si::microseconds)
SYSX_UNITS_LITERAL_(_ms, sysx::si::milliseconds)
SYSX_UNITS_LITERAL_(_s, sysx::si::seconds)

#undef SYSX_UNITS_LITERAL_
#undef SYSX_LITERAL_FUNC_

#endif // TIME_H_INCLUDED_
