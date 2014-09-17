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

#include <pthread.h>
#include <map>

#include "decaf/lang/compatibility.hpp"
#include "decaf/util/concurrent/locks/Lock.hpp"

DECAF_OPEN_NAMESPACE4(decaf, util, concurrent, locks)

/**
 * A reentrant mutual exclusion Lock with the same basic behavior and semantics
 * as the implicit monitor lock accessed using synchronized statements, but with
 * extended capabilities.
 * 
 * A ReentrantLock is owned by the thread last successfully locking, but not yet
 * unlocking it. A thread invoking lock will return, successfully acquiring the
 * lock, when the lock is not owned by another thread. The method will return
 * immediately if the current thread already owns the lock.
 */
class ReentrantLock : public Lock {
  public:
    ReentrantLock();
    virtual ~ReentrantLock();
    ReentrantLock(const ReentrantLock& other) = delete;
    ReentrantLock& operator=(const ReentrantLock& rhs) = delete;   

    /**
     * Acquires the lock.
     * 
     * Acquires the lock if it is not held by another thread and
     * returns immediately.
     * 
     * If the lock is held by another thread then the current thread becomes
     * disabled for thread scheduling purposes and lies dormant until the lock
     * has been acquired.
     */
    virtual void lock();
    
    /**
     * Attempts to release this lock.
     */
    virtual void unlock();
    
    /**
     * Acquires the lock only if it is not held by another thread at the time
     * of invocation.
     * 
     * Acquires the lock if it is not held by another thread and returns
     * immediately with the value true.
     * 
     * If the current thread already holds this lock then  the method returns true.
     * 
     * If the lock is held by another thread then this method will return
     * immediately with the value false.
     * 
     * @return true if the lock was free and was acquired by the current thread,
     * or the lock was already held by the current thread; and false otherwise
     */
    virtual bool tryLock();
    
    /**
     * Acquires the lock if it is not held by another thread within the given
     * waiting time.
     * 
     * Acquires the lock if it is not held by another thread and returns immediately
     * with the value true.
     * 
     * If the current thread already holds this lock then the method returns true.
     * 
     * If the lock is held by another thread then the current thread becomes
     * disabled for thread scheduling purposes and lies dormant until one of
     * two things happens:
     * 
     *   - The lock is acquired by the current thread; or
     *   - The specified waiting time elapses
     * 
     * If the lock is acquired then the value true is returned.
     * 
     * If the specified waiting time elapses then the value false is returned.
     * If the time is less than or equal to zero, the method will not wait at all.
     * 
     * @param t the time to wait for the lock
     * @param unit the time unit of the timeout argument
     * @return true if the lock was free and was acquired by the current thread,
     * or the lock was already held by the current thread; and false if the waiting time
     * elapsed before the lock could be acquired
     */
    virtual bool tryLock(const uint64_t& t, const TimeUnit* timeUnit);
    
    virtual Condition* newCondition() { return 0; }

  private:
    pthread_mutex_t m_mutex;
    pthread_mutexattr_t m_mutexAttr;
};

DECAF_CLOSE_NAMESPACE4

#endif	/* DECAF_REENTRANTLOCK_HPP */

