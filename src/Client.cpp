/********************************************************************
*   File Name:   Client.cpp
*   Description: This file implements the class function of client,
*                Multi-Thread is applied to deal with send/receive 
*   Init Date: 2020/11/05
*********************************************************************/


#include "Client.h"

using namespace std;

/*****   Initialize the network info of target server   *****/
Client::Client(char* serverIP, int serverPort){
    
    bzero(&remote_addr,sizeof(struct sockaddr_in));     // Initialize the data

	remote_addr.sin_family = AF_INET;                       // Set up IP communication
	remote_addr.sin_addr.s_addr = inet_addr(serverIP);      // Set up server IP
	remote_addr.sin_port = htons(serverPort);               // Set up server Port

    ncountNo = 0;
	
	/* Create the client socket -- TCP protocol */
	if((nclient_Sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){ 

        // If creating socket fails, exit.
		perror("socket error");

        close(nclient_Sockfd);
		exit(1);
	}
    
}

/*****   Bind and connect the target server   *****/
void Client::Connection(){

	if(connect(nclient_Sockfd, (struct sockaddr *)&remote_addr, sizeof(struct sockaddr)) < 0){
		
        // If connecting the server fails, exit.
        perror("connect error");

        close(nclient_Sockfd);
		exit(1);
	}

    /* Print the info of successful connection */
    cout << "Connecting Server Successfuly!" << endl; 
}

/*****  Send the message to server every second            *****/
/*****  Create the child threads to recerive the repsonse from server, and print it out    *****/
void Client::Run(){

    /* Create the child thread to receive the respond from server*/
    pthread_t thrReceive;
    pthread_create(&thrReceive,NULL,client_thrReceiveHandler,&nclient_Sockfd);


    char bufferSend[BUFSIZ];
    int msg_Length = 0, failed_count = 0;

    /*  send the message to server periodically  */
    while(1){

        /*  If the number of failed sending message to server is bigger than defined maximum, exit!  */
        if( failed_count > MAXFAILEDNUM ){ 
            
            cout << "Too many fails to send msg to Server,exit!" << endl; 
            break; 
        }

        memset(bufferSend,0,BUFSIZ);
        msg_Length = 0;

        /* Increase or Reset the sent message count */
        ncountNo++; 
        if(ncountNo > MAXSENTMSGCOUNT)  ncountNo = 0;  // If the sent message count is bigger than defined nunber, reset it 

        sprintf(bufferSend,"%d",ncountNo);

        /* Call the function to send the message to server */
		msg_Length = send(nclient_Sockfd, bufferSend, strlen(bufferSend), 0);


        if(msg_Length > 0){

            //If successful to send message to Server, print it, and reset failed sent times
            cout << "Send msg to Server Successfully" << endl; 
            failed_count = 0; 
        }

		else{

            //If failed to send message to Server, print it, and increase failed sent times
            cout << "Failed to send msg to Server" << endl; 
            failed_count++;  
        }

        sleep(1);  // wait 1 sencond to resend message

    }

    /* If jump out the circle, close the client socket */
	close(nclient_Sockfd);
}

/********************************************************************
*   Thread Function Name: void *client_thrAcceptHandler(void *socketListen)
*   Description: Recerive the repsonse from the server, and print it out
*   Called By: Client.cpp[Run]
*   Input: socketCon -> the socket fd for this client
*********************************************************************/
void* client_thrReceiveHandler(void *socketCon){

    char bufferRecv[BUFSIZ];                
    int receiveMsg_Length;
    int _socketCon;

    /*  Receive and print out the response from server periodically  */
    while(1){

			memset(bufferRecv, 0, BUFSIZ);
            _socketCon = *((int*)socketCon);

            /* Receive the message from server*/
            receiveMsg_Length = recv(_socketCon, bufferRecv, BUFSIZ, 0);

            if(receiveMsg_Length == 0){ // If the server is shutdown unnormally, exit

               cout << "Server Shutdown Unnormally" << endl;
               exit(1);
            }
            else if(receiveMsg_Length < 0){ // If failed to receive the response from server, quit the circle

                cout << "Failed to receive the server's response" << endl;
                break;
            }

            /*  Receive the response successfully, print it out  */
            bufferRecv[receiveMsg_Length] = '\0';
			printf("Recive from server response: %s\n", bufferRecv);
            
			usleep(100000);
		}
}


