/******************************************************************************
 *                      code by : Orpaz Houta                                 *
 *                      review by : Alex Sevostyanov                          *
 *                      coding date - 11-06-2020                              *
 ******************************************************************************/
 #include <limits.h> /* CHAR_BIT */

 #include "trie.h"
 #include "ca_test_util.h" 	/* ©️ chanan  aviv */

 #define MAX_RANGE (10000)
 #define SIZE (25)

 void TestCreateInsert();
 void TestFindRemove();

 int main()
 {
     TestCreateInsert();
     TestFindRemove();

     TEST_SUMMARY();

     return 0;
 }

 void TestCreateInsert()
 {
     trie_t *test_trie = NULL;
     char test1 = 1;
     char test2 = 2;
     char test3 = 5;
     char test4 = 20;

     test_trie = TrieCreate(CHAR_BIT * sizeof(char));

     INT_TEST(1, TrieIsEmpty(test_trie));

     INT_TEST(0, TrieInsert(test_trie, (size_t)test1));
     TrieRemove(test_trie, (size_t)test1);
     INT_TEST(1, TrieIsEmpty(test_trie));

     INT_TEST(0, TrieInsert(test_trie, (size_t)test1));
     INT_TEST(0, TrieInsert(test_trie, (size_t)test2));
     INT_TEST(0, TrieInsert(test_trie, (size_t)test3));
     INT_TEST(0, TrieInsert(test_trie, (size_t)test4));

     INT_TEST(0, TrieIsEmpty(test_trie));
     INT_TEST(4, TrieSize(test_trie));

     TrieDestroy(test_trie);
 }

 void TestFindRemove()
 {
     trie_t *test_trie = NULL;
     int i = 0;
     int j = 0;
     size_t array[SIZE];
     int test_size = SIZE;

     test_trie = TrieCreate(CHAR_BIT * sizeof(size_t));
     INT_TEST(1, TrieIsEmpty(test_trie));

     for (i = 0 ; i < SIZE ; i++)
     {
         array[i] = i;
     }

     for (i = 0 ; i < SIZE ; i++)
     {
         INT_TEST(i, (int)TrieSize(test_trie));
         TrieInsert(test_trie, array[i]);
         INT_TEST((i + 1), (int)TrieSize(test_trie));
     }
     INT_TEST(0, TrieIsEmpty(test_trie));
     INT_TEST(SIZE, (int)TrieSize(test_trie));


     for (i = 0 ; i < SIZE ; j = (rand() % SIZE), ++i)
     {
         INT_TEST(1, IsInTrie(test_trie, array[j]));
     }

     INT_TEST(0, IsInTrie(test_trie, SIZE));
     INT_TEST(SIZE, TrieGetNext(test_trie, SIZE - 1));
     INT_TEST(SIZE, TrieGetNext(test_trie, SIZE - 2));
     INT_TEST(SIZE, TrieGetNext(test_trie, 8));
     INT_TEST(SIZE, TrieGetNext(test_trie, 3));
     INT_TEST(SIZE, TrieGetNext(test_trie, 16));

     test_size = SIZE;
     for (i = 0; !TrieIsEmpty(test_trie); ++i)
     {
         --test_size;
         TrieRemove(test_trie, array[i]);
         INT_TEST(test_size, (int)TrieSize(test_trie));
     }

     for (i = 0 ; i < SIZE ; j = (rand() % SIZE), ++i)
     {
         INT_TEST(0, IsInTrie(test_trie, array[j]));
     }

     TrieRemove(test_trie, array[i]);

     TrieDestroy(test_trie);
 }
