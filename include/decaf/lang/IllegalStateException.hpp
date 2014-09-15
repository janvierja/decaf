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
#ifndef DECAF_LANG_ILLEGALSTATEEXCEPTION_HPP
#define	DECAF_LANG_ILLEGALSTATEEXCEPTION_HPP

#include "decaf/lang/Common.hpp"
#include "decaf/lang/Object.hpp"
#include "decaf/lang/RuntimeException.hpp"

DECAF_OPEN_NAMESPACE2(decaf, lang)

/**
 * Signals that a method has been invoked at an illegal or inappropriate time.
 * In other words, the Java environment or Java application is not in an
 * appropriate state for the requested operation.
 */
class IllegalStateException : public RuntimeException, public virtual Object {
  public:

    /**
     * Constructs a new IllegalStateException with null as its detail message.
     * The cause is not initialized, and may subsequently be initialized by 
     * a call to Throwable.initCause(decaf::lang::Throwable).
     */
    IllegalStateException() : RuntimeException() { }

    /**
     * Constructs a new IllegalStateException with the specified detail message. 
     * The cause is not initialized, and may subsequently be initialized by a
     * call to Throwable.initCause(decaf::.lang::Throwable).
     * @param message the detail message. The detail message is saved for later
     *                 retrieval by the Throwable.getMessage() method.
     */
    explicit IllegalStateException(const std::string& message) : RuntimeException(message) { }

    /**
     * Constructs a new IllegalStateException with the specified detail message and cause.
     * Note that the detail message associated with cause is not automatically
     * incorporated in this exception's detail message.
     * @param message the detail message. The detail message is saved for later
     *                 retrieval by the Throwable.getMessage() method.
     * @param cause the cause (which is saved for later retrieval by the 
     *               Throwable.getCause() method). (A null value is permitted,
     *               and indicates that the cause is nonexistent or unknown.)
     */
    explicit IllegalStateException(const std::string& message, Throwable* cause) :
    RuntimeException(message, cause) { }

    /**
     * Constructs a new IllegalStateException with the specified cause and a detail message 
     * of (cause==null ? null : cause.toString()) (which typically contains the 
     * class and detail message of cause). This constructor is useful for 
     * exceptions that are little more than wrappers for other throwables
     * @param cause the cause (which is saved for later retrieval by the 
     *               Throwable.getCause() method). (A null value is permitted,
     *               and indicates that the cause is nonexistent or unknown.)
     */
    explicit IllegalStateException(Throwable* cause) : RuntimeException(cause) { }

    virtual ~IllegalStateException() = default;
}; // class RuntimeException

DECAF_CLOSE_NAMESPACE2

#endif	/* DECAF_LANG_RUNTIMEEXCEPTION_HPP */

