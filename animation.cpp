#include <iostream>
#include "animation.h"


using namespace std;


ANIMATION::ANIMATION() {
	loop = true;
	slide = false;
	hflip = false;
	speed = 6;
}








void ANIMATION::load(char* path) {
	data = load_datafile(path);
	frames = items_in_datafile(data);
	step = 0;
	angle = 0;
	old_angle = 0;
	frame_direction = 1;
	wait_frames = speed;
	played_once = false;
}







void ANIMATION::pivot(int px, int py) {
	
	use_pivot = true;
	pivot_x = px;
	pivot_y = py;
	
	return;
}








void ANIMATION::play(BITMAP* target, int x, int y) {


	if (angle == 0) {
	
		if (hflip)
			draw_sprite_h_flip(target, (BITMAP*) data[step].dat, x, y);
		else
			draw_sprite(target, (BITMAP*) data[step].dat, x, y);
	}
	else {
		if (use_pivot)
			pivot_sprite(target, (BITMAP*) data[step].dat, x, y, pivot_x, pivot_y, itofix((int)angle));
		else
			rotate_sprite(target, (BITMAP*) data[step].dat, x, y, itofix((int)angle));
	}
	
	
	
	
	if (wait_frames-- == 0) {
		
		
		step += frame_direction;
		wait_frames = speed;
		
	
		if (played_once && loop == false) {
			
			if (frame_direction == 1)
				step = frames - 1;
			else	step = 0;
			
			return;
		}
		
		if (slide) {
			if (step == frames) {
				reverse();
				step = frames - 2;
			}
	
			if (step < 0) {
				reverse();
				step = 1;
				played_once = true;
			}
		
		}
		
		if (step == frames) {
			played_once = true;
			step = loop ? 0 : frames - 1;
		}
		
		if (step < 0)
			step = frames - 1;
	}
	
	return;
}








void ANIMATION::reverse() {

	frame_direction = -frame_direction;
	return;
}
















CUTSCENE::CUTSCENE() {
	x = 0;
	y = 0;
}








void CUTSCENE::load(char* path) {
	data = load_datafile(path);
	frames = items_in_datafile(data);
	step = 0;
}








int CUTSCENE::play(BITMAP* target) {
	draw_rle_sprite(target, (RLE_SPRITE*) data[step++].dat, (int)x, (int)y);
	
	if (step == frames) {
		--step;
		return 0;
	} else
		return 1;
}
