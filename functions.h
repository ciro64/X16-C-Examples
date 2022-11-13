void set_video(uint8_t sprites_enable, uint8_t layer1_enable, uint8_t layer0_enable, uint8_t chroma_disable, uint8_t output_mode) {
	//vera_sprites_enable(1) can be used in cc65 if you just want to enable sprites
	
	POKE(0x9F29, (sprites_enable << 6) | (layer1_enable << 5) | (layer0_enable << 4) | (chroma_disable << 2) | (output_mode << 0));
}

void set_scale(uint8_t width_mul, uint8_t height_mul) {
	POKE(0x9F2A, 256 >> width_mul);
	POKE(0x9F2B, 256 >> height_mul);
}

void set_sprite(uint16_t index, uint32_t address, uint8_t mode, uint16_t x, uint16_t y, uint8_t h_flip, uint8_t v_flip, uint8_t z_depth, uint8_t collision_mask, uint8_t palette_offset, uint8_t width, uint8_t height) {
	//data0 is a VRAM data port that can auto-increment its address everytime it's accessed
	//By vpoking into 0 we can set that address
	
	vpoke(0, 0x11FC00 + index * 8);
	VERA.data0 = (mode << 7) | (address >> 13);
	VERA.data0 = x & 0xFF;
	VERA.data0 = x >> 8;
	VERA.data0 = y & 0xFF;
	VERA.data0 = y >> 8;
	VERA.data0 = (collision_mask << 4) | (z_depth << 2) | (v_flip << 1) | (h_flip << 0);
	VERA.data0 = (height << 6) | (width << 4) | (palette_offset << 0);
}

void load_sprite(uint32_t relative_address, const uint8_t *data, uint8_t width, uint8_t height) {
	uint16_t i;
	vpoke(0, 0x110000 + relative_address);
	for (i = 0; ++i < width*height; )
		VERA.data0 = data[i];
}
