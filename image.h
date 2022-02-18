#ifndef IMAGE_H
#define IMAGE_H	0

#include <allegro.h>

struct IMAGE {
	
	BITMAP* bitmap;
	int speed;			// The amount of cycles it takes to dis/appear
	int wspeed;			// Width divided by speed
	int hspeed;			// Height divided by speed
	int count;			// Counter, from 0 to speed
	int pivot_x;
	int pivot_y;
	bool visible;			// Whether the image is hidden or not
	
	void load(char*);
	void draw(BITMAP*, int, int, float);
	void hide();
	void show();
};

#endif
