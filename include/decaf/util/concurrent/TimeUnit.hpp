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

#ifndef DECAF_TIMEUNIT_H
#define DECAF_TIMEUNIT_H

#include <cstdint>
#include <string>

#include "decaf/lang/compatibility.hpp"
#include "decaf/lang/Object.hpp"
#include "decaf/util/SleepingStopwatch.hpp"

DECAF_OPEN_NAMESPACE3(decaf, util, concurrent)

/**
 * A TimeUnit represents time durations at a given unit of granularity and provides utility methods
 * to convert across units, and to perform timing and delay operations in these units. A TimeUnit
 * does not maintain time information, but only helps organize and use time representations that may
 * be maintained separately across various contexts. A nanosecond is defined as one thousandth of a microsecond,
 * a microsecond as one thousandth of a millisecond, a millisecond as one thousandth of a second,
 * a minute as sixty seconds, an hour as sixty minutes, and a day as twenty four hours.
 *
 * A TimeUnit is mainly used to inform time-based methods how a given timing parameter should be interpreted.
 * For example, the following code will timeout in 50 milliseconds:
 *
 *     TimeUnit::MILLISECONDS->Sleep(50);
 *
 * while this code will timeout in 50 seconds
 *
 *     TimeUnit* timeUnit = TimeUnit::SECONDS;
 *     timeUnit->Sleep(50);
 *
 * It is important to note that TimeUnit::NANOSECONDS, TimeUnit::MICROSECONDS, and so forth are static pointers
 * maintained by TimeUnit. You would not need to delete it.
 *
 *     TimeUnit* timeUnit = TimeUnit::NANOSECONDS;
 *     delete timeUnit; // README: Do not do this. The compiler won't allow you to do this anyway
 *
 */
class TimeUnit : public Object {
  public:
    TimeUnit();

    virtual uint64_t Convert(const uint64_t sourceDuration, TimeUnit* sourceUnit) = 0;
    virtual uint64_t ToNanos(const uint64_t duration) = 0;
    virtual uint64_t ToMicros(const uint64_t duration) = 0;
    virtual uint64_t ToMillis(const uint64_t duration) = 0;
    virtual uint64_t ToSeconds(const uint64_t duration) = 0;
    virtual uint64_t ToMinutes(const uint64_t duration) = 0;
    virtual uint64_t ToHours(const uint64_t duration) = 0;
    virtual uint64_t ToDays(const uint64_t duration) = 0;

    void Sleep(uint64_t timeout);

    virtual std::string ToShortString() = 0;

    static const uint64_t MIN;
    static const uint64_t MAX;

    /*
     * Pre-allocated/constructed TimeUnits
     */
    static TimeUnit * const NANOSECONDS;
    static TimeUnit * const MICROSECONDS;
    static TimeUnit * const MILLISECONDS;
    static TimeUnit * const SECONDS;
    static TimeUnit * const MINUTES;
    static TimeUnit * const HOURS;
    static TimeUnit * const DAYS;

  protected:
    virtual ~TimeUnit() throw () = default;

    static const uint64_t C0 = 1L;
    static const uint64_t C1 = C0 * 1000L;
    static const uint64_t C2 = C1 * 1000L;
    static const uint64_t C3 = C2 * 1000L;
    static const uint64_t C4 = C3 * 60L;
    static const uint64_t C5 = C4 * 60L;
    static const uint64_t C6 = C5 * 24L;

    /*
     * Scale d by m, checking for overflow
     */
    static uint64_t Scale(const uint64_t d, const uint64_t m, const uint64_t over);

  private:
    SleepingStopwatch m_stopwatch;
};

DECAF_OPEN_NAMESPACE(detail)

/**
 * A TimeUnit that represents nanoseconds
 */
class Nanoseconds : public TimeUnit {
  public:
    Nanoseconds() = default;

    virtual uint64_t ToNanos(const uint64_t d) {
        return d;
    }

    virtual uint64_t ToMicros(const uint64_t d) {
        return (d / (C1 / C0));
    }

    virtual uint64_t ToMillis(const uint64_t d) {
        return (d / (C2 / C0));
    }

    virtual uint64_t ToSeconds(const uint64_t d) {
        return (d / (C3 / C0));
    }

    virtual uint64_t ToMinutes(const uint64_t d) {
        return (d / (C4 / C0));
    }

    virtual uint64_t ToHours(const uint64_t d) {
        return (d / (C5 / C0));
    }

    virtual uint64_t ToDays(const uint64_t d) {
        return (d / (C6 / C0));
    }

    virtual uint64_t Convert(const uint64_t d, TimeUnit* u) {
        return u->ToNanos(d);
    }

    virtual std::string ToString() const throw () {
        return "NANOSECONDS";
    };

    virtual std::string ToShortString() {
        return "ns";
    };

  protected:
    virtual ~Nanoseconds() throw () = default;
};

/**
 * A TimeUnit that represents microseconds
 */
class Microseconds : public TimeUnit {
  public:
    Microseconds() = default;

    virtual uint64_t ToNanos(const uint64_t d) {
        return Scale(d, (C1 / C0), (TimeUnit::MAX / (C1 / C0)));
        ;
    }

    virtual uint64_t ToMicros(const uint64_t d) {
        return d;
    }

    virtual uint64_t ToMillis(const uint64_t d) {
        return (d / (C2 / C1));
    }

    virtual uint64_t ToSeconds(const uint64_t d) {
        return (d / (C3 / C1));
    }

    virtual uint64_t ToMinutes(const uint64_t d) {
        return (d / (C4 / C1));
    }

    virtual uint64_t ToHours(const uint64_t d) {
        return (d / (C5 / C1));
    }

    virtual uint64_t ToDays(const uint64_t d) {
        return (d / (C6 / C1));
    }

    virtual uint64_t Convert(const uint64_t d, TimeUnit* u) {
        return u->ToMicros(d);
    }

    virtual std::string ToString() const throw () {
        return "MICROSECONDS";
    };

    virtual std::string ToShortString() {
        return "us";
    };

  protected:
    virtual ~Microseconds() throw () = default;
};

/**
 * A TimeUnit that represents milliseconds
 */
class Milliseconds : public TimeUnit {
  public:
    Milliseconds() = default;

    virtual uint64_t ToNanos(const uint64_t d) {
        return Scale(d, (C2 / C0), (TimeUnit::MAX / (C2 / C0)));
    }

    virtual uint64_t ToMicros(const uint64_t d) {
        return Scale(d, (C2 / C1), (TimeUnit::MAX / (C2 / C1)));
    }

    virtual uint64_t ToMillis(const uint64_t d) {
        return d;
    }

    virtual uint64_t ToSeconds(const uint64_t d) {
        return (d / (C3 / C2));
    }

    virtual uint64_t ToMinutes(const uint64_t d) {
        return (d / (C4 / C2));
    }

    virtual uint64_t ToHours(const uint64_t d) {
        return (d / (C5 / C2));
    }

    virtual uint64_t ToDays(const uint64_t d) {
        return (d / (C6 / C2));
    }

    virtual uint64_t Convert(const uint64_t d, TimeUnit* u) {
        return u->ToMillis(d);
    }

    virtual std::string ToString() const throw () {
        return "MILLISECONDS";
    };

    virtual std::string ToShortString() {
        return "ms";
    };

  protected:
    virtual ~Milliseconds() throw () = default;
};

/**
 * A TimeUnit that represents seconds
 */
class Seconds : public TimeUnit {
  public:
    Seconds() = default;

    virtual uint64_t ToNanos(const uint64_t d) {
        return Scale(d, (C3 / C0), (TimeUnit::MAX / (C3 / C0)));
    }

    virtual uint64_t ToMicros(const uint64_t d) {
        return Scale(d, (C3 / C1), (TimeUnit::MAX / (C3 / C1)));
    }

    virtual uint64_t ToMillis(const uint64_t d) {
        return Scale(d, (C3 / C2), (TimeUnit::MAX / (C3 / C2)));
    }

    virtual uint64_t ToSeconds(const uint64_t d) {
        return d;
    }

    virtual uint64_t ToMinutes(const uint64_t d) {
        return (d / (C4 / C3));
    }

    virtual uint64_t ToHours(const uint64_t d) {
        return (d / (C5 / C3));
    }

    virtual uint64_t ToDays(const uint64_t d) {
        return (d / (C6 / C3));
    }

    virtual uint64_t Convert(const uint64_t d, TimeUnit* u) {
        return u->ToSeconds(d);
    }

    virtual std::string ToString() const throw () {
        return "SECONDS";
    };

    virtual std::string ToShortString() {
        return "s";
    };

  protected:
    virtual ~Seconds() throw () = default;
};

/**
 * A TimeUnit that represents minutes
 */
class Minutes : public TimeUnit {
  public:
    Minutes() = default;

    virtual uint64_t ToNanos(const uint64_t d) {
        return Scale(d, (C4 / C0), (TimeUnit::MAX / (C4 / C0)));
    }

    virtual uint64_t ToMicros(const uint64_t d) {
        return Scale(d, (C4 / C1), (TimeUnit::MAX / (C4 / C1)));
    }

    virtual uint64_t ToMillis(const uint64_t d) {
        return Scale(d, (C4 / C2), (TimeUnit::MAX / (C4 / C2)));
    }

    virtual uint64_t ToSeconds(const uint64_t d) {
        return Scale(d, (C4 / C3), (TimeUnit::MAX / (C4 / C3)));
    }

    virtual uint64_t ToMinutes(const uint64_t d) {
        return d;
    }

    virtual uint64_t ToHours(const uint64_t d) {
        return (d / (C5 / C4));
    }

    virtual uint64_t ToDays(const uint64_t d) {
        return (d / (C6 / C4));
    }

    virtual uint64_t Convert(const uint64_t d, TimeUnit* u) {
        return u->ToMinutes(d);
    }

    virtual std::string ToString() const throw () {
        return "MINUTES";
    };

    virtual std::string ToShortString() {
        return "m";
    };

  protected:
    virtual ~Minutes() throw () = default;
};

/**
 * A TimeUnit that represents hours
 */
class Hours : public TimeUnit {
  public:
    Hours() = default;

    virtual uint64_t ToNanos(const uint64_t d) {
        return Scale(d, (C5 / C0), (TimeUnit::MAX / (C5 / C0)));
    }

    virtual uint64_t ToMicros(const uint64_t d) {
        return Scale(d, (C5 / C1), (TimeUnit::MAX / (C5 / C1)));
    }

    virtual uint64_t ToMillis(const uint64_t d) {
        return Scale(d, (C5 / C2), (TimeUnit::MAX / (C5 / C2)));
    }

    virtual uint64_t ToSeconds(const uint64_t d) {
        return Scale(d, (C5 / C3), (TimeUnit::MAX / (C5 / C3)));
    }

    virtual uint64_t ToMinutes(const uint64_t d) {
        return Scale(d, (C5 / C4), (TimeUnit::MAX / (C5 / C4)));
    }

    virtual uint64_t ToHours(const uint64_t d) {
        return d;
    }

    virtual uint64_t ToDays(const uint64_t d) {
        return (d / (C6 / C5));
    }

    virtual uint64_t Convert(const uint64_t d, TimeUnit* u) {
        return u->ToHours(d);
    }

    virtual std::string ToString() const throw () {
        return "HOURS";
    };

    virtual std::string ToShortString() {
        return "h";
    };

  protected:
    virtual ~Hours() throw () = default;
};

/**
 * A TimeUnit that represents days
 */
class Days : public TimeUnit {
  public:
    Days() = default;

    virtual uint64_t ToNanos(const uint64_t d) {
        return Scale(d, (C6 / C0), (TimeUnit::MAX / (C6 / C0)));
    }

    virtual uint64_t ToMicros(const uint64_t d) {
        return Scale(d, (C6 / C1), (TimeUnit::MAX / (C6 / C1)));
    }

    virtual uint64_t ToMillis(const uint64_t d) {
        return Scale(d, (C6 / C2), (TimeUnit::MAX / (C6 / C2)));
    }

    virtual uint64_t ToSeconds(const uint64_t d) {
        return Scale(d, (C6 / C3), (TimeUnit::MAX / (C6 / C3)));
    }

    virtual uint64_t ToMinutes(const uint64_t d) {
        return Scale(d, (C6 / C4), (TimeUnit::MAX / (C6 / C4)));
    }

    virtual uint64_t ToHours(const uint64_t d) {
        return Scale(d, (C6 / C5), (TimeUnit::MAX / (C6 / C5)));
    }

    virtual uint64_t ToDays(const uint64_t d) {
        return d;
    }

    virtual uint64_t Convert(const uint64_t d, TimeUnit* u) {
        return u->ToDays(d);
    }

    virtual std::string ToString() const throw () {
        return "DAYS";
    };

    virtual std::string ToShortString() {
        return "d";
    };

  protected:
    virtual ~Days() throw () = default;
};

DECAF_CLOSE_NAMESPACE
DECAF_CLOSE_NAMESPACE3

#endif // DECAF_TIMEUNIT_H
