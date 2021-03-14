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

int main(int argc, char const *argv[])
{
    if(argc != 2)
    {
        cerr<<"Missing port number.\n";
        exit(0);
    }
    int port = atoi(argv[1]);
   
    sockaddr_in serverSocket;
    bzero((char *)&serverSocket, sizeof(serverSocket));
    serverSocket.sin_family = AF_INET;
    serverSocket.sin_port = htons(port);
    serverSocket.sin_addr.s_addr = htonl(INADDR_ANY);

    int serverSocketID = socket(AF_INET, SOCK_STREAM,0);
    if(serverSocketID < 0 )
    {
        cerr<<"Error in connection.\n";
        exit(0);
    }
    cout<<"Server socket is created.\n";

    
    int bindStatus = bind(serverSocketID, (struct sockaddr *)&serverSocket, sizeof(serverSocket));
    if(bindStatus < 0)
    {
        cerr<<"Error in binding.\n";
        exit(0);
    }

    cout<<"Waiting for client to connect....\n";

    
    if(listen(serverSocketID, 4)==0)
    {
        cout<<"Listening...\n";
    }
    else
    {
       cout<<"Error in binding.\n";
    }

    pid_t pid;
    char msg[1500],p=1;
    int newSocketID;
    
    while(1)
    {   
        sockaddr_in newSocket;
        socklen_t newSocketLen = sizeof(newSocket);
        newSocketID = accept(serverSocketID,(sockaddr *) &newSocket,&newSocketLen);
        if(newSocketID < 0)
        {
            cerr<<"Not successful accept.\n";
            exit(0);
        }
        cout<<"New client connected successfully.\n";
        
        pid = fork();
        if ( pid < 0 ) {
			cerr<<"fork call failed.\n";
			close(newSocketID);
			close(serverSocketID);
			exit(0);
	}
        else if(pid == 0){
             close(serverSocketID);
        
        while(1){
            cout<<"Waiting for a message from client\n";
            recv(newSocketID, (char *)&msg, sizeof(msg),0);
            if(!strcmp(msg, "exit"))
            {
            cout<<"Session terminated\n";
            break;
            }
        cout<<msg<<endl;
        string data;
        getline(cin,data);
        strcpy(msg, data.c_str());
        if(data == "exit")
        {
            cout<<"Session terminated\n";
            break;
        }
        send(newSocketID, (char *)&msg,sizeof(msg),0);
        }
        }
  
    }
   
    close(serverSocketID);
    close(newSocketID);
}
