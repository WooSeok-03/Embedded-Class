#ifndef FND_H
#define FND_H

#include "Arduino.h"

#define C_ANODE 0
#define C_CATHODE 1

void fnd_init_1(char *fnd_pin, char common);
void fnd_num_1(char number);
void fnd_init_2(char *fnd_pin, char common);
void fnd_num_2(char number);
void fnd_init(char fnd_count, char *fnd_pin, char common);
void fnd_num_delay(char num);
void fnd_num_millis(unsigned long current_millis, char num);

#endif
