// Created by Alexander Hill and Nicholas McDaniel

#include <cx16.h>
#include <tgi.h>

#include "menu.h"
#include "vera.h"

void main(void) {
	int players;
	vera_init();
	players = player_selection();
	while(1) {}
}
