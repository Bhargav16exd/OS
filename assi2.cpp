#include <iostream>
#include <queue>
#include <vector>
using namespace std;

void printResult(int tat[] , int wt[] , int n){

    float totalTAT = 0 , totalWT = 0 ,avgTAT = 0 , avgWT = 0 ;

    for(int i=0 ; i<n ; i++){
        totalTAT = totalTAT + tat[i];
        totalWT = totalWT + wt[i];
    }

    avgTAT = totalTAT / n ;
    avgWT = totalWT / n ;

    cout << "TAT : " << totalTAT << " WT : " << totalWT << endl;
    cout << "Avg TAT : " << avgTAT << " Avg WT : " << avgWT  << endl; 
}

void fcfs(int at[],int bt[], int n){
    
    //Initialilze Type of Process
    using process = pair<int , int>;

    //Initializing Priority Queue
    priority_queue<process,vector<process>,greater<process>> pq ;

    //Utils
    int ct = 0;
    int completed = 0 ;
    bool done[n] = {false};
    int tat[n] = {};
    int wt[n] = {};

    while(completed < n){

        for(int i=0;i<n;i++){
            if(at[i]<=ct && !done[i]){
                pq.push({at[i],i});
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

        }else{
            ct ++ ;
        }
    }

    printResult(tat,wt,n);

}

void sjfN(int at[],int bt[], int n){
    
    //Initialilze Type of Process
    using process = pair<int , int>;

    //Initializing Priority Queue
    priority_queue<process,vector<process>,greater<process>> pq ;

    //Utils
    int ct = 0;
    int completed = 0 ;
    bool done[n] = {false};
    int tat[n] = {};
    int wt[n] = {};

    while(completed < n){

        for(int i=0;i<n;i++){
            if(at[i]<=ct && !done[i]){
                pq.push({bt[i],i});
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

        }else{
            ct ++ ;
        }
    }

    printResult(tat,wt,n);

}

void sjfP(int at[],int bt[], int n){
    
    //Initialilze Type of Process
    using process = pair<int , int>;

    //Initializing Priority Queue
    priority_queue<process,vector<process>,greater<process>> pq ;

    //Utils
    int ct = 0;
    int completed = 0 ;
    bool done[n] = {false};
    int tat[n] = {};
    int wt[n] = {};
    int btToBeModified [n] = {};

    for(int i = 0 ; i < n ; i ++){
        btToBeModified[i] = bt[i];
    }

    while(completed < n){

        for(int i=0;i<n;i++){
            if(at[i]<=ct && !done[i]){
                pq.push({bt[i],i});
                done[i] = true;
            }
        }

        if(!pq.empty()){

            process el = pq.top();
            pq.pop();
            int idx = el.second;

            btToBeModified[idx] = btToBeModified[idx] - 1 ;
            ct ++ ;

            if(btToBeModified[idx] == 0 ){

                tat[idx] = ct - at[idx];
                wt[idx] = tat[idx] - bt[idx];
                completed ++ ;

            }else{
                pq.push(el);
            }

        }else{
            ct++;
        }

        
    }

    printResult(tat,wt,n);

}

void prioP(int at[],int bt[], int p[] ,int n){
    
    //Initialilze Type of Process
    using process = pair<int , int>;

    //Initializing Priority Queue
    priority_queue<process,vector<process>> pq ;

    //Utils
    int ct = 0;
    int completed = 0 ;
    bool done[n] = {false};
    int tat[n] = {};
    int wt[n] = {};
    int btToBeModified [n] = {};

    for(int i = 0 ; i < n ; i ++){
        btToBeModified[i] = bt[i];
    }

    while(completed < n){

        for(int i=0;i<n;i++){
            if(at[i]<=ct && !done[i]){
                pq.push({p[i],i});
                done[i] = true;
            }
        }

        if(!pq.empty()){

            process el = pq.top();
            pq.pop();
            int idx = el.second;

            btToBeModified[idx] = btToBeModified[idx] - 1 ;
            ct ++ ;

            if(btToBeModified[idx] == 0 ){

                tat[idx] = ct - at[idx];
                wt[idx] = tat[idx] - bt[idx];
                completed ++ ;

            }else{
                pq.push(el);
            }

        }else{
            ct++;
        }

        
    }

    printResult(tat,wt,n);

}

void prioN(int at[],int bt[], int p[], int n){
    
    //Initialilze Type of Process
    using process = pair<int , int>;

    //Initializing Priority Queue
    priority_queue<process,vector<process>,greater<process>> pq ;

    //Utils
    int ct = 0;
    int completed = 0 ;
    bool done[n] = {false};
    int tat[n] = {};
    int wt[n] = {};

    while(completed < n){

        for(int i=0;i<n;i++){
            if(at[i]<=ct && !done[i]){
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

        }else{
            ct ++ ;
        }
    }

    printResult(tat,wt,n);

}

void roundRobin(int at[],int bt[] , int n , int timeQuantum){

    //Intializing Type of Process
    using process = pair <int ,int >;
    
    //Initialize Queue
    queue<process> q;

    //Utility
    int ct = 0 ;
    int completed = 0 ;
    bool done[n] = {false};
    int tat[n] = {};
    int wt[n] = {};
    int btToBeModified[n] = {};

    for(int i = 0 ; i<n ; i++){
        btToBeModified[i] = bt[i];
    }

    while(completed < n){

        for(int i =0 ; i < n ; i++){
            if(at[i] <= ct && !done[i]){
                q.push({at[i],i});
                done[i] = true ;
            }
        }

        if(!q.empty()){

            process el = q.front();
            q.pop();
            int idx = el.second;

            if(btToBeModified[idx] <= timeQuantum){

                ct = ct + btToBeModified[idx];
                btToBeModified[idx] = 0 ;
                tat[idx] = ct - at[idx];
                wt[idx] = tat[idx] - bt[idx];
                completed ++ ;
                
            }else{
                btToBeModified[idx] = btToBeModified[idx] - timeQuantum;
                ct = ct + timeQuantum;
                
                for(int i = idx + 1 ; i < n ; i++){
                    if(at[i] <= ct && !done[i]){
                        q.push({at[i],i});
                        done[i] = true ;
                    }
                }

                q.push(el);
            }


        }else{
            ct++;
        }

    }

    printResult(tat,wt,n);
}


int main(){

    int n ;
    cout << "Enter Number of Process : ";
    cin >> n;

    int at[n] = {};
    int bt[n] = {};
    int p[n]  = {};

    for(int i=0 ; i<n ; i++){
        cout << "Enter AT for Process " <<  i+1 << " " ;
        cin >> at[i];
    }

    for(int i=0 ; i<n ; i++){
        cout << "Enter BT for Process " <<  i+1 << " " ;
        cin >> bt[i];
    }


    for(int i=0 ; i<n ; i++){
        cout << "Enter Priority for Process " <<  i+1 << " " ;
        cin >> p[i];
    }


    while(true){

        int choice; 
        cout << "1 fcfs 2 sjfN 3 sjfP 4 Round Robin 5 PrioN 6 PrioN ";
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
                int timeQuantum ;
                cout << "Enter Time Quantum : ";
                cin >> timeQuantum;
                roundRobin(at,bt,n,timeQuantum);
                break;

            case 5 : 
                prioN(at,bt,p,n);
                break;

            case 6 : 
                prioP(at,bt,p,n);
                break;

            default :
                cout << "Invalid Choice" << endl;
                break;
        }

        break;
    }

}