Zag Unit Test -- ZUT
====================

C/C++ header-only, lightweight, unit test framework

###Use

```C++
#include "zut.h"

int add(int a, int b) {
	return a + b;
}

ZUT_START

ZUT_LOG("About to run test_add\n");

ZUT_TEST("test_add", {
	AssertEqual(add(1, 2), 3);
})

ZUT_END

Compile it and you're good to go !

Don't forget to always enclose your test with ZUT_START and ZUT_END.

###Available assertions

1. AssertEqual

2. AssertNotEqual

3. AssertTrue

4. AssertFalse

5. AssertNull

6. AssertNotNull

7. AssertThrow (C++ only)

