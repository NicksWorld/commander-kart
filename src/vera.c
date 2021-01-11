// Created by Alexander Hill

#include <cx16.h>

#define COLOR_GRASS_DARK 0x162
#define COLOR_GRASS_LIGHT 0x283
#define COLOR_ROAD 0x555
#define COLOR_SKY 0x6CC

void vera_init(void) {
	long i;
	// Palette initialization
	vpoke((unsigned char)(COLOR_SKY & 0xFF), 0x1FA02);
	vpoke((unsigned char)(COLOR_SKY >> 8), 0x1FA03);
	vpoke((unsigned char)(COLOR_ROAD & 0xFF), 0x1FA04);
	vpoke((unsigned char)(COLOR_ROAD >> 8), 0x1FA05);
	vpoke((unsigned char)(COLOR_GRASS_DARK & 0xFF), 0x1FA06);
	vpoke((unsigned char)(COLOR_GRASS_DARK >> 8), 0x1FA07);
	vpoke((unsigned char)(COLOR_GRASS_LIGHT & 0xFF), 0x1FA08);
	vpoke((unsigned char)(COLOR_GRASS_LIGHT >> 8), 0x1FA09);
	// Tileset initialization @ $13800
	for(i = 0; i < 64; ++i) {
		vpoke(0x00, 0x13800 + i);
	}
	for(i = 0; i < 64; ++i) {
		vpoke(0x55, 0x13840 + i);
	}
	// Layer 0: 32x32 16x16 tiles 2bpp @ $12C00
	VERA.layer0.config = 0x01;
	VERA.layer0.mapbase = 0x96;
	VERA.layer0.tilebase = 0x9F;
	VERA.layer0.vscroll = 8;
	// Layer 1: 320x240 bitmap 8bpp @ $00000
	VERA.layer1.config = 0x07;
	VERA.layer1.tilebase = 0x00;
	VERA.layer1.hscroll = 0x0000;
	// Background initialization
	for(i = 0; i < 512; i += 2) {
		vpoke(0x00, 0x12C00 + i);
		vpoke(0x00, 0x12C01 + i);
	}
	for(i = 0; i < 512; i += 2) {
		vpoke(0x01, 0x12E00 + i);
		vpoke(0x00, 0x12E01 + i);
	}
	// Clear bitmap layer
	for(i = 0; i < 76800; ++i) {
		vpoke(0x00, i);
	}
}
