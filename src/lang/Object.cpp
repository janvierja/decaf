#include <cxxabi.h>

#if defined(DECAF_CC11)
#include <chrono>
#endif

#include "decaf/lang/Object.hpp"

DECAF_OPEN_NAMESPACE2(decaf, lang)

#define DECAF_OBJECT_ALIGNMENT_SHIFT    3

using std::string;

#if defined(DECAF_CC11)
using std::lock_guard;
using std::recursive_mutex;
using std::chrono::milliseconds;
using std::chrono::nanoseconds;
#endif

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

#if defined(DECAF_CC11)
    lock_guard<recursive_mutex> lock(m_mutex);
#endif
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
#if defined(DECAF_CC11)
    m_monitor.m_condition.notify_one();
#endif
}

// ----------------------------------------------------------------------------

void Object::notifyAll() {
#if defined(DECAF_CC11)
    m_monitor.m_condition.notify_all();
#endif
}

// ----------------------------------------------------------------------------

void Object::wait() {
#if defined(DECAF_CC11)
    m_monitor.m_condition.wait(m_monitor.m_mutex);
#endif
}

// ----------------------------------------------------------------------------

void Object::wait(uint64_t timeout) {
#if defined(DECAF_CC11)
    m_monitor.m_condition.wait_for(m_monitor.m_mutex, milliseconds(timeout));
#endif
}

// ----------------------------------------------------------------------------

void Object::wait(uint64_t timeout, uint64_t nanos) {
#if defined(DECAF_CC11)
    m_monitor.m_condition.wait_for(m_monitor.m_mutex,
        (milliseconds(timeout) + nanoseconds(nanos)));
#endif
}

DECAF_CLOSE_NAMESPACE2
