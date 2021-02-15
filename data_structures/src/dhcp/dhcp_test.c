/******************************************************************************
 *                      code by : Orpaz Houta                                 *
 *                      review by : Alex Sevostyanov                          *
 *                      coding date - 11-06-2020                              *
 ******************************************************************************/
 #include <stddef.h>    /* size_t */

 #include "ca_test_util.h"

 #include "dhcp.h"

 void TestInsert();
 void TestRemove();

 int main()
 {
     TestInsert();
     TestRemove();

     TEST_SUMMARY();

     return 0;
 }

 void TestInsert()
 {
     unsigned char subnet_id[4] = {192, 168, 1, 0};
     unsigned char expected_ip[4] = {0};
     dhcp_t *test = DHCPCreate(subnet_id, 24);
     unsigned char *result = (unsigned char *)malloc(sizeof(unsigned char) * 4);
     int insert_result = 0;

     unsigned char test_ip[5][4] = {{192, 168, 1, 1}, {192, 168, 1, 2},
                                    {192, 168, 1, 3}, {192, 168, 1, 4},
                                    {192, 168, 1, 5}};

     insert_result = DHCPAllocateIP(test,test_ip[0], result);
     INT_TEST(0, insert_result);
     INT_TEST(252, DHCPCountFree(test));

     insert_result = DHCPAllocateIP(test,test_ip[1], result);
     INT_TEST(0, insert_result);
     INT_TEST(251, DHCPCountFree(test));

     insert_result = DHCPAllocateIP(test,test_ip[2], result);
     INT_TEST(0, insert_result);
     INT_TEST(250, DHCPCountFree(test));

     insert_result = DHCPAllocateIP(test,test_ip[3], result);
     INT_TEST(0, insert_result);
     INT_TEST(249, DHCPCountFree(test));


     insert_result = DHCPAllocateIP(test,test_ip[4], result);
     INT_TEST(0, insert_result);
     INT_TEST(248, DHCPCountFree(test));
     INT_TEST(0,memcmp(test_ip[4], result, 4));

     /* Insert occupied ip adresses */
     expected_ip[0] = 192;
     expected_ip[1] = 168;
     expected_ip[2] = 1;
     expected_ip[3] = 6;

     insert_result = DHCPAllocateIP(test,test_ip[0], result);
     INT_TEST(0 , memcmp(expected_ip, result, 4));
     INT_TEST(0, insert_result);
     INT_TEST(247, DHCPCountFree(test));

     /* Try to insert the same ip again */
     expected_ip[0] = 192;
     expected_ip[1] = 168;
     expected_ip[2] = 1;
     expected_ip[3] = 7;

     insert_result = DHCPAllocateIP(test,test_ip[0], result);
     INT_TEST(0 , memcmp(expected_ip, result, 4));
     INT_TEST(0, insert_result);
     INT_TEST(246, DHCPCountFree(test));

     DHCPDestroy(test);
     free(result);
     test = NULL;
 }

 void TestRemove()
 {
     unsigned char subnet_id[4] = {192, 168, 1, 0};
     dhcp_t *test = DHCPCreate(subnet_id, 24);
     unsigned char *result = (unsigned char *)malloc(sizeof(unsigned char) * 4);
     int insert_result = 0;
     int i = 0;
     int remove_status = 0;

     unsigned char test_ip[5][4] ={{192, 168, 1, 1}, {192, 168, 1, 2},
                                   {192, 168, 1, 3}, {192, 168, 1, 4},
                                   {192, 168, 1, 5}};


     for (i = 0; i < 5; ++i)
     {
         insert_result = DHCPAllocateIP(test,test_ip[i], result);
         INT_TEST(0,insert_result);
     }
     INT_TEST(248, DHCPCountFree(test));


     /* remove and reallocate the same ip address */
     DHCPFreeIP(test,test_ip[1]);
     INT_TEST(249, DHCPCountFree(test));
     DHCPAllocateIP(test,test_ip[1], result);
     INT_TEST(248, DHCPCountFree(test));

     DHCPFreeIP(test,test_ip[0]);
     INT_TEST(249, DHCPCountFree(test));
     DHCPFreeIP(test,test_ip[1]);
     INT_TEST(250, DHCPCountFree(test));
     DHCPFreeIP(test,test_ip[2]);
     INT_TEST(251, DHCPCountFree(test));
     DHCPFreeIP(test,test_ip[3]);
     INT_TEST(252, DHCPCountFree(test));

     /* Free the same ip address twise */
     remove_status = DHCPFreeIP(test,test_ip[3]);
     INT_TEST(DHCP_STATUS_DOUBLE_FREE_FAILURE, remove_status);
     INT_TEST(252, DHCPCountFree(test));

     /* sending 0 instead of specific request */
     DHCPAllocateIP(test, 0, result);
     INT_TEST(251, DHCPCountFree(test));

     DHCPDestroy(test);
     free(result);
     test = NULL;
 }
