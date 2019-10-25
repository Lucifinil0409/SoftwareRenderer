#pragma once

#ifndef DEVICE
#define DEVICE

#include<Windows.h>

//window constant////////////////////////////////////////////
#define WINDOW_CLASS_NAME "WIN3DCLASS"	//��������
#define WINDOW_TITLE "SoftwareRenderer"	//���ڱ���
#define WINDOW_WIDTH 800	//Ĭ��ֵ
#define WINDOW_HEIGHT 600	//Ĭ��ֵ

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
			//����ʧ��
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


//ϵͳ������Ϣ����ص�����
LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	//ϵͳ����Ϣ�������
	PAINTSTRUCT ps;//����WM_PAINT��
	HDC hdc;//�豸�������

	//��Ϣ�ж�
	switch (msg) {
	case WM_CREATE: {
		//��ʼ������
			//�ɹ�����
		return(0);
	}break;

	case WM_PAINT: {
		//��֤�����Ƿ���Ч
		hdc = BeginPaint(hwnd, &ps);
		//���ƴ���
		EndPaint(hwnd, &ps);
		//�ɹ�����
		return(0);
	}break;

	case WM_DESTROY: {
		//�ر�Ӧ�ó����⽫����һ��WM_QUIT��Ϣ
		PostQuitMessage(0);
		//�ɹ�����
		return(0);
	}break;

	default: break;

	}//end switch

	//ʹ��windowsĬ�Ϻ�������������Ϣ
	return (DefWindowProc(hwnd, msg, wparam, lparam));
}//end WinProc

#endif
