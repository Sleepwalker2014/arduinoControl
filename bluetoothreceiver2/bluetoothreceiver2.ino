#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX
int outPutPin = 6;
int inputPin = 244;
int control = 13;
int charCounter = 0;
char receivedChar = ' ';
char charArray[20];

void setup() {
    pinMode(outPutPin, OUTPUT);
    pinMode(inputPin, INPUT);
    pinMode(control, OUTPUT);
    digitalWrite(control, HIGH);
    
    Serial.begin(9600);
    mySerial.begin(9600);
}

void loop() { // run over and over
    if (mySerial.available() > 0) {
        receivedChar = mySerial.read();

        if (receivedChar == '<') {
            return false;
        }
        
        if (receivedChar == '>') {
            charCounter = 0;

            parseMessage(charArray);

            emptyReceivedMessage(charArray);
            
            return false;
        }

        charArray[charCounter] = receivedChar;
        charCounter++;
    }
}

void convertAnalogValueToCharArray (char *charArray, int analogValue) {
    sprintf(charArray,"%d#", analogValue);
}

void parseMessage(char *message) {
    char messageBuffer[3][4];

    int i = 0;
    int messagePartCounter = 0;
    int messageCharCounter = 0;

    while (message[i] != '\0') {
        if (message[i] == '|') {
            i++;

            messagePartCounter++;
            messageCharCounter = 0;
            continue;
        }

        messageBuffer[messagePartCounter][messageCharCounter] = message[i];
        messageCharCounter++;
        i++;
    }

    int command = atoi(messageBuffer[0]);
    int pin = atoi(messageBuffer[1]);
    int value = atoi(messageBuffer[2]);
}

void emptyReceivedMessage(char *message) {
    int i = 0;

    for (int i = 0; i < 20; ++i) {
        message[i] = '\0';
    }
}

void setPinMode(int pin, int mode) {
    pinMode(pin, mode);
}

void setDigitalPinValue(int pin, bool value) {
    setPinMode(pin, OUTPUT);
    digitalWrite(pin, value);
}

void setAnalogPinValue(int pin, int value) {
    setPinMode(pin, OUTPUT);
    analogWrite(pin, value);
}

bool readDigitalPinValue(int pin) {
    setPinMode(pin, INPUT);
    return digitalRead(pin);
}

int readAnalogPinValue(int pin) {
    setPinMode(pin, INPUT);
    return analogRead(pin);
}

