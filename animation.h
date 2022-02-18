#ifndef ANIMATION_H
#define ANIMATION_H	1

#include <allegro.h>
#include "misc.h"

extern BITMAP* buffer;

struct ANIMATION {
	ANIMATION();
	void load(char*);
	void play(BITMAP*, int, int);	// Play the animation!
	void reverse();		// Play it backwards (or forwards if it's already backwards)
	void pivot(int, int);	// Pivot around this point

	DATAFILE* data;		// Datafile containing images
	int step;		// Current frame
	int speed;		// Frame-rate in milliseconds
	int frame_direction;	// Current direction of the sliding frames
	bool loop;		// Shall we repeat the animation continuously?
	bool slide;		// Slide from first frame to last, then back.
	bool hflip;		// Flip the animation horizontally?
	bool played_once;	// This is only used when loop == false
	float angle;		// Angle to rotate the images

	private:
	bool use_pivot;		// If it's going to pivot instead of just rotate
	int pivot_x;		// Location of pivot point on bitmap
	int pivot_y;
	int frames;		// Total number of frames in animation
	int wait_frames;	// How long to wait before changing frames
	float old_angle;	// Previous angle
};


struct CUTSCENE {
	CUTSCENE();
	void load(char*);
	int play(BITMAP*);	// Play the cutscene!

	DATAFILE* data;		// Datafile containing images
	float x;		// Location to draw on *target
	float y;
	int step;		// Current frame

	private:
	int frames;		// Total number of frames in cutscene
};

#endif
