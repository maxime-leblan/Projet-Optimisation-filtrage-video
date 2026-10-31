#include <stdio.h>
#include <time.h>

/*
Commande de compilation : 
gcc -Wall timer_res.c -o timer_res
*/

int main(void) {
    struct timespec res;

    // Appels à clock_getres pour obtenir la résolution
    if (clock_getres(CLOCK_MONOTONIC, &res) == 0) {
        printf("Resolution CLOCK_MONOTONIC : %ld s, %ld ns\n", 
               res.tv_sec, res.tv_nsec);
    } else {
        perror("Erreur lors de l'appel a clock_getres");
        return 1;
    }

    return 0;
}