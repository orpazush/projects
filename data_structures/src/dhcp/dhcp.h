/******************************************************************************
 *                      code by : Orpaz Houta                                 *
 *                      review by : Alex Sevostyanov                          *
 *                      coding date - 11-06-2020                              *
 ******************************************************************************/

#ifndef __DHCP_H__
#define __DHCP_H__

typedef struct dhcp dhcp_t;

typedef enum dhcp_status
{
    DHCP_STATUS_OK,
    DHCP_STATUS_FAILURE,
    DHCP_STATUS_DOUBLE_FREE_FAILURE
} dhcp_status_t;

#define BYTES_IN_IP (4)

/*****************************************************************************
* Function: DHCPCreate                                                       *
* -------------------------------------------------------------------------- *
* The function creates a new DHCP & initiates it with 3 preserved addresses  *       .
*                                                                            *
* subnet_ip[BYTES_IN_IP]: const unsigned char, will be used to set the       *
*                         network prefix.                                    *
* size_t num_bits_in_subnet - the number of bits belonging the network (not  *
*                             include the private host identifier)           *
*                                                                            *
* Return: dhcp_t *, success - pointer to the new DHCP.                       *
*                   failure - NULL In case of allocation failure;            *
*                                                                            *
* Time complexity  - O(1)                                                    *
 *****************************************************************************/
dhcp_t *DHCPCreate(const unsigned char subnet_ip[BYTES_IN_IP],
				   size_t num_bits_in_subnet);

/*****************************************************************************
* Function: DHCPDestroy                                                      *
* -------------------------------------------------------------------------- *
* The function frees all the previously allocated memory for the DHCP.       *
* NOTE - Calling the function with a NULL pointer has no effect.             *
*                                                                            *
* dhcp, dhcp_t *, pointer to the DHCP.                                       *
*                                                                            *
* Time complexity  - O(n)                                                    *
*                                                                            *
* Return value: none.                                                        *
 *****************************************************************************/
void DHCPDestroy(dhcp_t *dhcp);

/*****************************************************************************
* Function: DHCPAllocateIP                                                   *
* -------------------------------------------------------------------------- *
* The function receives an ip address and checks whether the requested ip    *
* can be allocated. In case the requested ip is already occupied, or the     *
* requested ip was not specified, the function allocates the smallest        *
* address available (that is bigger or equal to the requested ip).           *
* NOTE - Sending the function an ip address belonging to a different subnet  *
*        will cause undefined behaviour.                                     *
*      - sending 'dhcp' with no available addresses will cause undefined     *
*        behaviour. it possible to check this case with DHCPFreeIP()         *
*                                                                            *
* dhcp, dhcp_t *, pointer to the DHCP.                                       *
* requested_ip[BYTES_IN_IP], const unsigned char - preferred ip address      *
* result_ip[BYTES_IN_IP], unsigned char - the allocated ip address.          *
*                                                                            *
* Return: dhcp_status_t, success - DHCP_STATUS_OK.                           *
*                        failure - DHCP_STATUS_FAILURE if allocation failed; *
*                                  or 'dhcp' has no available addresses      *
*                                                                            *
* Time complexity - O(log(n))                                                *
 ****************************************************************************/
dhcp_status_t  DHCPAllocateIP(dhcp_t *dhcp,
			   const unsigned char requested_ip[BYTES_IN_IP],
			   unsigned char result_ip[BYTES_IN_IP]);

/*****************************************************************************
* Function: DHCPFreeIP                                                       *
* -------------------------------------------------------------------------- *
* The function frees a given ip address.                                     *
* This effectively increases the number of available ip addresses in the DHCP.
* NOTE - Sending the function an ip address belonging to a different subnet  *
*        will cause undefined behaviour.                                     *
*                                                                            *
* dhcp: dhcp_t *, pointer to the DHCP.                                       *
* ip_to_free[BYTES_IN_IP]: const unsigned char, the ip address to free       *
*                                                                            *
* Return: dhcp_status_t, success - DHCP_STATUS_OK.                           *
*                        failure - DHCP_STATUS_DOUBLE_FREE_FAILURE if the    *
*                                  given address was already free            *
*                                                                            *
* Time complexity - O(log(n))                                                *
 *****************************************************************************/
 dhcp_status_t DHCPFreeIP(dhcp_t *dhcp, const
                          unsigned char ip_to_free[BYTES_IN_IP]);

 /****************************************************************************
 * Function: DHCPCountFree                                                   *
 * --------------------------------------------------------------------------*
 * The function counts the number of available ip addresses for allocation.  *
 *                                                                           *
 * dhcp: dhcp_t *, pointer to the DHCP.                                      *
 *                                                                           *
 * Returns: size_t, the number of available ip addresses for allocation.     *
 *                                                                           *
 * Time complexity - O(1)                                                    *
 ****************************************************************************/
size_t DHCPCountFree(const dhcp_t *dhcp);


#endif /* ifdef __DHCP_H__ */
