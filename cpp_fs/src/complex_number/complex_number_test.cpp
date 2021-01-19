/******************************************************************************
*						CREATED BY:	Orpaz Houta                     	      *
*						CREATED ON: 26/07/2020               			      *
*				   		REVIEWER: Gil Mazliah (Gilio:)         				  *
******************************************************************************/
#include <iostream>

#include "complex_number.hpp"
#include "ca_test_util.hpp"

using namespace std;
using namespace ilrd;

void SanityTest();
void TestOperators();
void Test100M();
int main()
{
    SanityTest();
    TestOperators();
    Test100M();

    TEST_SUMMARY();

    return 0;
}

void SanityTest()
{
    Complex c1(3, 4);
    Complex c2(1, 2);
    Complex c3(3, 4);

    cout << c1 << endl;
    cout << c2 << endl;

    INT_TEST(true, (c1 != c2));
    INT_TEST(true, (c1 == c3));
    INT_TEST(false, (c1 == c2));
    INT_TEST(false, (c1 != c3));

    Complex result1(4, 6);
    INT_TEST(true, (result1 == (c1 + c2)));

    Complex result2(2, 2);
    INT_TEST(true, (result2 == (c1 - c2)));

    Complex result3(-5, 10);
    INT_TEST(true, (result3 == (c1 * c2)));

    Complex result4(2.2, -0.4);
    INT_TEST(true, (result4 == (c1 / c2)));

    Complex result5 = c1 * c2;
    c1 *= c2;
    INT_TEST(true, (c1 == result5));

    Complex result6 = c1 / c2;
    c1 /= c2;
    INT_TEST(true, (c1 == result6));

    Complex result7 = c1 + c2;
    c1 += c2;
    INT_TEST(true, (c1 == result7));

    Complex result8 = c1 - c2;
    c1 -= c2;
    INT_TEST(true, (c1 == result8));
}

void TestOperators()
{
    Complex c1(3, 4);
    Complex c2(1, 2);

    //comparison with complex on the right
    INT_TEST(true, (c1 != 3));
    INT_TEST(false, (c1 == 4));
    //comparison with complex on the left
    INT_TEST(false, (-3 == c2));
    INT_TEST(true, (80 != c2));

    //operations with complex on the left
    Complex result1(20, 4);
    INT_TEST(true, (result1 == (c1 + 17)));
    INT_TEST(true, (result1 == (17 + c1)));

    Complex result2(-2, 4);
    INT_TEST(true, (result2 == (c1 - 5)));

    Complex result3(30, 40);
    INT_TEST(true, (result3 == (c1 * 10)));
    INT_TEST(true, (result3 == (10 * c1)));

    Complex result4(0.3, 0.4);
    INT_TEST(true, (result4 == (c1 / 10)));

    //operations with complex on the left
    Complex result5(1.2, -1.6);
    INT_TEST(true, (result5 == (10 / c1)));
    
    Complex result6(-3, -4);
    INT_TEST(true, (result6 == (0 - c1)));
    
    Complex result7(30.4, 1.2);
    Complex c3 = c1 + c2 + 12 / c2 * c1;

    // cout << c3 << endl;
    // cout << result7 << endl;

    // cin >> c1 >> c2 >> c3;
    // cout << c1 << endl;
    // cout << c2 << endl;
    // cout << c3 << endl;
}

void Test100M()
{
    Complex c1(1,1), c2(1,1);

    for (size_t i = 0; i < 100000000; ++i)
    {
        c1 += c2;
    }
}

