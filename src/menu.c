// Created by Alexander Hill and Nicholas McDaniel

#include <tgi.h>

#include "layout.h"
#include "track.h"

// Display the menu and return the number of players
int player_selection(void) {
	signed char segments[4];
	segments[0] = 10;
	segments[1] = 5;
	segments[2] = -10;
	segments[3] = -5;
	render_track(segments, 4, 0, RENDER_BOTTOM-1);
	// ...
	return 0;
}
