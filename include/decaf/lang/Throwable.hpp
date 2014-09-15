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

#ifndef DECAF_THROWABLE_HPP
#define DECAF_THROWABLE_HPP

#include "decaf/lang/compatibility.hpp"
#include "decaf/lang/Object.hpp"

DECAF_OPEN_NAMESPACE2(decaf, lang)

/**
 * Throwable is the base class of all errors and exceptions in the 
 * decaf class library.
 */
class Throwable : public Object {
  public:

    /**
     * Constructs a throwable with no message. The cause is not initialized, and 
     * may subsequently be initialized by a call to initCause(decaf::lang::Throwable*).
     */
    Throwable() : m_message(), m_cause(this) { }

    /**
     * Constructs a new throwable with the specified detail message. The cause 
     * is not initialized, and may subsequently be initialized by a call 
     * to initCause(decaf::lang::Throwable*).
     */
    explicit Throwable(const std::string& message) :
    m_message(message), m_cause(this) { }

    /**
     * Constructs a new throwable with the specified detail message and cause.
     * Note that the detail message associated with cause is not automatically 
     * incorporated in this throwable's detail message.
     */
    explicit Throwable(const std::string& message, Throwable* cause) :
    m_message(message), m_cause(cause) { }

    /**
     * Constructs a new throwable with the specified cause and a detail message of
     * (cause==null ? null : cause.toString()) (which typically contains the class 
     * and detail message of cause). This constructor is useful for throwables that
     * are little more than wrappers for other throwables
     */
    explicit Throwable(Throwable* cause) :
    m_message((cause == 0 ? "" : cause->toString())), m_cause(cause) { }

    virtual ~Throwable() = default;

    /**
     * Returns the detail message string of this throwable.
     */
    std::string getMessage() const {
        return m_message;
    }

    /**
     * Returns the cause of this throwable or 0 if the cause is nonexistent or
     * unknown. (The cause is the throwable that caused this throwable to get thrown.)
     */
    Throwable* getCause() const {
        return (m_cause == this ? 0 : m_cause);
    } // TODO: must be method-synch

    /**
     * Initializes the cause of this throwable to the specified value. (The cause
     * is the throwable that caused this throwable to get thrown.)
     * This method can be called at most once. It is generally called from within 
     * the constructor, or immediately after creating the throwable. If this throwable
     * was created with Throwable(Throwable*) or Throwable(const std::string&,Throwable*),
     * this method cannot be called even once.
     */
    Throwable* initCause(Throwable* cause);

    /**
     * Returns a short description of this throwable. The result is the concatenation of:
     *     * the name of the class of this object
     *     * ": " (a colon and a space)
     *     * the result of invoking this object's getMessage() method
     */
    std::string toString() {
        std::string name = getTypeName();
        std::string message = getMessage();
        return (((!message.empty()) ? name + ": " + message : name));
    }
  private:
    /**
     * Specifies the details about the Throwable.
     */
    std::string m_message;

    /*
     * The throwable that caused this throwable to get thrown, or null if this
     * throwable was not caused by another throwable, or if the causative
     * throwable is unknown.  If this field is equal to this throwable itself,
     * it indicates that the cause of this throwable has not yet been
     * initialized.
     */
    Throwable* m_cause;

}; // class Throwable

DECAF_CLOSE_NAMESPACE2

#endif // DECAF_THROWABLE_HPP
