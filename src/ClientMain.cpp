
/********************************************************************
*   File Name:   ClientMain.h
*   Description: The main function file for client side, which depends on Client.h/cpp, CommonHead.h
*                There are two modes to start the client execution:
*                  1. Commond line mode:  ./TCPClient ServerIP ServerPort, E.g ./TCPClient 127.0.0.1 18888       
*                  2. Online input IP/Port mode: 1) ./TCPClient; 2) Follow the guide in terminal to input ServerIP and ServerPort 
*   Init Date: 2020/11/05
*********************************************************************/

#include "Client.h"

using namespace std;

int main(int argc, char *argv[])  
{

    char serverIP[BUFSIZ];   
    int  serverPort;

    if(argc == 3){          //If ServerIP and ServerPort are input as commond line, go to this condition

        cout << "Command Line Option Mode" << endl;

        sprintf(serverIP,"%s",argv[1]);
        serverPort = atoi(argv[2]);
    }
    else {                 // Else, follow the guide to input ServerIP and ServerPort online

        cout << "Default Option Mode" << endl;

        sprintf(serverIP,"%s",SERVER_IP);
        serverPort = SERVER_PORT;
    }
    
    Client clientApp(serverIP,serverPort); // Initialize the class object, and create the socket

    clientApp.Connection();  // Call this function to bind the socket to connect the server
    clientApp.Run();  // Call this function to send the message to server every second, and receive the response from server, print it out.
   
    return 1;
}