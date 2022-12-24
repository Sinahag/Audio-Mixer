#include "threadControl.h"

static pthread_t hihatBtnThread;
static pthread_t snareBtnThread;
static pthread_t bassBtnThread;
static pthread_t modeBtnThread;
static pthread_t joystickThread;
static pthread_t screenPrintThread;

void initalizeHW()
{
    initMatrix();
    userbtnInitalize();
    AudioMixer_init();
    Threads_init();
    return
}

void initalizeThreads()
{
    if (pthread_create(&joystickThread, NULL, &joystickRead, NULL))
    {
        perror("Could not create joystick thread\n");
        return;
    }
    if (pthread_create(&modeBtnThread, NULL, &modeBtn, NULL))
    {
        perror("Could not create modeBtn thread\n");
        return;
    }
    if (pthread_create(&bassBtnThread, NULL, &bassBtn, NULL))
    {
        perror("Could not create bassBtn thread\n");
        return;
    }
    if (pthread_create(&snareBtnThread, NULL, &snareBtn, NULL))
    {
        perror("Could not create snareBtn thread\n");
        return;
    }
    if (pthread_create(&hihatBtnThread, NULL, &hihatBtn, NULL))
    {
        perror("Could not create hihatBtn thread\n");
        return;
    }
    if (pthread_create(&screenPrintThread, NULL, &hihatBtn, NULL))
    {
        perror("Could not create screenPrint thread\n");
        return;
    }
    return
}

void cancelThreads()
{

    printf("Closing all threads\n");
    endThreads();
    pthread_join(joystickThread, NULL);
    pthread_join(modeBtnThread, NULL);
    pthread_join(bassBtnThread, NULL);
    pthread_join(snareBtnThread, NULL);
    pthread_join(hihatBtnThread, NULL);
    pthread_cancel(screenPrintThread, NULL);
}