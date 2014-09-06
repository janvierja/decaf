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

#ifndef DECAF_LANG_THREADGROUP_HPP
#define DECAF_LANG_THREADGROUP_HPP

#include "decaf/lang/Commmon.hpp"

DECAF_OPEN_NAMESPACE2(decaf, lang)

/**
 * A thread group represents a set of threads. In addition, a thread group can also include
 * other thread groups. The thread groups form a tree in which every thread group except the
 * initial thread group has a parent.
 *
 * A thread is allowed to access information about its own thread group, but not to access information about its thread group's parent thread group or any other thread groups.
 */
class ThreadGroup : public virtual Object {
} // class Thread

DECAF_CLOSE_NAMESPACE2

#endif // DECAF_LANG_THREADGROUP_HPP
