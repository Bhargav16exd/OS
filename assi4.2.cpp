//With synchronization
#include <iostream>
#include <pthread.h>
using namespace std;

int ticketAvailable = 10;
int rc = 0;

pthread_mutex_t mutex;
pthread_mutex_t db;

void* reader(void* arg){

    int id = *((int*)arg);

    pthread_mutex_lock(&mutex);
        rc = rc +1 ;
        if(rc == 1) pthread_mutex_lock(&db);
    pthread_mutex_unlock(&mutex);

    cout << "Reader " << id << " Available Tickets : " << ticketAvailable << endl;

    pthread_mutex_lock(&mutex);
        rc = rc -1 ;
        if(rc == 0) pthread_mutex_unlock(&db);
    pthread_mutex_unlock(&mutex);
    
    pthread_exit(0);

}

void* writer(void* arg){

    int id = *((int*)arg);

    pthread_mutex_lock(&db);

    if(ticketAvailable > 0){
        ticketAvailable--;
        cout << "[Writer " << id << "] Booked a ticket. Tickets left: " << ticketAvailable << endl;
    }
    else{
        cout << "[Writer " << id << "] No tickets available to book." << endl;
    }

    pthread_mutex_unlock(&db);

    pthread_exit(0);
}


int main(){
    
    pthread_t r[5] , w[2];
    int rId[5] , wId[2];

    for(int i=0;i<5;i++){
       rId[i] = i + 1;
       pthread_create(&r[i],NULL,reader,&rId[i]);
    }


    for(int i=0;i<2;i++){
        wId[i] = i + 1;
        pthread_create(&w[i],NULL,writer,&wId[i]);
    }

    for(int i=0;i<5;i++){
        pthread_join(r[i],NULL);
    }


    for(int i=0;i<2;i++){
        pthread_join(w[i],NULL);
    }

    return 0;

}