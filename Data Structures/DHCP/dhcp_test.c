/***************************User's declarations********************************/

#include <stdio.h>
#include <arpa/inet.h>

#include "dhcp.h"

/************************Test function declarations****************************/

dhcp_t *DhcpCreateTest(const char *net_address, unsigned int mask_bits_size);
void DhcpDestroyTest(dhcp_t *dhcp);
void DhcpGetAddressTest(dhcp_t *dhcp, uint32_t* ip_address);
void DhcpReleaseAddressTest(dhcp_t *dhcp, uint32_t ip_address);

/********************************Test Cases************************************/

void TestCase(void);

/************************************Main**************************************/

int main(void)
{
    printf("------------------------------------\n");
    TestCase();
    printf("------------------------------------\n");

    return (0);
}

/************************Test function implemintations*************************/

dhcp_t *DhcpCreateTest(const char *net_address, unsigned int mask_bits_size)
{
    dhcp_t *dhcp = NULL;

    dhcp = DhcpCreate(net_address, mask_bits_size);

    if(NULL == dhcp)
    {
        printf("Create was failed.\n\n");
    }

    else
    {
        printf("Create success.\n\n");
    }
    
    return (dhcp);
}

/**********************************************************************/

void DhcpDestroyTest(dhcp_t *dhcp)
{
    DhcpDestroy(dhcp);

    printf("The DHCP was destroyed.\n\n");
}

/**********************************************************************/

void DhcpGetAddressTest(dhcp_t *dhcp, uint32_t* ip_address)
{
    char address_str[32];

    if(DhcpGetAddress(dhcp, ip_address))
    {
        printf("Get Address was failed.\n\n");
    }

    else
    {
        printf("Get Adress was success: ");
        inet_ntop(AF_INET, ip_address, address_str, INET_ADDRSTRLEN);
        printf("%s\n\n", address_str);
    }
}

/**********************************************************************/

void DhcpReleaseAddressTest(dhcp_t *dhcp, uint32_t ip_address)
{
    DhcpReleaseAddress(dhcp, ip_address);
    printf("IP was released.\n\n");
}

/******************************************************************************/

void TestCase(void)
{
    dhcp_t *dhcp = NULL;
    uint32_t container = 0;
    int i = 0;

    dhcp = DhcpCreateTest("255.255.255.0", 28);

    for(i = 0; i < 10; ++i)
    {
        DhcpGetAddressTest(dhcp, &container);
    }

    DhcpReleaseAddressTest(dhcp, 4294967042);

    DhcpGetAddressTest(dhcp, &container);

    DhcpDestroyTest(dhcp);
}

/******************************************************************************/