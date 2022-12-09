typedef int s32;
typedef unsigned int u32;
enum TYPE {
	CAR_RIGHT, CAR_LEFT, BUS_RIGHT, BUS_LEFT, CAR2_RIGHT, CAR2_LEFT, BALLOON_RIGHT, BALLOON_LEFT, BEE_RIGHT,
	BEE_LEFT, PIG_RIGHT, PIG_LEFT, CAT_RIGHT, CAT_LEFT, BIRD_RIGHT, BIRD_LEFT, TURTLE_RIGHT, TURTLE_LEFT, TEXT_GAME_OVER, CLOUD, GRASS, TRAFFIC,
};
enum BUTTON { NEW_GAME, LOAD_GAME, SETTINGS, INTRODUCTION, EXIT, MAIN };
enum THINGS { CLOUD1, CLOUD2, GRASS1,ROCK1, ROCK2, ROCK3, MUTE, UNMUTE};
static float render_scale = 0.01f;

static void
draw_arena_borders(float x, float y, float arena_x, float arena_y, u32 color) {
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
draw_borders(float x1, float y1, float half_size_x1, float half_size_y1, float x2, float y2, float half_size_x2, float half_size_y2, u32 color) {
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
	x *= render_state.height * render_scale;
	x += render_state.width / 2.f;
	if (x > 0)
		return true;
	return false;
}
static void draw_lane(float y, float half_size_x, float half_size_y, u32 color)
{
	float x0 = render_state.width / 2 - (render_state.width / 2 - half_size_x);
	float y0 = render_state.height / 2 - (render_state.height / 2 - half_size_x);

	draw_rect(0, y, x0, 0.8, 0x9C9900);
	//draw_rect(0, y-0.2, render_state.width / 2, 0.5, 0x33AA00);
}
//x: trung tam dino, y: trung taam dino
static void draw_truck(float x, float y, float half_size_x, float half_size_y)
{

	draw_rect(x, y + 1, 3.5, 2, 0xfff0000);

	draw_rect(x, y - 0.5, 5, 1.5, 0x1820FAA);
	draw_rect(x + 2.5, y - 2.5, 1, 1, 0x1820FAA);
	draw_rect(x - 1.5, y - 2.5, 1, 1, 0x1820FAA);

	draw_rect(x + 2, y + 1, 2.5, 3, 0x1820FF);
	draw_rect(x + 2, y + 1, 3, 2.5, 0x1820FF);
	//draw_rect(x + 3, y, 2, 0.5, 0x1820FF);
}
static void draw_dino(float x, float y, float half_size_x, float half_size_y)
{
	draw_rect(x + 3, y + 0.7, 2, 0.2, 0x000000);
	draw_rect(x, y - 3, 7 + 0.2, 1.5 + 0.2, 0x000000);

	draw_rect(x, y - 4.5, 2 + 0.2, 2 + 0.2, 0x000000);
	draw_rect(x + 1, y - 4.5 - 2, 2 + 0.2, 0.5 + 0.2, 0x000000);
	draw_rect(x + 2, y - 4.5 - 3, 2 + 0.2, 0.5 + 0.2, 0x000000);
	draw_rect(x + 3, y - 4.5 - 4, 1.5 + 0.2, 0.5 + 0.2, 0x000000);
	draw_rect(x + 4, y - 4.5 - 5, 1. + 0.2, 0.5 + 0.2, 0x000000);
	draw_rect(x + 4.5, y - 4.5 - 5.5, 0.9 + 0.2, 0.1 + 0.5, 0x000000);


	draw_rect(x + 3, y, 2, 0.5, 0x1820FF);
	draw_rect(x + 2, y - 1, 2, 0.5, 0x1820FF);
	draw_rect(x + 1, y - 2, 2, 0.5, 0x1820FF);
	draw_rect(x, y - 3, 2, 0.5, 0x1820FF);

	draw_rect(x, y - 3, 7, 1.5, 0x1820FF);


	draw_rect(x, y - 4.5, 2, 2, 0x1820FF);
	draw_rect(x + 1, y - 4.5 - 2, 2, 0.5, 0x1820FF);
	draw_rect(x + 2, y - 4.5 - 3, 2, 0.5, 0x1820FF);
	draw_rect(x + 3, y - 4.5 - 4, 1.5, 0.5, 0x1820FF);
	draw_rect(x + 4, y - 4.5 - 5, 1., 0.5, 0x1820FF);
	draw_rect(x + 4.5, y - 4.5 - 5.5, 0.9, 0.1, 0x1820FF);

	//draw_rect_in_pixels((int)x0, (int)y0, (int)x1, (int)y1, 0x1820FF);
}
static const char* letters[][7] = {
	" 00",
	"0  0",
	"0  0",
	"0000",
	"0  0",
	"0  0",
	"0  0",

	"000",
	"0  0",
	"0  0",
	"000",
	"0  0",
	"0  0",
	"000",

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
static const char* things[][11] = {
	//CLOUD1
	"000000000011111100000000",
	"0000000011111111100000000",
	"0000000111111111111000000",
	"000000111111111111110000",
	"00000001111111111110000",
	"0000011111111111111000",
	"0000111111111111111110000000",
	"0011111111111111111111100000",
	"0011111111111111111111111000",
	"111111111111111111111111111",
	"000011111111111111111111",
	//CLOUD2
	"00000000000111111110000000",
	"00000000011111111111000",
	"000000001111111111111100000",
	"0000000111111111111111110000",
	"0000001111111111111111111",
	"000000011111111111111111000",
	"00011111111111111111111111000000",
	"0011111111111111111111111110000",
	"001111111111111111111111111100",
	"0011111111111101111111111111",
	"00001111111100001111111111",
	//GRASS1
	"33333333333333333333333",
	"33333333303333333333333",
	"03333333000333333333330",
	"03333333000033333333300",
	"00333330000033333333300",
	"00333330000033333333300",
	"000333000000003333300",
	"0000300000000033333000",
	"0000000000000003330",
	"00000000000000033300",
	"0000000000000000300",
	//ROCK1
	"22222",
	"22222",
	"22222",
	"22222",
	"22222",
	"0000022222",
	"0000022222",
	"0000022222",
	"0000022222",
	"0000022222",
	"0000000000",
	//ROCK2
	"22222",
	"22222",
	"22222",
	"22222",
	"00000222222222222222",
	"00000222222222222222",
	"00000222222222222222",
	"00000222222222222222",
	"00000222222222222222",
	"00000000000000000000",
	"00000000000000000000",
	//ROCK3
	"0000222222222222",
	"0000222222222222",
	"0000222222222222",
	"00000002222222222222222",
	"00000002222222222222222",
	"00000002222222222222222",
	"2222222222222000022222",
	"2222222222222000022222",
	"00022222222000022222222222",
	"00022222222000022222222222",
	"00022222222",
	//MUTE
	"2000000100",
	"0200001100",
	"0020011100",
	"0002111100",
	"0011211100",
	"0011121100",
	"0011112100",
	"0000111200",
	"0000011120",
	"0000001102",
	"00000001002",
	//UMNUTE
	"00000100",
	"00001100",
	"0001110000001",
	"00111100001001",
	"111111001001001",
	"111111000101001",
	"111111001001001",
	"00111100001001",
	"0001110000001",
	"00001100",
	"00000100",
};
class Renderer
{
public:
	static int clamp(int min, int val, int max)
	{
		if (val < min) return min;
		if (val > max) return max;
		return val;
	}
	static void clear_screen(u32 color) {
		unsigned int* pixel = (u32*)render_state.memory;
		for (int y = 0; y < render_state.height; y++) {
			for (int x = 0; x < render_state.width; x++) {
				*pixel++ = color;
			}
		}
	}
	static void draw_rect_in_pixels(int x0, int y0, int x1, int y1, u32 color) {

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
}//123456789
static const char* entities[][14] = {
	//car
	"0000000000111111110",
	"0000000001111111111",
	"0000000001111111111",
	"0000002221111111111",
	"0000023331111111111",
	"0000233331111111111",
	"0000233331111111111",
	"0444444441111111111",
	"4444444441111111111",
	"5544424441111121111",
	"4444222440111222110",
	"0002262200002262200",
	"0000222000000222000",
	"0000020000000020000",

	//Truck
	"0000000000111111110",
	"0000000001111111111",
	"0000000001111111111",
	"0000002221111111111",
	"0000023331111111111",
	"0000233331111111111",
	"0000233331111111111",
	"0444444441111111111",
	"4444444441111111111",
	"5544424441111121111",
	"4444222440111222110",
	"0002262200002262200",
	"0000222000000222000",
	"0000020000000020000",

	//bird


	//dino


};
static void draw_entities(int number, float x, float y, float size, u32 color)
{
	float half_size = size * .5f;
	float original_y = y;
	switch (number)
	{
	case CAR:
	{
		break;

	}
	case TRUCK:
	{
		const char** entity;
		/*if (*text == 47) entity = entities[27];
		else if (*text == 46) entity = entities[26];*/
		entity = entities[number];
		float original_x = x;

		for (int i = 0; i <= 13; i++) {
			const char* row = entity[i];
			while (*row) {
				switch (*row)
				{
				case '0':
				{
					draw_rect(x, y, half_size, half_size, 0xFFFFFF);
					break;
				}
				case '1':
				{
					draw_rect(x, y, half_size, half_size, 0x3366CC);
					break;
				}
				case '2':
				{
					draw_rect(x, y, half_size, half_size, 0x000000);
					break;
				}
				case '3':
				{
					draw_rect(x, y, half_size, half_size, 0xC9C9C9);
					break;
				}
				case '4':
				{
					draw_rect(x, y, half_size, half_size, 0xFFD148);
					break;
				}
				case '5':
				{
					draw_rect(x, y, half_size, half_size, 0xB3641F);
					break;
				}
				case '6':
				{
					draw_rect(x, y, half_size, half_size, 0x3D3E59);
					break;
				}
				case '7':
				{
					draw_rect(x, y, half_size, half_size, color);
					break;
				}
				}

				x += size;
				row++;
			}
			y -= size;
			x = original_x;
		}
		break;

	}
	case BIRD:
	{
		break;

	}
	case DINOSAUR:
	{
		break;

	}
	}
}
static void
draw_number(int number, float x, float y, float size, u32 color) {
	float half_size = size;// *.5f;

	bool drew_number = false;
	while (number || !drew_number) {
		drew_number = true;

		int digit = number % 10;
		number = number / 10;

		switch (digit) {
		case 0: {
			draw_rect(x - size, y, half_size, 2.5f * size, color);
			draw_rect(x + size, y, half_size, 2.5f * size, color);
			draw_rect(x, y + size * 2.f, half_size, half_size, color);
			draw_rect(x, y - size * 2.f, half_size, half_size, color);
			x -= size * 4.f;
		} break;

		case 1: {
			draw_rect(x + size, y, half_size, 2.5f * size, color);
			x -= size * 2.f;
		} break;

		case 2: {
			draw_rect(x, y + size * 2.f, 1.5f * size, half_size, color);
			draw_rect(x, y, 1.5f * size, half_size, color);
			draw_rect(x, y - size * 2.f, 1.5f * size, half_size, color);
			draw_rect(x + size, y + size, half_size, half_size, color);
			draw_rect(x - size, y - size, half_size, half_size, color);
			x -= size * 4.f;
		} break;

		case 3: {
			draw_rect(x - half_size, y + size * 2.f, size, half_size, color);
			draw_rect(x - half_size, y, size, half_size, color);
			draw_rect(x - half_size, y - size * 2.f, size, half_size, color);
			draw_rect(x + size, y, half_size, 2.5f * size, color);
			x -= size * 4.f;
		} break;

		case 4: {
			draw_rect(x + size, y, half_size, 2.5f * size, color);
			draw_rect(x - size, y + size, half_size, 1.5f * size, color);
			draw_rect(x, y, half_size, half_size, color);
			x -= size * 4.f;
		} break;

		case 5: {
			draw_rect(x, y + size * 2.f, 1.5f * size, half_size, color);
			draw_rect(x, y, 1.5f * size, half_size, color);
			draw_rect(x, y - size * 2.f, 1.5f * size, half_size, color);
			draw_rect(x - size, y + size, half_size, half_size, color);
			draw_rect(x + size, y - size, half_size, half_size, color);
			x -= size * 4.f;
		} break;

		case 6: {
			draw_rect(x + half_size, y + size * 2.f, size, half_size, color);
			draw_rect(x + half_size, y, size, half_size, color);
			draw_rect(x + half_size, y - size * 2.f, size, half_size, color);
			draw_rect(x - size, y, half_size, 2.5f * size, color);
			draw_rect(x + size, y - size, half_size, half_size, color);
			x -= size * 4.f;
		} break;

		case 7: {
			draw_rect(x + size, y, half_size, 2.5f * size, color);
			draw_rect(x - half_size, y + size * 2.f, size, half_size, color);
			x -= size * 4.f;
		} break;

		case 8: {
			draw_rect(x - size, y, half_size, 2.5f * size, color);
			draw_rect(x + size, y, half_size, 2.5f * size, color);
			draw_rect(x, y + size * 2.f, half_size, half_size, color);
			draw_rect(x, y - size * 2.f, half_size, half_size, color);
			draw_rect(x, y, half_size, half_size, color);
			x -= size * 4.f;
		} break;

		case 9: {
			draw_rect(x - half_size, y + size * 2.f, size, half_size, color);
			draw_rect(x - half_size, y, size, half_size, color);
			draw_rect(x - half_size, y - size * 2.f, size, half_size, color);
			draw_rect(x + size, y, half_size, 2.5f * size, color);
			draw_rect(x - size, y + size, half_size, half_size, color);
			x -= size * 4.f;
		} break;
		}

	}
}
static void draw_Menu(float x, float y, float half_size_x, float half_size_y) {
	clear_screen(0x01C4FF);
	draw_text("THE CROSSING GAME", x - 72, y + 45, 1.5, 0xE61409);
	draw_text("A PROJECT BY GROUP THREE", x - 67, y + 30, 1, 0xFFE501);
	draw_text("NEW GAME", x - 22, y + 15, 1, 0xFF7901);
	draw_text("LOAD GAME", x - 22, y + 2, 1, 0xFF7901);
	draw_text("SETTING", x - 22, y - 11, 1, 0xFF7901);
	draw_text("INTRODUCTION", x - 22, y - 24, 1, 0xFF7901);
	draw_text("EXIT", x - 22, y - 37, 1, 0xFF7901);



	//draw_rect(x, y - 45, render_state.width, 7, 0xAB6E08);


				x += size;
				row++;
			}
			y -= size;
			x = original_x;
		}
	}
	static void draw_Menu(float x, float y, float half_size_x, float half_size_y, int hot_button) {
		clear_screen(0x01C4FF);
		/*draw_Background2(0, 0, 0, 0);
		draw_title(x - 83, y + 45, 0.5, 0xE61409);
		draw_Button(NEW_GAME, x - 25, y + 15, 0.7, 0x000000, hot_button);
		draw_Button(LOAD_GAME, x - 25, y + 2, 0.7, 0x000000, hot_button);
		draw_Button(SETTINGS, x - 25, y - 11, 0.7, 0x000000, hot_button);
		draw_Button(INTRODUCTION, x - 25, y - 24, 0.7, 0x000000, hot_button);
		draw_Button(EXIT, x - 25, y - 37, 0.7, 0x000000, hot_button);*/
		draw_Background3(0, 0, 0, 0);
		draw_text("BACK", x - 80, y + 45, 0.5, 0x000000);
		draw_Button(SETTINGS, x - 30, y +45, 1, 0x000000, hot_button);
		draw_things(MUTE, x - 30, y, 1);
		draw_things(UNMUTE, x , y, 1);
	}
	static void draw_Settings(float x, float y, float half_size_x, float half_size_y) {
		draw_Background3(0, 0, 0, 0);
		draw_text("BACK", x - 80, y + 45, 0.5, 0x000000);
		draw_Button(SETTINGS, x - 30, y + 45, 1, 0x000000, MAIN);
		draw_things(MUTE, x - 30, y, 1);
		draw_things(UNMUTE, x, y, 1);
	}
	static void draw_Introduction(float x, float y, float half_size_x, float half_size_y) {
		draw_Background3(0, 0, 0, 0);
		draw_text("BACK", x - 80, y + 45, 0.5, 0x000000);
		draw_Button(INTRODUCTION, x - 30, y + 45, 1, 0x000000, MAIN);
	}
	static void draw_player(float x, float y, float half_size_x, float half_size_y) {

	//toc
	draw_rect(x, y, 5, 5, 0xF5B16D);
	draw_rect(x, y + 5, 5, 2.5, 0x000000);
	//face
	draw_rect(x - 2, y + 0.25, 1, 1, 0x000000);
	draw_rect(x + 2, y + 0.25, 1, 1, 0x000000);
	//co
	draw_rect(x, y - 6, 3.5, 2, 0xF5B16D);
	//than
	draw_rect(x, y - 17, 8, 9, 0xDF0029);
	//chan
	draw_rect(x, y - 33, 7, 9, 0x00676B);
	//khoang cach quan
	draw_rect(x, y - 34, 1, 8, 0x50A625);
	//tay
	draw_rect(x - 6.8, y - 19, 1.2, 7.5, 0xF5B16D);
	draw_rect(x + 6.8, y - 19, 1.2, 7.5, 0xF5B16D);
	//detail
	//co
	draw_rect(x, y - 9, 1.5, 1.5, 0xF5B16D);
	//giay
	draw_rect(x + 5, y - 41, 2.5, 1, 0xCAE5E8);
	draw_rect(x - 5, y - 41, 2.5, 1, 0xCAE5E8);
	//toccon
	draw_rect(x - 4, y + 2, 1, 0.5, 0x363636);
	draw_rect(x + 4, y + 2, 1, 0.5, 0x363636);

	}
	static void draw_apple(int x, int y)
	{
		// tao do 
		draw_rect(x, y, 1.3, 1.3, 0xC42732);
		draw_rect(x, y, 0.9, 0.9, 0xF4303E);
		draw_rect(x + 0.7, y + 1.2, 1, 0.4, 0x868F26); // la
		draw_rect(x + 0.2, y + 0.4, 0.8, 0.7, 0xD9614D);
	}
	static void draw_plant(int x, int y)
	{
		//bui cay 
		draw_rect(x, y - 0.1, 3.9, 4.9, 0x000000);
		draw_rect(x, y, 3.5, 4.6, 0x9FAF4D);

		draw_rect(x - 5, y - 2.2, 3.4, 2.8, 0x000000);
		draw_rect(x - 5, y - 2.2, 3.1, 2.4, 0x5F692D);
		draw_rect(x - 5.7, y - 2.4, 2.4, 2.1, 0x213C11);

		draw_rect(x + 5, y - 2.7, 2.7, 2.3, 0x000000);
		draw_rect(x + 5, y - 2.7, 2.3, 2, 0x5F692D);
		draw_rect(x + 5.2, y - 3.4, 2, 1.3, 0x213C11);

		draw_apple(x + 0.5, y + 4);
		draw_apple(x - 2.7, y);
		draw_apple(x - 8, y - 2.7);
		draw_apple(x + 3.5, y - 1.8);

		draw_rect(x + 5, y - 2.7, 2.7, 2.3, 0x000000);
		draw_rect(x + 5, y - 2.7, 2.3, 2, 0x5F692D);
		draw_rect(x + 5.2, y - 3.4, 2, 1.3, 0x213C11);

		draw_apple(x + 0.5, y + 4);
		draw_apple(x - 2.7, y);
		draw_apple(x - 8, y - 2.7);
		draw_apple(x + 3.5, y - 1.8);

	}
	static void draw_Background(float x, float y, float max_size_x, float max_size_y)
	{
		//Khung 
		draw_arena_borders(x, y, 90, 47, 0x2D9929);
		draw_rect(x, y, 90, 47, 0x8DC740);//nen khung 
		draw_rect(x + 55, y, 2, 49, 0x2D9929);
		draw_rect(x + 74, y + 24, 18, 1.7, 0x2D9929);
		// lane 
		draw_rect(x - 18.5, y, 71.5, 47, 0x484D5C);//nen duong
		draw_rect(x - 18.5, y + 40, 71.5, 7, 0xC3FF5F);//bai co 
		draw_rect(x - 18.5, y + 34, 71.5, 1, 0x81AD3A);//bai co darker
		draw_rect(x - 18.5, y, 71.5, 6.5, 0xC3FF5F);//bai co 
		draw_rect(x - 18.5, y - 6, 71.5, 1, 0x81AD3A);//bai co darker
		draw_rect(x - 18.5, y - 40, 71.5, 6.5, 0xC3FF5F);//bai co 
		draw_rect(x - 18.5, y - 46, 71.5, 1, 0x81AD3A);//bai co darker
		for (int i = 0; i < 140; i += 25)
		{
			draw_rect(x - 80 + i, y - 20, 6, 1, 0x7E8397);//lane line darker	
			draw_rect(x - 80 + i, y + 20, 6, 1, 0x7E8397);//lane line darker
		}
		//Score
		draw_text("SCORE", x + 58.5, y + 44, 1.1, 0x0002D9);
		draw_text("HIGHSCORE", x + 58, y + 19, 0.6, 0xE30000);
		draw_text("ESCZ EXIT", x + 58, y , 0.5, 0x0000);
		draw_text("PZ PAUSE", x + 60, y - 5, 0.5, 0x000000);
		draw_text("SZ SAVE", x + 60, y - 10, 0.5, 0x0000);
		draw_text("WZ UP", x + 60, y -20 , 0.5, 0x0000);
		draw_text("SZ DOWN", x + 60, y - 25, 0.5, 0x0000);
		draw_text("AZ LEFT", x + 60, y - 30, 0.5, 0x0000);
		draw_text("DZ RIGHT", x + 60, y - 35, 0.5, 0x0000);
	}
	static void draw_things(int number, float x, float y, float size) {
		float half_size = size * .5f;
		float original_y = y;
		const char** button;
		float original_x = x;

		button = things[number];
		for (int i = 0; i <= 10; i++) {
			const char* row = button[i];
			while (*row) {
				switch (*row)
				{
				case '1':
				{
					draw_rect(x, y, half_size, half_size, 0xffffff);
					break;
				}
				case '2':
				{
					draw_rect(x, y, half_size, half_size, 0xa67564);
					break;
				}
				case '3':
				{
					draw_rect(x, y, half_size, half_size, 0x63b15d);
					break;
				}
				}
				x += size;
				row++;

			}
			y -= size;
			x = original_x;
		}
	}
	static void draw_Background2(float x, float y, float max_size_x, float max_size_y)
	{
		//Khung 
		draw_rect(x, y - 40, 120, 15, 0x784937);
		draw_things(CLOUD1, x - 50, y + 40, 1.5);
		draw_things(CLOUD1, x + 30, y + 60, 1.3);
		draw_things(CLOUD2, x + 50, y + 20, 1);
		draw_things(CLOUD2, x - 90, y + 25, 1.2);
		for (int i = 0; i <= 50; i++) {
			draw_things(GRASS1, x - 120 + i * 10, y - 25, .4);
		}
		for (int i = 0; i <= 10; i++) {
			draw_things(ROCK3, x - 120 + i * 20, y - 30, .3);
			draw_things(ROCK2, x - 120 + i * 20 + 10, y - 40, .2);
			draw_things(ROCK1, x - 120 + i * 20 + 15, y - 45, .2);
		}
	}
	static void draw_Background3(float x, float y, float max_size_x, float max_size_y)
	{
		//Khung 
		draw_rect(x, y - 40, 120, 15, 0x784937);
		for (int i = 0; i <= 50; i++) {
			draw_things(GRASS1, x - 140 + i * 10, y - 25, .4);
		}
		for (int i = 0; i <= 10; i++) {
			draw_things(ROCK3, x - 140 + i * 20, y - 30, .3);
			draw_things(ROCK2, x - 140 + i * 20 + 10, y - 40, .2);
			draw_things(ROCK1, x - 140 + i * 20 + 15, y - 45, .2);
		}
	}
	static void draw_trees(int x, int y) {
		for (int i = 0; i < 140; i += 30)
		{
			draw_tree(x - 80 + i, y + 44, 1.7, 0xC3FF5F);
			draw_tree(x - 80 + i, y + 4, 1.7, 0xC3FF5F);
			draw_tree(x - 80 + i, y - 36, 1.7, 0xC3FF5F);
		}
	}
};

