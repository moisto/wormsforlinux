#include "image.h"
#include <iostream>

using namespace std;

void IMAGE::load(char* path) {

	bitmap = load_bitmap(path, desktop_pallete);
	
	speed = 5;
	count = 0;
	
	wspeed = bitmap->w / speed;
	hspeed = bitmap->h / speed;
	
	pivot_x = bitmap->w / 2;
	pivot_y = bitmap->h / 2;

	return;
}








void IMAGE::hide() {
	
	if (visible && count == 0) {
		visible = false;
		count = speed;
	}
	
	return;
}








void IMAGE::show() {
	
	if (visible == false && count == 0) {
		visible = true;
		count = speed;
	}
	
	return;
}








void IMAGE::draw(BITMAP* target, int x, int y, float angle) {
	
	// Something executed show() or hide() recently
	if (count != 0) {
		
		int ws = count * wspeed;
		int hs = count * hspeed;
		
		count--;
		
		if (!visible) {
			ws = ((speed - 1) * wspeed) - ws;
			hs = ((speed - 1) * hspeed) - hs;
		}
		
		
		pivot_scaled_sprite(target, bitmap, x, y, pivot_x, pivot_y, ftofix(angle), ftofix((float)hs / (float)bitmap->h));
		
		return;
	}
	
	if (visible)
		pivot_sprite(target, bitmap, x, y, pivot_x, pivot_y, ftofix(angle));
	
	return;
}
