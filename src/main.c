// Created by Alexander Hill and Nicholas McDaniel

#include <tgi.h>

#include "menu.h"
#include "vera.h"

void main(void) {
	int players;
	//tgi_install(tgi_static_stddrv);
	//tgi_init();
	vera_init();
	//players = player_selection();
	while(1) {}
	// ...
	tgi_done();
	tgi_uninstall();
}
