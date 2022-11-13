#include <stdint.h>
#include <stdio.h>
#include <stdint.h>
#include <conio.h>
#include <cbm.h>
#include <peekpoke.h>

#include "constants.h"
#include "functions.h"

static const
#include "arrow_data.inc"


#define arrow_count 4

uint16_t screen_width = 320;
uint16_t screen_height = 240;
uint8_t arrow_speed = 2;
uint8_t arrow_width = 32;
uint8_t arrow_height = 32;
int16_t arrows_x[arrow_count] = { 20, 40, 60, 80 };
int16_t arrows_y[arrow_count] = { 10, 20, 30, 40 };
int8_t arrows_dir_x[arrow_count] = { 1, 1, -1, -1 };
int8_t arrows_dir_y[arrow_count] = { 1, -1, 1, -1 };

void update();
void move_sprite(uint8_t i);


void main(void) {
	uint8_t i = 0;
	
	set_scale(2,2);
	
	set_video(
		1, //sprites enable 
		0, //layer1 enable
		1, //layer0 enable
		0, //chroma disable
		OUTPUT_VGA //output mode
	);
	
	for (i = 0; i < arrow_count; i++) {
		set_sprite(
			i, // sprite index
			0x010000, // vram graphics address
			SPRITE_MODE_8_BPP, // mode (bytes per pixel)
			0, // x
			0, // y
			0, // horizontal flip
			0, // vertical flip
			SPRITE_Z_FRONT, // z-depth
			0, // collision mask
			0, // palette offset
			SPRITE_SIZE_32, // width
			SPRITE_SIZE_32 // height
		);
	}
	
	load_sprite(0, arrow_data, 64, 64);

	update();
}


void update() {
	uint8_t i;
	do {
		for (i = 0; i < arrow_count; i++) {
			
			move_sprite(i);
			
			set_sprite(
				i, // sprite index
				0x010000, // vram graphics address
				SPRITE_MODE_8_BPP, // mode (bytes per pixel)
				arrows_x[i], // x
				arrows_y[i], // y
				arrows_dir_x[i] > 0 ? 0 : 1, // horizontal flip
				arrows_dir_y[i] > 0 ? 0 : 1, // vertical flip
				SPRITE_Z_FRONT, // z-depth
				0, // collision mask
				0, // palette offset
				SPRITE_SIZE_32, // width
				SPRITE_SIZE_32 // height
			);
		}
		
		waitvsync();
	} while(1);
}


void move_sprite(uint8_t i) {
	
	arrows_x[i] = arrows_x[i] + (arrow_speed * arrows_dir_x[i]);
	if (arrows_x[i] < 0) {
		arrows_x[i] = 0;
		arrows_dir_x[i] = -arrows_dir_x[i];
	} else if (arrows_x[i] > screen_width-1 - arrow_width) {
		arrows_x[i] = screen_width-1 - arrow_width;
		arrows_dir_x[i] = -arrows_dir_x[i];
	}
	
	arrows_y[i] = arrows_y[i] + (arrow_speed * arrows_dir_y[i]);
	if (arrows_y[i] < 0) {
		arrows_y[i] = 0;
		arrows_dir_y[i] = -arrows_dir_y[i];
	} else if (arrows_y[i] > screen_height-1 - arrow_height) {
		arrows_y[i] = screen_height-1 - arrow_height;
		arrows_dir_y[i] = -arrows_dir_y[i];
	}
	
}
