// Created by Alexander Hill and Nicholas McDaniel

#include <tgi.h>

#include "layout.h"
#include "vera.h"

#define ROAD_HEIGHT 120
#define ROAD_WIDTH 8

#define Y_SIZE 30 // Initially 25

/*
  How it works:
  There are 4 segments rendered at a time (defined as the angles in angle[]).
  Each segment is affected by its own angle in addition to the previous angles.

  x, dx = See https://codeincomplete.com/articles/javascript-racer-v2-curves/

  old_mid = Helps adjust for the lack of floating point math.
  This variable causes any lost values to be made up before the next segment.

  vera_track(color, row_num, left_side, right_side) = Draws the road using the
  VERA on a 320x240 8bpp bitmap at the address $00000. Responsible for drawing
  the grass on top of the road color layer.
 */
void render_track(signed char angle[], int length, int start_index, int offset) {
	int left, right, segment, middle, x, dx, angle_index, row, y, old_mid;
	middle = 160; // 320 / 2
	dx = angle[start_index] >> 1; // Lessen the initial angle (Optional)
	x = 0;
	angle_index = start_index;
	
	for(segment = 0; segment < 4; ++segment) {
		if(angle_index >= length) {
			angle_index = 0;
		}
		old_mid = middle; // Is old_mid useless?
		for(y = 0; y < Y_SIZE; ++y) {
			row = ((4 - segment) * Y_SIZE) - y;
			left = middle - ((row << 1) + ROAD_WIDTH);
			right = middle + ((row << 1) + ROAD_WIDTH);
			if(segment & 1) {
			  vera_track(COLOR_GRASS_LIGHT, offset + row, left, right);
			} else {
			  vera_track(COLOR_GRASS_DARK, offset + row, left, right);
			}
			middle = old_mid - (((x + dx) * y) / Y_SIZE);
		}
		middle = old_mid - (x + dx);
		x += dx;
		dx += angle[angle_index];
		++angle_index;
	}
}
