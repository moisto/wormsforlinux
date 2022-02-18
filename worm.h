#ifndef WORM_H
#define WORM_H	1

#include "animation.h"
#include "misc.h"
#include "scope.h"

class WORM {

	public:
	
		BITMAP* terrain;		// Pointer to the terrain bitmap
		ANIMATION* animation;		// Points to the current animation sequence
		
		SCOPE scope;			// The weapon scope, for aiming

		ANIMATION anim_idle;
		ANIMATION anim_walk;
		ANIMATION anim_flip;
		ANIMATION anim_leap;
		ANIMATION anim_jump;
		
		char* name;			// The worm's name
		
		int health;			// The worm's health
		int direction;			// Direction is LEFT or RIGHT
		int rest;			// Cycles to rest before moving
		int his_turn;			// If its this worm's turn to play
		float x;			// Position of where the ANIMATION is displayed!
		float y;
		float xvel;			// Velocity of the worm
		float yvel;
		
		void spawn(BITMAP*);		// Spawn the worm (REQUIRED)
		void draw(BITMAP*);		// Draw the worm, weapon, and scope
		
		int X();			// Return the actual worm's position, not where the ANIMATION is!
		int Y();
		int walk(int);			// Walk LEFT or RIGHT
		int jump();			// The short, backwards jump
		int leap();			// The long jump forward
		int backflip();			// The classic worm backflip
		int process();			// Take care of everything
		int bind_to_map();		// Provide collision detection with the terrain
		int not_moving();		// Returns whether the worm is moving around
	
};

#endif
