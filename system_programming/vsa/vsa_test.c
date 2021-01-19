/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Shachar Reshef									 *
 * 					Last update : 8.5.20									 *
 ****************************************************************************/

#include <assert.h>	/* assert */
#include "vsa.h"
#include "ca_test_util.h" 	/* ©️ chanan & aviv */


void TestInitLargest();
void TestAllocFree();


int main()
{
	TestInitLargest(); 
	TestAllocFree();

    TEST_SUMMARY();

    return 0;
}


void TestInitLargest()
{
	vsa_t *test_segment = NULL;
	vsa_t *testvsa = NULL;
	size_t largest = 0;

	test_segment = (vsa_t *)malloc(200);
	testvsa = VSAInit(test_segment, 200);

#ifdef NDEBUG
	largest = VSALargestChunkAvailable(testvsa);
	INT_TEST(184, largest);

	VSAAlloc(testvsa, 16);
	largest = VSALargestChunkAvailable(testvsa);
	INT_TEST(160, largest);
	
	VSAAlloc(testvsa, 11);
	largest = VSALargestChunkAvailable(testvsa);
	INT_TEST(136, largest);

	VSAAlloc(testvsa, 100);
	largest = VSALargestChunkAvailable(testvsa);
	INT_TEST(24, largest);

	VSAAlloc(testvsa, 20);
	largest = VSALargestChunkAvailable(testvsa);
	INT_TEST(0, largest);
#endif

#ifndef NDEBUG
	largest = VSALargestChunkAvailable(testvsa);
	INT_TEST(176, largest);

	VSAAlloc(testvsa, 16);
	largest = VSALargestChunkAvailable(testvsa);
	INT_TEST(144, largest);
	
	VSAAlloc(testvsa, 11);
	largest = VSALargestChunkAvailable(testvsa);
	INT_TEST(112, largest);

	VSAAlloc(testvsa, 100);
	largest = VSALargestChunkAvailable(testvsa);
	INT_TEST(0, largest);
#endif

	free(test_segment);
	test_segment = NULL;
}


void TestAllocFree()
{
	vsa_t *test_segment = NULL;
	vsa_t *testvsa = NULL;
	int *alloc1 = NULL;
	int *alloc2 = NULL;
	int *alloc3 = NULL;
	size_t largest = 0;

	test_segment = (vsa_t *)malloc(200);
	testvsa = VSAInit(test_segment, 200);


#ifdef NDEBUG
	largest = VSALargestChunkAvailable(testvsa);
	INT_TEST(184, largest);

	alloc1 = (int *)VSAAlloc(testvsa, 40);
	largest = VSALargestChunkAvailable(testvsa);
	INT_TEST(136, largest);
	
	alloc2 = (int *)VSAAlloc(testvsa, 60);
	largest = VSALargestChunkAvailable(testvsa);
	INT_TEST(64, largest);

	alloc3 = (int *)VSAAlloc(testvsa, 50);
	largest = VSALargestChunkAvailable(testvsa);
	INT_TEST(0, largest);
	
	VSAFree(alloc3);
	largest = VSALargestChunkAvailable(testvsa);
	INT_TEST(64, largest);

	VSAFree(alloc2);
	largest = VSALargestChunkAvailable(testvsa);
	INT_TEST(136, largest);

	alloc2 = (int *)VSAAlloc(testvsa, 60);
	alloc3 = (int *)VSAAlloc(testvsa, 50);
	largest = VSALargestChunkAvailable(testvsa);
	INT_TEST(0, largest);

	VSAFree(alloc1);
	VSAFree(alloc2);
	VSAFree(alloc3);
	largest = VSALargestChunkAvailable(testvsa);
	INT_TEST(184, largest);

	alloc1 = (int *)VSAAlloc(testvsa, 40);
	alloc2 = (int *)VSAAlloc(testvsa, 60);
	alloc3 = (int *)VSAAlloc(testvsa, 50);
	largest = VSALargestChunkAvailable(testvsa);
	INT_TEST(0, largest);

	VSAFree(alloc2);
	largest = VSALargestChunkAvailable(testvsa);
	INT_TEST(64, largest);

	alloc2 = (int *)VSAAlloc(testvsa, 60);
	VSAFree(alloc1);
	VSAFree(alloc2);
	largest = VSALargestChunkAvailable(testvsa);
	INT_TEST(112, largest);
#endif

#ifndef NDEBUG
	largest = VSALargestChunkAvailable(testvsa);
	INT_TEST(176, largest);

	alloc1 = (int *)VSAAlloc(testvsa, 40);
	largest = VSALargestChunkAvailable(testvsa);
	INT_TEST(120, largest);
	
	alloc2 = (int *)VSAAlloc(testvsa, 60);
	largest = VSALargestChunkAvailable(testvsa);
	INT_TEST(40, largest);

	alloc3 = (int *)VSAAlloc(testvsa, 38);
	largest = VSALargestChunkAvailable(testvsa);
	INT_TEST(0, largest);
	
	VSAFree(alloc3);
	largest = VSALargestChunkAvailable(testvsa);
	INT_TEST(40, largest);

	VSAFree(alloc2);
	largest = VSALargestChunkAvailable(testvsa);
	INT_TEST(120, largest);

	alloc2 = (int *)VSAAlloc(testvsa, 60);
	alloc3 = (int *)VSAAlloc(testvsa, 38);
	largest = VSALargestChunkAvailable(testvsa);
	INT_TEST(0, largest);

	VSAFree(alloc1);
	VSAFree(alloc2);
	VSAFree(alloc3);
	largest = VSALargestChunkAvailable(testvsa);
	INT_TEST(176, largest);

	alloc1 = (int *)VSAAlloc(testvsa, 40);
	alloc2 = (int *)VSAAlloc(testvsa, 60);
	alloc3 = (int *)VSAAlloc(testvsa, 38);
	largest = VSALargestChunkAvailable(testvsa);
	INT_TEST(0, largest);

	VSAFree(alloc1);
	VSAFree(alloc2);
	largest = VSALargestChunkAvailable(testvsa);
	INT_TEST(120, largest);
	
#endif


	free(test_segment);
	test_segment = NULL;
}




















