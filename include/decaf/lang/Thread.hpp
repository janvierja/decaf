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

#ifndef DECAF_THREAD_HPP
#define DECAF_THREAD_HPP

#include "decaf/lang/Commmon.hpp"
#include "decaf/lang/Runnable.hpp"

DECAF_OPEN_NAMESPACE2(decaf, lang)

/**
 * A thread is a thread of execution in a program.
 *
 * Every thread has a priority. Threads with higher priority are executed in
 * preference to threads with lower priority. Each thread may or may not also
 * be marked as a daemon. When code running in some thread creates a new Thread object,
 * the new thread has its priority initially set equal to the priority of the creating thread,
 * and is a daemon thread if and only if the creating thread is a daemon.
 *
 * Every thread has a name for identification purposes. More than one thread may have
 * the same name. If a name is not specified when a thread is created, a new name is
 * generated for it.
 */
class Thread : public virtual Object, public virtual Runnable {
} // class Thread

DECAF_CLOSE_NAMESPACE2

#endif // DECAF_THREAD_HPP
