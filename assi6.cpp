#include <iostream>
using namespace std;


void fcfs(int numberOfPartitions , int partitions[] , int numberOfProcesses , int processSize[]){
    
    int allocation[numberOfProcesses] = {-1};

    for (int i = 0; i < numberOfProcesses; i++) allocation[i] = -1;
    bool blockFilled[numberOfPartitions] = {false} ;

    for(int i = 0 ; i < numberOfProcesses ; i ++ ){

        for(int j = 0 ; j < numberOfPartitions ; j ++ ){

            if( processSize[i] <= partitions[j] && blockFilled[j] == false){

                allocation[i] = j ;
                blockFilled[j] = true;

                break;
            }

        }
    }

    cout << "First Fit Allocation ... " << endl;

    for(int i = 0 ; i < numberOfProcesses ; i ++ ){
        
        if(allocation[i]!=-1){
            cout << "Process " << i + 1 << " of Size " << processSize[i] << " -> " << " Block " << allocation[i] + 1 << endl;
        }else{
            cout << "Process " << i + 1 << " of Size " << processSize[i] << " -> " << " Not Allocated " << endl;
        }

    }
}


void nextfit(int numberOfPartitions , int partitions[] , int numberOfProcesses , int processSize[]){

    int allocation[numberOfProcesses] ;
    for (int i = 0; i < numberOfProcesses; i++) allocation[i] = -1;
    
    bool blockFilled[numberOfPartitions] = {false} ;

    int lastPosition = 0 ;

    for(int i  = 0 ; i < numberOfProcesses ; i ++ ){

        int j = lastPosition;
        int count = 0;

        while(count < numberOfPartitions){

            if( processSize[i] <= partitions[j] && blockFilled[j] == false){
                allocation[i] = j ;
                blockFilled[j] = true;
                lastPosition = (j + 1) % numberOfPartitions;
                break;
            }
            j = (j + 1) % numberOfPartitions;
            count ++; 
        }
    }

    for(int i = 0 ; i < numberOfProcesses ; i ++ ){
        
        if(allocation[i]!=-1){
            cout << "Process " << i + 1 << " of Size " << processSize[i] << " -> " << " Block " << allocation[i] + 1 << endl;
        }else{
            cout << "Process " << i + 1 << " of Size " << processSize[i] << " -> " << " Not Allocated " << endl;
        }

    }


}

void bestFit(int numberOfPartitions , int partitions[] , int numberOfProcesses , int processSize[]){

    int allocation[numberOfProcesses] ;
    for (int i = 0; i < numberOfProcesses; i++) allocation[i] = -1;
    
    bool blockFilled[numberOfPartitions] = {false} ;

    for(int i  = 0 ; i < numberOfProcesses ; i ++ ){

        int minValue = 999 ;
        int bestFitIndex = -1;

        for( int j = 0 ; j < numberOfPartitions ; j++ ){

            if( processSize[i] <= partitions[j] && blockFilled[j] == false ){

                int currentMinValue = partitions[j] - processSize[i];
                if(currentMinValue < minValue){
                    minValue = currentMinValue;
                    bestFitIndex = j;
                }

            }
        }

        if(bestFitIndex != -1 ){
            allocation[i] = bestFitIndex;
            blockFilled[bestFitIndex] = true;
        }
        
    }

    //Print Data
    for(int i = 0 ; i < numberOfProcesses ; i ++ ){
        
        if(allocation[i]!=-1){
            cout << "Process " << i + 1 << " of Size " << processSize[i] << " -> " << " Block " << allocation[i] + 1 << endl;
        }else{
            cout << "Process " << i + 1 << " of Size " << processSize[i] << " -> " << " Not Allocated " << endl;
        }

    }



}

void worstFit(int numberOfPartitions , int partitions[] , int numberOfProcesses , int processSize[]){

    int allocation[numberOfProcesses] ;
    for (int i = 0; i < numberOfProcesses; i++) allocation[i] = -1;
    
    bool blockFilled[numberOfPartitions] = {false} ;

    for(int i  = 0 ; i < numberOfProcesses ; i ++ ){

        int minValue = 0 ;
        int bestFitIndex = -1;

        for( int j = 0 ; j < numberOfPartitions ; j++ ){

            if( processSize[i] <= partitions[j] && blockFilled[j] == false ){

                int currentMinValue = partitions[j] - processSize[i];
                if(currentMinValue > minValue){
                    minValue = currentMinValue;
                    bestFitIndex = j;
                }

            }
        }

        if(bestFitIndex != -1 ){
            allocation[i] = bestFitIndex;
            blockFilled[bestFitIndex] = true;
        }
        
    }

    //Print Data
    for(int i = 0 ; i < numberOfProcesses ; i ++ ){
        
        if(allocation[i]!=-1){
            cout << "Process " << i + 1 << " of Size " << processSize[i] << " -> " << " Block " << allocation[i] + 1 << endl;
        }else{
            cout << "Process " << i + 1 << " of Size " << processSize[i] << " -> " << " Not Allocated " << endl;
        }

    }



}

int main(){

    //Get number of partitions
    int numberOfPartitions;
    cout << "Enter Number of Partitions : " ;
    cin >> numberOfPartitions;

    //Get Partitions Sizes
    int partitions[numberOfPartitions] = {};
    cout << "Enter Partitions Sizes : ";
    for(int i = 0 ; i < numberOfPartitions ; i ++ ){
        cin >> partitions[i];
    }

    //Get number of processes 
    int numberOfProcesses;
    cout << "Enter Number of Processes : " ;
    cin >> numberOfProcesses;


    //Get Partitions Sizes
    int processSize[numberOfProcesses] = {};
    cout << "Enter Processes Sizes : ";
    for(int i = 0 ; i < numberOfProcesses ; i ++ ){
        cin >> processSize[i];
    }

    while(true){

        int choice ;
        cout << "1 FCFS , 2 Next Fit , 3 Best Fit , 4 Worst Fit " << endl;
        cin >> choice;

        switch(choice){

            case 1 :
                fcfs(numberOfPartitions,partitions,numberOfProcesses,processSize);
                break;

            case 2 :
                nextfit(numberOfPartitions,partitions,numberOfProcesses,processSize);
                break;

            case 3 :
                bestFit(numberOfPartitions,partitions,numberOfProcesses,processSize);
                break;

            case 4 : 
                worstFit(numberOfPartitions,partitions,numberOfProcesses,processSize);
                break;

            default:
                break;
        }

        break;

    }

    return 0 ;
}