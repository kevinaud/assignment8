/* #test parseLineTest1
	/* TEST INPUT 1 */
	char* pltest;
	pltest = "this is a test";
	char* pltest_expected;
	pltest_expected = "this is a test";

	char* parsed;

	/* CHECK INPUT 1 */
	parsed = parseLine(pltest);
	printf("PARSELINE TEST 1 expected value: %s\n", pltest_expected);
	printf("PARSELINE TEST 1 returned value: %s\n", parsed);
	fail_unless(strcmp(parsed, pltest_expected) == 0, "returned string was not the same as expected\n");
	printf("\n");

#test parseLineTest2
	/* TEST INPUT 2 */
	char* pltest;
	pltest = "$path";
	char* pltest_expected;
	pltest_expected = " ";

	char* parsed;

	/* CHECK INPUT 2 */
	parsed = parseLine(pltest);
	printf("PARSELINE TEST 2 expected value: %s\n", pltest_expected);
	printf("PARSELINE TEST 2 returned value: %s\n\n", parsed);
	fail_unless(strcmp(parsed, pltest_expected) == 0, "returned string was not the same as expected\n");
	
#test parseLineTest3
	/* TEST INPUT 3 */
	setenv("var", "new value", 0);
	fail_unless(strcmp(getEnvVal("var"), "new value") == 0, "setting environment variable failed in test setup");
	char* pltest;
	pltest = "$var";
	char* pltest_expected;
	pltest_expected = "new value";

	char* parsed;

	/* CHECK INPUT 3 */
	parsed = parseLine(pltest);
	printf("PARSELINE TEST 3 expected value: %s\n", pltest_expected);
	printf("PARSELINE TEST 3 returned value: %s\n\n", parsed);
	fail_unless(strcmp(parsed, pltest_expected) == 0, "returned string was not the same as expected\n");

#test parseLineTest4
	/* TEST INPUT 4 */
	char* pltest;
	pltest = "$PATH $PATH $PATH $PATH $PATH";
	char* pltest_expected;
	pltest_expected = NULL;

	char* parsed;

	/* CHECK INPUT 4 */
	parsed = parseLine(pltest);
	printf("PARSELINE TEST 4 expected value: %s\n", pltest_expected);
	printf("PARSELINE TEST 4 returned value: %s\n\n", parsed);
	fail_unless(parsed == pltest_expected, "returned string was not the same as expected\n");

#test parseLineTest5
	/* TEST INPUT 5 */
	char* pltest;
	pltest = "$PATH$PATH";
	char* pltest_expected;
	pltest_expected = " ";

	char* parsed;

	/* CHECK INPUT 5 */
	parsed = parseLine(pltest);
	printf("PARSELINE TEST 5 expected value: %s\n", pltest_expected);
	printf("PARSELINE TEST 5 returned value: %s\n\n", parsed);
	fail_unless(parsed == pltest_expected, "returned string was not the same as expected\n");

#test parseLineTest6
	/* TEST INPUT 6 */
	setenv("var", "new value", 0);
	fail_unless(strcmp(getEnvVal("var"), "new value") == 0, "setting environment variable failed in test setup");
	char* pltest;
	pltest = "$var ";
	char* pltest_expected;
	pltest_expected = "new value";

	char* parsed;

	/* CHECK INPUT 6 */
	parsed = parseLine(pltest);
	printf("PARSELINE TEST 6 expected value: %s\n", pltest_expected);
	printf("PARSELINE TEST 6 returned value: %s\n\n", parsed);
	fail_unless(strcmp(parsed, pltest_expected) == 0, "returned string was not the same as expected\n");

*/

	


