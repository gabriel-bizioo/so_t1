#include "queue.h"

/* Autor: Gabriel Pucci Bizio */
void init_fifoQ(fifo_qt *F) {
    F->vez_atual = 0;
    F->n_esperando = 0;
    pthread_mutex_init(&(F->semaforo), NULL);
}

void espera(fifo_qt *F) {
    int vez_processo;

    if(!pthread_mutex_lock(&(F->semaforo))) {
        vez_processo = F->n_esperando;
        F->n_esperando++;
        pthread_mutex_unlock(&(F->semaforo));
    }

    while(vez_processo != F->vez_atual);
}

void liberaPrimeiro(fifo_qt *F) {
    if(!pthread_mutex_lock(&(F->semaforo))) {
        F->vez_atual++;
        pthread_mutex_unlock(&(F->semaforo));
    }
}
