/*
 * DO NOT EDIT THIS FILE. Generated by checkmk.
 * Edit the original source file "functions-test.check" instead.
 */

#include <check.h>

#line 1 "functions-test.check"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "functions.h"

START_TEST(getEnvValTest)
{
#line 8
	char* systemPath;
	systemPath = getenv("PATH");

	fail_unless(strcmp(getEnvVal("PATH"), systemPath) == 0, "getEnvVal did not return same thing as getenv");
	fail_unless(strcmp(getEnvVal("path"), " ") == 0, "path without value did not return a space");

}
END_TEST

START_TEST(stringLengthTest)
{
#line 15
	int i;
	i = stringLength("test");

	fail_unless(i == 4, "did not return 4 for the word test");
	fail_unless(stringLength("") == 0, "did not return 0 for empty string");

}
END_TEST

START_TEST(stringCopyTest)
{
#line 22
	char* source;
	char* dest;
	source = "test";
	dest = stringCopy(source);

	fail_unless(strcmp(dest, source) == 0, "strcmp failed between dest and src");

	free(dest);
	dest = stringCopy("test");
	fail_unless(strcmp(dest, source) == 0, "strcmp failed between dest and src");

	free(dest);
	dest = stringCopy("");
	fail_unless(strcmp(dest, "") == 0, "strcmp failed between dest and an empty string");

}
END_TEST

START_TEST(readLineTest)
{
#line 38
	FILE* fp;
	fp = fopen("test.txt", "w");
	
	/* TEST INPUT 1 */
	char* rltest1;
	char* rltest1_expected;
	rltest1 = "this is a test\n";
	rltest1_expected = "this is a test";
	
	/* TEST INPUT 2 */
	char* rltest2;
	char* rltest2_expected;
	rltest2 = "this is a test\n";
	rltest2_expected = "this is a test";
	
	/* TEST INPUT 3 */
	char* rltest3;
	char* rltest3_expected;
	rltest3 = "this is a test dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd ddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd\n";
	rltest3_expected = NULL;

	/* TEST INPUT 4 */
	char* rltest4;
	char* rltest4_expected;
	rltest4 = "this is a test\n";
	rltest4_expected = "this is a test";

	fwrite(rltest1, sizeof(char), stringLength(rltest1), fp);
	fwrite(rltest2, sizeof(char), stringLength(rltest2), fp);
	fwrite(rltest3, sizeof(char), stringLength(rltest3), fp);
	fwrite(rltest4, sizeof(char), stringLength(rltest4), fp);
	fclose(fp);
	
	char* line;
	int fileHandle;
	fileHandle = open("test.txt", O_RDONLY);
	fail_unless(fileHandle != -1, "test input file could not be opened");
	
	/* CHECK TEST 1 */
	line = readLine(fileHandle);
	printf("READLINE TEST1 expected value: %s\n", rltest1_expected);
	printf("READLINE TEST1 returned value: %s\n", line);
	fail_unless(strcmp(line, rltest1_expected) == 0, "TEST1 values did not match\n", rltest1_expected, line);
	printf("\n");

	/* CHECK TEST 2 */
	line = readLine(fileHandle);
	printf("READLINE TEST2 expected value: %s\n", rltest2_expected);
	printf("READLINE TEST2 returned value: %s\n\n", line);
	fail_unless(strcmp(line, rltest2_expected) == 0, "TEST2 values did not match\n", rltest2_expected, line);
	printf("\n");

	/* CHECK TEST 3 */
	line = readLine(fileHandle);
	printf("READLINE TEST3 expected value: %s\n", rltest3_expected);
	printf("READLINE TEST3 returned value: %s\n\n", line);
	fail_unless(line == rltest3_expected, "TEST3 values did not match\n", rltest3_expected, line);
	printf("\n");

	/* CHECK TEST 4 */
	line = readLine(fileHandle);
	printf("READLINE TEST4 expected value: %s\n", rltest4_expected);
	printf("READLINE TEST4 returned value: %s\n\n", line);
	fail_unless(strcmp(line, rltest4_expected) == 0, "TEST4 values did not match\n", rltest4_expected, line);
	printf("\n");

	/* CLEAN UP DATA */
	close(fileHandle);
	remove("test.txt");

}
END_TEST

START_TEST(findDollarSignTest)
{
#line 109
	char* test;
	test = "this is a $test";
	int expected;
	expected = 10;
	int observed;
	observed = findDollarSign(test, 0);

	fail_unless(expected == observed, "dollar sign not found at correct location");

}
END_TEST

START_TEST(isValidFormTest1)
{
#line 119
	char* test;
	test = "$";
	int expected;
	expected = 0;
	int observed;
	observed = isValidForm(test, 0);

	fail_unless(observed == expected);

}
END_TEST

START_TEST(isValidFormTest2)
{
#line 129
	char* test;
	test = "$var";
	int expected;
	expected = 1;
	int observed;
	observed = isValidForm(test, 0);

	fail_unless(observed == expected);

}
END_TEST

START_TEST(isValidFormTest3)
{
#line 139
	char* test;
	test = "$3rf";
	fail_unless(stringLength(test) == 4, "stringLenth invalid\n");
	int expected;
	expected = 0;
	int observed;
	observed = isValidForm(test, 0);

	fail_unless(observed == expected);

}
END_TEST

START_TEST(isValidFormTest4)
{
#line 150
	char* test;
	test = "$_var";
	int expected;
	expected = 1;
	int observed;
	observed = isValidForm(test, 0);

	fail_unless(observed == expected);

}
END_TEST

START_TEST(isValidFormTest5)
{
#line 160
	char* test;
	test = "$v=r";
	int expected;
	expected = 0;
	int observed;
	observed = isValidForm(test, 0);

	fail_unless(observed == expected);

}
END_TEST

START_TEST(isValidFormTest6)
{
#line 170
	char* test;
	test = "$ ";
	int expected;
	expected = 0;
	int observed;
	observed = isValidForm(test, 0);

	fail_unless(observed == expected);

}
END_TEST

START_TEST(getVarLength1)
{
#line 180
	char* test;
	test = "get the $var length";
	int expected;
	expected = 4;
	int observed;
	observed = getVarLength(test, 8);
	
	fail_unless(expected == observed, "expected did not equal observed");

}
END_TEST

START_TEST(getVarLength2)
{
#line 190
	char* test;
	test = "get the $var";
	int expected;
	expected = 4;
	int observed;
	observed = getVarLength(test, 8);
	
	fail_unless(expected == observed, "expected did not equal observed");

}
END_TEST

START_TEST(getSubString1)
{
#line 200
	char* test;
	test = "$var $var";
	char* expected;
	expected = "$var";
	char* observed;
	observed = getSubString(test, 0, 3);

	fail_unless(strcmp(expected, observed) == 0, "expected was not equal to observed");
	
}
END_TEST

START_TEST(getSubString2)
{
#line 210
	char* test;
	test = "$var $var";
	char* expected;
	expected = "$var";
	char* observed;
	observed = getSubString(test, 5, 8);

	fail_unless(strcmp(expected, observed) == 0, "expected was not equal to observed");
#
}
END_TEST

START_TEST(parseLine1)
{
#line 220
	setenv("var", "new value", 0);
	printf("test1\n");
	char* test;
	test = "$var $2var";
	char* parsed;
	parsed = parseLine(test);

}
END_TEST

START_TEST(parseLine2)
{
#line 228
	setenv("var", "new value", 0);
	printf("test2\n");
	char* test;
	test = "$var $var";
	char* parsed;
	parsed = parseLine(test);

}
END_TEST

START_TEST(concatString1)
{
#line 236
	char* str1;
	char* str2;
	char* expected;
	char* observed;

	str1 = "var ";
	str2 = "var";
	expected = "var var";
	observed = concatString(str1, str2);
	printf("%s\n", observed);

	fail_unless(strcmp(expected,observed) == 0, "not equal strings");

}
END_TEST

START_TEST(concatString2)
{
#line 250
	char* str1;
	char* str2;
	char* str3;
	char* expected;
	char* observed;
	char* test;

	test = "beginning middle end";
	str1 = getSubString(test, 0, 9);
	str2 = getSubString(test, 10, 15);
	str3 = getSubString(test, 16, 19);
	expected = "beginning middle end";
	char* half;
	half = concatString(str1, str2);
	observed = concatString(half, str3);
	printf("%s\n", observed);

	fail_unless(strcmp(expected,observed) == 0, "not equal strings");
	fail_unless(stringLength(test) == 20, "fail");	










































}
END_TEST

int main(void)
{
    Suite *s1 = suite_create("Core");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, getEnvValTest);
    tcase_add_test(tc1_1, stringLengthTest);
    tcase_add_test(tc1_1, stringCopyTest);
    tcase_add_test(tc1_1, readLineTest);
    tcase_add_test(tc1_1, findDollarSignTest);
    tcase_add_test(tc1_1, isValidFormTest1);
    tcase_add_test(tc1_1, isValidFormTest2);
    tcase_add_test(tc1_1, isValidFormTest3);
    tcase_add_test(tc1_1, isValidFormTest4);
    tcase_add_test(tc1_1, isValidFormTest5);
    tcase_add_test(tc1_1, isValidFormTest6);
    tcase_add_test(tc1_1, getVarLength1);
    tcase_add_test(tc1_1, getVarLength2);
    tcase_add_test(tc1_1, getSubString1);
    tcase_add_test(tc1_1, getSubString2);
    tcase_add_test(tc1_1, parseLine1);
    tcase_add_test(tc1_1, parseLine2);
    tcase_add_test(tc1_1, concatString1);
    tcase_add_test(tc1_1, concatString2);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
