typedef int s32;
typedef unsigned int u32;
enum TYPE { CAR, TRUCK, BIRD, DINOSAUR };

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
static void draw_bird(float x, float y, float half_size_x, float half_size_y) //chieu dai
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
static void draw_turtle(float x, float y, float half_size_x, float half_size_y)
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

static void draw_turtleR(float x, float y, float half_size_x, float half_size_y)
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
	draw_text("NEW GAME", x - 22, y + 15, 1, 0xFF7901);
	draw_text("LOAD GAME", x - 22, y + 2, 1, 0xFF7901);
	draw_text("SETTING", x - 22, y - 11, 1, 0xFF7901);
	draw_text("INTRODUCTION", x - 22, y - 24, 1, 0xFF7901);
	draw_text("EXIT", x - 22, y - 37, 1, 0xFF7901);



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
static void draw_apple(int x, int y)
{
	// tao do 
	draw_rect(x, y, 1.3, 1.3, 0xC42732);
	draw_rect(x, y, 0.9, 0.9, 0xF4303E);
	draw_rect(x + 0.7, y + 1.2, 1, 0.4, 0x868F26); // la
	draw_rect(x+0.2, y + 0.4, 0.8, 0.7, 0xD9614D);
}
static void draw_plant(int x, int y)
{
	//bui cay 
	draw_rect(x , y-0.1 , 3.9, 4.9, 0x000000);
	draw_rect(x, y, 3.5, 4.6, 0x9FAF4D);

	draw_rect(x - 5, y - 2.2, 3.4, 2.8, 0x000000);
	draw_rect(x - 5, y - 2.2, 3.1, 2.4, 0x5F692D);
	draw_rect(x - 5.7, y - 2.4, 2.4, 2.1, 0x213C11);

	draw_rect(x + 5, y - 2.7, 2.7, 2.3, 0x000000);
	draw_rect(x + 5, y - 2.7, 2.3, 2, 0x5F692D);
	draw_rect(x + 5.2, y - 3.4, 2, 1.3, 0x213C11);

	draw_apple(x+0.5 , y + 4);
	draw_apple(x - 2.7, y );
	draw_apple(x - 8, y-2.7);
	draw_apple(x + 3.5, y - 1.8);

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

	for (int i = 0; i < 121; i += 40) {
		draw_plant(x - 80 + i, y - 43.2); // draw plant
	}
	for (int i = 0; i < 121; i += 40) {
		draw_plant(x - 80 + i, y + 8); // draw plant
	}
}
