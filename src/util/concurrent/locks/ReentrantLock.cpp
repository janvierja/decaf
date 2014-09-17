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

#include <time.h>

#include "decaf/util/concurrent/locks/ReentrantLock.hpp"

DECAF_OPEN_NAMESPACE4(decaf, util, concurrent, locks)

// -----------------------------------------------------------------------------

ReentrantLock::ReentrantLock() {
    pthread_mutexattr_init(&m_mutexAttr);
    pthread_mutexattr_settype(&m_mutexAttr, PTHREAD_MUTEX_RECURSIVE);

    pthread_mutex_init(&m_mutex, &m_mutexAttr);
}

// -----------------------------------------------------------------------------

ReentrantLock::~ReentrantLock() {
    pthread_mutex_unlock(&m_mutex);
    
    pthread_mutex_destroy(&m_mutex);
    pthread_mutexattr_destroy(&m_mutexAttr);
}

// -----------------------------------------------------------------------------

void ReentrantLock::lock() {
    pthread_mutex_lock(&m_mutex);
}

// -----------------------------------------------------------------------------

void ReentrantLock::unlock() {
    pthread_mutex_unlock(&m_mutex);
}

// -----------------------------------------------------------------------------

bool ReentrantLock::tryLock() {
    return ((pthread_mutex_trylock(&m_mutex) == 0) ? true : false);
}

// -----------------------------------------------------------------------------

bool ReentrantLock::tryLock(const uint64_t& t, const TimeUnit* timeUnit) {
    uint64_t nanos = TimeUnit::NANOSECONDS->convert(t, timeUnit);
    
    struct timespec timeout { 0, 0 };
    clock_gettime(CLOCK_REALTIME, &timeout);
    
    time_t sec { nanos / 1000000000 };
    long   nsec { (((static_cast<double>(nanos) / static_cast<double>(1000000000)) - sec) * 1000000000) };
    
    timeout.tv_sec  += sec;
    timeout.tv_nsec += nsec;
    
    return ((pthread_mutex_timedlock(&m_mutex, &timeout) == 0) ? true : false);
}

DECAF_CLOSE_NAMESPACE4