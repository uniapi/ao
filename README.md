# AO - Assert Operator

###  A New Approach To Unit Testing And Not Only

Concepts
========

**Assert operator** or _ao_  |ei'ou| is a software to simplify multi-platform testing.

The _ao_ promotes the approach of isolating test data from testing code and as a consequence
the _ao_ test consists of _assert operator cases_. 

An **assert operator case** is a test case consumed by the user-supplied `assert_case()` function
that should return an _assert operation_ as a result. The test case structure is usually defined by the `aocase_t` type
and hence the recommended function declaration is `aop_t assert_case(aocase_t *aoc)`.

An **assert operation** or _aop_ |ei'ou'pi| is an assertion unit of the assert operator case 
and is one of the following:
* *AOP_PASS* - the assert operation is successful (always 0)
* *AOP_FAIL* - the assert operation is failed and by default the test stops immediatly and the remaining assert operations are not run
* *AOP_SKIP* - the assert operation is skipped and the test continues to run the remaining assert operations

*To run an assert operation* means to execute the `assert_case()` function with a test case to determine its assertion unit, _aop_.
And during such exuction the assert operation can be violated by different factors 
and this process is called **assertion operation violation**.
It is strongly recommended to assert operation violation as some can disrupt and even crash the system.

Currently, the following _assertion operation violation_ can be caught:
* *AOV_MEMV* - Unexpected Memory Access
* *AOV_PTRV* - Unexpected Pointer Value
* *AOV_RTMV* - Unexpected Real Time Expiration
* *AOV_UTMV* - Unexpected User Time Expiration
* *AOV_ETMV* - Unexpected Execution Time Expiration

An easy way to assert time expiration is to use an according _assert operator timer_:
* *AOT_RTM* - Real Time
* *AOT_UTM* - User (Virtual) Time
* *AOT_ETM* - Execution (Profiling) Time

The _assert operation_, if complicated, can be subdivided into several assert operations
and concatenated together as a final result
using the most to less strict order: *AOP_FAIL*, *AOP_SKIP* and *AOP_PASS*.
However, if the further computation is unnecessary or expensive then _classical assertions_ should be used instead.

The plentiful functions provided are corporated the `libaop` library consisting of the following modules:
* `ao` - functions to run assert operator
* `aop` - functions to assert operations
* `aopf` - functions to assert operations with the _expected_ and _actual_ arguments auto-formatting and optional formatting
* `assert` - classical assertions
* `aov` - functions to assert operation violation
* `aot` - functions to run assert operator times
* `...` - \*modules are to be added...

Installation
============

```sh
tar xzvf ao.tar.gz
cd ao
./ao.sh setup --verbose
```
