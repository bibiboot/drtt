#include "ipc_master.h"
#include "globals.h"

void *start_ipc_master()
{
    int shmid;
    key_t key;
    char *shm; //*s;

    /*
     * We'll name our shared memory segment
     * "5678".
     */
    key = 5678;

    /*
     * Create the segment.
     */
    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    /*
     * Now we attach the segment to our data space.
     */
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    /*
     * Now put some things into the memory for the
     * other process to read.
     */
    globals.drtt = shm;

    /*
    for (c = 'a'; c <= 'z'; c++)
        *s++ = c;
    *s = NULL;
    printf("Added to memory\n");
    */

    /*
     * Finally, we wait until the other process
     * changes the first character of our memory
     * to '*', indicating that it has read what
     * we put there.
     */
    while (1){
        printf("Writing drrt : %s\n", globals.drtt);
        sleep(globals.config.ipc_sleep_time);
    }

}
