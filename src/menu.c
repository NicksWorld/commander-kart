// Created by Alexander Hill and Nicholas McDaniel

#include <tgi.h>

#include "layout.h"
#include "track.h"

// Display the menu and return the number of players
int player_selection(void) {
	signed char segments[4];
	segments[0] = 0;
	segments[1] = 0;
	segments[2] = 0;
	segments[3] = 0;
	render_track(segments, 4, 0, 4, RENDER_BOTTOM);
	// ...
	return 0;
}
