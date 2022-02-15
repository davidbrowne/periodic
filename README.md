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

### Building Block Functions
![identity and floor](./svg/identity_and_floor.svg) | ![identity and ceil](./svg/identity_and_ceil.svg)
---|---|

### Fundamental Periodic Driver and its Reverse/Inverse(?)
![sawtooth](./svg/identity_minus_floor.svg) | ![reverse of sawtooth](./svg/ceil_minus_identity.svg)
---|---|

### Periodic Coordinate Systems
People have a lot of experience with 3D coordinate systems, for representing data and transforming data between different coordinate system representations. The data consists of series of rotations that provides a 3D spatial orientation, plus an offset from the coordinate system that this is defined with respect to (e.g.,the world coordinate system).

Periodic systems can also be represented as an orientation and offset (i.e., translation) from a coordinate system that it is defined with respect to. A periodic system can be though of as having **two** orientations; forwards/backwards, clockwise/counter-clockwise, etc. The periodic translation is a value that will make a periodic coordinate system coincide with the system it is defined against. The values used must take into account their period.

To invert a general 3D coordinate system, we can derive the following:

![basic coordinate transform](./svg/xform.svg)

This shows the transformation from system *A* to system *B*. It also shows how to derive the inverse transformation from *B* to *A*. We have a rotation matrix *R* which provides the orientation, plus an offset *P* which is *A*'s origin in *B*'s coordinate system.

Our periodic transformations follow the same basic equations, except that instead of having a rotation matrix *R*, we have a single valued orientation *O* that has a value of +/-1. It is +1 if the coordinate systems have the same positive and negative orientation, and it is -1 if the coordinate systems have the opposite orientation. The inverses of the orientation are the same (if you are opposite you stay opposite, if you are the same you stay the same).

![periodic coordinate transform](./svg/periodic_xform.svg)

These coordinate system translations can be managed with either forward or reverse application of the **phi()** function (phase function).

#### Bearing Example
Navigational bearing and mathematical angles are very similar, but they can be considered different coordinate systems. Bearing has its origin in the north, while the 2D plane (used for the unit circle) has its origin in the east. The positive direction for bearing is clockwise, while the positive direction for mathematical angles is counter-clockwise (following the right-hand rule).

Since one is clockwise and the other counter-clockwise, any coordinate transformation is going to have *O* be -1. From the perspective of bearing, the math origin is 1/4 turn along the way in the positive orientation. From the perspective of math angles, the bearing origin is also 1/4 turn along the way in its positive orientation.

![bearing transform](./svg/bearing.svg)

We use *0.25* since in this case, our period is *turns*, but we could use a period of degrees or radians or other periodic unit.

#### Same Orientation Example
If we took the above example, but we decided to make a bearing also be counter-clockwise, what would that look like? The orientations are the same, so *O* is +1. If the math coordinate system is our **world** periodic system, then the CCW bearing is 1/4 turn along the way. However, the math coordinate system is 1/4 turn backwards from the bearing position, and this leads us to the following transformations (derived from above):

![forward bearing transform](./svg/bearing2.svg)

## Status

Current version: `v0.0.1`

* This project does nothing yet.

## Testing

This project uses [doctest](https://github.com/onqtam/doctest) for testing. We might occasionally use [nanobench](https://github.com/martinus/nanobench) for understanding implementation tradeoffs.

```
[doctest] doctest version is "2.4.8"
[doctest] run with "--help" for options
===============================================================================
[doctest] test cases:  1 |  1 passed | 0 failed | 0 skipped
[doctest] assertions: 63 | 63 passed | 0 failed |
[doctest] Status: SUCCESS!
```

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
//          Copyright David Browne 2020-2022.
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
