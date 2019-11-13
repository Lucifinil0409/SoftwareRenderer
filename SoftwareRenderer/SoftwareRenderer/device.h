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
	HINSTANCE hinstance = NULL;//Ӧ�ó���ʵ��
	WNDCLASSEX winclass;//�����Ĵ�����
	HWND hwnd = NULL;//��Ϣ���
	HDC hdc;//�豸����
	int width;//���ڿ��
	int height;//���ڸ߶�
	
	int createWindow() {
		//����������
		winclass.cbSize = sizeof(WNDCLASSEX);//�ýṹ�Ĵ�С
		winclass.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC | CS_DBLCLKS;//��ʽ���
		winclass.lpfnWndProc = WinProc;//ָ���¼��������ĺ���ָ��
		winclass.cbClsExtra = 0;//���������Ϣ
		winclass.cbWndExtra = 0;//����Ĵ�����Ϣ
		winclass.hInstance = hinstance;//Ӧ�ó���ʵ��
		winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//��ͼ�꣬ϵͳĬ��
		winclass.hCursor = LoadCursor(NULL, IDC_ARROW);//��꣬Ĭ�ϼ�ͷ
		winclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//���ڻ��ƴ��ڵı���ˢ
		winclass.lpszMenuName = NULL;//�˵�����
		winclass.lpszClassName = WINDOW_CLASS_NAME;//����
		winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);//Сͼ�꣬ϵͳĬ��

		//ע�ᴰ����
		if (!RegisterClassEx(&winclass)) {
			return(0);
		}

		//��������
		hwnd = CreateWindowEx(
			NULL,//��չ��ʽ
			WINDOW_CLASS_NAME,//������
			WINDOW_TITLE,//����
			WS_OVERLAPPEDWINDOW | WS_VISIBLE,//������ʽ
			0, 0,//���ڵĳ�ʼλ�ã����Ͻ�Ϊ��0,0��
			width, height,//���ڵĳ�ʼ��Ⱥ͸߶�
			NULL,//�����ھ��
			NULL,//�˵����
			hinstance,//Ӧ�ó���ʵ��
			NULL);//����Ĵ�������

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
			//����ʧ��
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
			//��תy������,��Ļ���Ͻ�Ϊ0��0
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


////ϵͳ������Ϣ����ص�����
//LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
//	//ϵͳ����Ϣ�������
//	PAINTSTRUCT ps;//����WM_PAINT��
//	HDC hdc;//�豸�������
//
//	//��Ϣ�ж�
//	switch (msg) {
//	case WM_CREATE: {
//		//��ʼ������
//		
//		//�ɹ�����
//		return(0);
//	}break;
//
//	case WM_PAINT: {
//		//��֤�����Ƿ���Ч
//		hdc = BeginPaint(hwnd, &ps);
//		//���ƴ���
//		EndPaint(hwnd, &ps);
//		//�ɹ�����
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
//		//�ر�Ӧ�ó����⽫����һ��WM_QUIT��Ϣ
//		PostQuitMessage(0);
//		//�ɹ�����
//		return(0);
//	}break;
//
//	default: break;
//
//	}//end switch
//
//	//ʹ��windowsĬ�Ϻ�������������Ϣ
//	return (DefWindowProc(hwnd, msg, wparam, lparam));
//}//end WinProc

#endif
