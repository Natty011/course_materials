#include <stdio.h>
#include <stdint.h>

#include "dhcp.h"
#include "bit_array.h"
#define CALSS_A_IP 8
#define CALSS_B_IP 16
#define CALSS_C_IP 24

void TestClassB(void);
void TestClassC(void);
void TestMixedClass(void);

void MakeRequest(dhcp_t *dhcp, unsigned char a, unsigned char b,
                 unsigned char c, unsigned char d);

void RequestAny(dhcp_t* dhcp);

void PrintIpArray(const unsigned char *ip);

int main()
{
   TestClassC();

   TestClassB();

   TestMixedClass();

   return 0;
}

void TestMixedClass(void)
{
   const unsigned char arr[BYTES_IN_IP] = {192, 168, 240, 0};
   dhcp_t *dhcp = DHCPCreate(arr, 20);
   if (!dhcp)
   {
      printf("Test Mixed Class:\nCreation FAILED...\n");
      return;
   }

   printf("\n\nTest Mixed Class - 20 bit subnet / 12 bit host id\n\n");
   printf("\tsubnet address : ");
   PrintIpArray(arr);
   putchar('\n');
   
   printf("free addrs = %lu\n\n", DHCPCountFree(dhcp));

   RequestAny(dhcp);
   RequestAny(dhcp);
   RequestAny(dhcp);
   RequestAny(dhcp);
   
   MakeRequest(dhcp, 192, 168, 241, 200);
   MakeRequest(dhcp, 192, 168, 250, 50);
   MakeRequest(dhcp, 192, 168, 250, 50);
   MakeRequest(dhcp, 192, 168, 255, 20);

   printf("\nrequest Network:\n");
   MakeRequest(dhcp, 192, 168, 240, 0);

   printf("\nrequest one before server :\n");
   MakeRequest(dhcp, 192, 168, 255, 253);

   printf("\nrequest Srver:\n");
   MakeRequest(dhcp, 192, 168, 255, 254);

   printf("\nrequest Broadcast:\n");
   MakeRequest(dhcp, 192, 168, 255, 255);

   DHCPDestroy(dhcp);
   dhcp = NULL;
}

void TestClassB(void)
{
   const unsigned char arr[BYTES_IN_IP] = {130, 150, 0, 0};

   dhcp_t *dhcp = DHCPCreate(arr, CALSS_B_IP);
   if (!dhcp)
   {
      printf("Test Class B:\nCreation FAILED...\n");
      return;
   }

   printf("\n\nTest Class B - 16 bit subnet / 16 bit host id\n\n");
   printf("\tsubnet address : ");
   PrintIpArray(arr);
   putchar('\n');

   printf("free addrs = %lu\n\n", DHCPCountFree(dhcp));

   RequestAny(dhcp);
   RequestAny(dhcp);
   RequestAny(dhcp);
   RequestAny(dhcp);
   
   MakeRequest(dhcp, 130, 150, 12, 230);
   MakeRequest(dhcp, 192, 150, 50, 20);
   MakeRequest(dhcp, 192, 150, 50, 20);

   printf("\nrequest one before server :\n");
   MakeRequest(dhcp, 192, 168, 255, 253);

   printf("\nrequest Srver:\n");
   MakeRequest(dhcp, 192, 168, 255, 254);

   printf("\nrequest Broadcast:\n");
   MakeRequest(dhcp, 192, 168, 255, 255);


   DHCPDestroy(dhcp);
   dhcp = NULL;
}

void TestClassC(void)
{
   const unsigned char arr[BYTES_IN_IP] = {192, 168, 1, 0};

   dhcp_t *dhcp = DHCPCreate(arr, CALSS_C_IP);
   if (!dhcp)
   {
      printf("Test Class C:\nCreation FAILED...\n");
      return;
   }

   printf("\n\nTest Class C - 24 bit subnet / 8 bit host id\n\n");
   printf("\tsubnet address : ");
   PrintIpArray(arr);
   putchar('\n');

   printf("free addrs = %lu\n\n", DHCPCountFree(dhcp));

   RequestAny(dhcp);
   RequestAny(dhcp);
   RequestAny(dhcp);
   RequestAny(dhcp);

   MakeRequest(dhcp, 192, 168, 1, 230);
   MakeRequest(dhcp, 192, 168, 1, 230);

   printf("\nrequest one before server :\n");
   MakeRequest(dhcp, 192, 168, 1, 253);

   printf("\nrequest Srver:\n");
   MakeRequest(dhcp, 192, 168, 1, 254);

   printf("\nrequest Broadcast:\n");
   MakeRequest(dhcp, 192, 168, 1, 255);


   DHCPDestroy(dhcp);
   dhcp = NULL;
}

void MakeRequest(dhcp_t *dhcp, unsigned char a, unsigned char b,
                 unsigned char c, unsigned char d)
{
   int res = 0;
   unsigned char request[BYTES_IN_IP] = {0};
   unsigned char ret_arr[BYTES_IN_IP] = {0};

   request[0] = a;
   request[1] = b;
   request[2] = c;
   request[3] = d;

   
   res = DHCPAllocateIP(dhcp, request, ret_arr);

   printf("request  ip : ");
   PrintIpArray(request);
   printf("Allocate %s\n", res == 0 ? "SUCCESS" : "FAIL");
   printf("retruned ip : ");
   PrintIpArray(ret_arr);
   printf("free addrs = %lu\n\n", DHCPCountFree(dhcp));
}

void RequestAny(dhcp_t* dhcp)
{
   int res = 0;
   unsigned char ret_arr[BYTES_IN_IP] = {0};

 
   
   res = DHCPAllocateIP(dhcp, NULL, ret_arr);

   printf("request  ip : ANY\n");
   printf("Allocate %s\n", res == 0 ? "SUCCESS" : "FAIL");
   printf("retruned ip : ");
   PrintIpArray(ret_arr);
   printf("free addrs = %lu\n\n", DHCPCountFree(dhcp));
}

void PrintIpArray(const unsigned char *ip)
{
   uint8_t i = 0;
   printf("%u", ip[i]);
   for (i = 1; i < BYTES_IN_IP; ++i)
   {
      printf(".%u", ip[i]);
   }
   putchar('\n');
}