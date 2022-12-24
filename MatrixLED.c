#include "MatrixLED.h"

static unsigned char writeLED[7] = {0x02, 0x04, 0x06, 0x08, 0x0A, 0x0C, 0x0E};

static unsigned char leftLED[10][7] = {
                            {0x20, 0x50, 0x50, 0x50, 0x50, 0x50, 0x20},//0
                            {0x70, 0x20, 0x20, 0x20, 0x20, 0x60, 0x20},//1
                            {0x70, 0x40, 0x20, 0x20, 0x10, 0x50, 0x20},//2
                            {0x60, 0x10, 0x10, 0x20, 0x10, 0x10, 0x60},//3
                            {0x10, 0x10, 0x70, 0x50, 0x50, 0x30, 0x10},//4
                            {0x20, 0x50, 0x10, 0x70, 0x40, 0x40, 0x70},//5
                            {0x20, 0x50, 0x50, 0x70, 0x40, 0x40, 0x30},//6
                            {0x20, 0x20, 0x20, 0x10, 0x10, 0x10, 0x70},//7
                            {0x20, 0x50, 0x50, 0x20, 0x50, 0x50, 0x20},//8
                            {0x10, 0x10, 0x10, 0x30, 0x50, 0x50, 0x70}
};
static unsigned char rightLED[10][7] = {
                            {0x01, 0x82, 0x82, 0x82, 0x82, 0x82, 0x01},//0
                            {0x83, 0x01, 0x01, 0x01, 0x01, 0x03, 0x01},//1
                            {0x83, 0x02, 0x01, 0x01, 0x80, 0x82, 0x01},//2
                            {0x03, 0x80, 0x80, 0x01, 0x80, 0x80, 0x03},//3
                            {0x80, 0x80, 0x83, 0x82, 0x82, 0x81, 0x80},//4
                            {0x01, 0x82, 0x80, 0x83, 0x02, 0x02, 0x81},//5
                            {0x01, 0x82, 0x82, 0x03, 0x02, 0x02, 0x81},
                            {0x01, 0x01, 0x01, 0x80, 0x80, 0x80, 0x83},
                            {0x01, 0x82, 0x82, 0x01, 0x82, 0x82, 0x01},
                            {0x80, 0x80, 0x80, 0x81, 0x82, 0x82, 0x83}
};
static unsigned char showMLED[7] = {0x50, 0x50, 0x50, 0x50, 0x70, 0x70, 0x50};

static int i2cFile = 0;
static int n = 0;

void i2cCommand(char* command)
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

void initMatrix(){
    i2cCommand(i2cStartpin1);
    i2cCommand(i2cStartpin2);
    i2cCommand(matrixOn);
    i2cCommand(displayOn);
    i2cFile = initI2cBus(I2CDRV_LINUX_BUS1, I2C_DEVICE_ADDRESS);
}

void writeI2cReg(int i2cFileDesc, unsigned char regAddr, unsigned char value){
    unsigned char buff[2];
    buff[0] = regAddr;
    buff[1] = value;
    int res = write(i2cFileDesc, buff, 2);
    if (res != 2) {
        perror("I2C: Unable to write i2c register.");
        exit(1);
    }
}

int initI2cBus(char* bus, int address){
    int i2cFileDesc = open(bus, O_RDWR);
    int result = ioctl(i2cFileDesc, I2C_SLAVE, address);
    if (result < 0) {
        perror("I2C: Unable to set I2C device to slave address.");
        exit(1);
    }
    return i2cFileDesc;
}

void dispInt(int val){
    i2cCommand(clearDouble);
    if(val < 0){
        for(n = 0; n < writeSize; n++){
            writeI2cReg(i2cFile, writeLED[n], leftLED[0][n]);
        }
        return;
    }else if(val > 99){
        char mixedLED[writeSize];
        for(n =0; n < writeSize; n++){
            mixedLED[n] = leftLED[9][n];
        }
        for(n=0; n<writeSize; n++){
            mixedLED[n] = mixedLED[n] | rightLED[9][n];
        }
        for(n = 0; n < writeSize; n++){
            writeI2cReg(i2cFile, writeLED[n], mixedLED[n]);
        }
        return;
    }
    if(val < 10){
        for(n = 0; n < writeSize; n++){
            writeI2cReg(i2cFile, writeLED[n], leftLED[val][n]);
        }
    }else{
        int left = val/10;
        int right = val%10;
        char mixedLED[writeSize];
        for(n =0; n < writeSize; n++){
            mixedLED[n] = leftLED[left][n];
        }
        for(n=0; n<writeSize; n++){
            mixedLED[n] = mixedLED[n] | rightLED[right][n];
        }
        for(n = 0; n < writeSize; n++){
            writeI2cReg(i2cFile, writeLED[n], mixedLED[n]);
        }
    }
    return;
}

void dispMode(int val){
    i2cCommand(clearDouble);
    if(val >= 10){
        printf("Invalid Mode\n");
    }else{
        char mixedLED[writeSize];
        for(n =0; n < writeSize; n++){
            mixedLED[n] = showMLED[n];
        }
        for(n=0; n<writeSize; n++){
            mixedLED[n] = mixedLED[n] | rightLED[val][n];
        }
        for(n = 0; n < writeSize; n++){
            writeI2cReg(i2cFile, writeLED[n], mixedLED[n]);
        }
    }
    return;
}