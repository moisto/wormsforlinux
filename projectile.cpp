#include "projectile.h"


using namespace std;

PROJECTILE::PROJECTILE(int type) {
	
	char* path;
	
	switch (type) {
		case BAZOOKA:
			path = "data/bazooka.tga";
			max_damage = BAZOOKA_DAMAGE;
			break;
		case SHOTGUN:
			path = "data/shotgun.tga";
			max_damage = SHOTGUN_DAMAGE;
			break;
		case LANDMINE:
			path = "data/landmine.tga";
			max_damage = LANDMINE_DAMAGE;
			break;	
	}
	
	image = load_bitmap(path, desktop_pallete);

	active = false;
	hit = false;
	
	power = 0;
}








int PROJECTILE::X() {
	return (int)x + image->w/2;
}







int PROJECTILE::Y() {
	return (int)y + image->h/2;
}







int PROJECTILE::bind_to_map() {

	
	// Update the coordinates
	x += xvel;
	y += yvel;

	
	if (y >= 0)

	// If the worm is colliding with the map
	if (!pink_pixel(terrain, X(), Y())) {
		//x -= xvel; // When pixel dection is perfect, uncomment these lines!
		//y -= yvel;
		
		// If gravity is forcing the object collision.
		if (pink_pixel(terrain, X(), int(Y() - GRAVITY)))
			y -= GRAVITY; // Don't let it happen.
		
		
		// Stop all motion (This is bad physics)
		xvel = 0;//-xvel * 0.5;
		yvel = 0;//-yvel * 0.3;
		active = false;
		hit = true;
		power = 0;
		
		circlefill(terrain, X(), Y(), 50, PINK);
	}
	
}









int PROJECTILE::process() {
	
	if (hit == true)
		hit = false;
	
	if (active) {
		
		int prev_x = (int)x;
		int prev_y = (int)y;
		
		yvel += GRAVITY;
		
		bind_to_map();
		
		angle = (int)(atan((y - prev_y) / (x - prev_x)) * 32);
		
		if (x > prev_x)
			angle = 128 + angle;
	}
	
	return 0;
}








void PROJECTILE::spawn(int sx, int sy, int a) {
	x = sx;
	y = sy;
	xvel = power * cos((a * MATH_PI) / 128);
	yvel = power * sin((a * MATH_PI) / 128);
	active = true;
	hit = false;
}








void PROJECTILE::draw(BITMAP* target) {
	
	if (active)
		rotate_sprite(target, image, x, y, itofix(angle));
	
	return;
}
