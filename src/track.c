// Created by Alexander Hill and Nicholas McDaniel

#include <tgi.h>

#include "layout.h"

#define ROAD_HEIGHT 100
#define ROAD_WIDTH 8

void render_track(signed char angle[], int length, int start_index, int render_distance, int offset) {
	int left, right, segment, y_size, middle, x, dx, angle_index, row, y, old_mid, total_rows;
	middle = tgi_getmaxx() >> 1;
	y_size = ROAD_HEIGHT / render_distance;
	dx = angle[start_index];
	x = 0;
	angle_index = start_index;
	total_rows = 100;
	for(segment = 0; segment < render_distance; ++segment) {
		if(angle_index >= length) {
			angle_index = 0;
		}
		old_mid = middle;
		for(y = 0; y < 25; ++y) {
			row = ((4 - segment) * 25) - y;
			left = middle - ((row << 1) + ROAD_WIDTH);
			right = middle + ((row << 1) + ROAD_WIDTH);
			if(segment & 1) {
				tgi_setcolor(COLOR_GRASS_LIGHT);
			} else {
				tgi_setcolor(COLOR_GRASS_DARK);
			}
			tgi_line(0, offset + row, left, offset + row);
			tgi_line(right, offset + row, tgi_getmaxx(), offset + row);
			tgi_setcolor(COLOR_ROAD);
			// tgi_line(left, offset + row, right, offset + row);
			middle = old_mid - (((x + dx) * y) / 25);
		}
		middle = old_mid - (x + dx);
		x += dx;
		dx += angle[angle_index];
		++angle_index;
	}
}
