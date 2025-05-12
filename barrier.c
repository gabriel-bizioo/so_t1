#include "barrier.h"
#include <stdio.h>

void init_barr(barrier_t *barr, int n) {

    pthread_mutex_init(&barr->enter, NULL);
    pthread_mutex_init(&barr->leave, NULL);
    barr->barrier_number = n;
    barr->total_processes = 0;
   }

void process_barrier(barrier_t *barr) {
    if(!pthread_mutex_lock(&(barr->enter))) {
        if(barr->total_processes == barr->barrier_number)
            barr->total_processes = 0; /* Reseta o valor para reutilizar a barreira */
        pthread_mutex_unlock(&(barr->enter));
    }

    if(!pthread_mutex_lock(&(barr->enter))) {
        barr->total_processes++;
        pthread_mutex_unlock(&(barr->enter));
    }

    while(barr->total_processes < barr->barrier_number);
}
