#ifndef PROJECTILE_H
#define PROJECTILE_H	1


#define BAZOOKA		1
#define BAZOOKA_DAMAGE	30
#define SHOTGUN		2
#define SHOTGUN_DAMAGE	25
#define LANDMINE	3
#define LANDMINE_DAMAGE	40


#include <iostream>
#include <math.h>
#include <allegro.h>
#include "misc.h"

class PROJECTILE {
	
	public:
	
		BITMAP* image;			// Image of the projectile
		BITMAP* terrain;
	
		int max_damage;			// Max amount of damage this projectile can inflict
		int angle;			// Angle to rotate the image
		int prev_angle;
		float x;			// Location
		float y;
		float xvel;			// Velocities
		float yvel;
		float power;
		
		bool active;
		bool hit;			// If the projectile hit something


		PROJECTILE(int);
		int X();
		int Y();
		int bind_to_map();
		int process();
		void spawn(int, int, int);
		void draw(BITMAP*);
};

#endif
