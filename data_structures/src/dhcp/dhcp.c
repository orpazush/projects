/******************************************************************************
 *                      code by : Orpaz Houta                                 *
 *                      review by : Alex Sevostyanov                          *
 *                      coding date - 11-06-2020                              *
 ******************************************************************************/
 #include <malloc.h>     /* malloc() */
 #include <assert.h>     /* assert() */
 #include <math.h>       /* pow() */
 # include <limits.h>    /* CHAR_BIT */

 #include "trie.h"
 #include "dhcp.h"

/*---------------------------------Structs-----------------------------------*/
struct dhcp
{
    trie_t *trie;
    size_t subnet_mask;
    size_t num_of_bits_in_mask;
};
/*---------------------------------------------------------------------------*/

/*--------------------------------Macros-------------------------------------*/
 #ifndef NDEBUG
 #define PRINT_ERROR(str) fprintf(stderr, "ERROR( %s : %d ) -- %s\n",\
 							     __FILE__, __LINE__ , str)
 #else
 #define PRINT_ERROR(str)
 #endif

 #define ASCII (256)  /* _CharToSizeT, _SizeTToChar */
 #define BITS_IN_IP (BYTES_IN_IP * CHAR_BIT)
/*---------------------------------------------------------------------------*/

/*---------------------------Static Functions--------------------------------*/
 static int _Init(dhcp_t *dhcp);
 static int _IsInSubnet(dhcp_t *dhcp, size_t to_insert);
 static void _SizeTToChar(dhcp_t *dhcp, unsigned char *dest, size_t num);
 static void _CharToSizeT(const unsigned char bytes[BYTES_IN_IP],
                          size_t *result);
/*---------------------------------------------------------------------------*/

/*------------------------------API Functions--------------------------------*/
 dhcp_t *DHCPCreate(const unsigned char subnet_ip[BYTES_IN_IP],
                    size_t num_bits_in_subnet)
 {
     dhcp_t *dhcp = NULL;

     assert(subnet_ip);

     dhcp = (dhcp_t *)malloc(sizeof(dhcp_t));
     if (!dhcp)
     {
         PRINT_ERROR("malloc failed in DHCPCreate\n");

         return (NULL);
     }

     dhcp->num_of_bits_in_mask = num_bits_in_subnet;
     dhcp->trie = TrieCreate(BITS_IN_IP - num_bits_in_subnet);

     if (!dhcp->trie || _Init(dhcp))
     {
         PRINT_ERROR("malloc failed in DHCPCreate\n");

         dhcp->trie = NULL;

         free(dhcp);
         dhcp = NULL;

         return (NULL);
     }

     _CharToSizeT(subnet_ip, &dhcp->subnet_mask);

     return dhcp;
 }


 void DHCPDestroy(dhcp_t *dhcp)
 {
     if (dhcp)
     {
         TrieDestroy(dhcp->trie);
         dhcp->trie = NULL;

         free(dhcp);
         dhcp = NULL;
     }
 }

 dhcp_status_t DHCPAllocateIP(dhcp_t *dhcp,
                              const unsigned char requested_ip[BYTES_IN_IP],
                              unsigned char result_ip[BYTES_IN_IP])
 {
     size_t result = 0;

     assert(dhcp);
     assert(DHCPCountFree(dhcp));

     /* when there is not specific request */
     if (!result)
     {
         result = dhcp->subnet_mask;
     }

     else
     {
         /* match the requested ip to size_t for the trie functions */
         _CharToSizeT(requested_ip, &result);

         /* case the user sent an ip not within the subnet */
         assert(_IsInSubnet(dhcp, result));
     }

     /* if the requested ip is already occupied it gets the next available ip */
     if (IsInTrie(dhcp->trie, result))
     {
         result = TrieGetNext(dhcp->trie, result);
     }

     if (TrieInsert(dhcp->trie, result))
     {
         return(DHCP_STATUS_FAILURE);
     }

     _SizeTToChar(dhcp, result_ip, result);

     return (DHCP_STATUS_OK);
 }

 dhcp_status_t DHCPFreeIP(dhcp_t *dhcp,
                          const unsigned char ip_to_free[BYTES_IN_IP])
 {
     size_t to_free = 0;

     assert(dhcp);
     assert(ip_to_free);

     _CharToSizeT(ip_to_free, &to_free);

     /* case the user sent an ip not within the subnet */
     assert(_IsInSubnet(dhcp, to_free));

     return ((TrieRemove(dhcp->trie, to_free)) ? DHCP_STATUS_DOUBLE_FREE_FAILURE
                                               : DHCP_STATUS_OK);
 }

 size_t DHCPCountFree(const dhcp_t *dhcp)
 {
     size_t host_bits = 0;

     assert(dhcp);

     host_bits = (BITS_IN_IP - dhcp->num_of_bits_in_mask);

     return((pow(2, host_bits) - TrieSize(dhcp->trie)));
 }
/*---------------------------------------------------------------------------*/

/*-------------------------------Static Definitions--------------------------*/
/* allocates implicitly the requested addresses in the brainfuel */
 static int _Init(dhcp_t *dhcp)
 {
     size_t network_address = 0;
     size_t server_address = -1;
     size_t broadcast_address = -2;
     int result = 0;

     result = TrieInsert(dhcp->trie, network_address) +
              TrieInsert(dhcp->trie, server_address) +
              TrieInsert(dhcp->trie, broadcast_address);

     if (DHCP_STATUS_OK != result )
     {
         TrieDestroy(dhcp->trie);

         return DHCP_STATUS_FAILURE;
     }

     return DHCP_STATUS_OK;
 }

/* converts a given char into a size_t - used to match the types for the trie
   functions */
 static void _CharToSizeT(const unsigned char bytes[BYTES_IN_IP], size_t *result)
 {
     unsigned int i = 0;
     unsigned int exponent = BYTES_IN_IP - 1;

     *result = 0;

     for (i = 0; BYTES_IN_IP > i; ++i,--exponent)
     {
         *result += bytes[i] * pow(ASCII,exponent);
     }
 }

/* converts a given size_t into a char - used to fix back the return value of
   trie functions to */
 static void _SizeTToChar(dhcp_t *dhcp, unsigned char *dest, size_t num)
 {
     size_t mask = ASCII - 1;
     size_t i = 0;

     num |= dhcp->subnet_mask;

     for (i = 0; i < BYTES_IN_IP; ++i)
     {
         dest[BYTES_IN_IP - 1 - i] = (num & mask);
         num >>= (size_t)CHAR_BIT;
     }
 }

/* checks whether the given request is belong to the relevant subnet */
 static int _IsInSubnet(dhcp_t *dhcp, size_t to_insert)
 {
     size_t non_masked_bits = BITS_IN_IP - dhcp->num_of_bits_in_mask;
     size_t subnet_mask = 0;

     subnet_mask = (dhcp->subnet_mask >> non_masked_bits << non_masked_bits);
     to_insert = (to_insert >> non_masked_bits << non_masked_bits);

     return(subnet_mask == to_insert);
 }
 /*---------------------------------------------------------------------------*/
