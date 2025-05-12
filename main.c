/* Autor: Gabriel Pucci Bizio */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>

#include "barrier.h"
#include "queue.h"



int main(int argc, char *argv[]) {
    barrier_t *barrier;
    fifo_qt *fifo;
    pid_t pid;
    int barrier_segment, fifo_segment, s, nProc, n, child_status, recurso = rand();

    printf("%d\n", argc);
    if(argc != 2) {
        printf("Forma de uso : \"%s n\", onde n = numero de processos\n", argv[0]);
        return -1;
    }

    n = atoi(argv[1]);
    barrier_segment = shmget(IPC_PRIVATE, sizeof(fifo_qt), 511);
    barrier = (barrier_t *) shmat(barrier_segment, NULL, 0);
    init_barr(barrier, n);

    fifo_segment = shmget(IPC_PRIVATE, sizeof(barrier_t), 511);
    fifo = (fifo_qt *) shmat(fifo_segment, NULL, 0);
    init_fifoQ(fifo);

    for(int i = 0; i < n; i++) {
        pid = fork();
        if(pid == 0) {
            nProc = i+1;
            printf("with logical number = %d\nFrom PID: %d\n", nProc, getppid());
            break;
        }
        printf("New child process PID: %d \n", pid);
    }

    if(pid == 0){
        printf("--Processo: %d chegando na barreira\n", nProc);
        process_barrier(barrier);
        printf("++Processo: %d saindo da barreira\n", nProc);

        for(int uso = 1; uso <= 3; uso++) {

            s = rand() % 4;
            printf("Processo %d Prologo: %d de %d segundos\n", nProc, uso, s);
            sleep(s);

            espera(fifo);

            s = rand() % 4;
            printf("Processo: %d USO: %d por %d segundos\n", nProc, uso, s);
            sleep(s);

            liberaPrimeiro(fifo);

            s = rand() % 4;
            printf("Processo %d Epilogo: %d de %d segundos\n", nProc, uso, s);
            sleep(s);
        }

        printf("--Processo: %d chegando novamente na barreira\n", nProc);
        process_barrier(barrier);
        printf("++Processo: %d saindo da barreira novamente\n", nProc);

        exit(nProc);
    }

    for(int i = 0; i < n; i++) {
        pid = wait(&child_status);
        printf("+++ Filho de numero logico %d e pid %d terminou!\n", child_status/255, pid);
    }

    return 0;
}
