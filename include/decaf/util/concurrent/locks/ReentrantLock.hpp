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

#ifndef DECAF_REENTRANTLOCK_HPP
#define	DECAF_REENTRANTLOCK_HPP

#include "decaf/lang/compatibility.hpp"
#include "decaf/util/concurrent/locks/Lock.hpp"

DECAF_OPEN_NAMESPACE4(decaf, util, concurrent, locks)

class ReentrantLock : public Lock, public virtual Object  {
  public:
    ReentrantLock();
    ReentrantLock(const ReentrantLock& orig);
    virtual ~ReentrantLock();
  private:

};

DECAF_CLOSE_NAMESPACE4

#endif	/* DECAF_REENTRANTLOCK_HPP */

