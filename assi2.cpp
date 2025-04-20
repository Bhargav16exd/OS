#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;



void fcfs( int at[] , int bt[] , int n ){

    //Declaring Type Process for Priority Queue
    using pro = pair<int,int>;

    // Priority Queue Initialization
    priority_queue<pro,vector<pro>,greater<pro>> pq;

    //Utility Vars
    int ct = 0;
    int tat[n] = {};
    int wt [n] = {};
    bool done[n] = {false};
    int completed = 0; 


    while(completed < n){

        for(int i = 0 ; i < n ; i++){

            if( at[i] <= ct && done[i]!= true ){
                pq.push({at[i],i});
                done[i] = true;
            }
        }


        if(!pq.empty()){

            pro el = pq.top();
            pq.pop();

            int idx = el.second;

            cout << idx;
            ct = ct + bt[idx];
            tat[idx] = ct - el.first;
            wt[idx] = tat[idx] - bt[idx];
            completed++;

        }else{
            ct ++ ;
        }


    }

    float avgTAT = 0;
    float avgWT = 0;
    float TAT = 0;
    float WT = 0;

    for(int i = 0 ; i < n ; i++){
        TAT = TAT + tat[i];
        WT = WT + wt[i];
    }

    cout << "Total TAT : "<< TAT << " TOTAL WT : " << WT << endl;
    avgTAT = TAT / n;
    avgWT = WT / n;

    cout << "AVG TAT : "<< avgTAT << " avg WT : " << avgWT << endl;
}


void sjfN( int at[] , int bt[] , int n ){

    //Declaring Type of Process to be used in Priority Queue
    using process = pair<int,int>;

    //Priority Queue Declartion 
    priority_queue<process,vector<process>,greater<process>> pq;

    //Utitlity Values
    int ct = 0;
    int completed = 0 ;
    int done[n] = {false};
    int tat[n] = {};
    int wt[n] = {};

    while(completed < n){

        for(int i = 0 ; i < n ; i++ ){
            if(at[i] <= ct && done[i]!= true){
                pq.push({bt[i],i});
                done[i] = true;
            }
        }

        if(!pq.empty()){
            process el = pq.top();
            pq.pop();
            
            int idx = el.second;
            ct = ct + el.first;
            tat[idx] = ct - at[idx];
            wt[idx] = tat[idx] - el.first;
            completed++;
        }
        else{
            ct ++ ;
        }

    }


    // Printing Data
    float avgTAT = 0;
    float avgWT = 0;
    float TAT = 0;
    float WT = 0;

    for(int i = 0 ; i < n ; i++){
        TAT = TAT + tat[i];
        WT = WT + wt[i];
    }

    cout << "Total TAT : "<< TAT << " TOTAL WT : " << WT << endl;
    avgTAT = TAT / n;
    avgWT = WT / n;

    cout << "AVG TAT : "<< avgTAT << " avg WT : " << avgWT << endl;

}


void sjfP( int at[] , int bt[] , int n){

    //Type Declartion for Priority Queue
    using process = pair<int,int>;

    //Priority Queue Declartion
    priority_queue<process,vector<process>,greater<process>> pq;

    //Utility Functions
    int ct = 0 ;
    int completed = 0;
    bool done[n] = {false};
    int tat[n] = {};
    int wt[n] = {};

    while(completed<n){

        for(int i = 0 ; i < n ; i++){
            if( at[i] <= ct && done[i]!= true ){
                pq.push({bt[i],i});
                done[i] = true;
            }
        }

        if(!pq.empty()){

            process el = pq.top();
            pq.pop();

            if ( el.first == 0 ){
                
                int idx = el.second;
                tat[idx] = ct - at[idx];
                wt[idx] = tat[idx] - bt[idx];
                completed++;

            }else{
                // If Burst Time is not zero Reduce it by 1
                el.first = el.first - 1;
                pq.push(el);
                ct ++ ;
            }

        }else{
            ct ++;
        }

    }


     // Printing Data
     float avgTAT = 0;
     float avgWT = 0;
     float TAT = 0;
     float WT = 0;
 
     for(int i = 0 ; i < n ; i++){
         TAT = TAT + tat[i];
         WT = WT + wt[i];
     }
 
     cout << "Total TAT : "<< TAT << " TOTAL WT : " << WT << endl;
     avgTAT = TAT / n;
     avgWT = WT / n;
 
     cout << "AVG TAT : "<< avgTAT << " avg WT : " << avgWT << endl;
}


void roundRobin( int at[] , int bt[] , int n , int timeQuantum){
    
    //Initialize Type for Priority Queue 
    using process = pair<int , int>;

    //Initialize Priority Queue
    queue<process> pq;

    //Utils
    int ct = 0 ;
    int completed = 0 ;
    bool done[n] = {false};
    int tat[n] = {};
    int wt[n]  = {};
    int btToBeModified[n] = {};
    
    for(int i = 0 ; i < n ; i ++){
        btToBeModified[i] = bt[i];
    } 

    while (completed < n)
    {
        for(int i=0 ; i<n ; i++){

            if(at[i] <= ct && done[i] != true){
                pq.push({at[i],i});
                done[i] = true ;
            }
        }

        if(!pq.empty()){

            process p = pq.front();
            pq.pop();
            
            int idx = p.second;

            if(btToBeModified[idx] <= timeQuantum ){

                ct = ct + btToBeModified[idx];
                btToBeModified[idx] = 0 ;
                tat[idx] = ct - at[idx];
                wt[idx] = tat[idx] - bt[idx];
                completed ++;

                for(int i=idx+1 ; i<n ; i++){

                    if(at[i] <= ct && done[i] != true){
                        pq.push({at[i],i});
                        done[i] = true ;
                    }
                }

            }
            else{

                btToBeModified[idx] = btToBeModified[idx] - timeQuantum;
                ct = ct + timeQuantum;

                for(int i=idx+1 ; i<n ; i++){

                    if(at[i] <= ct && done[i] != true){
                        pq.push({at[i],i});
                        done[i] = true ;
                    }
                }
                pq.push(p);
            }


        }
        else{
            ct ++;
        }
        
    }

     // Printing Data
     float avgTAT = 0;
     float avgWT = 0;
     float TAT = 0;
     float WT = 0;  cout << ct << endl;
 
     for(int i = 0 ; i < n ; i++){
         cout << tat[i] << " ";
         cout << wt[i] << endl;
     }
 
     cout << "Total TAT : "<< TAT << " TOTAL WT : " << WT << endl;
     avgTAT = TAT / n;
     avgWT = WT / n;
 
     cout << "AVG TAT : "<< avgTAT << " avg WT : " << avgWT << endl;
    
}


void priorityN( int at[] , int bt[] , int p [], int n ){

    //Declaring Type of Process to be used in Priority Queue
    using process = pair<int,int>;

    //Priority Queue Declartion 
    priority_queue<process,vector<process>,greater<process>> pq;

    //Utitlity Values
    int ct = 0;
    int completed = 0 ;
    int done[n] = {false};
    int tat[n] = {};
    int wt[n] = {};

    while(completed < n){

        for(int i = 0 ; i < n ; i++ ){
            if(at[i] <= ct && done[i]!= true){
                pq.push({p[i],i});
                done[i] = true;
            }
        }

        if(!pq.empty()){
            process el = pq.top();
            pq.pop();
            
            int idx = el.second;
            ct = ct + bt[idx];
            tat[idx] = ct - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            completed++;
        }
        else{
            ct ++ ;
        }

    }


    // Printing Data
    float avgTAT = 0;
    float avgWT = 0;
    float TAT = 0;
    float WT = 0;

    for(int i = 0 ; i < n ; i++){
        TAT = TAT + tat[i];
        WT = WT + wt[i];
    }

    cout << "Total TAT : "<< TAT << " TOTAL WT : " << WT << endl;
    avgTAT = TAT / n;
    avgWT = WT / n;

    cout << "AVG TAT : "<< avgTAT << " avg WT : " << avgWT << endl;

}


void priorityP( int at[] , int bt[] , int p [] ,int n){

    //Type Declartion for Priority Queue
    using process = pair<int,int>;

    //Priority Queue Declartion
    priority_queue<process,vector<process>> pq;

    //Utility Functions
    int ct = 0 ;
    int completed = 0;
    bool done[n] = {false};
    int tat[n] = {};
    int wt[n] = {};
    int btToBeModified[n] = {};
    
    for(int i = 0 ; i < n ; i ++){
        btToBeModified[i] = bt[i];
    } 

    while(completed<n){

        for(int i = 0 ; i < n ; i++){
            if( at[i] <= ct && done[i]!= true){
                pq.push({p[i],i});
                done[i] = true;
            }
        }

        if(!pq.empty()){

            process el = pq.top();
            pq.pop();
            int idx = el.second;

            btToBeModified[idx] = btToBeModified[idx] - 1;
            ct ++;

            if ( btToBeModified[idx] == 0 ){
                cout << ct << "at idx " << idx << endl ;
                tat[idx] = ct - at[idx];
                wt[idx] = tat[idx] - bt[idx];
                completed++;

            }else{
                pq.push(el);
            }

        }else{
            ct ++;
        }

    }


    for(int i = 0 ; i < n ; i++){
        cout << tat[i] << " ";
    }
     
     // Printing Data
     float avgTAT = 0;
     float avgWT = 0;
     float TAT = 0;
     float WT = 0;
 
     for(int i = 0 ; i < n ; i++){
         TAT = TAT + tat[i];
         WT = WT + wt[i];
     }
 
     cout << "Total TAT : "<< TAT << " TOTAL WT : " << WT << endl;
     avgTAT = TAT / n;
     avgWT = WT / n;
 
     cout << "AVG TAT : "<< avgTAT << " avg WT : " << avgWT << endl;
}

int main(){

    int n; 
    cout << "Enter Number of Process : ";
    cin >> n;

    int at[n] = {};
    int bt[n] = {};
    int prio[n] = {};


    for(int i = 0 ; i < n ; i++ ){
        cout << "Enter Arrival Time Process " << i + 1 << " " ;
        cin >> at[i];
    }

    for(int i = 0 ; i < n ; i++ ){
        cout << "Enter Bus Time Process " << i + 1 << " " ;
        cin >> bt[i];
    }

    for(int i = 0 ; i < n ; i++ ){
        cout << "Enter Priority for Process " << i + 1 << " " ;
        cin >> prio[i];
    }


    while(true){

        int choice ;
        cout << "FCFS 1 \nSJF Non Preemptive 2 \nSJF Non Preemptive 3 \nRound Robin 4 \nPriority Non Preemptive 5 \nPriority Preemption 6 "<<endl;
        cin >> choice;
        
        switch(choice){

            case 1 :
                fcfs(at,bt,n);
                break;

            case 2 :
                sjfN(at,bt,n);
                break;

            case 3 :
                sjfP(at,bt,n);
                break;

            case 4 :
                int timeQuantum;
                cout << "Enter Time Quantum : ";
                cin >> timeQuantum;
                roundRobin(at,bt,n,timeQuantum);
                break;

            case 5 :
                priorityN(at,bt,prio,n);
                break;

            case 6 :
                priorityP(at,bt,prio,n);
                break;

            default :
                cout <<"Invalid Choice"<<endl;
                break;
        }

        if(choice == 3 ){
            break;
        }
    }


    return 0;
}

        