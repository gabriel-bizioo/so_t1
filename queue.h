#ifndef QUEUE
#define QUEUE

/* Autor: Gabriel Pucci Bizio */
#include <pthread.h>

/* 'vez_atual': Indica qual processo esta utilizando os recursos atualmente, de acordo com a ordem de entrada
 * 'n_esperando': indica quantos processos entraram na funcao desde a inicializacao.
 * 'semaforo': mutex para alteracao segura das outras variaveis
 * Tamanho atual da fila = n_esperando - vez_atual - 1
 */
typedef struct fifo_s {
    int vez_atual;
    int n_esperando;
    pthread_mutex_t semaforo;

} fifo_qt;

/*
 * Inicializa o mutex com valor padrao
 * e as variaveis com valor = 0
 */
void init_fifoQ(fifo_qt *F);

/*
 * Insere o processo que chamou esta funcao
 * na fila de espera ordenada
 */
void espera(fifo_qt *F);

/*
 * passa a vez do uso dos recursos para
 * o proximo processo na fila
 */
void liberaPrimeiro(fifo_qt *F);


#endif
