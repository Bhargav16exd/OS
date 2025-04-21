#include <iostream>
#include <vector>

using namespace std;


int p , t;

//Current Allocation
vector<vector<int>> currentAllocation;

//Maximum Need
vector<vector<int>> maximumAllocation;

//Remaining Need
vector<vector<int>> remainingNeed;

//Safe Sequence 
vector<int> safeSequence;

//Available Resources
vector<int> availableResources;

//Finish
vector<bool> finish;


void printResults(){

    cout << "Current Allocation : "<<endl;
    for(int i = 0 ; i < p ; i ++ ){
        for(int j = 0 ; j < t ; j ++ ){
            cout << currentAllocation[i][j] << " ";
        }
        cout<<endl;
    }

    cout << "Max Allocation : "<<endl;
    for(int i = 0 ; i < p ; i ++ ){
        for(int j = 0 ; j < t ; j ++ ){
            cout << maximumAllocation[i][j] << " ";
        }
        cout<<endl;
    }


    cout << "Remaining Need : "<<endl;
    for(int i = 0 ; i < p ; i ++ ){
        for(int j = 0 ; j < t ; j ++ ){
            cout << remainingNeed[i][j] << " ";
        }
        cout<<endl;
    }

}


void getSafeSequence(){

    for(int i = 0 ; i < p ; i ++ ){

        if(!finish[i]){

            bool canBeAllocated = true;

            for(int j = 0 ; j < t ; j ++ ){
                if(remainingNeed[i][j] > availableResources[j]){
                    canBeAllocated = false;
                    break;
                }
            }

            if(canBeAllocated){

                //Update Available Resources
                for(int x = 0 ; x < t ; x ++ ){
                    availableResources[x] = availableResources[x] + currentAllocation[i][x];
                }

                finish[i] = true;
                safeSequence.push_back(i);

                getSafeSequence();

                //Backtrack
                for(int x = 0 ; x < t ; x ++ ){
                    availableResources[x] = availableResources[x] - currentAllocation[i][x];
                }

                finish[i] = false;
                safeSequence.pop_back();

            }

        }

    }


    if( safeSequence.size() == p ){
        for(int i = 0 ; i < p ; i ++ ){
            cout << "P" << safeSequence[i] << ( i == p-1 ? " " : " -> ");
        }
        cout<<endl;
    }

}

int main(){
    
    //Get Number of Process
    cout << "Enter Number of Process : ";
    cin >> p ;

    //Get Number of Resource Type 
    cout << "Enter Number of Resource Type : ";
    cin >> t;

    //Intializing Vectors
    currentAllocation.resize(p,vector<int>(t));
    maximumAllocation.resize(p,vector<int>(t));
    remainingNeed.resize(p,vector<int>(t));
    availableResources.resize(t);
    finish.resize(p,false);

    //Get Current Allocation
    cout << "Current Allocation : "<<endl;
    for(int i = 0 ; i < p ; i ++ ){

        cout << "Process "<< i+1 << " : ";
        for(int j = 0 ; j < t ; j ++ ){
            cin >> currentAllocation[i][j];
        }
    }

    //Get Maximum Need
    cout << "Maximum Need : "<<endl;
    for(int i = 0 ; i < p ; i ++ ){
        cout << "Process "<< i+1 << " : ";
        for(int j = 0 ; j < t ; j ++ ){
            cin >> maximumAllocation[i][j];
        }
    }


    //Calculating Remaining Need
    for(int i = 0 ; i < p ; i ++ ){
        for(int j = 0 ; j < t ; j ++ ){
            remainingNeed[i][j] = maximumAllocation[i][j] - currentAllocation[i][j];
        }
    }

    //Get Available Resources
    cout << "Enter Available Resources : ";
    for(int i = 0 ; i < t ; i ++ ){
        cin >> availableResources[i];
    }


    printResults();
    cout << "Finding Safe Sequence ... " << endl;
    getSafeSequence();

}