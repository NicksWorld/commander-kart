// Created by Alexander Hill and Nicholas McDaniel

#include <cx16.h>

#define COLOR_GRASS_DARK 0x162
#define COLOR_GRASS_LIGHT 0x283
#define COLOR_ROAD 0x555
#define COLOR_SKY 0x6CC

void vera_init(void) {
	long i;

	// Disable both layers to draw faster
	vera_layer_enable(0b00);

	VERA.display.hscale = 64;
	VERA.display.vscale = 64;

	// Layer 0: 32x32 16x16 tiles 2bpp @ $12C00
	// | Map Height | Map width | T256C  | Bitmap Mode | Color Depth |
	// | 00 -> 32   | 00 -> 32  | 0 -> ? | 0 -> No     | 01 -> 2 bpp |
	VERA.layer0.config = 0b00000001;
	VERA.layer0.mapbase = 0x96;
	VERA.layer0.tilebase = 0x9F;
	// Shift the output image upward
	VERA.layer0.vscroll = 8;

	// Layer 1: 320x240 bitmap 8bpp @ $00000
	// | Map Height | Map width | T256C  | Bitmap Mode | Color Depth |
	// | 00 -> 32   | 00 -> 32  | 0 -> ? | 1 -> Yes    | 11 -> 8 bpp |
	VERA.layer1.config = 0b00000111;
	VERA.layer1.tilebase = 0x00;
	// Set the palette offset to 0
	VERA.layer1.hscroll = 0x0000;

	// Palette initialization (Range = $1FA00-$1FBFF) (Each color requires 2 bytes)
	vpoke((unsigned char)(COLOR_SKY & 0xFF), 0x1FA00);
	vpoke((unsigned char)(COLOR_SKY >> 8), 0x1FA01);
	vpoke((unsigned char)(COLOR_ROAD & 0xFF), 0x1FA02);
	vpoke((unsigned char)(COLOR_ROAD >> 8), 0x1FA03);
	vpoke((unsigned char)(COLOR_GRASS_DARK & 0xFF), 0x1FA04);
	vpoke((unsigned char)(COLOR_GRASS_DARK >> 8), 0x1FA05);
	vpoke((unsigned char)(COLOR_GRASS_LIGHT & 0xFF), 0x1FA06);
	vpoke((unsigned char)(COLOR_GRASS_LIGHT >> 8), 0x1FA07);

	// Tileset initialization @ $13800 (0x9C)
	for(i = 0; i < 64; ++i) {
		// Sky color
		vpoke(0x00, 0x13800 + i);
		// Road color
		vpoke(0x55, 0x13840 + i);
	}

	// Tilemap initialization @ $12c00
	for(i = 0; i < 512; i += 2) {
		// Sky rendering
		vpoke(0x00, 0x12C00 + i);
		vpoke(0x00, 0x12C01 + i);

		// Road rendering
		vpoke(0x01, 0x12E00 + i);
		vpoke(0x00, 0x12E01 + i);
	}

	// Bitmap initialization (320x240 8bpp) @ $00000
	for(i = 0; i < 76800; ++i) {
		// Insert the palette color (0x00 = transparent)
		vpoke(0x00, i);
	}

	// Poof! Both layers appear!
	vera_layer_enable(0b11);
}

void vera_track(unsigned char color, int row, int left, int right) {
	long base, i, skip;
	base = row * 320;
	skip = base + right;
	VERA.address = (unsigned short)(base & 0xFFFF);
	VERA.address_hi = VERA_INC_1 | (base >> 16);
	for(i = 0; i < left; ++i) {
		VERA.data0 = color;
	}
	VERA.address = skip & 0xFFFF;
	VERA.address_hi = VERA_INC_1 | (skip >> 16);
	for(i = right; i < 320; ++i) {
		VERA.data0 = color;
	}
}
