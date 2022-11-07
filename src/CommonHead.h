

/********************************************************************
*   File Name:   CommonHead.h
*   Description: This file is used to define the common macros and structures
*   Init Date: 2020/11/05
*********************************************************************/

#ifndef TCPSERVERCLIENTS_COMMONHEAD_H
#define TCPSERVERCLIENTS_COMMONHEAD_H


#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <mutex>

#include <sys/select.h>
#include <sys/ioctl.h>
#include <sys/time.h>

#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

#define SERVER_IP "127.0.0.1"            // Define server IP, 127.0.0.1 is just for local test

#define SERVER_PORT 8080                // Define server port

#define HANDSHARK_MSG "Hello,Client!\n"  // Send the message when the server connects with clients successfully

#define MAXCLIENTNUM 100                 // Define the maximum clients connected with server

#define MAXFAILEDNUM 2000                // Define the maximum number of failed to send message to server

#define MAXSENTMSGCOUNT 100000           // Maxmum number of the sent message count

/* Socekt information stucture used to record clients' information */
typedef struct TCPSOCKETINFO{
    int socketCon;                  // Socket descriptor
    char *ipaddr;                   // Client's IP address
    uint16_t port;                  // Client's port
}_TCPSOCKETINFO;



#endif //TCPSERVERCLIENTS_COMMONHEAD_H
