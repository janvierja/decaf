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
#ifndef DECAF_CLONENOTSUPPORTEDEXCEPTION_HPP
#define	DECAF_CLONENOTSUPPORTEDEXCEPTION_HPP

#include "decaf/lang/compatibility.hpp"
#include "decaf/lang/Exception.hpp"

DECAF_OPEN_NAMESPACE2(decaf, lang)

/**
 * CloneNotSupportedException is the base class of those exceptions that can be thrown 
 * during the normal operation of the framework. 
 */
class CloneNotSupportedException : public Exception {
  public:

    /**
     * Constructs a new runtime exception with null as its detail message.
     * The cause is not initialized, and may subsequently be initialized by 
     * a call to Throwable.initCause(decaf::lang::Throwable).
     */
    CloneNotSupportedException() : Exception() { }

    /**
     * Constructs a new runtime exception with the specified detail message. 
     * The cause is not initialized, and may subsequently be initialized by a
     * call to Throwable.initCause(decaf::.lang::Throwable).
     * @param message the detail message. The detail message is saved for later
     *                 retrieval by the Throwable.getMessage() method.
     */
    explicit CloneNotSupportedException(const std::string& message) : Exception(message) { }

    /**
     * Constructs a new runtime exception with the specified detail message and cause.
     * Note that the detail message associated with cause is not automatically
     * incorporated in this exception's detail message.
     * @param message the detail message. The detail message is saved for later
     *                 retrieval by the Throwable.getMessage() method.
     * @param cause the cause (which is saved for later retrieval by the 
     *               Throwable.getCause() method). (A null value is permitted,
     *               and indicates that the cause is nonexistent or unknown.)
     */
    explicit CloneNotSupportedException(const std::string& message, Throwable* cause) :
      Exception(message, cause) { }

    /**
     * Constructs a new runtime exception with the specified cause and a detail message 
     * of (cause==null ? null : cause.toString()) (which typically contains the 
     * class and detail message of cause). This constructor is useful for 
     * exceptions that are little more than wrappers for other throwables
     * @param cause the cause (which is saved for later retrieval by the 
     *               Throwable.getCause() method). (A null value is permitted,
     *               and indicates that the cause is nonexistent or unknown.)
     */
    explicit CloneNotSupportedException(Throwable* cause) : Exception(cause) { }

    virtual ~CloneNotSupportedException() = default;
}; // class CloneNotSupportedException

DECAF_CLOSE_NAMESPACE2

#endif	/* DECAF_CLONENOTSUPPORTEDEXCEPTION_HPP */

