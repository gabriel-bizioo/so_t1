#ifndef BARRIER
#define BARRIER

#include <pthread.h>

/* Armazena respectivamente:
 *  um semaforo mutex,
 *  quantidade de processos a serem esperados,
 *  quantidade de processos em espera no estado atual
 */
typedef struct barrier_s {
    pthread_mutex_t enter;
    pthread_mutex_t leave;
    int barrier_number;
    int total_processes;
} barrier_t;

/* inicializa barreira com barrier_number = n */
void init_barr(barrier_t *barr, int n);

/* Insere a thread que chamar a funcao na barreira,
 * libera as threads contidas quando 'barrier_number' threads
 * tiverem sido inseridas
 */
void process_barrier(barrier_t *barr);
#endif
