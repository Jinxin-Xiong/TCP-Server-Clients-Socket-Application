
/********************************************************************
*   File Name:   ServerMain.h
*   Description: The main function file for server side, which depends on Server.h/cpp, CommonHead.h
*                1. The listen port is set from the macro "SERVER_PORT" in CommonHead.h 
*                2. Call the server class function, complete the communications with multi-clients
*   Init Date: 2020/11/05
*********************************************************************/

#include "Server.h"

int main()
{

    Server serverApp(SERVER_PORT); // Initialize the class object and create the socket


    serverApp.Bind();  // Bind the socket with the target port
   
    serverApp.Listen(); // Set the socket as listen mode, ready to accept the request from client
   
    serverApp.Run();   // Accept and build the communication with multi-clients,receive and echo back the messages sent by clients


    return 1;
}
