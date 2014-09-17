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

#ifndef DECAF_LOCK_HPP
#define	DECAF_LOCK_HPP

#include "decaf/lang/compatibility.hpp"
#include "decaf/lang/Object.hpp"
#include "decaf/util/concurrent/TimeUnit.hpp"
#include "decaf/util/concurrent/locks/Condition.hpp"

DECAF_OPEN_NAMESPACE4(decaf, util, concurrent, locks)

/**
 * Lock implementations provide more extensive locking operations than can be
 * obtained using synchronized methods and statements. They allow more flexible
 * structuring, may have quite different properties, and may support multiple
 * associated Condition objects.
 * 
 * A lock is a tool for controlling access to a shared resource by multiple
 * threads. Commonly, a lock provides exclusive access to a shared resource:
 * only one thread at a time can acquire the lock and all access to the shared
 * resource requires that the lock be acquired first. However, some locks may
 * allow concurrent access to a shared resource, such as the read lock of
 * a ReadWriteLock.
 * 
 * The use of synchronized statements makes it much easier to program with
 * monitor locks, and helps avoid many common programming errors involving locks,
 * there are occasions where you need to work with locks in a more flexible way.
 * For example, some algorithms for traversing concurrently accessed data structures
 * require the use of "hand-over-hand" or "chain locking": you acquire the lock
 * of node A, then node B, then release A and acquire C, then release B and acquire
 * D and so on. Implementations of the Lock interface enable the use of such
 * techniques by allowing a lock to be acquired and released in different scopes,
 * and allowing multiple locks to be acquired and released in any order.
 * 
 * With this increased flexibility comes additional responsibility. The absence of
 * block-structured locking removes the automatic release of locks that occurs with
 * synchronized statements. In most cases, the following idiom should be used:
 * 
 * @code{.cpp}
 *    Lock* l = ...;
 *    l->lock();
 *    try {
 *        // access the resource protected by this lock
 *    } catch(...) {
 *        l->unlock();
 *    }
 * @endcode
 * 
 * When locking and unlocking occur in different scopes, care must be taken to
 * ensure that all code that is executed while the lock is held is protected by
 * try-catch to ensure that the lock is released when necessary.
 * 
 * Lock implementations provide additional functionality over the use of
 * synchronized statements by providing a non-blocking attempt to acquire a
 * lock (tryLock()), and an attempt to acquire the lock that can
 * timeout (tryLock(long, TimeUnit)). 
 */
class Lock : public Object {
  public:
    virtual ~Lock() { this->unlock(); }
    
    /**
     * Acquires the lock
     */
    virtual void lock() = 0;

    /**
     * Releases the lock
     */
    virtual void unlock() = 0;

    /**
     * Acquires the lock only if it is free at the time of invocation.
     * Acquires the lock if it is available and returns immediately with the 
     * value true. If the lock is not available then this method will return 
     * immediately with the value false.
     * @return true if the lock was acquired, false, otherwise
     */
    virtual bool tryLock() = 0;

    /**
     * Acquires the lock if it is free within the given waiting time and the 
     * current thread has not been interrupted.

     * @param t the maximum time to wait for the lock
     * @param unit the timeunit of the 't' argument
     * @return true if the lock was acquired and false if the waiting time 
     * elapsed before the lock was acquired
     */
    virtual bool tryLock(const uint64_t& t, const TimeUnit* unit) = 0;

    /**
     * Returns a new Condition instance that is bound to this Lock instance.
     * 
     * Before waiting on the condition the lock must be held by the current 
     * thread. A call to Condition.await() will atomically release the lock 
     * before waiting and re-acquire the lock before the wait returns.
     * 
     * @return A new Condition instance for this Lock instance
     */
    virtual Condition* newCondition() = 0;
};

DECAF_CLOSE_NAMESPACE4

#endif	/* DECAF_LOCK_HPP */

