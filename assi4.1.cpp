//Without synchronization
#include <iostream>
#include <pthread.h>
using namespace std;

int ticketAvailable = 10;

void* reader(void* arg){

    int id = *((int*)arg);
    cout << "Reader " << id << " Available Tickets : " << ticketAvailable << endl;
    pthread_exit(0);

}

void* writer(void* arg){

    int id = *((int*)arg);

    if(ticketAvailable > 0){
        ticketAvailable--;
        cout << "[Writer " << id << "] Booked a ticket. Tickets left: " << ticketAvailable << endl;
    }
    else{
        cout << "[Writer " << id << "] No tickets available to book." << endl;
    }

    pthread_exit(0);
}


int main(){
    
    pthread_t r[5] , w[3];
    int rId[5] , wId[3];

    for(int i=0;i<5;i++){
       rId[i] = i + 1;
       pthread_create(&r[i],NULL,reader,&rId[i]);
    }


    for(int i=0;i<3;i++){
        wId[i] = i + 1;
        pthread_create(&w[i],NULL,writer,&wId[i]);
    }

    for(int i=0;i<5;i++){
        pthread_join(r[i],NULL);
    }


    for(int i=0;i<3;i++){
        pthread_join(w[i],NULL);
    }

    return 0;

}