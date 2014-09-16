/*
 * Copyright (c) 2014, Janvier D. Anonical. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef DECAF_COMPATIBILITY_HPP
#define DECAF_COMPATIBILITY_HPP

// ----- identify operating system ------------------------------------------

#if defined(_WIN32)
#   define DECAF_OS_WINDOWS
#   define DECAF_LIB_PREFIX ""
#   define DECAF_LIB_SUFFIX ".dll"
#   if defined(_WIN64)
#      define DECAF_OS_WIN64 // Windows 2003/2008/Vista
#      define DECAF_PLATFORM Microsoft Windows x64
#   else
#      define DECAF_OS_WIN32 // Windows NT/2000/XP
#      define DECAF_PLATFORM Microsoft Windows x86
#   endif
#elif defined(__sun) || defined(sun)
#   define DECAF_OS_SOLARIS // Oracle Solaris
#   define DECAF_OS_UNIX
#   define DECAF_LIB_PREFIX "lib"
#   define DECAF_LIB_SUFFIX ".so"
#   include <sys/types.h> // for _LP64 definition
#   if defined(__sparc)
#       if defined(_LP64)
#           define DECAF_OS_SOLARIS64
#           define DECAF_PLATFORM Oracle Solaris SPARC 64b
#       else
#           define DECAF_OS_SOLARIS32
#           define DECAF_PLATFORM Oracle Solaris SPARC 32b
#       endif
#   elif defined(__x86)
#       if defined(_LP64)
#           define DECAF_OS_SOLARIS64
#           define DECAF_PLATFORM Oracle Solaris x64
#       else
#           define DECAF_OS_SOLARIS32
#           define DECAF_PLATFORM Oracle Solaris x86
#       endif
#   endif
#elif defined(__linux__)
#   define DECAF_OS_LINUX // Linux
#   define DECAF_LIB_PREFIX "lib"
#   define DECAF_LIB_SUFFIX ".so"
#   define DECAF_OS_UNIX
#   if defined(__x86_64__) || defined(__amd64__)
#       define DECAF_OS_LINUX64
#       define DECAF_PLATFORM Linux x64
#   elif defined(__x86_32__) || defined(__i386__)
#       define DECAF_OS_LINUX32
#       define DECAF_PLATFORM Linux x86
#   endif
#elif defined(__APPLE__)
#   define DECAF_OS_DARWIN // Mac OS X
#   define DECAF_OS_UNIX
#   define DECAF_LIB_PREFIX "lib"
#   define DECAF_LIB_SUFFIX ".dylib"
#   if defined(__x86_64__) || defined(__amd64__)
#       define DECAF_OS_DARWIN64
#       define DECAF_PLATFORM Apple Mac OS X x64
#   elif defined(__x86_32__) || defined(__i386__)
#       define DECAF_OS_DARWIN32
#       define DECAF_PLATFORM Apple Mac OS X x86
#   endif
#endif

#ifndef DECAF_PLATFORM
#   error "Decaf for C++ does not support this platform."
#endif


// ----- identify compiler --------------------------------------------------

#if defined(_MSC_VER) && _MSC_VER >= 1400
#   define DECAF_CC_MSVC // Microsoft Visual C/C++
#   if _MSC_VER == 1400
#       define DECAF_CC msvc 2005
#   elif _MSC_VER == 1500
#       define DECAF_CC msvc 2008
#   elif _MSC_VER == 1600
#       define DECAF_CC msvc 2010
#   elif _MSC_VER == 1700
#       define DECAF_CC msvc 2012
#   elif _MSC_VER == 1800
#       define DECAF_CC msvc 2013
#   else
#       define DECAF_CC msvc
#   endif
#elif defined(__SUNPRO_CC) && __SUNPRO_CC >= 0x590
#   define DECAF_CC_SUN // Forte Developer, or Oracle Solaris Studio
#   if defined (STLPORT)
#       define DECAF_CC sunpro stlport
#   else
#       define DECAF_CC sunpro
#   endif
#elif defined(__GNUG__) && (__GNUC__ >= 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 5))
#   define DECAF_CC_GNU // GNU C++
#   define DECAF_CC gcc
#else
#   error "Decaf for C++ does not support this compiler or compiler version."
#endif

#if __cplusplus > 199711L
#   define DECAF_CC11
#endif

// ----- namespace macros -----------------------------------------------------

namespace decaf { namespace lang { } }

#define DECAF_OPEN_NAMESPACE(ns) namespace ns { \
    using namespace decaf::lang;

#define DECAF_INNER_NAMESPACE(ns) namespace ns {
#define DECAF_OPEN_NAMESPACE2(ns1, ns2) \
    DECAF_OPEN_NAMESPACE(ns1) DECAF_INNER_NAMESPACE(ns2)
#define DECAF_OPEN_NAMESPACE3(ns1, ns2, ns3) \
    DECAF_OPEN_NAMESPACE2(ns1, ns2) DECAF_INNER_NAMESPACE(ns3)
#define DECAF_OPEN_NAMESPACE4(ns1, ns2, ns3, ns4) \
    DECAF_OPEN_NAMESPACE3(ns1, ns2, ns3) DECAF_INNER_NAMESPACE(ns4)
#define DECAF_OPEN_NAMESPACE5(ns1, ns2, ns3, ns4, ns5) \
    DECAF_OPEN_NAMESPACE3(ns1, ns2, ns3, ns4) DECAF_INNER_NAMESPACE(ns5)

#define DECAF_CLOSE_NAMESPACE }
#define DECAF_CLOSE_NAMESPACE2 } }
#define DECAF_CLOSE_NAMESPACE3 } } }
#define DECAF_CLOSE_NAMESPACE4 } } } }
#define DECAF_CLOSE_NAMESPACE5 } } } } }

/**
 * This macro "mangles" the specified @a Name, producing an identifier which
 * is unique in the current file.
 *
 * @param Name the name to produce a new identifier on its basis
 */
#define DECAF_JOIN(X, Y) DECAF_DO_JOIN(X, Y)
#define DECAF_DO_JOIN(X, Y) DECAF_DO_JOIN2(X, Y)
#define DECAF_DO_JOIN2(X, Y) X##Y
#define DECAF_UNIQUE_IDENTIFIER(Name) DECAF_JOIN(Name, __LINE__)

#endif // DECAF_COMPATIBILITY_HPP
