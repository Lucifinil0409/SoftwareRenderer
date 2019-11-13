#pragma once

#define WINDOW_CLASS_NAME "WIN3DCLASS"	//窗口类名
#define WINDOW_TITLE "SoftwareRenderer"	//窗口标题
#define WINDOW_WIDTH 800	//默认值
#define WINDOW_HEIGHT 600	//默认值

#define MY_PI 3.1415926

enum DRAW_MODE{
	LINE_MODE,
	FILL_MODE
};

struct Color {
	float R, G, B;
};

struct Coord {
	int x;
	int y;
};


