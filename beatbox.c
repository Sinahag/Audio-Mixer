#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/time.h>
#include "threadControl.h"

//TODO: CHANGE ASLAMIXER NAME TO DEFAULT AFTER EVERYTHING
int main(void)
{
    initalizeHW();
    printf("Starting readWaveFile\n");
    initalizeThreads();

    printf("Enter 'Q' to quit.\n");
    while (true)
    {
        // Quit?
        if (toupper(getchar()) == 'Q')
        {
            break;
        }
    }
    printf("Starting cleanup.. if forever looping then change pthread_join to pthread_cancel\n");
    cancelThreads();
    AudioMixer_cleanup();
    return 0;
}
