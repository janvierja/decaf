
#include "decaf/lang/Throwable.hpp"
#include "decaf/lang/IllegalStateException.hpp"
#include "decaf/lang/IllegalArgumentException.hpp"

DECAF_OPEN_NAMESPACE2(decaf, lang)

// ----------------------------------------------------------------------------
Throwable* Throwable::initCause(Throwable* cause) {
    if (this->m_cause != this)
        throw IllegalStateException("Can't overwrite cause");
    if (cause == this)
        throw IllegalArgumentException("Self-causation not permitted");

    this->m_cause = cause;
    return this;
}

DECAF_CLOSE_NAMESPACE2
