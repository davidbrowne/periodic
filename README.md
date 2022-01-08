# periodic - exploring angles and intervals

**periodic** is a **c++20 library** that is for exploring things about angles and intervals.

## Possible Topics
* Binary Angular Measurement (BAM), most likely for 64-bit angles
* Repeating and non-repeating periods
* Inverses of periods
* Periodic coordinate systems - e.g., math-centric vs. navigation-centric
* Turns (as opposed to radians or degrees), and conversions between systems
* Tau vs. pi
* Unsigned periods, like [0, 360), vs signed periods [-180, 180)
* Phase shift/amplitude shift/amplitude scaling/period scaling, etc.
* Periodic intervals (and inverse intervals) - animation, easing

## Status

Current version: `v0.0.1`

* This project does nothing yet.

## Testing

This project will use [doctest](https://github.com/onqtam/doctest) for testing. We might occasionally use [nanobench](https://github.com/martinus/nanobench) for understanding implementation tradeoffs.

## License [![BSL](https://img.shields.io/badge/license-BSL-blue)](https://choosealicense.com/licenses/bsl-1.0/)

```
//          Copyright David Browne 2021-2022.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)
```

This project uses the [Boost Software License 1.0](https://choosealicense.com/licenses/bsl-1.0/).

### Third Party Attribution 

The libraries we use (some just occasionally):

```
// cxcm - a c++20 library that provides constexpr versions of some <cmath> and related functions.
//
//          Copyright David Browne 2020-2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)
```

```
// doctest.h - the lightest feature-rich C++ single-header testing framework for unit tests and TDD
//
// Copyright (c) 2016-2021 Viktor Kirilov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
```

```
// Microbenchmark framework for C++11/14/17/20
// https://github.com/martinus/nanobench
//
// Licensed under the MIT License <http://opensource.org/licenses/MIT>.
// SPDX-License-Identifier: MIT
// Copyright (c) 2019-2021 Martin Ankerl <martin.ankerl@gmail.com>
```
