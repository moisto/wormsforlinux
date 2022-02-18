#include "misc.h"


// Internal game timer
void Timer() {
	game_time++;
} END_OF_FUNCTION(Timer);








// Return the number of items inside a datafile
int items_in_datafile(DATAFILE* data) {
	int len = 0;
	while (data[len].type != DAT_END)
		len++;
	
	return len - 1;
}







// Check if a certain pixel is transparent pink (#ff00ff)
int pink_pixel(BITMAP* bmp, int x, int y) {
	
	//if ((x >= 0 && x <= bmp->w) && (y >= 0 && y <= bmp->h)) {
	
		if (getpixel(bmp, x, y) == PINK)
			return 1;
	//}
	
	return 0;
}









