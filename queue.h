#ifndef QUEUE
#define QUEUE

#include <pthread.h>

typedef struct fifo_s {
    int vez_atual;
    int n_esperando;
    pthread_mutex_t semaforo;

} fifo_qt;

void espera(fifo_qt *F);

void liberaPrimeiro(fifo_qt *F);

void init_fifoQ(fifo_qt *F);

#endif
