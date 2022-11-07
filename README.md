# TCP-Server-Clients-Socket-Application


## Introduction
We Implemet an application in C++ on Linux to create the connections between multiple clients and server using TCP 

![Supported Platforms](https://img.shields.io/badge/platform-Linux-red.svg)
[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/Jinxin-Xiong/TCP-Server-Clients-Socket-Application/blob/main/LICENSE)


## Description of The Features

* Server Side:

  ​	1. Create the server socket based on TCP. 
  
  ​	2. Listening on a target port (Default: 8080). 
  
  ​	3. Support to accept multiple clients. 
  
  ​	4. Real-time receive the clients' messages and echo back to the responding clients in time. 
  
  ​	5. Implement this application in C/C++ on Linux, and multi-thread is applied. 
  
  
* Client Side:

  ​	1. Two options to start the client service (Default option and command line option).
  
  ​	2. Send the message to the server periodically (one time each second).
  
  ​	3. Receive the server's response in time, and print the response message on the terminal.
  
  ​	4. The main thread is used to deal with "send task", the child thread is used to deal with "receive/print task".
  
  ​	5. Implement this application in C/C++ on Linux.
  
  
  
## Code File Stucture

![All the files](https://github.com/Jinxin-Xiong/TCP-Server-Clients-Socket-Application/blob/main/img/Codefilescreenshot.png?raw=true)


## Code Style

![Code style](https://github.com/Jinxin-Xiong/TCP-Server-Clients-Socket-Application/blob/main/img/codestyle.png?raw=true) 


## Build and Run

### Build the programe

```
git clone https://github.com/Jinxin-Xiong/TCP-Server-Clients-Socket-Application.git
cd TCP-Server-Clients-Socket-Application
sudo make
```

![How to build](https://github.com/Jinxin-Xiong/TCP-Server-Clients-Socket-Application/blob/main/img/CompileScreenshot.png?raw=true)


* Service would be generated in parent directory

* Run server before cliens

* `Ctrl + c` to interrupt blocking server and client process

![The executables](https://github.com/Jinxin-Xiong/TCP-Server-Clients-Socket-Application/blob/main/img/Executablesscreenshot.png?raw=true)


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
./TCPServerClients_server
```
​	The status after you start the server service (Listen to the target port)：

![Listen to the port](https://github.com/Jinxin-Xiong/TCP-Server-Clients-Socket-Application/blob/main/img/Runserverscreenshot.png?raw=true)

![Receive and echo back clients' message](https://user-images.githubusercontent.com/64098916/200217221-2438aa0d-8a28-4795-8af4-6ace8a8e29f0.png)


### Run Client TCP Service 

* Run client on client side

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
![Communication with Server](![image](https://user-images.githubusercontent.com/64098916/200217023-aeb25728-e196-44f2-bd00-24719f131132.png)


## Demonstration

* Tips: Since there is only one desktop in working place, I just run one server terminal and six client terminals in the same computer (local network). But generally, this program can support much more than six clients

* In future, it would be necessary to test this program in the real server-multi client scenario: 

![One server - six clients](https://github.com/Jinxin-Xiong/TCP-Server-Clients-Socket-Application/blob/main/img/ServerMultiClientsDemo.png?raw=true)
