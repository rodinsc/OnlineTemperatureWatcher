#include <EtherCard.h>
#include <dht11.h>

#define DELAY_SECONDS 30  //The delay between each post request in seconds.
#define DHT11Pin 4  //Defining DHT 11 PIN

const char host[] PROGMEM = "URL";  //Host IP Address or domain

static byte macaddr[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };  //MAC address of the ethernet card. Must be unique in your network.

byte Ethernet::buffer[700]; //The buffer

dht11 DHT11;  //DHT 11
Stash stash;  //Stash (Used on POST request)
uint32_t timer; //Timer, used for interval.

void postTemperature(int temp)
{
  byte sd = stash.create();
  stash.print("temp=");
  stash.print(temp);
  stash.save();
  
  Stash::prepare(PSTR("POST /temperature HTTP/1.1" "\r\n"
                      "Host: $F" "\r\n"
                      "Content-Length: $D" "\r\n"
                      "Content-Type: application/x-www-form-urlencoded" "\r\n"
                      "\r\n"
                      "$H"),
                 host, stash.size(), sd);
  ether.tcpSend();
}

void setup() {
  Serial.begin(4800);
  
  if(ether.begin(sizeof Ethernet::buffer, macaddr, SS) == 0)
  {
    Serial.println(F("Failed to start Ethernet module."));
  }
  if (!ether.dhcpSetup())
  {
    Serial.println(F("DHCP configuration failed."));
  }
  else
  {
    Serial.println(F("DHCP successfully configured."));
  }

  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);
  ether.printIp("DNS: ", ether.dnsip);

  if (!ether.dnsLookup(host))
  {
    Serial.println(F("DNS lookup failed for the host."));
  }
  else
  {
    Serial.println(F("DNS lookup success for the host."));
  }
  
  ether.printIp("SRV: ", ether.hisip);

  DHT11.read(DHT11Pin);
}

void loop() {
  ether.packetLoop(ether.packetReceive());
  if(millis() > timer)
  {
    timer = millis() + (DELAY_SECONDS * 1000);
    postTemperature(DHT11.temperature);
    Serial.println(F("Data update sent."));
  }
}
