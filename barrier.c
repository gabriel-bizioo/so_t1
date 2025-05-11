#include "barrier.h"

void init_barr(barrier_t *barr, int n) {

    pthread_mutex_init(&barr->semaphore, NULL);
    barr->barrier_number = n;
    barr->total_processes = 0;
}

void process_barrier(barrier_t *barr) {
    if(!pthread_mutex_lock(&(barr->semaphore))) {
        barr->total_processes++;    // Regiao critica
        pthread_mutex_unlock(&(barr->semaphore));

        // Reseta contador de threads na ultima thread:
        if(barr->total_processes == barr->barrier_number) {
            barr->total_processes = 0;
            return;
        }
    }

    while(barr->total_processes < barr->barrier_number);
}
