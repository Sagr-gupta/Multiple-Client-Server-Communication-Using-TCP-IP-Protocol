INTRODUCTION - This is a simple TCP client server application that describes the communication between multiple clients and a server using fork. This project can support upto 4 clients at a time. It consist of four files of which testServer.cpp & testcClient.cpp  is used for connection establishment between a single client and server while server.cpp & client.cpp is used for connection establishment between multiple clients and a server.
 
This project is mainly divided in two main actors:

       a) SERVER
	   
       1.  Using socket(), create TCP socket. 
       2.  Using bind(), bind the socket to server address.
       3.  Using listen(), put the server socket in a passive mode, where it waits for the client to approach the server to   make a connection.
       4.  Using accept(), connection is established between client and server, and they are ready to transfer data.
       5.  Go back to Step 3. 

       b) CLIENT
	   
	   1. Using socket(), create TCP socket.
       2. Using connect(), connect newly created client socket to server. 
 
 
 
HOW TO RUN - 
        For establishing a connection between client and server, first compile server.cpp  in one terminal and provide port number(e.g 2000) and now it waits for the client to approach. Now in other terminal compile client.cpp and provide ipaddress(localhost) and port number (2000). A connection will be established between client and server. Now in another terminal again compile client.cpp and after that you can exchnage information with both the client by a server simultaneously. 
		
TECH STACK USED - 
   C++ , Socket Programming and Computer Networks.
   Using :
- <sys/types.h>----//Defines a collection of typedef symbols and structures
- <sys/socket.h>---//Declarations of socket constants, types, and functions
- <netinet/in.h>---//Definitions for the internet protocol family
- <arpa/inet.h>----//Definitions for internet operations
- <netdb.h>--------//Definitions for network database operations
- <unistd.h>-------//Definitions for standard symbolic constants and types

IMPORTANT LOGIC USED -

    1. This is the flow of code that we used for establishment of connection between clients and server.
    

    
