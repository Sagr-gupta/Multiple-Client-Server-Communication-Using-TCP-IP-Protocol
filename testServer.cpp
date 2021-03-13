#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        cerr<<"Missing port number.\n";
        exit(0);
    }
    int port = atoi(argv[1]);
    char message[1500];

    // Define a socketaddr_in struct for server socket (for socket listening)
    sockaddr_in serverSocket;
    bzero((char *)&serverSocket, sizeof(serverSocket));
    serverSocket.sin_family = AF_INET;
    serverSocket.sin_port = htons(port);
    serverSocket.sin_addr.s_addr = htonl(INADDR_ANY);

    // socket() for server socket
    // int socketID = socket(Family,Type,Protocol)
    int serverSocketID = socket(AF_INET, SOCK_STREAM,0);
    if(serverSocketID < 0 )
    {
        cerr<<"Not Successful\n";
        exit(0);
    }

    // bind() the socket to a port
    // int status = bind(socketID, &addressPort, sizeOfPort)
    int bindStatus = bind(serverSocketID, (struct sockaddr *)&serverSocket, sizeof(serverSocket));
    if(bindStatus < 0)
    {
        cerr<<"Not successful bind\n";
        exit(0);
    }

    cout<<"Waiting for client to connect....\n";

    //listen() for any incoming communication
    //int status = listen(socketID, queueLimit)
    listen(serverSocketID, 1);

    //define a sockaddr_in struct for the connection socket
    sockaddr_in newSocket;
    socklen_t newSocketLen = sizeof(newSocket);

    //accept() the connection
    //int newID = accept(socketID, &clientAddress,&addressLen)

    int newSocketID = accept(serverSocketID,(sockaddr *) &newSocket,&newSocketLen);
    if(newSocketID < 0)
    {
        cerr<<"Not successful accept.\n";
        exit(0);
    }
    cout<<"Client connected successfully.\n";

    //send() and recv() bytes
    //int data = send(socketID, MSG, MSGLen,flags)
    //int data = recv(socketID, recvBuf, bufLen, flags)
    while(1)
    {
        cout<<"Waiting for a message from client\n";
        recv(newSocketID, (char *)&message, sizeof(message),0);
        if(!strcmp(message, "exit"))
        {
            cout<<"Session terminated\n";
            break;
        }
        cout<<message<<endl;
        string data;
        getline(cin,data);
        strcpy(message, data.c_str());
        if(data == "exit")
        {
            cout<<"Session terminated\n";
            break;
        }
        send(newSocketID, (char *)&message,sizeof(message),0);

    }
    //close() the socket
    //int status = close(socketID);
    close(newSocketID);
    close(serverSocketID);
}
