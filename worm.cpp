#include <iostream>
#include "worm.h"

using namespace std;



void WORM::spawn(BITMAP* t) {

	// Set the terrain pointer!
	terrain = t;
	
	// Load the worm animations!
	anim_idle.load("data/worm_idle.dat");
	anim_walk.load("data/worm_walk.dat");
	anim_flip.load("data/worm_backflip.dat");
	anim_leap.load("data/worm_leap.dat");
	anim_jump.load("data/worm_jump.dat");
	
	// Turn off looping for these animations
	anim_flip.loop = false;
	anim_flip.speed = 2;
	anim_leap.loop = false;
	anim_leap.speed = 2;
	anim_jump.loop = false;
	anim_jump.speed = 2;
	
	
	// Set the current animation to "idle"
	animation = &anim_idle;

	// Pick a direction to start facing
	if ((direction = rand() % 2 ? LEFT : RIGHT) == RIGHT) {
		anim_idle.hflip = true;
		anim_walk.hflip = true;
		anim_jump.hflip = true;
		anim_leap.hflip = true;
		anim_flip.hflip = true;
	}
	
	// Give it a name
	name = "Unnamed Soldier";
	
	// Full health
	health = 100;
	
	// Spawn at a random location
	x = 100 + rand() % (SCREEN_W - 200);
	y = 10;

	xvel = 1;
	yvel = 0;
	
	rest = 0;
	
	his_turn = false;

	return;
}








int WORM::X() {
	return int(x + 20);
}








int WORM::Y() {
	return int(y + 50);
}








int WORM::jump() {

	if (not_moving() && rest == 0) {
		
		if (animation != &anim_jump) {
			anim_jump.hflip = animation->hflip;
			anim_jump.step = 0;
			anim_jump.played_once = false;
			animation = &anim_jump;
		}
		
		xvel = -direction * 0.6;
		yvel = -6;
		
		rest = 7;
	}
				
	return 0;
}








int WORM::leap() {
	
	if (not_moving() && rest == 0) {
		
		if (animation != &anim_leap) {
			anim_leap.hflip = animation->hflip;
			anim_leap.step = 0;
			anim_leap.played_once = false;
			animation = &anim_leap;
		}
				
		xvel = direction * 4;
		yvel = -5.5;
		
		rest = 12;
	}
	
	return 0;
}








int WORM::backflip() {
	
	if (not_moving() && rest == 0) {
		
		if (animation != &anim_flip) {
			anim_flip.hflip = animation->hflip;
			anim_flip.step = 0;
			anim_flip.played_once = false;
			animation = &anim_flip;
		}
		
		xvel = -direction * 0.7;
		yvel = -10;
		
		rest = 7;
	}
	
	return 0;
}








int WORM::walk(int d) {

	if (not_moving() && rest == 0) {	
		
		if (direction != d) {
			direction = d;
			anim_walk.hflip = !anim_walk.hflip;
			rest = 7;
		} else {
			xvel = direction;
			yvel -= GRAVITY;
		}
		
		if (animation != &anim_walk)
			animation = &anim_walk;
	}
	
	return 0;
}








int WORM::not_moving() {
	// Determines if the worm is moving.
	// In my physics "engine", gravity is ALWAYS pushing down,
	// so this function ignores the pull of gravity.
	return xvel == 0 && abs((int)yvel) <= GRAVITY;
}








int WORM::bind_to_map() {

	
	// Update the coordinates
	x += xvel;
	y += yvel;

	if (x >= 0 && x < terrain->w && y >= 0 && y < terrain->h)

	// If the worm is colliding with the map
	if (!pink_pixel(terrain, X(), Y())) {
		x -= xvel;
		y -= yvel;
		
		// If gravity is forcing the object collision.
		if (pink_pixel(terrain, X(), int(Y() - GRAVITY)))
			y -= GRAVITY; // Don't let it happen.
		
		
		if (yvel > 12) {
			health = health - yvel/2.5;
			//his_turn = false;
		}
		
		// Stop all motion (This is bad physics)
		xvel = 0;//-xvel * 0.5;
		yvel = 0;//-yvel * 0.3;
	}
	
}








int WORM::process() {
	
	// Forget about really small numbers
	if ((xvel > 0 && xvel < 0.3) || (xvel < 0 && xvel > -0.3))
		xvel = 0;
	
	if ((yvel > 0 && yvel < 0.3) || (yvel < 0 && yvel > -0.3))
		yvel = 0;	

	
	
	// When the worm isn't doing anything.
	if (not_moving()) {
		
		if (rest > 0)
			rest--;

		// If the worm is standing still, show the weapon scope.
		scope.show();
		
		// If I haven't updated the animation yet.
		if (animation != &anim_idle) {
			anim_idle.hflip = animation->hflip;
			animation = &anim_idle;
		}

	} else {
		// If the worm IS moving, hide the weapon scope.
		scope.hide();
	}	
	

	
	// Handle the weapon scope
	scope.process();
	
	// Add the gravity
	yvel += GRAVITY;
	
	// Handle terrain collision
	bind_to_map();
	
	return 0;
}








void WORM::draw(BITMAP* target) {
	
	// Draw the worm
	animation->play(target, (int)x, (int)y);
	
	if (his_turn) {
		
		// Draw the scope (if it's active)
		
		scope.draw(target, X(), Y() - 20, direction);
	}
	
	return;
}

