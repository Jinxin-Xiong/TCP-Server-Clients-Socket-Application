# TCP-Server-Clients-Socket-Application


## Introduction
We Implemet an application in C++ on Linux to create the connections between multiple clients and server using TCP 

![Supported Platforms](https://img.shields.io/badge/platform-Linux-red.svg)
[![Build Status]()]()
[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/Jinxin-Xiong/TCP-Server-Clients-Socket-Application/blob/main/LICENSE)


## Description of The Features

* Server Side:

  ​	1. Create the server socket based on TCP.
  ​	2. Listening on a target port (Default: 8080).
  ​	3. Support to accept multiple clients.
  ​	4. Real-time receive the clients' messages and echo back to the responding clients in time.
  ​	5. Implement this application in C/C++ on Linux, and multi-thread is applied.
  
* CLient Side:

  ​	1. Two options to start the client service (Default option and command line option).
  ​	2. Send the message to the server periodically (one time each second).
  ​	3. Receive the server's response in time, and print the response message on the terminal.
  ​	4. The main thread is used to deal with "send task", the child thread is used to deal with "receive/print task".
  ​	5. Implement this application in C/C++ on Linux.

## Build and Run

* build

```
git clone https://github.com/Jinxin-Xiong/TCP-Server-Clients-Socket-Application.git
cd TCP-Server-Clients-Socket-Application
sudo make
```

* Service would be generated in build directory

```
cd build
```

* Run server before cliens
* `Ctrl + c` to interrupt blocking server and client process


### Configure some common parameters in CommonHead.h []

* Set server IP, 127.0.0.1 is just for local test

```
 #define SERVER_IP "127.0.0.1"   
 ```
 
 * Set server port

```
 #define SERVER_PORT 8080  
 ```
 
 * Set the maximum number of connected clients

```
 #define MAXCLIENTNUM 100 
 ```


### Run Server TCP Service 

* Run server service on the server side:

```
cd build
./TCPServerClients_server
```
​	The status after you start the server service (Listen to the target port)：

![The status in terminal](./img/1.png)


### Run Client TCP Service 

* Run client in another shell

​	There are two options：
1) Default option: The Server IP and Port are default set in CommonHead.h;   
2) Command Line option: Type Server IP and Port as commond line
```
/*****  Option 1: Default option (Default IP: 127.0.0.1; Default Port: 8080)    *****/
./TCPServerClients_client
```
```
/*****  Option 2: Command Line option    *****/
./TCPServerClients_client IP Port (ex. ./TCPServerClients_client 127.0.0.1 8080) 
```


### Demonstration


### Test Result
