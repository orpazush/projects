/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Gil Steinberg     						         *
 * 					Last update : 3.8.20									 *
 ****************************************************************************/
#include <iostream>

#include "rc_string.hpp"
#include "ca_test_util.hpp"

using namespace std;
using namespace ilrd;

void SanityTest();
void TestCopyOperators();
void TestBracketsAndRc();

int main()
{
    SanityTest();
    TestCopyOperators();
    TestBracketsAndRc();

    TEST_SUMMARY();

    return 0;
}

void SanityTest()
{
    RCString s1("hello");
    RCString s2("can you");
    RCString s3("here me?");
    RCString s4;

    INT_TEST(true, s1.GetLength() == 5);
    INT_TEST(true, s2.GetLength() == 7);
    INT_TEST(true, s3.GetLength() == 8);

    INT_TEST(true, ("hello" == s1));
    INT_TEST(true, ("can you" == s2));
    INT_TEST(true, ("here me?" == s3));
    INT_TEST(true, ("" == s4));

    cout << s1 << endl;
    cout << s2 << endl;
    cout << s3 << endl;

    s1 = s2;
    INT_TEST(true, s1.GetLength() == s2.GetLength());
    INT_TEST(true, (s1 == s2));
    INT_TEST(false, (s3 == s2));

    s2 = s3;
    INT_TEST(true, s2.GetLength() == s3.GetLength());
    INT_TEST(true, (s3 == s2));
    INT_TEST(false, (s1 == s2));

    s3 = s4;
    INT_TEST(true, s3.GetLength() == 0);
    INT_TEST(true, (s3 == s4));
    INT_TEST(false, (s3 == s2));
}

void TestCopyOperators()
{
    RCString s1("s1");
    RCString s2(s1);
    RCString s3("s3");
    RCString s4(s3);

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

void TestBracketsAndRc()
{
    const RCString s1("0123456");

    char test1 = s1[2];
    INT_TEST(true, test1 == '2');

    char test2 = s1[5];
    INT_TEST(true, test2 == '5');

    RCString s2 = "654321";
    INT_TEST(false, s1 == s2);
    INT_TEST(true, s2[3] == s1[3]);

    s2[1] = 'a';
    INT_TEST(true, s2[1] == 'a');

    s2[2] = s1[2];
    INT_TEST(true, s2[2] == s1[2]);

    RCString *ps3 = new RCString("copies");
    const RCString s4(*ps3);
    RCString s5 = s4;

    INT_TEST(true, *ps3 == s4);
    INT_TEST(true, *ps3 == s5);
    INT_TEST(false, s5 != s4);

    delete ps3;
    INT_TEST(true, s5[0] == 'c');
    INT_TEST(true, s4[1] == 'o');

    cout << "s5[3] of copies: "<< s5[3] << endl;
    cout << "const s4[0] of copies: " << s4[0] << endl;
}
