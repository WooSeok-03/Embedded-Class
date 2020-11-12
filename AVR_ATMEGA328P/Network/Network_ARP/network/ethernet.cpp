#include "ethernet.h"

char rx_dst_mac[6];

void print_Ethernet_head(char *rx_buff)
{
  // Eternet Packet
  Serial.printf("============================================\n");
  Serial.printf("Destnation MAC Address : ");
  for(int i = 0; i < 6; i++) Serial.printf("%02x ", rx_buff[i+INDEX_ETHERNET_DESTINATION_MAC_ADDR]);
  Serial.printf("\n");

  Serial.printf("Source MAC Address :     ");
  for(int i = 0; i < 6; i++) Serial.printf("%02x ", rx_buff[i+INDEX_ETHERNET_SOURCE_MAC_ADDR]);
  Serial.printf("\n");

  Serial.printf("Type :                   ");
  for(int i = 0; i < 2; i++) Serial.printf("%02x ", rx_buff[i+INDEX_ETHERNET_TYPE]);
  Serial.printf("\n");
  Serial.printf("============================================\n");

}

int which_packet_type(char *rx_buff)
{
  if(rx_buff[0+INDEX_ETHERNET_TYPE] == 0x08 && rx_buff[1+INDEX_ETHERNET_TYPE] == 0x06) return ARP_PACKET;
  else if(rx_buff[0+INDEX_ETHERNET_TYPE] == 0x08 && rx_buff[1+INDEX_ETHERNET_TYPE] == 0x00) return IP_PACKET;
}

void parsing_Ethernet_head(char *rx_buff)
{
  for(int i = 0; i < 6; i++) rx_dst_mac[i] = rx_buff[i+INDEX_ETHERNET_SOURCE_MAC_ADDR];
}

void make_Ethernet_head(char *tx_buff, uint8_t *my_mac, int ethernet_type)
{
  for(int i = 0; i < 6; i++) tx_buff[i+INDEX_ETHERNET_DESTINATION_MAC_ADDR] = rx_dst_mac[i];
  for(int i = 0; i < 6; i++) tx_buff[i+INDEX_ETHERNET_SOURCE_MAC_ADDR] = my_mac[i];

  if(ethernet_type == ARP_PACKET)
  {
    tx_buff[0 + INDEX_ETHERNET_TYPE] == 0x08;
    tx_buff[1 + INDEX_ETHERNET_TYPE] == 0x06;
  }
  else if(ethernet_type == IP_PACKET)
  {
    tx_buff[0 + INDEX_ETHERNET_TYPE] == 0x08;
    tx_buff[1 + INDEX_ETHERNET_TYPE] == 0x00;
  }
}