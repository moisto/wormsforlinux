#ifndef GAMESTATE_H
#define GAMESTATE_H	1

#include <allegro.h>

#define STATE_PLAYING	1
#define STATE_QUIT	2


struct GAMESTATE {
	
	int state;
	BITMAP* buffer;
	
	GAMESTATE();	
};

#endif
