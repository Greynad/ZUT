/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * Authored by Murmur
 */

#ifndef ZAGTEST_H
#define ZAGTEST_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#ifdef __cplusplus
}
#endif /* __cplusplus */

#ifdef __cplusplus

/*
 * If C++ template are available, use them, it adds type checking to the assert
 *
 * @params a, b : can be of any type thanks to C++ template
 * @return bool : return true if a is equal to b, false instead
 */
template<typename T> bool 
_AssertEqual(T a, T b) {
	return (a == b);
}

#undef ZAG_ASSERT
#define ZAG_ASSERT(A, B) _AssertEqual(A, B)

#else

/*
 * If we compile strict C, assert is a simple equality check
 * Use carefully, C Macro aren't functions
 */
#undef ZAG_ASSERT
#define ZAG_ASSERT(A, B) (A == B)

#endif /* __cplusplus */
/*
 * /!\ This function never returns
 * Display information about the failing test and exit with error code -1
 *
 * @params:
 *      msg       : custom message displayed before exiting
 *      line      : source code line number where the test failed
 *      test_nbr  : test id number
 *      func_name : identifier of the failing test 
 */
#ifdef OS_WINDOWS
#define ERR_OUTPUT "Failed test %i : %s at line %i: %s\n"
#else
#define ERR_OUTPUT "\033[31mFailed test %i : %s at line %i\033[39m: %s\n"
#endif
__attribute__((noreturn)) void 
errorf(const char* msg, int line, int test_nbr, const char* func_name) {
	fprintf(stderr, ERR_OUTPUT, test_nbr, func_name, line, msg);
	exit(-1);
}

/*
 * Mark beginning of test suite (once per test file)
 */
#define ZUT_START \
int main(void) { \
	int test_nbr = 0; \

/*
 * Mark end of test suite (once per test file)
 */
#define ZUT_END \
	puts("\r\n..............................................."); \
	printf("Ran %i test(s) ... Everything went Ok\n", test_nbr); \
	return 0;}

/*
 * Run a test
 * 
 * @params
 *      TEST_NAME    : the string identifier of the test
 *      TEST_CONTENT : bracket enclosed code which contains different assert
 */
#define ZUT_TEST(TEST_NAME, TEST_CONTENT) \
	{const char* test_name = TEST_NAME; \
	printf("Running test %i : %s \n", ++test_nbr, TEST_NAME); \
	TEST_CONTENT printf("%s ....passed !\n\n", TEST_NAME);}

/*
 * Display info message to the console (stdout)
 * @params
 *      same as printf
 */
#define ZUT_LOG(...) printf(__VA_ARGS__)


/*
 * throw an error if A is not equal to B
 */
#define AssertEqual(A, B) \
	if (!ZAG_ASSERT(A, B)) \
		errorf(#A" is not equal to "#B, __LINE__, test_nbr, test_name)

/*
 * throw an error if A is equal to B
 */
#define AssertNotEqual(A, B) \
	if (ZAG_ASSERT(A, B)) \
		errorf(#A" is equal to "#B, __LINE__, test_nbr, test_name)

/*
 * throw an error if A is false
 */
#define AssertTrue(A) \
	if (!ZAG_ASSERT(A, true)) \
		errorf(#A" is false", __LINE__, test_nbr, test_name)

/*
 * throw an error if A is true
 */
#define AssertFalse(A) \
	if (!ZAG_ASSERT(A, false)) \
		errorf(#A" is true", __LINE__, test_nbr, test_name)

/*
 * throw an error if A is not NULL or nullptr
 */
#define AssertNull(A) \
	if (!ZAG_ASSERT((intptr_t)A, NULL)) \
		errorf(#A" is not null", __LINE__, test_nbr, test_name)

/*
 * throw an error if A is not NULL, nullptr
 */
#define AssertNotNull(A) \
	if (ZAG_ASSERT((intptr_t)A, NULL)) \
		errorf(#A" is null", __LINE__, test_nbr, test_name)

/*
 * /!\ C++ only
 * throw an error if statement A doesn't throw EXCEPT
 */
#ifdef __cplusplus

#define AssertThrow(A, EXCEPT) \
    /* __assertThrowReturn should be zeroed by the compiler,
     * nevertheless, better safe than sorry */ \
	int __assertThrowReturn = 0; \
	try{A;} catch (EXCEPT e) {__assertThrowReturn = 1;} \
	if (!__assertThrowReturn) \
		errorf(#A" doesn't throw "#EXCEPT, __LINE__, test_nbr, test_name)

#endif /* __CPLUS_PLUS */

#endif /* ZAGTEST_H */