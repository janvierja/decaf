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

#ifndef DECAF_CONDITION_HPP
#define	DECAF_CONDITION_HPP

#include "decaf/lang/compatibility.hpp"
#include "decaf/lang/Object.hpp"

DECAF_OPEN_NAMESPACE4(decaf, util, concurrent, locks)

/**
 * 
 */
class Condition : public Object {
  public:
    /**
     * Causes the current thread to wait until it is signaled.
     */
    void await() = 0;

    /**
     * Causes the current thread to wait until it is signalled or interrupted,
     * or the specified waiting time elapses.
     * 
     * @param t the maximum time to wait
     * @param unit the time unit of argument t
     * @return false if the waiting time detectably elapsed before return 
     * from the method, else true
     */
    bool await(const uint64_t& t, const TimeUnit* unit) = 0;

    /**
     * Causes the current thread to wait until it is signalled or interrupted,
     * or the specified waiting time elapses.
     * 
     * @param nanosTimeout the maximum time to wait, in nanoseconds
     * @return an estimate of the nanosTimeout value minus the time spent 
     * waiting upon return from this method. A positive value may be used as 
     * the argument to a subsequent call to this method to finish waiting out
     * the desired time. A value less than or equal to zero indicates that no 
     * time remains.
     */
    int64_t awaitNanos(const uint64_t& nanosTimeout) = 0;

    /**
     * Wakes up one waiting thread.
     * If any threads are waiting on this condition then one is selected for 
     * waking up. That thread must then re-acquire the lock before returning 
     * from await.
     */
    void signal() = 0;

    /**
     * Wakes up all waiting threads.
     * If any threads are waiting on this condition then they are all woken up.
     * Each thread must re-acquire the lock before it can return from await.
     */
    void signalAll() = 0;
};

DECAF_CLOSE_NAMESPACE4

#endif	/* DECAF_CONDITION_HPP */

