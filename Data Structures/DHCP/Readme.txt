/*
    DHCP API to support DHCP server application for creating, destroying, receiving and releasing IP addresses to hosts in the network.

    Functionality includes:
        - GetAddress: returns a new IP address to assign to host
        - ReleaseAddress: releases a given IP address and returns it to the   
                          pool
        - RenewAddress: TBD - renews a lease of IP address of a client 
*/

/**********************************************************************/

dhcp implemintation consist 3 files:

dhcp.h: a header file
dhcp.c: functions implemintation
dhcp_test.c for a functionality testing

/**********************************************************************/
