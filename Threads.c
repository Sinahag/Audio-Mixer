#include "Threads.h"
#include "intervalTimer.h"
#include <pthread.h>
#include <time.h>

static pthread_mutex_t matrixMutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t bpmMutex = PTHREAD_MUTEX_INITIALIZER;
// static pthread_mutex_t joystickMutex = PTHREAD_MUTEX_INITIALIZER;
static int bpm = 120;
static wavedata_t WavefileData[3];
static pthread_t playMode;
static int halfBeatTime = (1000 * 30) / 120;
static bool matrixTurn = true;
static bool endThreads = false;

static char *myFiles[] = {"wave-files/100051__menegass__gui-drum-bd-hard.wav",     // bass
                          "wave-files/100053__menegass__gui-drum-cc.wav",          // hi hat
                          "wave-files/100059__menegass__gui-drum-snare-soft.wav"}; // snare

void sleepForMs(long long delayInMs)
{
    const long long NS_PER_MS = 1000 * 1000;
    const long long NS_PER_SECOND = 1000000000;
    long long delayNs = delayInMs * NS_PER_MS;
    int seconds = delayNs / NS_PER_SECOND;
    int nanoseconds = delayNs % NS_PER_SECOND;
    struct timespec reqDelay = {seconds, nanoseconds};
    nanosleep(&reqDelay, (struct timespec *)NULL);
}

void Threads_init()
{
    for (int i = 0; i < 3; i++)
    {
        AudioMixer_readWaveFileIntoMemory(myFiles[i], &WavefileData[i]);
    }
}

void *beatOne()
{
    while (1)
    {
        pthread_mutex_lock(&bpmMutex);
        halfBeatTime = (1000 * 30) / bpm;
        pthread_mutex_unlock(&bpmMutex);
        Interval_markInterval(INTERVAL_BEAT_BOX);
        // AudioMixer_readWaveFileIntoMemory(myFiles[0], &WavefileData[0]);
        AudioMixer_queueSound(&WavefileData[1]); // hihat
        AudioMixer_queueSound(&WavefileData[0]); // bass
        sleepForMs(halfBeatTime);
        Interval_markInterval(INTERVAL_BEAT_BOX);
        AudioMixer_queueSound(&WavefileData[1]); // hihat
        sleepForMs(halfBeatTime);
        Interval_markInterval(INTERVAL_BEAT_BOX);
        AudioMixer_queueSound(&WavefileData[1]); // hihat
        AudioMixer_queueSound(&WavefileData[2]); // snare
        sleepForMs(halfBeatTime);
        Interval_markInterval(INTERVAL_BEAT_BOX);
        AudioMixer_queueSound(&WavefileData[1]); // hihat
        sleepForMs(halfBeatTime);
        Interval_markInterval(INTERVAL_BEAT_BOX);
        AudioMixer_queueSound(&WavefileData[1]); // hihat
        AudioMixer_queueSound(&WavefileData[0]); // bass
        sleepForMs(halfBeatTime);
        Interval_markInterval(INTERVAL_BEAT_BOX);
        AudioMixer_queueSound(&WavefileData[1]); // hihat
        sleepForMs(halfBeatTime);
        Interval_markInterval(INTERVAL_BEAT_BOX);
        AudioMixer_queueSound(&WavefileData[1]); // hihat
        AudioMixer_queueSound(&WavefileData[2]); // snare
        sleepForMs(halfBeatTime);
        Interval_markInterval(INTERVAL_BEAT_BOX);
        AudioMixer_queueSound(&WavefileData[1]); // hihat
        sleepForMs(halfBeatTime);
    }
    return NULL;
}

void *beatTwo()
{
    while (1)
    {
        pthread_mutex_lock(&bpmMutex);
        halfBeatTime = (1000 * 30) / bpm;
        pthread_mutex_unlock(&bpmMutex);

        Interval_markInterval(INTERVAL_BEAT_BOX);
        AudioMixer_queueSound(&WavefileData[1]); // hihat
        sleepForMs(halfBeatTime / 2);
        Interval_markInterval(INTERVAL_BEAT_BOX);
        AudioMixer_queueSound(&WavefileData[1]); // hihat
        sleepForMs(halfBeatTime / 2);
        Interval_markInterval(INTERVAL_BEAT_BOX);
        AudioMixer_queueSound(&WavefileData[1]); // hihat
        sleepForMs(halfBeatTime / 2);
        Interval_markInterval(INTERVAL_BEAT_BOX);
        AudioMixer_queueSound(&WavefileData[1]); // hihat
        sleepForMs(halfBeatTime);
        Interval_markInterval(INTERVAL_BEAT_BOX);
        AudioMixer_queueSound(&WavefileData[0]); // bass
        AudioMixer_queueSound(&WavefileData[1]); // hihat
        sleepForMs(halfBeatTime);
        Interval_markInterval(INTERVAL_BEAT_BOX);
        AudioMixer_queueSound(&WavefileData[0]); // bass
        AudioMixer_queueSound(&WavefileData[1]); // hihat
        sleepForMs(halfBeatTime);
        Interval_markInterval(INTERVAL_BEAT_BOX);
        AudioMixer_queueSound(&WavefileData[0]); // bass
        AudioMixer_queueSound(&WavefileData[2]); // snare
        sleepForMs(halfBeatTime);
        Interval_markInterval(INTERVAL_BEAT_BOX);
        AudioMixer_queueSound(&WavefileData[1]); // hihat
        AudioMixer_queueSound(&WavefileData[0]); // bass
        AudioMixer_queueSound(&WavefileData[2]); // snare
        sleepForMs(halfBeatTime);
    }
    return NULL;
}

void *modeBtn()
{
    bool held = false;
    int mode = 1;
    int prevMode = 0;
    bool pthreadMade = false;
    while (!endThreads)
    {
        sleepForMs(debounceTime);
        if (checkBtn('m'))
        {
            if (!held)
            {
                mode++;
                held = true;
            }
        }
        else
        {
            held = false;
        }
        if (mode > (MAXMODES))
        {
            mode = 1;
        }
        if (matrixTurn)
        {
            // pthread_mutex_lock(&matrixMutex);
            dispMode(mode);
            // pthread_mutex_unlock(&matrixMutex);
        }
        if (!pthreadMade)
        {
            switch (mode)
            {
            case 1:
                prevMode = 1;
                pthreadMade = true;
                break;
            case 2:
                if (pthread_create(&playMode, NULL, &beatOne, NULL))
                {
                    perror("Could not create playMode thread\n");
                    return 0;
                }
                prevMode = 2;
                pthreadMade = true;
                break;
            case 3:
                if (pthread_create(&playMode, NULL, &beatTwo, NULL))
                {
                    perror("Could not create playMode thread\n");
                    return 0;
                }
                prevMode = 3;
                pthreadMade = true;
                break;
            }
        }
        if (pthreadMade && (prevMode != mode))
        {
            if (prevMode != 0)
            {
                pthread_cancel(playMode);
            }
            pthreadMade = false;
        }
    }
    if (pthreadMade)
    {
        pthread_cancel(playMode);
    }
    return NULL;
}

void *bassBtn()
{
    bool held = false;
    while (!endThreads)
    {
        sleepForMs(debounceTime);
        if (checkBtn('b'))
        {
            if (!held)
            {
                AudioMixer_queueSound(&WavefileData[0]);
                held = true;
            }
        }
        else
        {
            held = false;
        }
    }
    return NULL;
}

void *snareBtn()
{
    bool held = false;
    while (!endThreads)
    {
        sleepForMs(debounceTime);
        if (checkBtn('s'))
        {
            if (!held)
            {
                AudioMixer_queueSound(&WavefileData[0]);
                held = true;
            }
        }
        else
        {
            held = false;
        }
    }
    return NULL;
}

void *hihatBtn()
{
    bool held = false;
    while (!endThreads)
    {
        sleepForMs(debounceTime);
        if (checkBtn('h'))
        {
            if (!held)
            {
                AudioMixer_queueSound(&WavefileData[0]);
                held = true;
            }
        }
        else
        {
            held = false;
        }
    }
    return NULL;
}

void *joystickRead()
{
    int volume = AudioMixer_getVolume();
    while (!endThreads)
    {
        sleepForMs(debounceTime);
        switch (Joystick_getDirection())
        {
        case RIGHT: // HW wise is right
            pthread_mutex_lock(&bpmMutex);
            bpm += 5;
            if (bpm > 300)
            {
                bpm = 300;
            }
            matrixTurn = false;
            if (!matrixTurn)
            {
                dispInt(bpm);
            }
            pthread_mutex_unlock(&bpmMutex);
            break;
        case LEFT: // HW wise is left
            pthread_mutex_lock(&bpmMutex);
            bpm -= 5;
            if (bpm < 40)
            {
                bpm = 40;
            }
            matrixTurn = false;
            if (!matrixTurn)
            {
                dispInt(bpm);
            }
            pthread_mutex_unlock(&bpmMutex);
            break;
        case UP: // HW wise is up
            volume += 5;
            if (volume > 100)
            {
                volume = 100;
            }
            AudioMixer_setVolume(volume);
            matrixTurn = false;
            if (!matrixTurn)
            {
                dispInt(volume);
            }
            break;
        case DOWN: // HW wise is down
            volume -= 5;
            if (volume < 0)
            {
                volume = 0;
            }
            AudioMixer_setVolume(volume);
            matrixTurn = false;
            if (!matrixTurn)
            {
                dispInt(volume);
            }
            break;
        case NEUTRAL:
            sleepForMs(1000);
            matrixTurn = true;
            break;
        }
    }
    return NULL;
}

void endThreads()
{
    endThreads = true;
    return
}
