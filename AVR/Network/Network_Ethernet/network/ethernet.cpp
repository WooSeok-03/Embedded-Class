#include "ethernet.h"

void print_Ethernet_head(char *rx_buff)
{
  // Eternet Packet
  Serial.printf("============================================\n");
  Serial.printf("Destnation MAC Address : ");
  for(int i = 0; i < 6; i++) Serial.printf("%02x ", rx_buff[i+INDEX_ETHERNET_DESTINATION_MAC_ADDR]);
  Serial.printf("\n");

  Serial.printf("Source MAC Address :      ");
  for(int i = 0; i < 6; i++) Serial.printf("%02x ", rx_buff[i+INDEX_ETHERNET_SOURCE_MAC_ADDR]);
  Serial.printf("\n");

  Serial.printf("Type MAC Address :      ");
  for(int i = 0; i < 2; i++) Serial.printf("%02x ", rx_buff[i+INDEX_ETHERNET_TYPE]);
  Serial.printf("\n");
  Serial.printf("============================================\n");

}
