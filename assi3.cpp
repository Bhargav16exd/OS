#include <iostream>
#include <unistd.h>
#include <cstring>

using namespace std; 


int main(){

    //File Descriptors
    int pipe1[2] , pipe2[2];
    
    //Pid
    pid_t pid;

    //Initializing Pipes 
    if( pipe(pipe1) == -1 || pipe(pipe2) == -1 ){
        perror("Error While Creating Pipes");
        exit(1);
    }

    pid = fork();

    if( pid == 0 ){
        
        //child process
        close(pipe1[1]);
        close(pipe2[0]);

        //Reading Data from Pipe
        char msgFromParent[100];
        read(pipe1[0],msgFromParent,sizeof(msgFromParent));

        if (strlen(msgFromParent) == 0 ){
            cout << "No Message From Parent Recieved " << endl;
            exit(0);
        }

        cout << "CHILD : Recieved Message From Parent : " << msgFromParent << endl;

        // Get Data From User for Sending Message to Parent from Child
        char msgToParent[100];
        cout << "CHILD : Enter Message to Send to Parent : " ;
        cin.getline(msgToParent,sizeof(msgToParent));

        //Writing Message To Pipe 2
        write(pipe2[1],msgToParent,sizeof(msgToParent));

        close(pipe1[0]);
        close(pipe2[1]);
     
    }
    else if (pid > 0 ){
        
        //parent process
        close(pipe1[0]);
        close(pipe2[1]);


        //Getting Data from the User
        char msgToChild[100];
        
        cout << "PARENT : Enter Message to Send to Child : " ;
        cin.getline(msgToChild,sizeof(msgToChild));

        //Writing the Message to the Pipe
        write(pipe1[1], msgToChild,strlen(msgToChild)+1);


        char msgFromChild[100];

        read(pipe2[0],msgFromChild,sizeof(msgFromChild));

        if (strlen(msgFromChild) == 0 ){
            cout << "No Message From Parent Recieved " << endl;
            exit(0);
        }

        cout << "PARAENT : Recieved Message From Child : " << msgFromChild << endl;

        close(pipe1[1]);
        close(pipe2[0]);

    }
    else{
        cout << "Error While Executing Fork Call " << endl;
        exit(0); 
    }

    return 0;
}