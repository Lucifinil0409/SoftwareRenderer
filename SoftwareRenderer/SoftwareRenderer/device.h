#pragma once

#include<Windows.h>
#include"constant.h"
#include"Buffer.h"

#ifndef DEVICE
#define DEVICE

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

		return 1;
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

	void releaseWindow() {
		ReleaseDC(hwnd, hdc);
	}

	HDC getHDC() { return hdc; }
	HWND getHWND() { return hwnd; }
	HINSTANCE getHINSTANCE() { return hinstance; }
	WNDCLASSEX getWNDCLASSEX() { return winclass; }
	int getWidth() { return width; }
	int getHeight() { return height; }

	void draw(const Buffer &buffer) {//////////////////////////////////////////////////////////
		COLORREF *arr = new COLORREF[buffer.viewportWidth * buffer.viewportHeight];
		Color* c;
		for (int y = 0; y < buffer.viewportHeight; y++) {
			//翻转y轴坐标,屏幕左上角为0，0
			int offsetY = y * buffer.viewportWidth;

			for (int x = 0; x < buffer.viewportWidth; x++) {
				c = buffer.ptr + offsetY + x;

				*(arr + offsetY + x) = RGB(int(c->B), int(c->G), int(c->R));
			}

		}
		HBITMAP map = CreateBitmap(buffer.viewportWidth, buffer.viewportHeight, 1, 4 * 8, (void*)arr);
		HDC src = CreateCompatibleDC(hdc);
		SelectObject(src, map);
		BitBlt(hdc, 0, 0, buffer.viewportWidth, buffer.viewportHeight, src, 0, 0, SRCCOPY);
		DeleteObject(map);
		DeleteDC(src);
		delete[] arr;
	}

};


////系统的主消息处理回调函数
//LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
//	//系统主消息处理程序
//	PAINTSTRUCT ps;//用于WM_PAINT中
//	HDC hdc;//设备场景句柄
//
//	//消息判断
//	switch (msg) {
//	case WM_CREATE: {
//		//初始化代码
//		
//		//成功返回
//		return(0);
//	}break;
//
//	case WM_PAINT: {
//		//验证窗口是否有效
//		hdc = BeginPaint(hwnd, &ps);
//		//绘制代码
//		EndPaint(hwnd, &ps);
//		//成功返回
//		return(0);
//	}break;
//
//	case WM_KEYDOWN: {
//		switch (wparam) {
//		/*case 'S': {
//			Vec3 moveDir = mainCamera.N;
//			mainCamera.cameraPos -= moveDir * 0.1f;
//			mainCamera.UpdateCamera();
//			break;
//		}
//		case 'W': {
//			Vec3 moveDir = mainCamera.N;
//			mainCamera.cameraPos += moveDir * 0.1f;
//			mainCamera.UpdateCamera();
//			break;
//		}
//		case 'A': {
//			Vec3 moveDir = mainCamera.U;
//			mainCamera.cameraPos -= moveDir * 0.1f;
//			mainCamera.UpdateCamera();
//			break;
//		}
//		case 'D': {
//			Vec3 moveDir = mainCamera.U;
//			mainCamera.cameraPos += moveDir * 0.1f;
//			mainCamera.UpdateCamera();
//			break;
//		}
//		default: {
//			break;
//		}*/
//
//		}break;
//	}
//
//
//	case WM_DESTROY: {
//		//关闭应用程序，这将返回一条WM_QUIT消息
//		PostQuitMessage(0);
//		//成功返回
//		return(0);
//	}break;
//
//	default: break;
//
//	}//end switch
//
//	//使用windows默认函数处理其他消息
//	return (DefWindowProc(hwnd, msg, wparam, lparam));
//}//end WinProc

#endif
