#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include "barrier.h"

int main(int argc, char *argv[]) {
    pid_t pid;
    int nProc = 0, n = 3, segment_id, i;
    barrier_t *barrier;
    int original_pid = getppid();

    segment_id = shmget(IPC_PRIVATE, sizeof(barrier_t), 511); //pode tudo

    barrier = (barrier_t *) shmat(segment_id, NULL, 0);
    init_barr(barrier, n);

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
        process_barrier(barrier);
        int ns = (rand() % 20);
        printf("Child number %d\nSleeping for %d seconds...\n", nProc, ns);
        sleep(ns);
    }


    return 0;
}
