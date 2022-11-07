
/********************************************************************
*   File Name:   Client.h
*   Description: This file defines the class of client, which implements functions as below: 
*                1. Initialize the essential information of socket
                 2. Create the client socket based on TCP protocol
                 3. Bind and connect the server
                 4. Send the message to server every second
                 5. Recerive the repsonse from server, print it out
                 6. Apply multi-threads to deal with send/receive
*   Init Date: 2020/11/05
*********************************************************************/

#ifndef TCPSERVERCLIENTS_CLIENT_H
#define TCPSERVERCLIENTS_CLIENT_H


#include "CommonHead.h"

class Client {

public:

    Client(char* serverIP, int serverPort);

    void Connection();

    void Run();


private:
    struct sockaddr_in remote_addr;  // Socekt information stucture

    int nclient_Sockfd;  // Client Socket fd

    int ncountNo;  // The message sending to server is designed as progressively increasing number
    

};

/* Thread function for receing the response from server */
void* client_thrReceiveHandler(void *socketCon);  // socketCon input is Client Socket fd



#endif //TCPSERVERCLIENTS_CLIENT_H
