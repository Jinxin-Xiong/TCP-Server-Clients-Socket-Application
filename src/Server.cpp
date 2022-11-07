
/********************************************************************
*   File Name:   Server.cpp
*   Description: This file implements the class function of server,
*                Multi-Thread is applied to deal with recv/echo back 
*   Init Date: 2020/11/05
*********************************************************************/


#include "Server.h"

using namespace std;

mutex mutexLocker;  // Apply the mutex locker to protect shared data accessed by differnt threads

/*  Record the clients' information into array  */
struct TCPSOCKETINFO arrConSocket[MAXCLIENTNUM]; // clients' information array
int  conClientCount;                 // the number of current connected clients

/*****   Initialize the TCP socket for the server   *****/                
Server::Server(int server_port){

    /* Create TCP Socket */
    nserver_Socketfd = socket(AF_INET,SOCK_STREAM, 0);

    if( nserver_Socketfd< 0){  // If failed to creating, exit

        cout << "Failed to Create Socket!" <<endl;
        exit(1);
    }
    else{ cout << "Create Socket Successfully !" << endl; }

    bzero(&server_addr,sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY); // Address is set as INADDR_ANY 
    server_addr.sin_port = htons(server_port);  // Set up the port that would be listened
}

/*****   Bind the target port   *****/
void Server::Bind(){

    if(bind(nserver_Socketfd, (struct sockaddr*)& server_addr, sizeof(server_addr)) != 0){

        cout << "Server Bind Failed!" << endl;

        close(nserver_Socketfd);
        exit(1);
    }

    cout << "Bind Successful!" << endl;
}

/*****   Listen the target port   *****/
void Server::Listen(int queue_len){

    if(listen(nserver_Socketfd, queue_len) != 0){

        cout << "Server Listen Failed!" << endl;

        close(nserver_Socketfd); 
        exit(1);
    }

    cout << "Listen Successful!" << endl;
}

/*****   Call the thread function, complete the accept/connect/receive/echo back tasks   *****/
/*****   between the server and multi-clients   *****/
void Server::Run(){    

    server_thrAcceptHandler(&nserver_Socketfd);
}

/********************************************************************
*   Function Name: void *server_thrAcceptHandler(void *socketListen)
*   Description: listen and accpet the connecting requests from clients, achieve the network info of the connecting clients, create the child threads for the connecting clients
*   Called By: Server.cpp[Run]
*   Input: socketListen -> the socket fd for server listen
*********************************************************************/
void* server_thrAcceptHandler(void* socketListen){
    
    memset(arrConSocket,0,MAXCLIENTNUM*sizeof(_TCPSOCKETINFO));
    conClientCount = 0;

    int sockaddr_in_size = sizeof(struct sockaddr_in);
    struct sockaddr_in client_addr;
    int _socketListen = *((int*)socketListen);
    
    int socketCon = 0;
    TCPSOCKETINFO socketInfo;

    pthread_t thrReceive;

    /*  Accept the connecting requests from the clients, maintain the clients' info array, create threads to receive messages    */
    while(1){        

        if(conClientCount >= MAXCLIENTNUM){

            cout << "The connected clients exceeds the maximum, not accept new connecting request any more! " << endl;
           
            usleep(500000);
            continue;
        }

        /* Accept the connecting requests */
        socketCon = accept(_socketListen, (struct sockaddr *)(&client_addr), (socklen_t *)(&sockaddr_in_size));
        
        if(socketCon < 0){  // If failed to call accept function, retry it
            
            cout << "Failed to call accept(), continue to try" << endl;
            continue;
        }
        
        else{

            cout << "Connected " <<  inet_ntoa(client_addr.sin_addr) << ": " << client_addr.sin_port << endl;
        }

        cout << "Client socket: " << socketCon << endl;

        /* Get the network info of the new connected client */        
        socketInfo.socketCon = socketCon;
        socketInfo.ipaddr = inet_ntoa(client_addr.sin_addr);
        socketInfo.port = client_addr.sin_port;

        /* Save the the network info of the new connected client to the array  */
        /* Apply the mutex locker to protect the shared array  */
        mutexLocker.lock();
        arrConSocket[conClientCount] = socketInfo;
        conClientCount++;
        mutexLocker.unlock();

        cout << "Current Number of users: " << conClientCount << endl;

        /* Create a child thread for the new connected client, and receive/echo back the messages from this client  */
        pthread_create(&thrReceive, NULL, server_thrReceiveHandler, &socketInfo);
       

        /* Sleep 0.5 second, and re-detect new connecting clients */
        usleep(500000);
    }
}



/********************************************************************
*   Thread Function Name: void *fun_thrReceiveHandler(void *socketInfo)
*   Description: Receive the messages for the connected clients cyclically, and echo back to them 
*   Called By: Server.c[server_thrAcceptHandler]
*   Input: socketInfo -> the network info of the connected client
*********************************************************************/
void* server_thrReceiveHandler(void* socketInfo){
    int buffer_length;
    int i,j;
    char buffer[BUFSIZ];
    TCPSOCKETINFO _socketInfo = *((TCPSOCKETINFO *)socketInfo);

    /* Send the hand shaking message to the new cilent */
    send(_socketInfo.socketCon, HANDSHARK_MSG, sizeof(HANDSHARK_MSG), 0);

    /* Receive the messages from the client cyclically */
    while(1){

        // Clear the receiving buffer for the message
        bzero(&buffer,sizeof(buffer));
        buffer_length = 0;
        
        // Call the revv function to receive the messages sent by the client
        cout << "Receiving messages from client " << _socketInfo.ipaddr << endl;
        
        buffer_length = recv(_socketInfo.socketCon, buffer, BUFSIZ, 0);

        if(buffer_length == 0){  // The client is taken as quit status
              
            // Find the position in the array
            for(j = 0; j < conClientCount; j++){

                if(arrConSocket[j].socketCon == _socketInfo.socketCon){
                    break;
                }
            }

            /* Apply the mutex locker to protect the shared array  */
            mutexLocker.lock();

            // Remove this client's information from the array as this client quits
            for(i = j; i < conClientCount-1; i++){

                arrConSocket[i] = arrConSocket[i+1];
            }

            conClientCount --;

            mutexLocker.unlock();;

            break;
        }

        else if(buffer_length < 0){  // If failed to call recv() function

            cout << "Fail to call recv()" << endl;
            break;
        }

        /*  Receive the message from client successfully, print it out  */
        buffer[buffer_length] = '\0';

        cout << _socketInfo.ipaddr << ": " << _socketInfo.port << " said: " << buffer << endl;

        /*  Echo back the message to the corresponding client  */
        send(_socketInfo.socketCon,buffer,buffer_length,0);

        usleep(200000);
    }

    cout << _socketInfo.ipaddr << ": " << _socketInfo.port << " is closed" << endl;

    cout << "Current Number of users: " << conClientCount << endl;
    
    close(_socketInfo.socketCon);
}


