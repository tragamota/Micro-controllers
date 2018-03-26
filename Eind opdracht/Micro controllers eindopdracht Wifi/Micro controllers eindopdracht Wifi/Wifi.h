/*
 * Wifi.h
 *
 * Created: 14-3-2018 20:03:49
 *  Author: Ian
 */ 

void WifiInit(void);
void WifiConnectToAP(char *SSID, char *password);
void WifiTcpConnect(char *IP, int port);
void WifiTcpSendData(char *data, int size);
void WifiTcpReadData(char *rdata);
void WifiTcpClose(void);