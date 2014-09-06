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

#include "decaf/util/concurrent/locks/Mutex.hpp"

DECAF_OPEN_NAMESPACE4(decaf, util, concurrent, locks)

// ----------------------------------------------------------------------------

Mutex::Mutex(bool initiallyOwned)
: m_mutex(PTHREAD_MUTEX_INITIALIZER), m_mutexAttribute() {
    pthread_mutexattr_init(&m_mutexAttribute);
    pthread_mutexattr_settype(&m_mutexAttribute, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&m_mutex, &m_mutexAttribute);

    if (initiallyOwned)
        pthread_mutex_lock(&m_mutex);
}

// ----------------------------------------------------------------------------

Mutex::~Mutex() {
    pthread_mutex_unlock(&m_mutex);

    pthread_mutex_destroy(&m_mutex);
    pthread_mutexattr_destroy(&m_mutexAttribute);
}

// ----------------------------------------------------------------------------

bool Mutex::wait() const {
    pthread_mutex_lock(&m_mutex);
    return true;
}

// ----------------------------------------------------------------------------

void Mutex::release() const {
    pthread_mutex_unlock(&m_mutex);
}

DECAF_CLOSE_NAMESPACE4

