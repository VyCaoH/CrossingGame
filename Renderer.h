typedef int s32;
typedef unsigned int u32;
enum TYPE { CAR_RIGHT, CAR_LEFT, CAR2_RIGHT, CAR2_LEFT, BUS_RIGHT, BUS_LEFT, BALLOON_RIGHT, BALLOON_LEFT, BIRD, DINOSAUR,  TURTLE_RIGHT,TURTLE_LEFT};

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

// Nho xoa half x vaf xoa half y
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
static void draw_birdL(float x, float y, float half_size_x, float half_size_y) //chieu dai
{
	//nen black
	draw_rect(x , y , 1.65, 3.25, 0x000000);
	draw_rect(x + 2.6, y+ 0.1, 1.6, 1.4, 0x000000);
	draw_rect(x - 1.55, y + 1.6, 1.2, 1.3, 0x000000);
	draw_rect(x - 2.8, y - 0.9, 1.45, 1.2, 0x000000);
	// cai canh 
	draw_rect(x + 2.6, y + 0.7, 1.45, 0.35, 0xFFFFFFF);
	draw_rect(x + 2.6, y , 1.2, 0.45, 0xFFFFFFF);
	draw_rect(x + 2.75, y - 0.45, 1.2, 0.3, 0xFFD015);
	//body
	draw_rect(x + 0.65, y + 1.25 , 1.25, 0.6, 0xFFD015);
	draw_rect(x , y + 2.25, 1.35, 0.5, 0xFFD015);
	draw_rect(x +0.1 , y+0.5 , 1.3, 0.4, 0xFFD015);
	draw_rect(x -0.35, y - 0.09, 1.3, 0.6, 0xFFD015);
	draw_rect(x + 0.75, y - 1.35, 1.1, 0.6, 0xBD7119);
	draw_rect(x , y - 1.95, 1.1, 0.8, 0xBD7119);
	draw_rect(x - 0.75, y - 2, 1, 0.4, 0xBD7119);
	 
	// con mat
	draw_rect(x -1.45, y + 1.7, 0.65, 0.75, 0xFFFFFF);
	draw_rect(x - 1.75, y + 2.5, 0.2, 0.25, 0xFFFFFF);
	draw_rect(x - 1.85, y + 1.35, 0.65, 0.75, 0xFFFFFF);
	//trong den
	draw_rect(x - 1.8, y + 1.45, 0.25, 0.45, 0x000000);
	// cai mieng
	draw_rect(x - 2.75, y - 0.4, 1.35, 0.3, 0xFF6000);
	draw_rect(x - 1.2, y - 0.8, 0.3, 0.39, 0xFF6000);
	draw_rect(x - 2.55, y - 1.35, 1.1, 0.3, 0xFF6000);
	// cai chan 
	draw_rect(x - 0.75, y - 2, 1, 0.4, 0xBD7119);
}
static void draw_birdR(float x, float y, float half_size_x, float half_size_y) 
{
	//nen black
	draw_rect(x, y, 1.65, 3.25, 0x000000);
	draw_rect(x - 2.6, y + 0.1, 1.6, 1.4, 0x000000);
	draw_rect(x + 1.55, y + 1.6, 1.2, 1.3, 0x000000);
	draw_rect(x + 2.8, y - 0.9, 1.45, 1.2, 0x000000);
	// cai canh 
	draw_rect(x - 2.6, y + 0.7, 1.45, 0.35, 0xFFFFFFF);
	draw_rect(x - 2.6, y, 1.2, 0.45, 0xFFFFFFF);
	draw_rect(x - 2.75, y - 0.45, 1.2, 0.3, 0xFFD015);
	//body
	draw_rect(x - 0.65, y + 1.25, 1.25, 0.6, 0xFFD015);
	draw_rect(x, y + 2.25, 1.35, 0.5, 0xFFD015);
	draw_rect(x - 0.1, y + 0.5, 1.3, 0.4, 0xFFD015);
	draw_rect(x + 0.35, y - 0.09, 1.3, 0.6, 0xFFD015);
	draw_rect(x - 0.75, y - 1.35, 1.1, 0.6, 0xBD7119);
	draw_rect(x, y - 1.95, 1.1, 0.8, 0xBD7119);
	draw_rect(x + 0.75, y - 2, 1, 0.4, 0xBD7119);

	// con mat
	draw_rect(x + 1.45, y + 1.7, 0.65, 0.75, 0xFFFFFF);
	draw_rect(x + 1.75, y + 2.5, 0.2, 0.25, 0xFFFFFF);
	draw_rect(x + 1.85, y + 1.35, 0.65, 0.75, 0xFFFFFF);
	//trong den
	draw_rect(x + 1.8, y + 1.45, 0.25, 0.45, 0x000000);
	// cai mieng
	draw_rect(x + 2.75, y - 0.4, 1.35, 0.3, 0xFF6000);
	draw_rect(x + 1.2, y - 0.8, 0.3, 0.39, 0xFF6000);
	draw_rect(x + 2.55, y - 1.35, 1.1, 0.3, 0xFF6000);
	// cai chan 
	draw_rect(x + 0.75, y - 2, 1, 0.4, 0xBD7119);
}
static void draw_titan(float x, float y, float half_size_x, float half_size_y)
{
	//nen black
	draw_rect(x, y+1, 3, 3.3, 0x000000); // head
	draw_rect(x , y - 3.3, 2.1, 3.2, 0x000000); //than
	draw_rect(x, y - 3.75, 2.5, 1, 0x000000); //tay
	draw_rect(x, y - 3.75, 2.9, 0.7, 0x000000); //tay
	//nen trang
	draw_rect(x, y - 6, 0.6, 0.4, 0xFFFFFF);

	//head
	draw_rect(x, y + 0.85, 2.5, 2.85, 0xFCCCB5); //mau da trang
	draw_rect(x, y + 0.85, 2, 3.2, 0xFCCCB5); //mau da trang
	draw_rect(x - 2.1, y + 2.35, 0.35, 1.25, 0xF0B79D);//dau nau xam
	draw_rect(x - 1.25, y + 3, 0.35, 1, 0xF0B79D);//dau nau xam
	draw_rect(x - 0.25, y + 3.3, 0.35, 0.7, 0xF0B79D);//dau nau xam
	draw_rect(x + 1, y + 3, 0.35, 1, 0xF0B79D);//dau nau xam
	draw_rect(x , y + 3.8, 1.9, 0.2, 0xF0B79D);//dau nau xam
	draw_rect(x + 2.1, y + 2.35, 0.35, 1.25, 0xF0B79D);//dau nau xam
	
	draw_rect(x + 2.15, y + 1.7, 0.35, 1, 0xCD3230);//do tuoi
	draw_rect(x - 2.1, y + 1.8, 0.3, 0.35, 0x651919);//do tham
	draw_rect(x + 2.1, y + 1.8, 0.4, 0.25, 0x651919);//do tham

	draw_rect(x - 1.7, y + 1.5, 1, 0.3, 0xED8E71);//chan may
	draw_rect(x + 1.1, y + 1.5, 1, 0.3, 0xED8E71);//chan may
	draw_rect(x-0.4, y + 0.5, 0.35, 1, 0xF7AC84);//mui
	//mat
	draw_rect(x - 1.7, y + 0.7, 1, 0.6, 0x651919);//do tham
	draw_rect(x + 1, y + 0.7, 1, 0.6, 0x651919);//do tham
	draw_rect(x - 1.85, y + 1, 0.3, 0.3, 0xFFFFFF);//trang
	draw_rect(x + 1.15, y + 1, 0.3, 0.3, 0xFFFFFF);//trang
	draw_rect(x - 1.5, y , 0.6, 0.25, 0xA8302F);//mi duoi 
	draw_rect(x + 1, y, 0.6, 0.25, 0xA8302F);//mi duoi 

	//mieng
	draw_rect(x , y - 0.75 , 2.6, 0.2, 0x962223);//moi tren
	draw_rect(x-0.2, y - 1.5, 2.3, 0.16, 0x962223);//moi duoi
	draw_rect(x + 1.8, y - 1.5, 0.3, 0.6, 0xA83B42);//mieng rach

	draw_rect(x, y - 1.2, 2.6, 0.17, 0xFFFFFF);//Rang
	draw_rect(x - 0.5, y - 1.2, 0.3, 0.17, 0xE7E3E2);//Rang
	draw_rect(x + 0.5, y - 1.2, 0.3, 0.17, 0xE7E3E2);//Rang

	draw_rect(x - 0.2, y - 2.2, 1.5, 0.15, 0x902424);//cam
	draw_rect(x + 2.1, y - 1, 0.3, 0.6, 0xB83D6A);//mieng rach
	draw_rect(x -1.8, y - 1.3, 0.2, 0.6, 0xB83D6A);//mieng rach
	
	draw_rect(x - 1.4, y - 1.3 , 0.25, 0.8, 0xF0B79D);//da mat 
	draw_rect(x + 1.4, y - 1.3, 0.25, 0.8, 0xF0B79D);//da mat 
	
	//than 
	draw_rect(x, y - 3.9, 1.8, 1.4, 0xBD1F1F); //than

	draw_rect(x - 2.2, y - 3.8, 0.28, 0.7, 0xC92A27); // co tay
	draw_rect(x - 2.2, y - 3.6, 0.28, 0.2, 0xEBBA9A); // co tay
	draw_rect(x - 2.2, y - 4.3, 0.28, 0.2, 0x8E2931); // co tay
	draw_rect(x + 2.2, y - 3.8, 0.28, 0.7, 0xC92A27); // co tay
	draw_rect(x + 2.2, y - 3.6, 0.28, 0.2, 0xEBBA9A); // co tay
	draw_rect(x + 2.2, y - 4.3, 0.28, 0.2, 0x8E2931); // co tay

	draw_rect(x - 1.36, y - 3.2, 0.35, 0.75, 0xF0B79D); // co bung
	draw_rect(x - 1.35, y - 5.2, 0.4, 0.9, 0x711D1D); // co chan 
	draw_rect(x - 1.35, y - 4.5, 0.4, 0.25, 0x8F520A); // giap
	draw_rect(x - 1.35, y - 5.5, 0.4, 0.25, 0xF0B79D); // co chan 
	draw_rect(x - 0.8, y - 3, 0.32, 0.3, 0xF4B594); //da
	draw_rect(x - 0.8, y - 4.1, 0.32, 0.3, 0xD4876C); //co bung
	draw_rect(x - 0.8, y - 4.8, 0.32, 0.45, 0xFFB6A2); //da
	draw_rect(x -0.2, y - 3.5, 0.3, 0.8, 0xF4B594); //da
	draw_rect(x - 0.2, y - 2.75, 0.32, 0.25, 0x93221E); //thit den
	draw_rect(x - 0.2, y - 4.2, 0.32, 0.25, 0x8D2421); //thit den
	draw_rect(x - 0.2, y - 4.6, 0.32, 0.25, 0xEB7778); //thit den
	draw_rect(x - 0.2, y - 5, 0.32, 0.2, 0x8D2421); //thit den

	draw_rect(x + 1.36, y - 3.2, 0.35, 0.75, 0xF0B79D); // co bung
	draw_rect(x + 1.35, y - 5.2, 0.4, 0.9, 0xAB141A); // co chan 
	draw_rect(x + 1.35, y - 4.5, 0.4, 0.25, 0x820F14); // giap
	draw_rect(x + 1.35, y - 5.5, 0.4, 0.25, 0xF0B79D); // co chan 
	draw_rect(x + 0.8, y - 3, 0.32, 0.3, 0xF4B594); //da
	draw_rect(x + 0.8, y - 4.1, 0.32, 0.3, 0xD4876C); //co bung
	draw_rect(x + 0.8, y - 4.8, 0.32, 0.45, 0xFFB6A2); //da
	draw_rect(x + 0.2, y - 3.5, 0.3, 0.8, 0xF4B594); //da
	draw_rect(x + 0.2, y - 2.75, 0.32, 0.25, 0x93221E); //thit den
	draw_rect(x + 0.2, y - 4.2, 0.32, 0.25, 0x8D2421); //thit den
	draw_rect(x + 0.2, y - 4.6, 0.32, 0.25, 0xDB4039); //thit den
	draw_rect(x + 0.2, y - 5, 0.32, 0.2, 0x8D2421); //thit den

	//draw_rect(x, y - 3.75, 2.5, 0.4, 0xBD1F1F); //tay
}
static void draw_turtleR(float x, float y, float half_size_x, float half_size_y)
{
	//nen black
	draw_rect(x, y + 2.8, 1.5, 0.3, 0x000000);
	draw_rect(x - 1.2, y + 2.5, 1.4, 0.3, 0x000000);
	draw_rect(x + 0.9, y + 2.5, 1.4, 0.3, 0x000000);
	draw_rect(x - 1.7, y + 2.2, 1.3, 0.3, 0x000000);
	draw_rect(x + 1.2, y + 2.2, 1.3, 0.3, 0x000000);
	draw_rect(x - 1.9, y + 1.9, 1.3, 0.3, 0x000000);
	draw_rect(x + 1.4, y + 1.9, 1.3, 0.3, 0x000000);
	draw_rect(x - 2.3, y + 1.4, 1.4, 0.3, 0x000000);
	draw_rect(x + 1.6, y + 1.4, 1.3, 0.3, 0x000000);
	draw_rect(x - 2.6, y + 1, 1.3, 0.3, 0x000000);
	draw_rect(x - 2.7, y + 0.7, 1.3, 0.3, 0x000000);
	draw_rect(x - 3, y + 0.2, 1.4, 0.4, 0x000000);
	draw_rect(x - 2.7, y - 0.5, 1.3, 0.4, 0x000000);


	draw_rect(x + 1.6, y + 1.2, 1.2, 0.3, 0x000000);
	draw_rect(x + 3.2, y, 1, 1, 0x000000); // dau 
	draw_rect(x + 3.5, y - 0.2, 1, 0.8, 0x000000); // dau 
	draw_rect(x + 2, y - 1, 1, 0.8, 0x000000);
	draw_rect(x - 2, y - 1, 1, 0.8, 0x000000);
	draw_rect(x + 1, y - 1.5, 1, 0.8, 0x000000);
	draw_rect(x - 1, y - 1.5, 1, 0.8, 0x000000);
	draw_rect(x + 1.75, y - 2.2, 0.8, 0.5, 0x000000);// chan
	draw_rect(x - 1.75, y - 2.2, 0.8, 0.5, 0x000000);
	draw_rect(x + 2, y - 2, 0.8, 0.8, 0x000000);
	draw_rect(x - 2, y - 2, 0.8, 0.8, 0x000000);
	//mai rua
	draw_rect(x, y + 2.5, 1, 0.3, 0xB6D53C);
	draw_rect(x - 0.3, y + 2.5, 1, 0.3, 0xB6D53C);
	draw_rect(x + 0.3, y + 2.5, 1, 0.3, 0xB6D53C);
	draw_rect(x - 1.4, y + 2.2, 1.2, 0.3, 0xB6D53C);

	draw_rect(x, y - 1, 1.4, 1, 0x3A5753);
	draw_rect(x - 1.9, y - 1.8, 0.6, 0.8, 0x3A5753);
	draw_rect(x + 1.9, y - 1.8, 0.6, 0.8, 0x3A5753);

	draw_rect(x, y + 0.2, 2.6, 1.2, 0xB6D53C);
	draw_rect(x + 0.8, y + 2.2, 1.2, 0.3, 0xB6D53C);
	draw_rect(x - 1.6, y + 1.9, 1.2, 0.3, 0xB6D53C);
	draw_rect(x - 1, y + 1.9, 1.5, 0.4, 0xB6D53C);
	draw_rect(x + 1.1, y + 1.9, 1.2, 0.3, 0xB6D53C);
	draw_rect(x - 2, y + 1.4, 1.2, 0.3, 0xB6D53C);
	draw_rect(x + 1.3, y + 1.4, 1.2, 0.3, 0xB6D53C);
	draw_rect(x - 2.3, y + 1, 1.2, 0.3, 0xB6D53C);
	draw_rect(x - 2.5, y + 0.7, 1.2, 0.3, 0xB6D53C);
	draw_rect(x - 2.8, y + 0.2, 1.2, 0.4, 0xB6D53C);
	draw_rect(x - 2.2, y - 0.3, 1, 0.3, 0xB6D53C);

	//van rua
	draw_rect(x - 0.3, y + 1.5, 1, 0.25, 0x6CA333);
	draw_rect(x - 1.9, y + 1.8, 1, 0.25, 0x6CA333);
	draw_rect(x + 1.4, y + 1.8, 1, 0.25, 0x6CA333);

	draw_rect(x - 0.3, y + 0.4, 1.2, 0.3, 0x71AA35);
	draw_rect(x - 2.2, y + 0.8, 1.5, 0.25, 0x71AA35);
	draw_rect(x + 1.7, y - 0.1, 1, 0.25, 0x71AA35);

	draw_rect(x + 2, y + 0.5, 1, 0.3, 0x397841);

	draw_rect(x - 0.3, y + 1.2, 1, 0.3, 0x71AA35);
	draw_rect(x - 2.5, y - 0.4, 1, 0.3, 0x71AA35);
	draw_rect(x - 2.7, y + 0.18, 1.2, 0.27, 0x397841);


	// cai dau
	draw_rect(x + 3.5, y - 0.2, 0.75, 0.5, 0xB3D63A);
	draw_rect(x + 3.1, y + 0.2, 0.75, 0.5, 0xB3D63A);
	draw_rect(x + 3.35, y - 0.45, 0.75, 0.25, 0x71AA37);
	// con mat 
	draw_rect(x + 3.25, y + 0.2, 0.2, 0.2, 0x000000);

	draw_rect(x - 2.25, y - 2.4, 0.9, 0.7, 0x000000);// chan
	draw_rect(x + 2.25, y - 2.4, 0.9, 0.7, 0x000000);
	draw_rect(x - 2.15, y - 2.25, 0.7, 0.5, 0xB6D53C);// chan xanh 
	draw_rect(x + 2.15, y - 2.25, 0.7, 0.5, 0xB6D53C);
	draw_rect(x - 2, y - 2.1, 0.7, 0.5, 0x64962F);// chan xanh 
	draw_rect(x + 2, y - 2.1, 0.7, 0.5, 0x64962F);
	draw_rect(x - 1.8, y - 1.9, 0.7, 0.35, 0x446B4C);// chan xanh 
	draw_rect(x + 1.8, y - 1.9, 0.7, 0.35, 0x446B4C);
}

static void draw_turtleL(float x, float y, float half_size_x, float half_size_y)
{
	//nen black
	draw_rect(x, y + 2.8, 1.5, 0.3, 0x000000);
	draw_rect(x + 1.2, y + 2.5, 1.4, 0.3, 0x000000);
	draw_rect(x - 0.9, y + 2.5, 1.4, 0.3, 0x000000);
	draw_rect(x + 1.7, y + 2.2, 1.3, 0.3, 0x000000);
	draw_rect(x - 1.2, y + 2.2, 1.3, 0.3, 0x000000);
	draw_rect(x + 1.9, y + 1.9, 1.3, 0.3, 0x000000);
	draw_rect(x - 1.5, y + 1.9, 1.4, 0.3, 0x000000);
	draw_rect(x + 2.3, y + 1.4, 1.4, 0.3, 0x000000);
	draw_rect(x - 1.7, y + 1.4, 1.5, 0.4, 0x000000);
	draw_rect(x + 2.6, y + 1, 1.3, 0.3, 0x000000);
	draw_rect(x + 2.7, y + 0.7, 1.3, 0.3, 0x000000);
	draw_rect(x + 3, y + 0.2, 1.4, 0.4, 0x000000);
	draw_rect(x + 2.7, y - 0.5, 1.3, 0.4, 0x000000);


	draw_rect(x - 1.6, y + 1.2, 1.2, 0.3, 0x000000);
	draw_rect(x - 3.3, y, 1, 1, 0x000000); // dau 
	draw_rect(x - 3.5, y - 0.2, 1, 0.8, 0x000000); // dau 
	draw_rect(x - 2, y - 1, 1, 0.8, 0x000000);
	draw_rect(x + 2, y - 1, 1, 0.8, 0x000000);
	draw_rect(x - 1, y - 1.5, 1, 0.8, 0x000000);
	draw_rect(x + 1, y - 1.5, 1, 0.8, 0x000000);
	draw_rect(x - 1.75, y - 2.2, 0.8, 0.5, 0x000000);// chan
	draw_rect(x + 1.75, y - 2.2, 0.8, 0.5, 0x000000);

	draw_rect(x - 2, y - 2, 0.8, 0.8, 0x000000);
	draw_rect(x + 2, y - 2, 0.8, 0.8, 0x000000);
	//mai rua
	draw_rect(x, y + 2.5, 1, 0.3, 0xB6D53C);
	draw_rect(x + 0.3, y + 2.5, 1, 0.3, 0xB6D53C);
	draw_rect(x - 0.3, y + 2.5, 1, 0.3, 0xB6D53C);
	draw_rect(x + 1.4, y + 2.2, 1.2, 0.3, 0xB6D53C);

	draw_rect(x, y - 1, 1.4, 1, 0x3A5753);
	draw_rect(x + 1.9, y - 1.8, 0.6, 0.8, 0x3A5753);
	draw_rect(x - 1.9, y - 1.8, 0.6, 0.8, 0x3A5753);

	draw_rect(x, y + 0.2, 2.6, 1.2, 0xB6D53C);
	draw_rect(x - 0.8, y + 2.2, 1.2, 0.3, 0xB6D53C);
	draw_rect(x + 1.6, y + 1.9, 1.2, 0.3, 0xB6D53C);
	draw_rect(x + 1, y + 1.9, 1.5, 0.4, 0xB6D53C);
	draw_rect(x - 1.1, y + 1.9, 1.2, 0.3, 0xB6D53C);
	draw_rect(x + 2, y + 1.4, 1.2, 0.3, 0xB6D53C);
	draw_rect(x - 1.3, y + 1.4, 1.2, 0.3, 0xB6D53C);
	draw_rect(x + 2.3, y + 1, 1.2, 0.3, 0xB6D53C);
	draw_rect(x + 2.5, y + 0.7, 1.2, 0.3, 0xB6D53C);
	draw_rect(x + 2.8, y + 0.2, 1.2, 0.4, 0xB6D53C);
	draw_rect(x + 2.2, y - 0.3, 1, 0.3, 0xB6D53C);


	//van rua
	draw_rect(x + 0.3, y + 1.5, 1, 0.25, 0x6CA333);
	draw_rect(x + 1.9, y + 1.8, 1, 0.25, 0x6CA333);
	draw_rect(x - 1.4, y + 1.8, 1, 0.25, 0x6CA333);

	draw_rect(x + 0.3, y + 0.4, 1.2, 0.3, 0x71AA35);
	draw_rect(x + 2.2, y + 0.8, 1.5, 0.25, 0x71AA35);
	draw_rect(x - 1.7, y - 0.1, 1, 0.25, 0x71AA35);

	draw_rect(x - 2, y + 0.5, 1, 0.3, 0x397841);

	draw_rect(x + 0.3, y + 1.2, 1, 0.3, 0x71AA35);
	draw_rect(x + 2.5, y - 0.4, 1, 0.3, 0x71AA35);
	draw_rect(x + 2.7, y + 0.18, 1.2, 0.27, 0x397841);


	// cai dau
	draw_rect(x - 3.5, y - 0.2, 0.75, 0.5, 0xB3D63A);
	draw_rect(x - 3.1, y + 0.2, 0.75, 0.5, 0xB3D63A);
	draw_rect(x - 3.35, y - 0.45, 0.75, 0.25, 0x71AA37);
	// con mat 
	draw_rect(x - 3.25, y + 0.2, 0.2, 0.2, 0x000000);

	draw_rect(x - 2.25, y - 2.4, 0.9, 0.7, 0x000000);// chan
	draw_rect(x + 2.25, y - 2.4, 0.9, 0.7, 0x000000);
	draw_rect(x - 2.15, y - 2.25, 0.7, 0.5, 0xB6D53C);// chan xanh 
	draw_rect(x + 2.15, y - 2.25, 0.7, 0.5, 0xB6D53C);
	draw_rect(x - 2, y - 2.1, 0.7, 0.5, 0x64962F);// chan xanh 
	draw_rect(x + 2, y - 2.1, 0.7, 0.5, 0x64962F);
	draw_rect(x - 1.8, y - 1.9, 0.7, 0.35, 0x446B4C);// chan xanh 
	draw_rect(x + 1.8, y - 1.9, 0.7, 0.35, 0x446B4C);
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

static void draw_text(const char* text, float x, float y, float size, u32 color) {
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
static const char* entities[][14] = {
	//1:black, 0:none, 2: yellow dam, 3: yellow nhat, 4: nau
	//car_right
	"",
	"",
	"",
	"99999999999999999993333333999999999999999999",
	"99999999999999999993888888339999999999999999",
	"99999999999999999993888888339999999999999999",
	"99999733333333333403888888333389999999999999",
	"99999733333333333433433333433333899999999999",
	"99999333333333333433433333433333399999999999",
	"99999222311132222422422223431112249999999999",
	"99999223166613222422422222316661229999999999",
	"99999923165613222422422222316561999999999999",
	"99999999166619999999999999916661999999999999",
	"99999999911199999999999999991119999999999999",

	//car_left
	"",
	"",
	"",
	"99999999999999999933333339999999999999999999",
	"99999999999999993388888839999999999999999999",
	"99999999999999993388888839999999999999999999",
	"99999999999998333388888830433333333333799999",
	"99999999999833333433333433433333333333799999",
	"99999999999333333433333433433333333333399999",
	"99999999994221113432222422422223111322299999",
	"99999999992216661322222422422231666132299999",
	"99999999999916561322222422422231656132999999",
	"99999999999916661999999999999991666199999999",
	"99999999999991119999999999999999111999999999",


	//bus_right
	//0: xanh den, 1: xanh nhat, 2: xanh sieu nhat, vang: 4, cam: 5, 6: cam nhat, 9:rong
	"944444444444444444999999",
	"454444444444444446400999",
	"666666666666666666490999",
	"633363336333666666400999",
	"633363336333663636490999",
	"613361336133663636499999",
	"666666666666661616444444",
	"666666666666666666444444",
	"444444444444463636444444",
	"454440004444461616400044",
	"444400300444466666003004",
	"000003030000000000030300",
	"999900300999999999003009",
	"999990009999999999900099",

	//bus_right
	"999999444444444444444449",
	"999004644444444444444454",
	"999094666666666666666666",
	"999004666666333633363336",
	"999094636366333633363336",
	"999994636366331633163316",
	"444444616166666666666666",
	"444444666666666666666666",
	"444444636364444444444444",
	"440004616164444400044454",
	"400300666664444003004444",
	"003030000000000030300000",
	"900300999999999003009999",
	"990009999999999900099999",

	//car2_left
	"999999991122233999999",
	"999999917773777399999",
	"999999177773777739999",
	"999911777773777773999",
	"991177777773777723999",
	"914422221222223222439",
	"112255222222222552223",
	"333566533333335665333",
	"933566533333335665333",
	"999955999999999559999",
	"",

	"",
	"",
	//car2_right
	"999999332221199999999",
	"999993777377719999999",
	"999937777377771999999",
	"999377777377777119999",
	"999327777377777771199",
	"934222322222122224419",
	"322255222222222552211",
	"333566533333335665333",
	"333566533333335665339",
	"999955999999999559999",
	"",
	"",
	"",
	"",

	//balloon_left
	"999111999",
	"911233119",
	"912335319",
	"122335531",
	"122333331",
	"122333321",
	"912233219",
	"912222219",
	"991222199",
	"999111999",
	"999949999",
	"999949999",
	"999994999",
	"999999499",

	//balloon_right
	"999111999",
	"911233119",
	"912335319",
	"122335531",
	"122333331",
	"122333321",
	"912233219",
	"912222219",
	"991222199",
	"999111999",
	"999949999",
	"999949999",
	"999499999",
	"994999999",
	//bird
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

	//dino
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




};


static void draw_entities(int number, float x, float y, float size, u32 color)
{
	float half_size = size * .5f;
	float original_y = y-7;
	switch (number)
	{
	case CAR_RIGHT:
	{
		x -= 9.f;
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
					draw_rect(x, y, half_size, half_size, 0x8E8E8E);
					break;
				}
				case '1':
				{
					draw_rect(x, y, half_size, half_size, 0x000000);
					break;
				}
				case '2':
				{
					draw_rect(x, y, half_size, half_size, 0xB4931E);
					break;
				}
				case '3':
				{
					draw_rect(x, y, half_size, half_size, 0xE8C341);
					break;
				}
				case '4':
				{
					draw_rect(x, y, half_size, half_size, 0x553F0E);
					break;
				}
				case '5':
				{
					draw_rect(x, y, half_size, half_size, 0x6C747B);
					break;
				}
				case '6':
				{
					draw_rect(x, y, half_size, half_size, 0x8E8E8E);
					break;
				}
				case '7':
				{
					draw_rect(x, y, half_size, half_size, 0xDB1A19);
					break;
				}
				case '8':
				{
					draw_rect(x, y, half_size, half_size, 0x83ACC9);
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
	case CAR_LEFT:
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
					draw_rect(x, y, half_size, half_size, 0x8E8E8E);
					break;
				}
				case '1':
				{
					draw_rect(x, y, half_size, half_size, 0x000000);
					break;
				}
				case '2':
				{
					draw_rect(x, y, half_size, half_size, 0xB4931E);
					break;
				}
				case '3':
				{
					draw_rect(x, y, half_size, half_size, 0xE8C341);
					break;
				}
				case '4':
				{
					draw_rect(x, y, half_size, half_size, 0x553F0E);
					break;
				}
				case '5':
				{
					draw_rect(x, y, half_size, half_size, 0x6C747B);
					break;
				}
				case '6':
				{
					draw_rect(x, y, half_size, half_size, 0x8E8E8E);
					break;
				}
				case '7':
				{
					draw_rect(x, y, half_size, half_size, 0xDB1A19);
					break;
				}
				case '8':
				{
					draw_rect(x, y, half_size, half_size, 0x83ACC9);
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
	case BUS_RIGHT:
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
					draw_rect(x, y, half_size, half_size, 0x1D3037);
					break;
				}
				case '1':
				{
					draw_rect(x, y, half_size, half_size, 0x688E99);
					break;
				}
				case '2':
				{
					
					break;
				}
				case '3':
				{
					draw_rect(x, y, half_size, half_size, 0xAFC2C9);
					break;
				}
				case '4':
				{
					draw_rect(x, y, half_size, half_size, 0xFFD90C);
					break;
				}
				case '5':
				{
					draw_rect(x, y, half_size, half_size, 0xFF8A06);
					break;
				}
				case '6':
				{
					draw_rect(x, y, half_size, half_size, 0xFFC100);
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
	case BUS_LEFT:
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
					draw_rect(x, y, half_size, half_size, 0x1D3037);
					break;
				}
				case '1':
				{
					draw_rect(x, y, half_size, half_size, 0x688E99);
					break;
				}
				case '2':
				{

					break;
				}
				case '3':
				{
					draw_rect(x, y, half_size, half_size, 0xAFC2C9);
					break;
				}
				case '4':
				{
					draw_rect(x, y, half_size, half_size, 0xFFD90C);
					break;
				}
				case '5':
				{
					draw_rect(x, y, half_size, half_size, 0xFF8A06);
					break;
				}
				case '6':
				{
					draw_rect(x, y, half_size, half_size, 0xFFC100);
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
	case CAR2_LEFT:
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
					break;
				}
				case '1':
				{
					draw_rect(x, y, half_size, half_size, 0x83D1F8);
					break;
				}
				case '2':
				{
					draw_rect(x, y, half_size, half_size, 0x4C93D5);
					break;
				}
				case '3':
				{
					draw_rect(x, y, half_size, half_size, 0x0A75C7);
					break;
				}
				case '4':
				{
					draw_rect(x, y, half_size, half_size, 0xD2E79C);
					break;
				}
				case '5':
				{
					draw_rect(x, y, half_size, half_size, 0x1B1B1B);
					break;
				}
				case '6':
				{
					draw_rect(x, y, half_size, half_size, 0xA0A0A0);
					break;
				}
				case '7':
				{
					draw_rect(x, y, half_size, half_size, 0x67D7E3);
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
	case CAR2_RIGHT:
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
					break;
				}
				case '1':
				{
					draw_rect(x, y, half_size, half_size, 0x83D1F8);
					break;
				}
				case '2':
				{
					draw_rect(x, y, half_size, half_size, 0x4C93D5);
					break;
				}
				case '3':
				{
					draw_rect(x, y, half_size, half_size, 0x0A75C7);
					break;
				}
				case '4':
				{
					draw_rect(x, y, half_size, half_size, 0xD2E79C);
					break;
				}
				case '5':
				{
					draw_rect(x, y, half_size, half_size, 0x1B1B1B);
					break;
				}
				case '6':
				{
					draw_rect(x, y, half_size, half_size, 0xA0A0A0);
					break;
				}
				case '7':
				{
					draw_rect(x, y, half_size, half_size, 0x67D7E3);
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
	case BALLOON_LEFT:
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
					break;
				}
				case '1':
				{
					draw_rect(x, y, half_size, half_size, 0x5E002F);
					break;
				}
				case '2':
				{
					draw_rect(x, y, half_size, half_size, 0xBA005D);
					break;
				}
				case '3':
				{
					draw_rect(x, y, half_size, half_size, 0xFF0080);
					break;
				}
				case '4':
				{
					draw_rect(x, y, half_size, half_size, 0x000000);
					break;
				}
				case '5':
				{
					draw_rect(x, y, half_size, half_size, 0xFAD2CF);
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
	case BALLOON_RIGHT:
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
					break;
				}
				case '1':
				{
					draw_rect(x, y, half_size, half_size, 0x5E002F);
					break;
				}
				case '2':
				{
					draw_rect(x, y, half_size, half_size, 0xBA005D);
					break;
				}
				case '3':
				{
					draw_rect(x, y, half_size, half_size, 0xFF0080);
					break;
				}
				case '4':
				{
					draw_rect(x, y, half_size, half_size, 0x000000);
					break;
				}
				case '5':
				{
					draw_rect(x, y, half_size, half_size, 0xFAD2CF);
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
	//case CLOUD:
	//{
	//	const char** entity;
	//	entity = entities[number];
	//	float original_x = x;

	//	for (int i = 0; i <= 13; i++) {
	//		const char* row = entity[i];
	//		while (*row) {
	//			switch (*row)
	//			{
	//			case '0':
	//			{
	//				draw_rect(x, y, half_size, half_size, 0xFFFFFF);
	//				break;
	//			}
	//			case '1':
	//			{
	//				draw_rect(x, y, half_size, half_size, 0x3366CC);
	//				break;
	//			}
	//			/*case '3':
	//			{
	//				draw_rect(x, y, half_size, half_size, 0x01C4FF);
	//			}*/
	//			}
	//			x += size;
	//			row++;
	//		}
	//		y -= size;
	//		x = original_x;
	//	}
	//	break;
	//}
	//case GRASS:
	//{
	//	const char** entity;
	//	entity = entities[number];
	//	float original_x = x;

	//	for (int i = 0; i <= 13; i++) {
	//		const char* row = entity[i];
	//		while (*row) {
	//			switch (*row)
	//			{
	//			case '0':
	//			{
	//				draw_rect(x, y, half_size, half_size, 0xA56802);
	//				break;
	//			}
	//			case '1':
	//			{
	//				draw_rect(x, y, half_size, half_size, 0x8B5304);
	//				break;
	//			}
	//			case '2':
	//			{
	//				draw_rect(x, y, half_size, half_size, 0x00FF80);
	//			}
	//			case '3':
	//			{
	//				draw_rect(x, y, half_size, half_size, 0x02DD5A);
	//			}
	//			}
	//			x += size;
	//			row++;
	//		}
	//		y -= size;
	//		x = original_x;
	//	}
	//	break;
	//}
	}
}
static void draw_number(int number, float x, float y, float size, u32 color) {
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
	draw_text("NEW GAME", x - 22, y + 15, 0.75, 0xFF7901);
	draw_text("LOAD GAME", x - 22, y + 4, 0.75, 0xFF7901);
	draw_text("SETTING", x - 22, y - 9, 0.75, 0xFF7901);
	draw_text("INTRODUCTION", x - 22, y - 22, 0.75, 0xFF7901);
	draw_text("EXIT", x - 22, y - 35, 0.75, 0xFF7901);
	draw_entities(4, x - 72, y + 20, 1, 0xE61409);
	draw_entities(4, x + 50, y + 20, 1, 0xE61409);
	draw_entities(5, x - 95, y - 45, 1, 0xE61409);



	//draw_rect(x, y - 45, render_state.width, 7, 0xAB6E08);


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

static void draw_Background(float x, float y, float max_size_x, float max_size_y)
{
	//Khung 
	draw_arena_borders(x, y, 90, 49, 0x2D9929);
	draw_rect(x, y, 90, 49, 0x8DC740);//nen khung 
	draw_rect(x+55, y, 2, 49, 0x2D9929); 
	draw_rect(x + 74, y+24, 18, 1.7, 0x2D9929);
	// lane 
	draw_rect(x - 18.5, y, 71.5, 49, 0xEDA16D);//nen duong
	for (int j = 0; j < 90; j += 8)
	{
		for (int i = 0; i < 160; i += 18) //dom duong 
		{
			draw_rect(x - 103 + i, y + 47- j, 1.5, 0.8, 0xEEB395);
			draw_rect(x - 105 + i, y + 48- j, 1.5, 0.7, 0xC68164);
		}
		for (int i = 0; i < 130; i += 18) //dom duong 
		{
			draw_rect(x - 77 + i, y + 42 - j, 1.5, 0.8, 0xC68164);
			draw_rect(x - 75+ i, y + 43 - j, 1.5, 0.7, 0xC7684D);
		}
	}
	//soc dat
	draw_rect(x - 18.5, y + 38, 71.5, 0.5, 0xA06A12);
	draw_rect(x - 18.5, y + 26, 71.5, 0.5, 0xA06A12);
	draw_rect(x - 18.5, y + 13, 71.5, 0.5, 0xA06A12);
	draw_rect(x - 18.5, y + 1.5 , 71.5, 0.5, 0xA06A12);
	draw_rect(x - 18.5, y -11.5, 71.5, 0.5, 0xA06A12);
	draw_rect(x - 18.5, y - 24.5, 71.5, 0.5, 0xA06A12);
	draw_rect(x - 18.5, y - 37, 71.5, 0.5, 0xA06A12);

	//bui cay 
	draw_rect(x - 85, y - 35, 4, 7, 0x000000);
}