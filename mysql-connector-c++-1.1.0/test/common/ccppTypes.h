/*
  Copyright (c) 2008, 2010, Oracle and/or its affiliates. All rights reserved.

  The MySQL Connector/C++ is licensed under the terms of the GPLv2
  <http://www.gnu.org/licenses/old-licenses/gpl-2.0.html>, like most
  MySQL Connectors. There are special exceptions to the terms and
  conditions of the GPLv2 as it is applied to this software, see the
  FLOSS License Exception
  <http://www.mysql.com/about/legal/licensing/foss-exception.html>.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published
  by the Free Software Foundation; version 2 of the License.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
  or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
  for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin St, Fifth Floor, Boston, MA 02110-1301  USA
*/
/*
  Some common definitions and inclusions for C/C++ tests.
*/

#ifndef __C_CPP_TYPES_H_
#define __C_CPP_TYPES_H_

#if (defined(_WIN32) || defined(_WIN64)) && !defined(__MINGW32__)
/* MySQL 5.1 might have defined it before in include/config-win.h */
#  ifdef strncasecmp
#    undef strncasecmp
#  endif
#  define strncasecmp(s1,s2,n) _strnicmp(s1,s2,n)
#else
#  include <string.h>
#endif

#include "cppconn/config.h"
#if !defined(_WIN32) || defined(__MINGW32__)
#  include <stdlib.h>
#  ifndef HAVE_FUNCTION_STRTOLL
#    ifdef HAVE_FUNCTION_STRTOL
#      define strtoll(__a, __b, __c) strtol((__a), (__b), (__c))
#    else
#      ifdef HAVE_FUNCTION_STRTOIMAX
#        define strtoll(__a, __b, __c) strtoimax((__a), NULL, 10)
#      else
#        error "Compilation will fail because code does not know an equivalent of strtol/strtoll"
#      endif
#    endif
#    define HAVE_FUNCTION_STRTOLL 1
#  endif
#  ifndef HAVE_FUNCTION_STRTOULL
#    ifdef HAVE_FUNCTION_STRTOUL
#      define strtoull(__a, __b, __c) strtoul((__a), (__b), (__c))
#    else
#      ifdef HAVE_FUNCTION_STRTOUMAX
#        define strtoull(__a, __b, __c) strtoumax((__a), NULL, 10)
#      else
#        error Compilation will fail because code does not know an equivalent of strtoul/strtoull
#      endif
#    endif
#    define HAVE_FUNCTION_STRTOULL 1
#  endif
#else
#  define strtoll(x, e, b) _strtoi64((x), (e), (b))
#  define strtoull(x, e, b) _strtoui64((x), (e), (b))
#endif	//	_WIN32


#include <vector>
#include <string>
#include <memory>
#include <map>
#include <iostream>
#include <list>
#include <cctype>
/*#include <locale>*/

#ifndef _ABSTRACT
#define _ABSTRACT
#endif

#ifndef _PURE
#define _PURE =0
#endif

#ifndef L64
#if defined(_WIN32) && !defined(__MINGW32__)
#define L64(x) x##i64
#else
#define L64(x) x##LL
#endif
#endif

#ifndef UL64
#if defined(_WIN32) && !defined(__MINGW32__)
#define UL64(x) x##ui64
#else
#define UL64(x) x##ULL
#endif
#endif


/*----------------------------------------------------------------------------
ci_char_traits : Case-insensitive char traits.
----------------------------------------------------------------------------*/
template <typename charT> struct ci_char_traits
: public std::char_traits<charT>
// just inherit all the other functions
//  that we don't need to override
{
  static bool eq (charT c1, charT c2)
  {
    return std::tolower(c1) == std::tolower(c2);
  }

  static bool ne (charT c1, charT c2)
  {
    return std::tolower(c1) != std::tolower(c2);
  }

  static bool lt (charT c1, charT c2)
  {
    return std::tolower(c1) < std::tolower(c2);
  }

  static int compare (const charT* s1, const charT* s2, size_t n)
  {
    return strncasecmp(s1, s2, n);
  }

  static const charT* find (const charT* s, std::allocator<char>::size_type n, charT a)
  {
    while ( --n != static_cast<std::allocator<char>::size_type>(-1)
          && std::tolower(*s) != std::tolower(a))
    {
      ++s;
    }

    return (n != static_cast<std::allocator<char>::size_type>(-1) ? s : 0);
  }
};

//Some stubs for unicode use. Following usual win scheme
#ifdef UNICODE_32BIT
typedef std::basic_string
<wchar_t,
std::char_traits<wchar_t>,
std::allocator<wchar_t> >
String;

#ifndef _T
#define _T(strConst) L ## strConst
#endif

#else
typedef std::basic_string
<char,
std::char_traits<char>,
std::allocator<char> >
String;

typedef std::basic_string
<char,
ci_char_traits<char>,
std::allocator<char> >
ciString;

#ifndef _T
#define _T(strConst) strConst
#endif

#endif

typedef std::vector<String>   List;
typedef List::iterator        Iterator;
typedef List::const_iterator  ConstIterator;

typedef std::map<String, String>  Properties;
typedef Properties::iterator      PropsIterator;
typedef List::const_iterator      PropsConstIterator;

#endif /* __C_CPP_TYPES_H_ */
