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
#ifndef DECAF_LANG_CLONENOTSUPPORTEDEXCEPTION_HPP
#define	DECAF_LANG_CLONENOTSUPPORTEDEXCEPTION_HPP

#include <string>

#include "decaf/lang/Common.hpp"
#include "decaf/lang/Object.hpp"
#include "decaf/lang/Exception.hpp"

DECAF_OPEN_NAMESPACE2(decaf, lang)

/**
 * The class Exception and its subclasses are a form of Throwable that 
 * indicates conditions that a reasonable application might want to catch. 
 */
class CloneNotSupportedException : public Exception, public virtual Object {
  public:

    /**
     * Constructs a new exception with null as its detail message.
     * The cause is not initialized, and may subsequently be initialized by 
     * a call to Throwable.initCause(decaf::lang::Throwable).
     */
    CloneNotSupportedException() : Exception() { }

    /**
     * Constructs a new exception with the specified detail message. The cause
     * is not initialized, and may subsequently be initialized by a call to 
     * Throwable.initCause(decaf::.lang::Throwable).
     * @param message the detail message. The detail message is saved for later
     *                 retrieval by the Throwable.getMessage() method.
     */
    explicit CloneNotSupportedException(const std::string& message) : Throwable(message) { }


    virtual ~CloneNotSupportedException() = default;
}; // class Exception

DECAF_CLOSE_NAMESPACE2

#endif	/* DECAF_LANG_CLONENOTSUPPORTEDEXCEPTION_HPP */

