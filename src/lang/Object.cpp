#include <cxxabi.h>
#include <chrono>

#include "decaf/lang/Object.hpp"

DECAF_OPEN_NAMESPACE2(decaf, lang)

#define DECAF_OBJECT_ALIGNMENT_SHIFT    3

using std::string;
using std::lock_guard;
using std::recursive_mutex;
using std::chrono::milliseconds;
using std::chrono::nanoseconds;

// ----------------------------------------------------------------------------

uint64_t Object::hashCode() const throw () {
    if (m_hashCode == 0)
        m_hashCode = (reinterpret_cast<uint64_t> (this) >>
        DECAF_OBJECT_ALIGNMENT_SHIFT) * 2654435761u;
    return m_hashCode;
}

// ----------------------------------------------------------------------------

bool Object::equals(const Object& obj) const throw () {
    return (this->hashCode() == obj.hashCode());
}

// ----------------------------------------------------------------------------

const Object::Type& Object::getType() const {
    return typeid (*this);
}

// ----------------------------------------------------------------------------

string Object::getTypeName() const {
    char buf[1024]{};
    size_t bufsz = sizeof (buf);
    int status{0};

    lock_guard<recursive_mutex> lock(m_mutex);
    char* res = abi::__cxa_demangle(getType().name(), buf, &bufsz, &status);
    string demangledName = string(res);

    return demangledName.c_str();
}

// ----------------------------------------------------------------------------

string Object::toString() const {
    string demangledName = getTypeName();
    static const uint8_t stringHashCodeValueSize{64};
    char stringHashCodeValue[stringHashCodeValueSize]{};

    snprintf(stringHashCodeValue, stringHashCodeValueSize, "%llx", hashCode());
    return string(demangledName + "@" + stringHashCodeValue);
}

// ----------------------------------------------------------------------------

void Object::notify() {
    m_monitor.m_conditionVariable.notify_one();
}

// ----------------------------------------------------------------------------

void Object::notifyAll() {
    m_monitor.m_conditionVariable.notify_all();
}

// ----------------------------------------------------------------------------

void Object::wait() {
    m_monitor.m_conditionVariable.wait(m_monitor.m_mutex);
}

// ----------------------------------------------------------------------------

void Object::wait(uint64_t timeout) {
    m_monitor.m_conditionVariable.wait_for(m_monitor.m_mutex, milliseconds(timeout));
}

// ----------------------------------------------------------------------------

void Object::wait(uint64_t timeout, uint64_t nanos) {
    m_monitor.m_conditionVariable.wait_for(m_monitor.m_mutex,
        (milliseconds(timeout) + nanoseconds(nanos)));
}

DECAF_CLOSE_NAMESPACE2
