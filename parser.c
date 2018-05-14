#include <errno.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#include "car.h"

List * tokenize(const char * text) {
// Tokenize the text, store all data in a List, return pointer
    char * buffer = (char *) malloc(BUFFSIZE1*sizeof(char));
    List * L = (List *) malloc(sizeof(List));
    if (L == NULL) {return NULL;}
    List * ptr = L;
    int length = strlen(text);
    int safecounter = 0;
    for (int iter=0; iter < length; iter++) {
        if (text[iter] == '(' || text[iter] == ')' || text[iter] == ' ') {safecounter++;}
        for (int j=0; text[iter] != '(' && text[iter] != ')' && text[iter] != ' '; j++, iter++) {
            buffer[j] = text[iter];
            buffer[j+1] = '\0';
            safecounter = 0;
        }

        if (safecounter < 1) {
            ptr->elem = (char *) malloc(strlen(buffer)*sizeof(char));
            strcpy(ptr->elem, buffer);
            ptr->next = (List *) malloc(sizeof(List));
            ptr = ptr->next;
        }
    }
    ptr->elem = (char *) malloc(strlen(buffer)*sizeof(char));
    ptr->next = NULL;
    return L;
}

SensorMsg * parser(List * L) {
// Parse sensor message.
// Input tokenized List, returns pointer to SensorMsg structure

    unsigned int inside = FALSE; // true if in the braces
    if (L == NULL) { return NULL; }
    SensorMsg * Smsg = (SensorMsg *) malloc(sizeof(SensorMsg));
    List * ptr = L;
    while (ptr != NULL) {
        if (strcmp(ptr->elem, "angle") == 0) {
            ptr = ptr->next;
            Smsg->angle = atof(ptr->elem);
        }
        else if (strcmp(ptr->elem, "curLapTime") == 0) {
            ptr = ptr->next;
            Smsg->curLapTime = atof(ptr->elem);
        }
        else if (strcmp(ptr->elem, "damage")== 0) {
            ptr = ptr->next;
            Smsg->damage = atof(ptr->elem);
        }
        else if (strcmp(ptr->elem, "distFromStart")== 0) {
            ptr = ptr->next;
            Smsg->distFromStart = atof(ptr->elem);
        }
        else if (strcmp(ptr->elem, "totalDistFromStart")== 0) {
            ptr = ptr->next;
            Smsg->totalDistFromStart = atof(ptr->elem);
        }
        else if (strcmp(ptr->elem, "distRaced")== 0) {
            ptr = ptr->next;
            Smsg->distRaced = atof(ptr->elem);
        }
        else if (strcmp(ptr->elem, "fuel")== 0) {
            ptr = ptr->next;
            Smsg->fuel = atof(ptr->elem);
        }
        else if (strcmp(ptr->elem, "gear")== 0) {
            ptr = ptr->next;
            Smsg->gear = atof(ptr->elem);
        }
        else if (strcmp(ptr->elem, "lastLapTime")== 0) {
            ptr = ptr->next;
            Smsg->lastLapTime = atof(ptr->elem);
        }
        else if (strcmp(ptr->elem, "opponents")== 0) {
            for (int i=0; i<36; i++) {
                ptr = ptr->next;
                Smsg->opponents[i] = atof(ptr->elem);
            }
        }
        else if (strcmp(ptr->elem, "racePos")== 0) {
            ptr = ptr->next;
            Smsg->racePos = atof(ptr->elem);
        }
        else if (strcmp(ptr->elem, "rpm")== 0) {
            ptr = ptr->next;
            Smsg->rpm = atof(ptr->elem);
        }
        else if (strcmp(ptr->elem, "speedX")== 0) {
            ptr = ptr->next;
            Smsg->speedX = atof(ptr->elem);
        }
        else if (strcmp(ptr->elem, "speedY")== 0) {
            ptr = ptr->next;
            Smsg->speedY = atof(ptr->elem);
        }
        else if (strcmp(ptr->elem, "speedZ")== 0) {
            ptr = ptr->next;
            Smsg->speedZ = atof(ptr->elem);
        }
        else if (strcmp(ptr->elem, "track")== 0) {
            for (int i=0; i<19; i++) {
                ptr = ptr->next;
                Smsg->track[i] = atof(ptr->elem);
            }
        }
        else if (strcmp(ptr->elem, "trackPos")== 0) {
            ptr = ptr->next;
            Smsg->trackPos = atof(ptr->elem);
        }
        else if (strcmp(ptr->elem, "wheelSpinVel")== 0) {
            for (int i=0; i<4; i++) {
                ptr = ptr->next;
                Smsg->wheelSpinVel[i] = atof(ptr->elem);
            }
        }
        else if (strcmp(ptr->elem, "z")== 0) {
            ptr = ptr->next;
            Smsg->z = atof(ptr->elem);
        }
        else if (strcmp(ptr->elem, "focus")== 0) {
            for (int i=0; i<5; i++) {
                ptr = ptr->next;
                Smsg->focus[i] = atof(ptr->elem);
            }
        }
        else { ptr = ptr->next; }
    }

    return Smsg;
}


char * fancyout(CtrlMsg CM) {
// Input generated Control Message structure (CtrlMsg)
// returns command string pointer

    char * ctrstr = (char *) malloc(MSGLEN1*sizeof(char));
    char * buffer = (char *) malloc(BUFFSIZE1*sizeof(char));

    strcpy(ctrstr ,"(accel ");
    sprintf(buffer, "%f",CM.accel);
    strcat(ctrstr, buffer);
    strcat(ctrstr, ")");

    strcat(ctrstr ,"(brake ");
    sprintf(buffer, "%f",CM.brake);
    strcat(ctrstr, buffer);
    strcat(ctrstr, ")");

    strcat(ctrstr ,"(gear ");
    sprintf(buffer, "%f",CM.gear);
    strcat(ctrstr, buffer);
    strcat(ctrstr, ")");

    strcat(ctrstr ,"(focus");
    for (int i=0; i<5; i++) {
        sprintf(buffer, " %f",CM.focus[i]);
        strcat(ctrstr, buffer);
    }
    strcat(ctrstr, ")");

    strcat(ctrstr ,"(clutch ");
    sprintf(buffer, "%f",CM.clutch);
    strcat(ctrstr, buffer);
    strcat(ctrstr, ")");

    strcat(ctrstr ,"(meta ");
    sprintf(buffer, "%f",CM.meta);
    strcat(ctrstr, buffer);
    strcat(ctrstr, ")");

    strcat(ctrstr ,"(steer ");
    sprintf(buffer, "%f",CM.steer);
    strcat(ctrstr, buffer);
    strcat(ctrstr, ")");

    return ctrstr;
}

