#ifndef MISC_H
#define MISC_H	1

#include <iostream>
#include <allegro.h>


#define MATH_PI		3.14159
#define PINK		16711935
#define ONCE		FALSE
#define FOREVER		TRUE
#define GRAVITY		0.3
#define LEFT		-1
#define RIGHT		1


void Timer();
int items_in_datafile(DATAFILE*);
int pink_pixel(BITMAP*, int, int);
//void print_worm_info(WORM*);

extern volatile int game_time;

#endif
