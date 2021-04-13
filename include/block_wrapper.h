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

#ifndef SYSX_UTILS_BLOCK_WRAPPER_H_INCLUDED_
#define SYSX_UTILS_BLOCK_WRAPPER_H_INCLUDED_

#include "macros.h"

#include <utility>

#define SYSX_UTILS_BLOCK_WRAPPER_NAME_ \
  SYSX_IMPL_CONCAT_( sysx_utils_block_wrapper_ , __LINE__ )

/**
 * \brief block annotation helper macro
 *
 * This macro can be used to easily implement new
 * block-based source-code annotations.
 *
 * \param Type The type of the specific class, that
 *             performs the handling of the code annotation
 *             (see sysx::utils::block_wrapper_t).
 *
 * Any additional arguments are passed to the constructor
 * of the given type.
 *
 * \see sysx::impl::block_wrapper
 */
#define SYSX_UTILS_BLOCK_( Type, ... ) \
  if( auto SYSX_UTILS_BLOCK_WRAPPER_NAME_ \
        = ::sysx::utils::block_wrapper_t< Type >{ __VA_ARGS__ } ) {} else

namespace sysx {
namespace utils {

/**
 * \brief helper class for source-code annotations
 *
 * This helper class is used as a wrapper for source-code annotations.
 *
 * On entrance of the annotated block (with some specific annotation
 * macro, see SYSX_UTILS_BLOCK_()), the constructor of the specific
 * annotation class \at T is executed an can perform its task.  Once the
 * control flow leaves the block, the destructor of the object can
 * perform its house-keeping.
 *
 * \tparam T the user-defined annotation class which is
 *           constructed/destructed.
 *
 * Example:
 * \code
 *   class some_annotation_helper 
 *   {
 *     // constructor
 *     some_annotation_helper( arguments ) {
 *       // executed at beginning of annotated block
 *     }
 *     ~some_annotation_helper() {
 *       // executed at end of block
 *     }
 *   }
 *   #define SYSX_ANNOTATE( Arg1, Arg2 ) \
 *     SYSX_UTILS_BLOCK_( some_annotation_helper, Arg1, OtherArg, Arg2 )
 *
 *   // ... somewhere inside the user code
 *   SYSX_ANNOTATE( 20, SC_NS ) {
 *     // ... annotated source code here
 *   }
 * \endcode
 *
 * \see SYSX_UTILS_BLOCK_()
 */
template< typename T >
struct block_wrapper_t
{

  template< typename... Args >
  block_wrapper_t( Args&&... args )
  : obj_{ std::forward<Args>(args) ... }
  { }

  operator bool() const { return false; }

private:
  T obj_;
};

} // namespace utils
} // namespace sysx

#endif /* SYSX_UTILS_BLOCK_WRAPPER_H_INCLUDED_ */
/* Taf!
 * :tag: (utils,h)
 */
