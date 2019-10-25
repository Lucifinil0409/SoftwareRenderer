#pragma once

#ifndef DEVICE
#define DEVICE

#include<Windows.h>

//window constant////////////////////////////////////////////
#define WINDOW_CLASS_NAME "WIN3DCLASS"	//窗口类名
#define WINDOW_TITLE "SoftwareRenderer"	//窗口标题
#define WINDOW_WIDTH 800	//默认值
#define WINDOW_HEIGHT 600	//默认值

//function////////////////////////////////////////////
LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

class Device {
private:
	HINSTANCE hinstance = NULL;//应用程序实例
	WNDCLASSEX winclass;//创建的窗口类
	HWND hwnd = NULL;//消息句柄
	HDC hdc;//设备场景
	int width;//窗口宽度
	int height;//窗口高度
	
	int createWindow() {
		//创建窗口类
		winclass.cbSize = sizeof(WNDCLASSEX);//该结构的大小
		winclass.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC | CS_DBLCLKS;//样式标记
		winclass.lpfnWndProc = WinProc;//指向事件处理程序的函数指针
		winclass.cbClsExtra = 0;//额外的类信息
		winclass.cbWndExtra = 0;//额外的窗口信息
		winclass.hInstance = hinstance;//应用程序实例
		winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//主图标，系统默认
		winclass.hCursor = LoadCursor(NULL, IDC_ARROW);//鼠标，默认箭头
		winclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//用于绘制窗口的背景刷
		winclass.lpszMenuName = NULL;//菜单名称
		winclass.lpszClassName = WINDOW_CLASS_NAME;//类名
		winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);//小图标，系统默认

		//注册窗口类
		if (!RegisterClassEx(&winclass)) {
			return(0);
		}

		//创建窗口
		hwnd = CreateWindowEx(
			NULL,//扩展样式
			WINDOW_CLASS_NAME,//窗口类
			WINDOW_TITLE,//标题
			WS_OVERLAPPEDWINDOW | WS_VISIBLE,//窗口样式
			0, 0,//窗口的初始位置，左上角为（0,0）
			width, height,//窗口的初始宽度和高度
			NULL,//父窗口句柄
			NULL,//菜单句柄
			hinstance,//应用程序实例
			NULL);//额外的创建参数

		if (!hwnd) {
			return 0;
		}

		return(1);
	}

	void releaseWindow() {
		ReleaseDC(hwnd, hdc);
	}

public:
	Device();
	Device(HINSTANCE hins,int newWidth = WINDOW_WIDTH, int newHeight = WINDOW_HEIGHT) {
		this->hinstance = hins;
		this->width = newWidth;
		this->height = newHeight;

		if (!createWindow()) {
			//创建失败
		}

		hdc = GetDC(hwnd);
	}
	~Device() {
		releaseWindow();
	}

	HDC getHDC() { return hdc; }
	HWND getHWND() { return hwnd; }
	HINSTANCE getHINSTANCE() { return hinstance; }
	WNDCLASSEX getWNDCLASSEX() { return winclass; }

	void drawWindow();

};


//系统的主消息处理回调函数
LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	//系统主消息处理程序
	PAINTSTRUCT ps;//用于WM_PAINT中
	HDC hdc;//设备场景句柄

	//消息判断
	switch (msg) {
	case WM_CREATE: {
		//初始化代码
			//成功返回
		return(0);
	}break;

	case WM_PAINT: {
		//验证窗口是否有效
		hdc = BeginPaint(hwnd, &ps);
		//绘制代码
		EndPaint(hwnd, &ps);
		//成功返回
		return(0);
	}break;

	case WM_DESTROY: {
		//关闭应用程序，这将返回一条WM_QUIT消息
		PostQuitMessage(0);
		//成功返回
		return(0);
	}break;

	default: break;

	}//end switch

	//使用windows默认函数处理其他消息
	return (DefWindowProc(hwnd, msg, wparam, lparam));
}//end WinProc

#endif
