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

#ifndef DECAF_LANG_RUNNABLE_HPP
#define DECAF_LANG_RUNNABLE_HPP

#include "decaf/lang/compatibility.hpp"
#include "decaf/lang/Object.hpp"

DECAF_OPEN_NAMESPACE2(decaf, lang)

/**
 * The Runnable interface should be implemented by any class whose instances are intended to be
 * executed by a thread. The class must define a method of no arguments called run.
 *
 * This interface is designed to provide a common protocol for objects that wish to execute code
 * while they are active. For example, Runnable is implemented by class Thread. Being active simply
 * means that a thread has been started and has not yet been stopped.
 *
 * In addition, Runnable provides the means for a class to be active while not subclassing Thread.
 * A class that implements Runnable can run without subclassing Thread by instantiating a
 * Thread instance and passing itself in as the target. In most cases, the Runnable interface should be
 * used if you are only planning to override the run() method and no other Thread methods. This is
 * important because classes should not be subclassed unless the programmer intends on modifying or
 * enhancing the fundamental behavior of the class.
 */
class Runnable : public Object {
  public:
    /**
     * When an object implementing interface Runnable is used to create a thread, starting the
     * thread causes the object's run method to be called in that separately executing thread.
     * The general contract of the method run is that it may take any action whatsoever.
     */
    virtual void Run() = 0;
}; // class Runnable

DECAF_CLOSE_NAMESPACE2

#endif // DECAF_RUNNABLE_HPP
