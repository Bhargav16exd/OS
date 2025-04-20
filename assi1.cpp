#include <iostream>
#include <unistd.h>
#include <fstream>
#include <wait.h>
#include <string>
using namespace std;


void cp (string src , string dest){
    
    string line;

    //file handling 
    // reading file
    ifstream srcFile(src);
    //Writing file
    ofstream destFile(dest);

    if(!srcFile.is_open() || !destFile.is_open()){
        cout << "Error While Opening a file"<<endl;
        exit(0);
    }

    while(getline(srcFile,line)){
        destFile << line << endl;
    }


    srcFile.close();
    destFile.close();

    exit(1);
    return;
}

void grep(string targetFileName,string targetString){

    // Read file 
    ifstream targetFile(targetFileName);
    string line;

    if(!targetFile.is_open()){
        cout << "Error While Opening a file"<<endl;
        exit(0);
    }


    while(getline(targetFile,line)){

        if(line.find(targetString)!= string::npos){
            cout << line << endl;
        }
    }

    targetFile.close();
    exit(1);
    return;
}



int main(){

    pid_t pid ; 
    int choice;


    while(true){

        cout << "Enter Choice: \nCP 1 \ngrep 2 \n3 Exit";
        cin >> choice ;

        switch(choice){

            case 1 :

                // Simulate fork
                pid = fork();

                if(pid == 0){
                    // Exec CP
                    string src;
                    string dest;

                    cout << "Enter Source file name : ";
                    cin >> src ; 

                    cout << "Enter Destination file name : ";
                    cin >> dest ; 

                    cp(src,dest);
                    exit(1);
                }
                else if(pid == -1){
                    cout <<"Fork Failed" << endl;
                    exit(1);
                }
                else{
                    wait(0);
                    cout << "Child Process "<< pid << " got completed" <<endl;
                }

                break;

            case 2 :
            
                pid = fork();

                if(pid == 0 ){
                    string targetFile ;
                    string wordToSearch ;

                    cout << "Enter Target File to search : ";
                    cin >> targetFile;
                    cout << "Enter Pattern to search : ";
                    cin >> wordToSearch;
                    
                    grep(targetFile,wordToSearch);
                    exit(1);

                }
                else if (pid == -1 ){
                    cout <<"Fork Failed" << endl;
                    exit(0);
                }
                else {
                    wait(0);
                    cout << "Child Process "<< pid << " got completed" <<endl;
                }
                break;

            default:
            cout << "Invalid Choice"<<endl;z
            break;
        }

        if (choice == 3){
            break;
        }
    }


}