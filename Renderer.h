
typedef int s32;
typedef unsigned int u32;

inline int clamp(int min, int val, int max)
{
	if (val < min) return min;
	if (val > max) return max;
	return val;
}
static void
clear_screen(u32 color) {
	unsigned int* pixel = (u32*)render_state.memory;
	for (int y = 0; y < render_state.height; y++) {
		for (int x = 0; x < render_state.width; x++) {
			*pixel++ = color;
		}
	}
}

static void
draw_rect_in_pixels(int x0, int y0, int x1, int y1, u32 color) {

	x0 = clamp(0, x0, render_state.width);
	x1 = clamp(0, x1, render_state.width);
	y0 = clamp(0, y0, render_state.height);
	y1 = clamp(0, y1, render_state.height);

	for (int y = y0; y < y1; y++) {
		u32* pixel = (u32*)render_state.memory + x0 + y * render_state.width;
		for (int x = x0; x < x1; x++) {
			*pixel++ = color;
		}
	}
}

static float render_scale = 0.01f;

static void
draw_arena_borders(float x, float y,float arena_x, float arena_y, u32 color) {
	x *= render_state.height * render_scale;
	y *= render_state.height * render_scale;
	arena_x *= render_state.height * render_scale;
	arena_y *= render_state.height * render_scale;

	x += render_state.width / 2.f;
	y += render_state.height / 2.f;

	// Change to pixels
	float x0 = x - arena_x;
	float x1 = x + arena_x;
	float y0 = y - arena_y;
	float y1 = y + arena_y;

	draw_rect_in_pixels(0, 0, render_state.width, render_state.height, color);
	draw_rect_in_pixels((int)x0, (int)y0, (int)x1, (int)y1, 0xffffffff);
	//draw_rect_in_pixels(0, render_state.height,x1, y1, color);
	//draw_rect_in_pixels(x1, y1, render_state.width, 0, color);
	//draw_rect_in_pixels(0, y1, x1, render_state.height, color);
	//draw_rect_in_pixels(x0, y1, render_state.width, render_state.height, color);
	//draw_rect_in_pixels(x1, y0, render_state.width, render_state.height, color);
}

static void
draw_rect(float x, float y, float half_size_x, float half_size_y, u32 color) {

	//int temp = render_state.height * render_scale;
	x *= render_state.height * render_scale;
	y *= render_state.height * render_scale;
	half_size_x *= render_state.height * render_scale;
	half_size_y *= render_state.height * render_scale;

	x += render_state.width / 2.f;
	y += render_state.height / 2.f;

	// Change to pixels
	float x0 = x - half_size_x;
	float x1 = x + half_size_x;
	float y0 = y - half_size_y;
	float y1 = y + half_size_y;

	draw_rect_in_pixels((int)x0, (int)y0, (int)x1, (int)y1, color);
}
static void
draw_borders(float x1,float y1,float half_size_x1, float half_size_y1, float x2, float y2, float half_size_x2, float half_size_y2, u32 color) {
	x1 *= render_state.height * render_scale;
	y1 *= render_state.height * render_scale;
	x1 += render_state.width / 2.f;
	y1 += render_state.height / 2.f;

	x2 *= render_state.height * render_scale;
	y2 *= render_state.height * render_scale;
	x2 += render_state.width / 2.f;
	y2 += render_state.height / 2.f;

	/*half_size_x *= render_state.height * render_scale;
	half_size_y *= render_state.height * render_scale;*/
	float x_1 = x1 - half_size_x1;
	float x_2 = x1 + half_size_x1;
	float y_1 = y1 - half_size_y1;
	float y_2 = y1 + half_size_y1;

	float x_3 = x2 - half_size_x2;
	float x_4 = x2 + half_size_x2;
	float y_3 = y2 - half_size_y2;
	float y_4 = y2 + half_size_y2;

	draw_rect_in_pixels((int)x_1, (int)y_1, (int)x_2, (int)y_2, color);
	draw_rect_in_pixels((int)x_3, (int)y_3, (int)x_4, (int)y_4, 0xffffffff);
}

static bool checkWall(float x)
{
	x*= render_state.height * render_scale;
	x+= render_state.width / 2.f;
	if (x > 0)
		return true;
	return false;
}
//x: trung tam dino, y: trung taam dino
static void draw_truck(float x, float y, float half_size_x, float half_size_y)
{

	draw_rect(x, y + 1, 3.5, 2, 0xfff0000);

	draw_rect(x, y - 0.5, 5, 1.5, 0x1820FAA);
	draw_rect(x+2.5, y-2.5 , 1, 1, 0x1820FAA);
	draw_rect(x -1.5, y - 2.5, 1, 1, 0x1820FAA);

	draw_rect(x + 2, y + 1, 2.5, 3, 0x1820FF);
	draw_rect(x + 2, y + 1, 3, 2.5, 0x1820FF);
	//draw_rect(x + 3, y, 2, 0.5, 0x1820FF);
}
static void draw_dino(float x, float y, float half_size_x, float half_size_y)
{
	draw_rect(x + 3,y + 0.7, 2, 0.2, 0x000000);
	draw_rect(x,y - 3, 7 + 0.2, 1.5 + 0.2, 0x000000);

	draw_rect(x,y - 4.5, 2 + 0.2, 2 + 0.2, 0x000000);
	draw_rect(x + 1,y - 4.5 - 2, 2 + 0.2, 0.5 + 0.2, 0x000000);
	draw_rect(x + 2,y - 4.5 - 3, 2 + 0.2, 0.5 + 0.2, 0x000000);
	draw_rect(x + 3,y - 4.5 - 4, 1.5 + 0.2, 0.5 + 0.2, 0x000000);
	draw_rect(x + 4,y - 4.5 - 5, 1. + 0.2, 0.5 + 0.2, 0x000000);
	draw_rect(x + 4.5,y - 4.5 - 5.5, 0.9 + 0.2, 0.1 + 0.5, 0x000000);


	draw_rect(x + 3,y, 2, 0.5, 0x1820FF);
	draw_rect(x + 2,y - 1, 2, 0.5, 0x1820FF);
	draw_rect(x + 1,y - 2, 2, 0.5, 0x1820FF);
	draw_rect(x,y - 3, 2, 0.5, 0x1820FF);

	draw_rect(x,y - 3, 7, 1.5, 0x1820FF);


	draw_rect(x,y - 4.5, 2, 2, 0x1820FF);
	draw_rect(x + 1,y - 4.5 - 2, 2, 0.5, 0x1820FF);
	draw_rect(x + 2,y - 4.5 - 3, 2, 0.5, 0x1820FF);
	draw_rect(x + 3,y - 4.5 - 4, 1.5, 0.5, 0x1820FF);
	draw_rect(x + 4,y - 4.5 - 5, 1., 0.5, 0x1820FF);
	draw_rect(x + 4.5,y - 4.5 - 5.5, 0.9, 0.1, 0x1820FF);

	//draw_rect_in_pixels((int)x0, (int)y0, (int)x1, (int)y1, 0x1820FF);
}
static const char* letters[][7] = {
	" 00",
	"|  0",
	"|  0",
	"|000",
	"|  0",
	"|  0",
	"|  0",

	"|00",
	"|  0",
	"|  0",
	"|00",
	"|  0",
	"|  0",
	"|00",

	" 000",
	"0",
	"0",
	"0",
	"0",
	"0",
	" 000",

	"000",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"000",

	"0000",
	"0",
	"0",
	"000",
	"0",
	"0",
	"0000",

	"0000",
	"0",
	"0",
	"000",
	"0",
	"0",
	"0",

	" 000",
	"0",
	"0",
	"0 00",
	"0  0",
	"0  0",
	" 000",

	"0  0",
	"0  0",
	"0  0",
	"0000",
	"0  0",
	"0  0",
	"0  0",

	"000",
	" 0",
	" 0",
	" 0",
	" 0",
	" 0",
	"000",

	" 000",
	"   0",
	"   0",
	"   0",
	"0  0",
	"0  0",
	" 000",

	"0  0",
	"0  0",
	"0 0",
	"00",
	"0 0",
	"0  0",
	"0  0",

	"0",
	"0",
	"0",
	"0",
	"0",
	"0",
	"0000",

	"00 00",
	"0 0 0",
	"0 0 0",
	"0   0",
	"0   0",
	"0   0",
	"0   0",

	"00  0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	"0  00",

	"0000",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0000",

	" 000",
	"0  0",
	"0  0",
	"000",
	"0",
	"0",
	"0",

	" 000 ",
	"0   0",
	"0   0",
	"0   0",
	"0 0 0",
	"0  0 ",
	" 00 0",

	"000",
	"0  0",
	"0  0",
	"000",
	"0  0",
	"0  0",
	"0  0",

	" 000",
	"0",
	"0 ",
	" 00",
	"   0",
	"   0",
	"000 ",

	"000",
	" 0",
	" 0",
	" 0",
	" 0",
	" 0",
	" 0",

	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	" 00",

	"0   0",
	"0   0",
	"0   0",
	"0   0",
	"0   0",
	" 0 0",
	"  0",

	"0   0 ",
	"0   0",
	"0   0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	" 0 0 ",

	"0   0",
	"0   0",
	" 0 0",
	"  0",
	" 0 0",
	"0   0",
	"0   0",

	"0   0",
	"0   0",
	" 0 0",
	"  0",
	"  0",
	"  0",
	"  0",

	"0000",
	"   0",
	"  0",
	" 0",
	"0",
	"0",
	"0000",

	"",
	"",
	"",
	"",
	"",
	"",
	"0",

	"   0",
	"  0",
	"  0",
	" 0",
	" 0",
	"0",
	"0",
};

static void
draw_text(const char* text, float x, float y, float size, u32 color) {
	float half_size = size * .5f;
	float original_y = y;

	while (*text) {
		if (*text != 32) {
			const char** letter;
			if (*text == 47) letter = letters[27];
			else if (*text == 46) letter = letters[26];
			else letter = letters[*text - 'A'];
			float original_x = x;

			for (int i = 0; i < 7; i++) {
				const char* row = letter[i];
				while (*row) {
					if (*row == '0') {
						draw_rect(x, y, half_size, half_size, color);
					}
					x += size;
					row++;
				}
				y -= size;
				x = original_x;
			}
		}
		text++;
		x += size * 6.f;
		y = original_y;
	}
}
//static void
//draw_text(const char* text, float x, float y, float size, u32 color) {
//	float half_size = size * .5f;
//	float original_y = y;
//
//	while (*text) {
//		if (*text != 32) {
//			const char** letter;
//			if (*text == 47) letter = letters[27];
//			else if (*text == 46) letter = letters[26];
//			else letter = letters[*text - 'A'];
//			float original_x = x;
//
//			for (int i = 0; i < 7; i++) {
//				const char* row = letter[i];
//				while (*row) {
//					if (*row == '0') {
//						draw_rect(x, y, half_size, half_size, color);
//					}
//					if (*row == '1')
//					{
//						draw_rect(x, y, half_size, half_size, color ^ color);
//					}
//					x += size;
//					row++;
//				}
//				y -= size;
//				x = original_x;
//			}
//		}
//		text++;
//		x += size * 6.f;
//		y = original_y;
//	}
//}
//void draw_line(float x, float y, float half_size_x, float half_size_y, u32 color)
//{
//	x *= render_state.height * render_scale;
//	y *= render_state.height * render_scale;
//	half_size_x *= render_state.height * render_scale;
//	half_size_y *= render_state.height * render_scale;
//
//	x += render_state.width / 2.f;
//	y += render_state.height / 2.f;
//
//	// Change to pixels
//	float x0 = x - half_size_x;
//	float x1 = x + half_size_x;
//	float y0 = y - half_size_y;
//	float y1 = y + half_size_y;
//}
//
//const char* letters[][7] = {
//	" ()",
//	"0  0",
//	"0  0",
//	"0000",
//	"0  0",
//	"0  0",
//	"0  0",
//
//	"000",
//	"0  0",
//	"0  0",
//	"000",
//	"0  0",
//	"0  0",
//	"000",
//
//	" 000",
//	"0",
//	"0",
//	"0",
//	"0",
//	"0",
//	" 000",
//
//	"000",
//	"0  0",
//	"0  0",
//	"0  0",
//	"0  0",
//	"0  0",
//	"000",
//
//	"0000",
//	"0",
//	"0",
//	"000",
//	"0",
//	"0",
//	"0000",
//
//	"0000",
//	"0",
//	"0",
//	"000",
//	"0",
//	"0",
//	"0",
//
//	" 000",
//	"0",
//	"0",
//	"0 00",
//	"0  0",
//	"0  0",
//	" 000",
//
//	"0  0",
//	"0  0",
//	"0  0",
//	"0000",
//	"0  0",
//	"0  0",
//	"0  0",
//
//	"000",
//	" 0",
//	" 0",
//	" 0",
//	" 0",
//	" 0",
//	"000",
//
//	" 000",
//	"   0",
//	"   0",
//	"   0",
//	"0  0",
//	"0  0",
//	" 000",
//
//	"0  0",
//	"0  0",
//	"0 0",
//	"00",
//	"0 0",
//	"0  0",
//	"0  0",
//
//	"0",
//	"0",
//	"0",
//	"0",
//	"0",
//	"0",
//	"0000",
//
//	"00 00",
//	"0 0 0",
//	"0 0 0",
//	"0   0",
//	"0   0",
//	"0   0",
//	"0   0",
//
//	"00  0",
//	"0 0 0",
//	"0 0 0",
//	"0 0 0",
//	"0 0 0",
//	"0 0 0",
//	"0  00",
//
//	"0000",
//	"0  0",
//	"0  0",
//	"0  0",
//	"0  0",
//	"0  0",
//	"0000",
//
//	" 000",
//	"0  0",
//	"0  0",
//	"000",
//	"0",
//	"0",
//	"0",
//
//	" 000 ",
//	"0   0",
//	"0   0",
//	"0   0",
//	"0 0 0",
//	"0  0 ",
//	" 00 0",
//
//	"000",
//	"0  0",
//	"0  0",
//	"000",
//	"0  0",
//	"0  0",
//	"0  0",
//
//	" 000",
//	"0",
//	"0 ",
//	" 00",
//	"   0",
//	"   0",
//	"000 ",
//
//	"000",
//	" 0",
//	" 0",
//	" 0",
//	" 0",
//	" 0",
//	" 0",
//
//	"0  0",
//	"0  0",
//	"0  0",
//	"0  0",
//	"0  0",
//	"0  0",
//	" 00",
//
//	"0   0",
//	"0   0",
//	"0   0",
//	"0   0",
//	"0   0",
//	" 0 0",
//	"  0",
//
//	"0   0 ",
//	"0   0",
//	"0   0",
//	"0 0 0",
//	"0 0 0",
//	"0 0 0",
//	" 0 0 ",
//
//	"0   0",
//	"0   0",
//	" 0 0",
//	"  0",
//	" 0 0",
//	"0   0",
//	"0   0",
//
//	"0   0",
//	"0   0",
//	" 0 0",
//	"  0",
//	"  0",
//	"  0",
//	"  0",
//
//	"0000",
//	"   0",
//	"  0",
//	" 0",
//	"0",
//	"0",
//	"0000",
//
//	"",
//	"",
//	"",
//	"",
//	"",
//	"",
//	"0",
//
//	"   0",
//	"  0",
//	"  0",
//	" 0",
//	" 0",
//	"0",
//	"0",
//};
//
//static void
//draw_text(const char* text, float x, float y, float size, u32 color) {
//	float half_size = size * .5f;
//	float original_y = y;
//
//	while (*text) {
//		if (*text != 32) {
//			const char** letter;
//			if (*text == 47) letter = letters[27];
//			else if (*text == 46) letter = letters[26];
//			else letter = letters[*text - 'A'];
//			float original_x = x;
//
//			for (int i = 0; i < 7; i++) {
//				const char* row = letter[i];
//				while (*row) {
//					if (*row == '0') {
//						draw_rect(x, y, half_size, half_size, color);
//					}
//					x += size;
//					row++;
//				}
//				y -= size;
//				x = original_x;
//			}
//		}
//		text++;
//		x += size * 6.f;
//		y = original_y;
//	}
//}
//
//static void
//draw_number(int number, float x, float y, float size, u32 color) {
//	float half_size = size * .5f;
//
//	bool drew_number = false;
//	while (number || !drew_number) {
//		drew_number = true;
//
//		int digit = number % 10;
//		number = number / 10;
//
//		switch (digit) {
//		case 0: {
//			draw_rect(x - size, y, half_size, 2.5f * size, color);
//			draw_rect(x + size, y, half_size, 2.5f * size, color);
//			draw_rect(x, y + size * 2.f, half_size, half_size, color);
//			draw_rect(x, y - size * 2.f, half_size, half_size, color);
//			x -= size * 4.f;
//		} break;
//
//		case 1: {
//			draw_rect(x + size, y, half_size, 2.5f * size, color);
//			x -= size * 2.f;
//		} break;
//
//		case 2: {
//			draw_rect(x, y + size * 2.f, 1.5f * size, half_size, color);
//			draw_rect(x, y, 1.5f * size, half_size, color);
//			draw_rect(x, y - size * 2.f, 1.5f * size, half_size, color);
//			draw_rect(x + size, y + size, half_size, half_size, color);
//			draw_rect(x - size, y - size, half_size, half_size, color);
//			x -= size * 4.f;
//		} break;
//
//		case 3: {
//			draw_rect(x - half_size, y + size * 2.f, size, half_size, color);
//			draw_rect(x - half_size, y, size, half_size, color);
//			draw_rect(x - half_size, y - size * 2.f, size, half_size, color);
//			draw_rect(x + size, y, half_size, 2.5f * size, color);
//			x -= size * 4.f;
//		} break;
//
//		case 4: {
//			draw_rect(x + size, y, half_size, 2.5f * size, color);
//			draw_rect(x - size, y + size, half_size, 1.5f * size, color);
//			draw_rect(x, y, half_size, half_size, color);
//			x -= size * 4.f;
//		} break;
//
//		case 5: {
//			draw_rect(x, y + size * 2.f, 1.5f * size, half_size, color);
//			draw_rect(x, y, 1.5f * size, half_size, color);
//			draw_rect(x, y - size * 2.f, 1.5f * size, half_size, color);
//			draw_rect(x - size, y + size, half_size, half_size, color);
//			draw_rect(x + size, y - size, half_size, half_size, color);
//			x -= size * 4.f;
//		} break;
//
//		case 6: {
//			draw_rect(x + half_size, y + size * 2.f, size, half_size, color);
//			draw_rect(x + half_size, y, size, half_size, color);
//			draw_rect(x + half_size, y - size * 2.f, size, half_size, color);
//			draw_rect(x - size, y, half_size, 2.5f * size, color);
//			draw_rect(x + size, y - size, half_size, half_size, color);
//			x -= size * 4.f;
//		} break;
//
//		case 7: {
//			draw_rect(x + size, y, half_size, 2.5f * size, color);
//			draw_rect(x - half_size, y + size * 2.f, size, half_size, color);
//			x -= size * 4.f;
//		} break;
//
//		case 8: {
//			draw_rect(x - size, y, half_size, 2.5f * size, color);
//			draw_rect(x + size, y, half_size, 2.5f * size, color);
//			draw_rect(x, y + size * 2.f, half_size, half_size, color);
//			draw_rect(x, y - size * 2.f, half_size, half_size, color);
//			draw_rect(x, y, half_size, half_size, color);
//			x -= size * 4.f;
//		} break;
//
//		case 9: {
//			draw_rect(x - half_size, y + size * 2.f, size, half_size, color);
//			draw_rect(x - half_size, y, size, half_size, color);
//			draw_rect(x - half_size, y - size * 2.f, size, half_size, color);
//			draw_rect(x + size, y, half_size, 2.5f * size, color);
//			draw_rect(x - size, y + size, half_size, half_size, color);
//			x -= size * 4.f;
//		} break;
//		}
//
//	}
//}