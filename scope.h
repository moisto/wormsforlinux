#ifndef SCOPE_H
#define SCOPE_H	1

#include <iostream>
#include <math.h>
#include <allegro.h>
#include "animation.h"
#include "image.h"
#include "misc.h"

struct SCOPE {
	
	DATAFILE* images;	// Images for drawing the scope
	DATAFILE* powergauge;
	DATAFILE* animation;

	int pivot_x;		// Pivot point
	int pivot_y;
	float weapon_power;
	int frame_count;	// Number of images in datafile
	int current_frame;	// The frame currently being drawn
	float angle;		// Scope angle
	bool active;		// Is the scope active?!
	
	SCOPE();
	int process();		// Think about stuff
	void draw(BITMAP*, int, int, int); // Draw our thoughts
	void show();		// Hide the scope
	void hide();		// Show the scope
		
	private:
	int appear;		// Counter used for show()
	int vanish;		// Counter used for hide()
};

#endif
