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

#ifndef DECAF_SYNCHRONIZED_HPP
#define	DECAF_SYNCHRONIZED_HPP

#include "decaf/lang/compatibility.hpp"
#include "decaf/lang/Object.hpp"

DECAF_OPEN_NAMESPACE2(decaf, lang)

/**
 * @internal
 */
class Synchronized {
  public:

    Synchronized(Object& lockable) : m_lockable(lockable) {
        m_lockable.enterSynchronizedBlock();
    }

    ~Synchronized() {
        m_lockable.exitSynchronizedBlock();
    }

    operator bool() const {
        return true;
    }
  private:
    Object& m_lockable;
};

DECAF_CLOSE_NAMESPACE2

#define synchronized(obj) \
    if (decaf::lang::Synchronized DECAF_UNIQUE_IDENTIFIER(decaf_lock_) = *obj)

#endif	/* DECAF_SYNCHRONIZED_HPP */

