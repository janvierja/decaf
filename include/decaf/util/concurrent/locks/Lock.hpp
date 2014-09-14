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

#ifndef DECAF_UTIL_CONCURRENT_LOCKS_LOCK_HPP
#define	DECAF_UTIL_CONCURRENT_LOCKS_LOCK_HPP

#include "decaf/util/concurrent/TimeUnit.hpp"

class Lock {
  public:
    /**
     * Acquires the lock
     */
    void lock() = 0;
    
    /**
     * Releases the lock
     */
    void unlock() = 0;
    
    /**
     * Acquires the lock only if it is free at the time of invocation.
     * Acquires the lock if it is available and returns immediately with the 
     * value true. If the lock is not available then this method will return 
     * immediately with the value false.
     * @return true if the lock was acquired, false, otherwise
     */
    bool tryLock() = 0;
    
    /**
     * Acquires the lock if it is free within the given waiting time and the 
     * current thread has not been interrupted.

     * @param t the maximum time to wait for the lock
     * @param unit the timeunit of the 't' argument
     * @return true if the lock was acquired and false if the waiting time 
     * elapsed before the lock was acquired
     */
    bool tryLock(const uint64_t& t, const TimeUnit* unit) = 0;
};

#endif	/* DECAF_UTIL_CONCURRENT_LOCKS_LOCK_HPP */

