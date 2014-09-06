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

#ifndef DECAF_COMMON_HPP
#define DECAF_COMMON_HPP

// ----- namespace macros -----------------------------------------------------

namespace decaf { namespace lang { } }
#define DECAF_OPEN_NAMESPACE(ns) namespace ns { \
    using namespace decaf::lang;

#define DECAF_INNER_NAMESPACE(ns) namespace ns {
#define DECAF_OPEN_NAMESPACE2(ns1, ns2) \
    DECAF_OPEN_NAMESPACE(ns1) DECAF_INNER_NAMESPACE(ns2)
#define DECAF_OPEN_NAMESPACE3(ns1, ns2, ns3) \
    DECAF_OPEN_NAMESPACE2(ns1, ns2) DECAF_INNER_NAMESPACE(ns3)
#define DECAF_OPEN_NAMESPACE4(ns1, ns2, ns3, ns4) \
    DECAF_OPEN_NAMESPACE3(ns1, ns2, ns3) DECAF_INNER_NAMESPACE(ns4)
#define DECAF_OPEN_NAMESPACE5(ns1, ns2, ns3, ns4, ns5) \
    DECAF_OPEN_NAMESPACE3(ns1, ns2, ns3, ns4) DECAF_INNER_NAMESPACE(ns5)

#define DECAF_CLOSE_NAMESPACE }
#define DECAF_CLOSE_NAMESPACE2 } }
#define DECAF_CLOSE_NAMESPACE3 } } }
#define DECAF_CLOSE_NAMESPACE4 } } } }
#define DECAF_CLOSE_NAMESPACE5 } } } } }

/**
 * This macro "mangles" the specified @a Name, producing an identifier which
 * is unique in the current file.
 *
 * @param Name the name to produce a new identifier on its basis
 */
#define DECAF_JOIN(X, Y) DECAF_DO_JOIN(X, Y)
#define DECAF_DO_JOIN(X, Y) DECAF_DO_JOIN2(X, Y)
#define DECAF_DO_JOIN2(X, Y) X##Y
#define DECAF_UNIQUE_IDENTIFIER(Name) DECAF_JOIN(Name, __LINE__)

#endif // DECAF_COMMON_HPP
