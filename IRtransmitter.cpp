#include "IRtransmitter.h"

static unsigned int VENT_LIGHT_ON[99] = {450, 700, 550, 650, 550, 1550, 450, 1600, 500, 1600, 500, 1550, 500, 1600, 500, 700, 500, 1600, 500, 1550, 500, 1600, 450, 750, 450, 4550, 500, 700, 550, 650, 500, 1550, 550, 1550, 500, 1600, 450, 1600, 550, 1550, 500, 700, 500, 1550, 500, 1600, 500, 1600, 450, 700, 500, 4550, 550, 650, 500, 700, 450, 1600, 500, 1600, 500, 1550, 550, 1550, 500, 1600, 450, 750, 500, 1550, 500, 1600, 500, 1550, 550, 650, 500, 4650, 550, 650, 500, 700, 450, 1600, 500, 1600, 550, 1550, 500, 1550, 550, 1550, 450, 750, 450, 1600, 500, 1600, 450};
static unsigned int VENT_LIGHT_OFF[99] = {500, 700, 500, 650, 550, 1550, 500, 1600, 500, 1550, 500, 1600, 500, 1550, 550, 700, 450, 700, 500, 700, 500, 700, 450, 750, 450, 4550, 500, 700, 500, 700, 450, 1600, 500, 1600, 500, 1600, 450, 1600, 500, 1600, 450, 750, 500, 700, 450, 700, 500, 700, 500, 700, 450, 4600, 500, 700, 500, 700, 450, 1600, 450, 1600, 500, 1600, 500, 1600, 450, 1600, 500, 700, 500, 700, 500, 700, 500, 700, 450, 700, 500, 4700, 450, 700, 500, 700, 500, 1600, 450, 1600, 550, 1550, 500, 1550, 500, 1600, 500, 700, 500, 700, 450, 700, 500};
static unsigned int VENT_LEVEL_0[99] = {450, 750, 450, 750, 450, 1600, 450, 1600, 500, 1600, 500, 1600, 500, 1550, 550, 650, 500, 1600, 450, 1600, 550, 650, 550, 650, 500, 4550, 500, 700, 450, 700, 500, 1600, 500, 1600, 500, 1550, 550, 1550, 500, 1550, 500, 700, 500, 1600, 500, 1550, 500, 700, 550, 650, 500, 4550, 500, 700, 450, 700, 550, 1550, 450, 1650, 450, 1600, 500, 1600, 500, 1550, 550, 650, 500, 1550, 500, 1600, 550, 650, 500, 700, 500, 4700, 450, 700, 500, 700, 500, 1550, 550, 1550, 500, 1600, 500, 1550, 500, 1600, 500, 700, 500, 1550, 500, 1600, 500};
static unsigned int VENT_LEVEL_1[99] = {450, 700, 500, 700, 500, 1600, 500, 1550, 550, 1550, 500, 1600, 450, 1600, 500, 700, 500, 1600, 450, 750, 450, 1600, 550, 650, 450, 4600, 450, 750, 450, 750, 500, 1550, 450, 1600, 500, 1600, 500, 1550, 500, 1600, 500, 700, 500, 1600, 450, 750, 450, 1600, 500, 700, 500, 4550, 500, 700, 450, 700, 500, 1600, 500, 1600, 450, 1600, 500, 1600, 450, 1600, 500, 700, 500, 1600, 500, 700, 450, 1600, 500, 700, 500, 4700, 450, 750, 450, 700, 500, 1600, 450, 1600, 500, 1600, 450, 1650, 450, 1600, 500, 700, 500, 1600, 450, 700, 500};
static unsigned int VENT_LEVEL_2[99] = {450, 750, 400, 750, 500, 1600, 450, 1600, 450, 1650, 450, 1650, 450, 1600, 500, 700, 500, 700, 450, 1600, 450, 800, 400, 750, 450, 4600, 450, 750, 450, 750, 400, 1650, 450, 1650, 500, 1550, 450, 1650, 450, 1650, 400, 800, 400, 750, 450, 1650, 450, 750, 500, 700, 400, 4600, 450, 750, 450, 750, 500, 1550, 450, 1650, 450, 1650, 450, 1600, 450, 1650, 450, 750, 450, 700, 450, 1650, 450, 750, 500, 700, 450, 4700, 450, 750, 450, 750, 500, 1550, 500, 1600, 450, 1650, 500, 1550, 450, 1650, 500, 700, 450, 750, 500, 1550, 500};
static unsigned int VENT_LEVEL_3[99] = {500, 700, 450, 750, 450, 1600, 500, 1600, 450, 1600, 500, 1600, 500, 1600, 450, 750, 450, 1600, 500, 700, 450, 750, 450, 750, 450, 4550, 500, 700, 500, 700, 450, 1600, 500, 1600, 500, 1600, 450, 1600, 500, 1600, 450, 750, 450, 1600, 500, 700, 500, 700, 500, 700, 450, 4600, 450, 700, 500, 700, 500, 1600, 450, 1600, 500, 1600, 450, 1600, 500, 1600, 500, 700, 450, 1650, 450, 700, 500, 750, 450, 700, 500, 4700, 450, 700, 500, 700, 500, 1600, 450, 1600, 500, 1600, 450, 1600, 500, 1600, 500, 700, 450, 1650, 450, 700, 500};

IRtransmitter::IRtransmitter() {
    irrecv.enableIRIn();
}

void IRtransmitter::speaker_on() {
    sendNEC(SPEAKERS_ON);
}

void IRtransmitter::play() {
    sendNEC(SPEAKERS_PLAY);
}

void IRtransmitter::next() {
    sendNEC(SPEAKERS_NEXT);
}


void IRtransmitter::previous() {
    sendNEC(SPEAKERS_PREVIOUS);
}

void IRtransmitter::playlist(int id) {
    for(int i = 0; i < 6; i++) {
        sendNEC(SPEAKERS_MENU);
    }
    for(int i = 0; i < 5; i++) {
        sendNEC(SPEAKERS_UP);
    }
    sendNEC(SPEAKERS_SELECT);
    delay(200);
    for(int i = 0; i < 3; i++) {
        sendNEC(SPEAKERS_UP);
    }
    sendNEC(SPEAKERS_SELECT);
    for(int i = 0; i < 10; i++) {
        sendNEC(SPEAKERS_UP);
    }
    for(int i = 0; i < id; i++) {
        sendNEC(SPEAKERS_DOWN);
    }
    sendNEC(SPEAKERS_SELECT);
    sendNEC(SPEAKERS_SELECT);
}

void IRtransmitter::light_on() {
    sendRAW(VENT_LIGHT_ON);   
}

void IRtransmitter::light_off() {
    sendRAW(VENT_LIGHT_OFF);
}

void IRtransmitter::level_0() {
    sendRAW(VENT_LEVEL_0);
}

void IRtransmitter::level_1() {
    sendRAW(VENT_LEVEL_1);
}

void IRtransmitter::level_2() {
    sendRAW(VENT_LEVEL_2);
}

void IRtransmitter::level_3() {
    sendRAW(VENT_LEVEL_3);
}

long IRtransmitter::read() {
    long aux = -1;
    if (irrecv.decode(&results)) {
        aux = this->results.value;
        Serial.println(aux, HEX);
        irrecv.resume();
    }
    return aux;
}


void IRtransmitter::sendNEC(unsigned long ircode) {
    for(int i = 0; i < 1; i++) {
        irsend.sendNEC(ircode, 32);
        delay(10);
    }
}

void IRtransmitter::sendRAW(unsigned int (&ircode)[99]) {
    for(int i = 0; i < 1; i++) {
        irsend.sendRaw(ircode, 99 , 38);
        delay(10);
    }
}
