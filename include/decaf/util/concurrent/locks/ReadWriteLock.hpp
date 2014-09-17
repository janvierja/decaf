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

#ifndef DECAF_READWRITELOCK_HPP
#define	DECAF_READWRITELOCK_HPP

#include "decaf/lang/compatibility.hpp"
#include "decaf/lang/Object.hpp"


DECAF_OPEN_NAMESPACE4(decaf, util, concurrent, locks)

class ReadWriteLock : public Object {
  public:
    /**
     * Returns the lock used for reading.
     * @return the lock used for reading
     */
    virtual Lock* readLock() = 0;

    /**
     * Returns the lock used for writing.
     * @return the lock used for writing
     */
    virtual Lock* writeLock() = 0;

};

DECAF_CLOSE_NAMESPACE4

#endif	/* DECAF_READWRITELOCK_HPP */

