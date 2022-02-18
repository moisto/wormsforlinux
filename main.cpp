#include <allegro.h>
#include "animation.h"
#include "gamestate.h"
#include "image.h"
#include "misc.h"
#include "projectile.h"
#include "scope.h"
#include "worm.h"


using namespace std;


// Function Prototypes
inline void play_sound(SAMPLE*, int, int, bool);
void initialize(int);
void pause_game(GAMESTATE*);
void game_over(GAMESTATE*);

// Global Variables
volatile int game_time;







void print_worm_info(BITMAP* target, WORM* worm) {
	
	if (!worm->his_turn && worm->not_moving()) {
	
	int w = text_length(font, worm->name) / 2;
	int h = text_height(font);
	
	
	rectfill(target, worm->X()-4-w, worm->Y()-94, worm->X()+w+4, worm->Y()+h-86, makecol(40, 0, 0));
	textout_centre(target, font, worm->name, worm->X(), worm->Y()-90, makecol(255, 0, 0));
	
	w = worm->health > 99 ? 16 : worm->health > 9 ? 10 : 5;
	
	rectfill(target, worm->X()-5-w, worm->Y()-74, worm->X()+w+4, worm->Y()+h-66, makecol(40, 0, 0));
	textprintf_centre_ex(target, font, worm->X(), worm->Y()-70, makecol(255, 0, 0), -1, "%i", worm->health);
	
	}
	
	return;
}





class CONTROLS {
	
	public:
		
	CONTROLS();
	
	int backspace_timer;
	int backspace_was_down;
	int backspace_strokes;
	
	int spacebar_was_down;
	
	int spacebar();
	int backspace();
};

CONTROLS::CONTROLS() {
	backspace_timer = 0;
	backspace_strokes = 0;
	backspace_was_down = false;
	
	spacebar_was_down = false;
}



int CONTROLS::spacebar() {
	if (key[KEY_SPACE]) {
		spacebar_was_down = true;
		return 1;
	} else {
		
		if (spacebar_was_down) {
			spacebar_was_down = 0;
			return 2;
		}
	}
	
	return 0;
}


int CONTROLS::backspace() {
	
	
	if (key[KEY_BACKSPACE]) {
		
		backspace_was_down = true;
		
	} else {

		// Now the backspace key is UP
		
		// Handle the timer
		if (backspace_timer)
			backspace_timer--;


		// If it was pressed and released
		if (backspace_was_down) {
			
			backspace_strokes++;
			
			// If the countdown hasn't started
			if (backspace_timer == 0)
				backspace_timer = 5;
		}
		
		backspace_was_down = false;
	}
	
	
	// Wait for the countdown to finish
	if (backspace_timer)
		return 0;
	
	// Return however many keystrokes were completed
	int total = backspace_strokes;
	
	backspace_strokes = 0;
	
	return total;
}






int main(int argc, char* argv[]) {
	
	
	if (argc > 1 && !strcmp(argv[1], "--window"))
		initialize(GFX_AUTODETECT_WINDOWED);
	else	initialize(GFX_AUTODETECT_FULLSCREEN);
	
	srand(time(NULL));
	
	GAMESTATE game;		// Game Engine variables
	
	PROJECTILE zook(BAZOOKA);
	
	BITMAP* cursor;
	BITMAP* background;
	BITMAP* terrain;
	
	WORM boggy;

	CONTROLS keyboard;
	
	
	cursor = load_bitmap("data/cursor_arrow.tga", desktop_pallete);
	background = load_bitmap("data/background_stars.tga", desktop_pallete);
	terrain = load_bitmap("data/terrain.tga", desktop_pallete);

	
	boggy.spawn(terrain);

	
	game.state = STATE_PLAYING;
	
	
	float myangle = 0;
	
	zook.terrain = terrain;
	
	
	WORM player2;
	
	player2.spawn(terrain);
	player2.name = "Howard Payne";
	
	boggy.his_turn = true;
	
	
	
	
	
	cout << "complete" << endl;	
	
	while (game.state == STATE_PLAYING) {

		// Logic
		while (game_time > 0) {
			
			
			if (key[KEY_ESC])
				game.state = STATE_QUIT;
			
			if (key[KEY_ENTER])
				boggy.leap();

			int bob = keyboard.backspace();
			
			if (bob == 2)
				boggy.backflip();
			
			if (bob == 1)
				boggy.jump();
			
			
			if (key[KEY_UP])
				myangle--;
			if (key[KEY_DOWN])
				myangle++;
			

			if (key[KEY_LEFT])
				boggy.walk(LEFT);

			if (key[KEY_RIGHT])
				boggy.walk(RIGHT);
			
			int joe = keyboard.spacebar();
			
			if (joe == 1)
				if (!zook.active)
					if (zook.power < 20)
						zook.power += 0.2;
			
			if (joe == 2)
				if (!zook.active) {
					zook.power = boggy.scope.weapon_power;
					zook.spawn(boggy.X() - zook.image->w/2, boggy.Y()  - 20 - zook.image->h/2, (int)(boggy.direction == LEFT ? 128 - boggy.scope.angle : boggy.scope.angle));
				}
			
			

			
			
			zook.process();
			

			
			
			
			boggy.process();
			player2.process();
			
			
			game_time--;
			
		}
		// End of Logic
		
		
		// Drawing
		acquire_screen();
		

		blit(background, game.buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		draw_sprite(game.buffer, terrain, 0, 0);

		print_worm_info(game.buffer, &player2);

		player2.draw(game.buffer);
		boggy.draw(game.buffer);
		
		
		zook.draw(game.buffer);
		
		


		draw_sprite(game.buffer, cursor, mouse_x, mouse_y);
		blit(game.buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		release_screen();
		
		// End of Drawing
	}

}


END_OF_MAIN();






void initialize(int windowmode) {
	
	cout << "Reticulating splines... " << flush;
	
	allegro_init();
	install_mouse();
	install_keyboard();
	//install_sound(DIGI_AUTODETECT, MIDI_NONE, NULL);
	install_timer();

	LOCK_VARIABLE(game_time);
	LOCK_FUNCTION(Timer);
	install_int_ex(Timer, BPS_TO_TIMER(60));

	text_mode(-1);
	set_color_depth(32);
	set_gfx_mode(windowmode, 800, 600, 0, 0);
	set_window_title("Worms for Linux!");
}



inline void play_sound(SAMPLE* snd, int volume, int pan, bool loop) {
		play_sample(snd, volume, pan, 1000, loop);
}
