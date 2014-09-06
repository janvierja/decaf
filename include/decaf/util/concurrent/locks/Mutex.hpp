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

#ifndef DECAF_UTIL_CONCURRENT_LOCKS_MUTEX_H
#define DECAF_UTIL_CONCURRENT_LOCKS_MUTEX_H

#include <pthread.h>

#include "decaf/lang/Common.hpp"

DECAF_OPEN_NAMESPACE4(decaf, util, concurrent, locks)

/**
 * A synchronization primitive.
 * @remarks When two or more threads need to access a shared resource at the same time,
 * the system needs a synchronization mechanism to ensure that only one thread at a time
 * uses the resource. Mutex is a synchronization primitive that grants exclusive access
 * to the shared resource to only one thread. If a thread acquires a mutex, the second
 * thread that wants to acquire that mutex is suspended until the first thread releases
 * the mutex.
 * @remarks You can use the Mutex.Wait() method to request ownership of a mutex. The
 * Mutex class enforces identity, so a mutex can be released only by the thread that
 * acquired it.
 */
class Mutex {
  public:
    /**
     * Initializes a new instance of the Mutex class with a bool value that indicates
     * whether the calling thread should have initial ownership of the mutex.
     * @param initallyOwned @b True to give the calling thread initial ownership of the
     * mutex; otherwise, @b false.
     * @remarks You can use the Mutex.wait() method to request ownership of a mutex. The thread
     * that owns the mutex can request the same mutex in repeated calls to wait() without blocking
     * its execution. However, the thread must call the release() method the same number of
     * times to release ownership of the mutex.
     */
    Mutex(bool initallyOwned = false);
    virtual ~Mutex();

    /**
     * Blocks the current thread until another thread that has ownership of this thread
     * releases it.
     * @return Returns @b true if ownership has been acquired by the current thread. If
     * the current thread is unable to get ownership, wait() never returns.
     * @remarks The caller of this method blocks indefinitely until the current ownership
     * of the mutex is acquired.
     */
    bool wait() const;

    /**
     * Releases the Mutex.
     */
    void release() const;

  private:
    mutable pthread_mutex_t m_mutex; /**< The native mutex. */
    pthread_mutexattr_t m_mutexAttribute; /**< The mutex attribute of @c mutex. */
};

DECAF_CLOSE_NAMESPACE4

#endif // DECAF_UTIL_CONCURRENT_LOCKS_MUTEX_H
