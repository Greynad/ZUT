#include "zut.h"  

int add(int a, int b) { return a + b; }

bool is_true() { return 1; }

int* ret_null() { return nullptr; }

int ret_notNull() { return 10; }

void thrower() { throw 20; }

ZUT_START  

ZUT_LOG("zut Testing session\n");

ZUT_TEST("test_Equal", {  
    AssertEqual(add(1, 2), 3);    
})

ZUT_TEST("test_notEqual", {  
    AssertNotEqual(add(1, 2), 4);    
})

ZUT_TEST("test_True", {  
    AssertTrue(is_true());    
})

ZUT_TEST("test_False", {  
    AssertFalse(!is_true());    
})

ZUT_TEST("test_null", {  
    AssertNull(ret_null());    
})

ZUT_TEST("test_notNull", {  
    AssertNotNull(ret_notNull());    
})

ZUT_TEST("test_throw", {
	AssertThrow(thrower(), int);
})

ZUT_END