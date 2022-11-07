
/********************************************************************
*   File Name:   Server.h
*   Description: This file defines the class of server, which implements functions as below: 
*                1. Initialize the essential information of socket
                 2. Create the server socket based on TCP protocol
                 3. Bind and listen the target port
                 4. Accept the connecting requests from multi-clients, build the connections with these clients
                 5. Apply multi-threads to receive/echo back the messages from multi-clients
*   Init Date: 2020/11/05
*********************************************************************/

#ifndef TCPSERVERCLIENTS_SERVER_H
#define TCPSERVERCLIENTS_SERVER_H


#include "CommonHead.h"

class Server {

public:
    Server(int port);

    void Bind();

    void Listen(int queue_len = 10);

    void Run();

private:
    struct sockaddr_in server_addr; // Socekt information stucture

    int nserver_Socketfd;  // Server Socket fd
};

/* Thread function for accect the connecting requests from clients */
void* server_thrAcceptHandler(void* socketListen);

/* Thread function for receive/echo back the messages from clients */
void* server_thrReceiveHandler(void *socketInfo);

#endif //TCPSERVERCLIENTS_SERVER_H
