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

#ifndef DECAF_LANG_OBJECT_HPP
#define DECAF_LANG_OBJECT_HPP

#include <typeinfo>
#include <cstdint>
#include <string>
#include <mutex>

#include "decaf/lang/Common.hpp"
#include "decaf/lang/CloneNotSupportedException.hpp"

DECAF_OPEN_NAMESPACE2(decaf, lang)

/**
 * Class Object is the root of the class hierarchy. Every class in the
 * Decaf Class Library has Object as a base class.
 */
class Object {
  public:
    typedef std::type_info Type;

    Object() throw () : m_hashCode(0) { }
    virtual ~Object() = default;

    /**
     * Returns a hash code value for the object. This returns distinct integers
     * for distinct objects. This is typically implemented by converting the
     * internal address of an object into an integer, but this implementation
     * technique is not required. Note that two objects are "the same" if their
     * hash codes are equal.
     *
     * @return A hash code value for this object.
     */
    virtual uint64_t hashCode() const throw ();

    /**
     * Determines whether the specified object @a obj is the @e same as the
     * current object. The term @e same" means both objects have the same hash code
     * and refers to the same object.
     *
     * @param obj The object to compare with the current object.
     * @return bool Returns @b true if the specified object is equals to the current object; otherwise,  @b false.
     *
     * @remarks Deriving classes should override the hashCode() function whenever this
     * function is overriden, so as to maintain the general contract for the hashCode()
     * function, which states that two objects are the same if their hash codes are equal.
     *
     * <dl class="section Example"><dt><b>Example</b></dt>
     *  <dd>
     *      The example below illustrates the comparison via equals(const Object&). The first
     *      example defines a @c Person class, which is a pointer type, and calls the @c Person class
     *      constructor to instantiate two new @c Person objects, @c person1a and @c person2, which have
     *      the same value. It also assigns @c person1a to another object variable, @c person1b. As the output
     *      from the example shows, @c person1a and @c person1b are equal because they refer to the same object.
     *      However, @c person1a and @c person2 are not equal, although they have the same value.
     *  </dd>
     *  @code{.cpp}
     *	 #include <string>
     *	 #include <iostream>
     *	 #include "Object.hpp"
     *
     *	 using namespace unity::system;
     *
     *	 class Person : public Object
     *	 {
     *	   public:
     *		   Person(std::string name) : personName(name) {}
     *		   const char* ToString()
     *		   {
     *			   return personName.c_str();
     *		   }
     *
     *		   virtual ~Person() throw() {}
     *	   private:
     *		   std::string personName;
     *
     *	 };
     *
     *	 int main(int argc, char* argv[])
     *	 {
     *		 std::cout << "--- Example1: ---" << std::endl;
     *		 Person* person3a = new Person("John");
     *		 Person* person3b = person3a;
     *		 Person* person4 = new Person(person3a->ToString());
     *
     *		 std::cout << "Calling equals:" << std::endl;
     *		 std::cout << "person1a and person1b: " << (person3a->equals(*person3b) ? "True": "False") << std::endl;
     *		 std::cout << "person1a and person2: " << (person3a->equals(*person4) ? "True": "False") << std::endl;
     *
     *		 std::cout << "Casting to an Object and calling equals:" << std::endl;
     *		 std::cout << "person1a and person1b: " << (((Object*)person3a)->equals(*((Object*)person3b)) ? "True": "False") << std::endl;
     *		 std::cout << "person1a and person2: " << (((Object*)person3a)->equals(*((Object*)person4)) ? "True": "False") << std::endl;
     *
     *		 std::cout << "--- Example2: ---" << std::endl;
     *
     *		 Person person1a("John");
     *		 Person person1b = person1a;
     *		 Person person2(person1a.ToString());
     *
     *		 std::cout << "Calling equals:" << std::endl;
     *		 std::cout << "person1a and person1b: " << (person1a.equals(person1b) ? "True": "False") << std::endl;
     *		 std::cout << "person1a and person2: " << (person1a.equals(person2) ? "True": "False") << std::endl;
     *
     *		 std::cout << "Casting to an Object and calling equals:" << std::endl;
     *		 std::cout << "person1a and person1b: " << (((Object)person1a).equals((Object)person1b) ? "True": "False") << std::endl;
     *		 std::cout << "person1a and person2: " << (((Object)person1a).equals((Object)person2) ? "True": "False") << std::endl;
     *
     *		 return 0;
     *	 }
     *	 // The example above displays the following output:
     *	 //
     *	 //  --- Example1: ---
     *	 //  Calling equals:
     *	 //  person1a and person1b: True
     *	 //  person1a and person2: False
     *	 //  Casting to an Object and calling equals:
     *	 //  person1a and person1b: True
     *	 //  person1a and person2: False
     *	 //  --- Example2: ---
     *	 //  Calling equals:
     *	 //  person1a and person1b: False
     *	 //  person1a and person2: False
     *	 //  Casting to an Object and calling equals:
     *	 //  person1a and person1b: False
     *	 //  person1a and person2: False
     *
     *  @endcode
     * </dl>
     *
     * @note The equals(const Object&) would be typically used on pointer types.
     * Using them on non-pointer types would @e always yield to @b false as each object will have their own
     * unique hash code, as seen from the output of the example above.
     *
     * @version Supported in: 1.0
     * @see Object::hashCode()
     */
    bool equals(const Object& obj) const throw ();

    /**
     * Gets the type of the current instance.
     *
     * @return Object::Type The runtime type of the current instance.
     *
     * @remarks Getting the runtime type of an object is equivalent to a call to the
     * C++ function typeid. Whatever contract applies to typeid() that is mandated by
     * Standart C++ applies to getType() as well.
     *
     * <dl class="section Example"><dt><b>Example</b></dt>
     *  <dd>
     *      The following code example demonstrates that getType() returns the runtime type
     *      of the current instance.
     *  </dd>
     *  @code{.cpp}
     *    #include <string>
     *    #include <iostream>
     *    #include "Object.hpp"
     *
     *    using namespace unity::system;
     *
     *    class Shape : public Object { };
     *    class Square : public Shape { };
     *    class Circle : public Shape { };
     *    class Purple { };
     *
     *    int main(int argc, char* argv[])
     *    {
     *      Circle circle;
     *      Shape shape;
     *
     *      Shape* shapePtr = new Shape();
     *      Shape* shapePtr1 = new Circle();
     *      Shape* shapePtr2 = new Square();
     *
     *      std::cout << "circle is of type: " << circle.getType().name() << std::endl;
     *      std::cout << "shape is of type: " << shape.getType().name() << std::endl;
     *      std::cout << "shapePtr is of type: " << shapePtr->getType().name() << std::endl;
     *      std::cout << "shapePtr1 is of type: " << shapePtr1->getType().name() << std::endl;
     *      std::cout << "shapePtr2 is of type: " << shapePtr2->getType().name() << std::endl;
     *
     *      return 0;
     *    }
     *    // The output of the code above is as follows.
     *    //      circle is of type: 6Circle
     *    //      shape is of type: 5Shape
     *    //      shapePtr is of type: 5Shape
     *    //      shapePtr1 is of type: 6Circle
     *    //      shapePtr2 is of type: 6Square
     *  @endcode
     *  </dl>
     *
     * @note As getType() is really a typeid() call, getType().name() returns a mangled name
     * with the call to @c getType().name() as seen from the output of the example above.
     *
     * @version Supported in: 1.0
     * @see decaf::lang
     * @see decaf::lang::Object
     */
    const Object::Type& getType() const;

    /**
     * Returns the string type name of this object.
     * @return The string type name of this object.
     */
    std::string getTypeName()const;

    /**
     * Returns the textual representation of the object. In general, the
     * ToString() function returns a string that "textually represent" the
     * object. The result should be a concise but informative representation
     * that is easy for a person to read.
     *
     * @return Returns a string representation of this object.
     */
    virtual std::string toString() const;

    /**
     * Wakes up a single thread that is waiting on this object's monitor. If any threads are
     * waiting on this object, one of them is chosen to be awakened. The choice is arbitrary and
     * occurs at the discretion of the implementation. A thread waits on an object's monitor by
     * calling one of the wait methods.
     *
     * The awakened thread will not be able to proceed until the current thread relinquishes the
     * lock on this object. The awakened thread will compete in the usual manner with any other
     * threads that might be actively competing to synchronize on this object; for example, the
     * awakened thread enjoys no reliable privilege or disadvantage in being the next thread to
     * lock this object.
     *
     * This method should only be called by a thread that is the owner of this object's monitor.
     */
    static void notify();

    /**
     * Wakes up all threads that are waiting on this object's monitor. A thread waits on an object's
     * monitor by calling one of the wait methods.
     *
     * The awakened threads will not be able to proceed until the current thread relinquishes the lock
     * on this object. The awakened threads will compete in the usual manner with any other threads that
     * might be actively competing to synchronize on this object; for example, the awakened threads enjoy
     * no reliable privilege or disadvantage in being the next thread to lock this object.
     *
     * This method should only be called by a thread that is the owner of this object's monitor. See the
     * notify method for a description of the ways in which a thread can become the owner of a monitor.
     */
    static void notifyAll();

    /**
     * Causes the current thread to wait until either another thread invokes the notify() method or the
     * notifyAll() method for this object, or a specified amount of time has elapsed.
     *
     * The current thread must own this object's monitor.
     *
     * @param timeout the maximum time to wait in milliseconds
     */
    static void wait(uint64_t timeout);

    /**
     * Causes the current thread to wait until another thread invokes the notify() method or the notifyAll()
     * method for this object, or some other thread interrupts the current thread, or a certain amount of
     * real time has elapsed.
     *
     * This method is similar to the wait method of one argument, but it allows finer control over the amount
     * of time to wait for a notification before giving up. The amount of real time, measured in nanoseconds,
     * is given by:
     *
     *      1000000*timeout+nanos
     *
     * In all other respects, this method does the same thing as the method wait(uint64_t) of one argument.
     * In particular, wait(0, 0) means the same thing as wait(0).
     *
     * The current thread must own this object's monitor.
     *
     * @param timeout the maximum time to wait in milliseconds
     * @param nanos additional time, in nanoseconds range 0-999999
     */
    static void wait(uint64_t timeout, uint64_t nanos);

  protected:
    /**
     * Creates and returns a copy of this object. The precise meaning of "copy" may depend
     * on the class of the object. The general intent is that, for any object x, the expression:
     *
     *     x.clone() != x
     *
     * will be true, and that the expression:
     *
     *     x.clone()->getType() == x.getType()
     *
     * will be true, but these are not absolute requirements. While it is typically the case that:
     *
     *     x.clone()->equals(x)
     *
     * will be true, this is not an absolute requirement.
     *
     * @return A pointer to the clone of this object. It is the client's responsibility to release
     * the pointer.
     */
    virtual Object* clone() {
        throw CloneNotSupportedException;
    }

    mutable uint64_t m_hashCode;

  private:
    mutable std::recursive_mutex m_mutex;
};

DECAF_CLOSE_NAMESPACE2

#endif // DECAF_LANG_OBJECT_HPP
