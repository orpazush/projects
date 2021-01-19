/******************************************************************************
*						CREATED BY:	Orpaz Houta                     	      *
*						CREATED ON: 26/07/2020               			      *
*				   		REVIEWER: Gil Mazliah (Gilio:)         				  *
******************************************************************************/
#include <iostream>

#include "simple_string.hpp"
#include "ca_test_util.hpp"

using namespace std;
using namespace ilrd;

void TestHollyFor();
void TestCopyOperators();

int main()
{
    TestHollyFor();
    TestCopyOperators();

    TEST_SUMMARY();

    return 0;
}

void TestHollyFor()
{
    String s1("hello");
    String s2("can you");
    String s3("here me?");
    String s4;

    INT_TEST(true, s1.Length() == 5);
    INT_TEST(true, s2.Length() == 7);
    INT_TEST(true, s3.Length() == 8);

    INT_TEST(true, ("hello" == s1));
    INT_TEST(true, ("can you" == s2));
    INT_TEST(true, ("here me?" == s3));
    INT_TEST(true, ("" == s4));

    cout << s1 << endl;
    cout << s2 << endl;
    cout << s3 << endl;

    s1 = s2;
    INT_TEST(true, s1.Length() == s2.Length());
    INT_TEST(true, (s1 == s2));
    INT_TEST(false, (s3 == s2));

    s2 = s3;
    INT_TEST(true, s2.Length() == s3.Length());
    INT_TEST(true, (s3 == s2));
    INT_TEST(false, (s1 == s2));

    s3 = s4;
    INT_TEST(true, s3.Length() == 0);
    INT_TEST(true, (s3 == s4));
    INT_TEST(false, (s3 == s2));
}    

void TestCopyOperators()
{
    String s1("s1");
    String s2(s1);
    String s3("s3");
    String s4(s3);

    INT_TEST(true, (s1 == s2));
    INT_TEST(true, (s3 == s4));

    s2 = "s2";
    s4 = "s4";

    INT_TEST(true, (s1 < s2));
    INT_TEST(true, (s3 < s4));

    s1 = s2 = s3 = s4;

    cout << s1 << endl;
    cout << s2 << endl;
    cout << s3 << endl;
    cout << s4 << endl;
}
