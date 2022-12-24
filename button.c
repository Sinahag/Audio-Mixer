
#include "button.h"

void runCommand(char* command)
{
    // Execute the shell command (output into pipe)
    FILE *pipe = popen(command, "r");
    // Ignore output of the command; but consume it
    // so we don't get an error when closing the pipe.
    char buffer[1024];
    while (!feof(pipe) && !ferror(pipe)) {
    if (fgets(buffer, sizeof(buffer), pipe) == NULL)
    break;
    // printf("--> %s", buffer); // Uncomment for debugging
    }
    // Get the exit code from the pipe; non-zero is an error:
    int exitCode = WEXITSTATUS(pclose(pipe));
    if (exitCode != 0) {
        perror("Unable to execute command:");
        printf(" command: %s\n", command);
        printf(" exit code: %d\n", exitCode);
    }
}

void buttonDefine(char* path, char* pin){
    FILE *pFile = fopen(path, "w");
    if (pFile == NULL) {
        printf("ERROR: Unable to open export file.\n");
        exit(1);
    }
    // Write to data to the file using fprintf():
    fprintf(pFile, "%s", pin);
    // Close the file using fclose():
    fclose(pFile);
}

bool buttonPress(char* fileName){
    FILE *pFile = fopen(fileName, "r");
    if (pFile == NULL) {
        printf("ERROR: Unable to open file (%s) for read\n", fileName);
        exit(-1);
    }
    // Read string (line)
    const int MAX_LENGTH = 1024;
    char buff[MAX_LENGTH];
    fgets(buff, MAX_LENGTH, pFile);
    // Close
    fclose(pFile);
    if(buff[0] == '0')
        return true;
    else
        return false;
}

static char* config[] = {config15,config16,config17,config18};
static char* direction[] = {direction15, direction16, direction17, direction18};
static char* activeLow[] = {activeLow15, activeLow16, activeLow17, activeLow18};

void userbtnInitalize(){
    for(int i = 0; i < 4; i++){
        runCommand(config[i]);
        buttonDefine(direction[i], "in");
        buttonDefine(activeLow[i], "1");
    }
}

bool checkBtn(char btn){
    switch(btn){
        case 'm':
            return buttonPress(value15);
            break;
        case 'b':
            return buttonPress(value16);
            break;
        case 's':
            return buttonPress(value17);
            break;
        case 'h':
            return buttonPress(value18);
            break;
        default:
            printf("Not valid input");
    }
    return false;
}
