// doit.c
// Anthony Gringeri

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>

#include "process_data.h"
#include "doit.h"

main(int argc, char *argv[]) {
    // initialize structs and info
    process_data *p = start();
    process_data **p2 = execute(argv + 1, p);
    p = p2[0];
    // print out stats
    print_data(p2[1]);
}

process_data** execute(char** command, process_data* status) {
    struct rusage *r = (struct rusage*)(malloc(sizeof(struct rusage)));

    int pid;

    if ((pid = fork()) <= 0) {
        // child
        execvp(command[0], command);
    } else {
        // parent
        wait(pid);
        getrusage(RUSAGE_SELF, r);
        return process_information(r, status);
    }

    exit(0); // program done
}