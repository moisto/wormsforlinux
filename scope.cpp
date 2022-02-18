#include "scope.h"

using namespace std;


SCOPE::SCOPE() {
	
	// Load the scope image!
	images = load_datafile("data/anim_scopezoom.dat");
	powergauge = load_datafile("data/anim_powergauge.dat");
	
	animation = images;

	angle = 0;
	current_frame = 0;
	frame_count = items_in_datafile(images) - 1;
	appear = frame_count;
	vanish = 0;
	pivot_x = 0;
	pivot_y = 14;
	
	weapon_power = 0;
	
	show();
}








void SCOPE::show() {

	if (!active) {
		active = true;
		appear = frame_count;
		vanish = 0;
	}
	
	return;
}








void SCOPE::hide() {

	if (active) {
		active = false;
		vanish = frame_count;
		appear = 0;
	}
	
	return;
}








void SCOPE::draw(BITMAP* target, int x, int y, int direction) {
	
	if (weapon_power > 0) {
		pivot_sprite(target, (BITMAP*) animation[(int)weapon_power].dat, x, y, pivot_x, pivot_y, ftofix(direction == LEFT? 128 - angle : angle));
	}
	else
	if (active || vanish > 0) {
		
		pivot_sprite(target, (BITMAP*) images[current_frame>frame_count?frame_count:current_frame].dat, x, y, pivot_x, pivot_y, ftofix(direction == LEFT? 128 - angle : angle));	
	}
	
	return;
}








int SCOPE::process() {
	
	
	if (key[KEY_SPACE]) {
		if (animation == images) {
			animation = powergauge;
			current_frame = 0;
		}
		
		if (weapon_power < 19)
			weapon_power += 0.3;

	} else
		if (animation == powergauge) {
			current_frame = 5;
			animation = images;
			weapon_power = 0;
		}
	
	
	if (active) {
		
		
		if (appear > 0) {
			current_frame = frame_count - appear;
			appear--;
		} else
			if (animation == images)
				current_frame = frame_count;


		if (key[KEY_UP] && angle > -64)
			angle -= 0.5;
			
		if (key[KEY_DOWN] && angle < 64)
			angle += 0.5;
		
	} else {
			if (vanish > 0) {
				current_frame = vanish;
				vanish--;
			}
	}
	
	return 0;
}
