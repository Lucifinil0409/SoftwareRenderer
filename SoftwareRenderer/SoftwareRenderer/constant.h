#pragma once

#define WINDOW_CLASS_NAME "WIN3DCLASS"	//��������
#define WINDOW_TITLE "SoftwareRenderer"	//���ڱ���
#define WINDOW_WIDTH 800	//Ĭ��ֵ
#define WINDOW_HEIGHT 600	//Ĭ��ֵ

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


