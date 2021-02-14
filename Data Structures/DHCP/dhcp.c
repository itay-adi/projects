#include <stdlib.h> /* malloc, free*/
#include <arpa/inet.h> /* inet_pton */
#include <assert.h> /* assert */

#include "dhcp.h"

/******************************************************************************/

typedef struct dhcp_node dhcp_node_t;

struct dhcp_node
{
    dhcp_node_t *children[2];
    char status[2];
};

struct dhcp
{
    uint32_t net_address;
    unsigned int mask;
    dhcp_node_t *root;
};

#define MAX_BITS 32

/***************************Recursice functions********************************/

dhcp_node_t* Rec_NodeCreate(char max_level, char current_level, int side);
void Rec_Destory(dhcp_node_t *node);
dhcp_node_t* Rec_GetAddress(dhcp_t *dhcp, dhcp_node_t* node, uint32_t* ip_address, char current_level);
dhcp_node_t* Rec_ReleaseAddress(dhcp_node_t* node, uint32_t ip_address, int current_level, int mask_size);

/***************************Assistance functions*******************************/

int IsNodeSideFull(dhcp_node_t* node, int side);
uint32_t BitArrMirror(uint32_t arr);
int BitArrIsOn(uint32_t arr, int index);

/******************************************************************************/

dhcp_t *DhcpCreate(const char *net_address, unsigned int mask_bits_size)
{
    dhcp_t *dhcp = NULL;
    char levels = MAX_BITS - mask_bits_size;
    
    /*creating the management struct*/
    dhcp = (dhcp_t *)malloc(sizeof(dhcp_t));

    if(NULL == dhcp)
    {
        return (NULL);
    }

    /*creating the root*/
    dhcp->root = (dhcp_node_t *)malloc(sizeof(dhcp_node_t));

    if(NULL == dhcp->root)
    {
        free(dhcp);

        return (NULL);
    }

    /*turns the net_adress string to an uint32_t*/
    if(!inet_pton(AF_INET, net_address, &dhcp->net_address))
    {
        free (dhcp->root);
        free (dhcp);
        
        return (NULL);
    }
    
    /*put the parameters*/

    /*creating the base children: 0000, 1110, 1111*/
    dhcp->root->children[0] = Rec_NodeCreate(levels, 1, 0);
    dhcp->root->children[1] = Rec_NodeCreate(levels, 1, 1);
    
    /*check if children creation was failed*/ 
    if(NULL == dhcp->root->children[0] || NULL == dhcp->root->children[1])
    {
        Rec_Destory(dhcp->root);
        free(dhcp);
        dhcp = NULL;

        return (NULL);
    }

    dhcp->root->status[0] = 0;
    dhcp->root->status[1] = 0;

    dhcp->mask = mask_bits_size;

    dhcp->net_address = BitArrMirror(dhcp->net_address);   

    return(dhcp);
}

/************************************************************/

dhcp_node_t* Rec_NodeCreate(char max_level, char current_level, int side)
{
    dhcp_node_t *node = NULL;

    /*checking if we passed the height limit*/
    if(max_level < current_level)
    {
        return (NULL);
    }

    node  = (dhcp_node_t *)malloc(sizeof(dhcp_node_t));
    
    /*checking if allocation was failed*/
    if(NULL == node)
    {
        return (NULL);
    }

    node->children[!side] = NULL;
    
    /*mark if we have space left for children: 1 no space, 0 free space*/
    if(current_level == max_level)
    {
        node->status[0] = 1;
        node->status[1] = 1;
    }

    else
    {
        node->status[0] = 0;
        node->status[1] = 0;
    }

    if (current_level == max_level - 1)
    {
        node->status[side] = 1;

        if (1 == side)
        {
            node->status[0] = 1;
        }
    }
    
    /*creating the needed child*/
    node->children[side] = Rec_NodeCreate(max_level, current_level + 1, side);

    /*check for failed allocation*/
    if(NULL == node->children[side] && current_level != max_level)
    {
        free(node);

        return (NULL);
    }

    /*creating the 2nd from right node*/
    if (1 == side && current_level == max_level - 1)
    {
        node->children[0] = Rec_NodeCreate(max_level, current_level + 1, 0);
    }

    return (node);
}

/******************************************************************************/

void DhcpDestroy(dhcp_t *dhcp)
{
    assert(dhcp);

    Rec_Destory(dhcp->root);

    free(dhcp);

    dhcp = NULL;
}

/************************************************************/

void Rec_Destory(dhcp_node_t *node)
{
    if (node->children[0])
    {
        Rec_Destory(node->children[0]);
        node->children[0] = NULL;
    }

    if (node->children[1])
    {
        Rec_Destory(node->children[1]);
        node->children[1] = NULL;
    }

    free(node);
    node = NULL;
}

/******************************************************************************/

int DhcpGetAddress(dhcp_t *dhcp, uint32_t* ip_address)
{
    char max_levels = 0;

    assert(dhcp);

    max_levels = MAX_BITS - dhcp->mask;

    *ip_address = (dhcp->net_address) >> max_levels;

    /*checking if the tree is already full*/
    if(IsNodeSideFull(dhcp->root, 0) && IsNodeSideFull(dhcp->root, 1))
    {
        return (1);
    }

    if (Rec_GetAddress(dhcp, dhcp->root, ip_address, 0) == NULL)
    {
        return (1);
    }

    *ip_address = BitArrMirror(*ip_address);

    return (0);
}

/************************************************************/

dhcp_node_t* Rec_GetAddress(dhcp_t *dhcp, dhcp_node_t* node, uint32_t* ip_address, char current_level)
{
    char max_levels = MAX_BITS - dhcp->mask;

    if(current_level != max_levels)
    {
        *ip_address <<= 1;
    }

    if (current_level > max_levels)
    {
        return (NULL);
    }

    /*if we arrived to an empty node, we create it*/
    if (NULL == node)
    {
        node = (dhcp_node_t*)malloc(sizeof(dhcp_node_t));

        if (NULL == node)
        {
            return (NULL);
        }

        if(current_level == max_levels)
        {
            node->status[0] = 1;
            node->status[1] = 1;
        }

        else
        {
            node->status[0] = 0;
            node->status[1] = 0;
        }

        node->children[0] = NULL;
        node->children[1] = NULL;
    }

    /*recursice call for drilling*/
    if (node->status[0] == 0)
    {
        node->children[0] = Rec_GetAddress(dhcp, node->children[0], ip_address, current_level + 1);
        
        if(node->children[0] == NULL)
        {
            return (NULL);
        }
    }

    else if (node->status[1] == 0)
    {
        *ip_address |= 1;
        node->children[1] = Rec_GetAddress(dhcp, node->children[1], ip_address, current_level + 1);

        if(node->children[1] == NULL)
        {
            return (NULL);
        }
    }

    /*checking if the sides are full*/
    if (current_level < max_levels && IsNodeSideFull(node, 0) == 1)
    {
        node->status[0] = 1;
    }

    if (current_level < max_levels && IsNodeSideFull(node, 1) == 1)
    {
        node->status[1] = 1;
    }

    return (node);
}

/******************************************************************************/

void DhcpReleaseAddress(dhcp_t *dhcp, uint32_t ip_address)
{
    char max_levels = 0;
    uint32_t dhcp_address_range = 0;
    uint32_t user_request = 0;

    assert(dhcp);

    max_levels = MAX_BITS - dhcp->mask;

    /*check if the user gave us a valid ip_adress*/
    dhcp_address_range = dhcp->net_address >> max_levels;
    user_request = ip_address >> max_levels;

    if(dhcp_address_range == user_request)
    {
        Rec_ReleaseAddress(dhcp->root, ip_address, 0, max_levels);
    }
}

/************************************************************/

dhcp_node_t* Rec_ReleaseAddress(dhcp_node_t* node, uint32_t ip_address, int current_level, int mask_size)
{
    int side = BitArrIsOn(ip_address, mask_size - current_level);

    node->status[side] = 0;

    if(current_level == mask_size)
    {
        free(node);
        
        node = NULL;
    }

    else
    {
        if(node->children[side])
        {
            node->children[side] = Rec_ReleaseAddress(node->children[side], ip_address, current_level + 1, mask_size);
        }
    }

    return (node);
}

/******************************************************************************/

uint32_t BitArrMirror(uint32_t arr)
{
	/*Swaps groups of 16bit*/
	arr = ((arr & 0xFFFF0000) >> 16) | ((arr & 0x0000FFFF) << 16);

    /*Swaps groups of 8bit*/
    arr = ((arr & 0xFF00FF00) >> 8) | ((arr & 0x00FF00FF) << 8);

	return (arr);
}

/******************************************************************************/

int IsNodeSideFull(dhcp_node_t* node, int side)
{
    if(node->children[side] == NULL)
    {
        return (0);
    }

    else
    {
        return (node->children[side]->status[0] == 1 && 
                node->children[side]->status[1] == 1);
    }
}

/******************************************************************************/

int BitArrIsOn(uint32_t arr, int index)
{
	arr >>= (index - 1);
	
	return (arr & 1); 
}

/******************************************************************************/