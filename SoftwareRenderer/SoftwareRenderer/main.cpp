//include////////////////////////////////////////////
#include<Windows.h>
#include<iostream>
#include"device.h"

//constant////////////////////////////////////////////

//function////////////////////////////////////////////
void GameMain(HDC hdc);

//WINMAIN////////////////////////////////////////////
int WINAPI WinMain(HINSTANCE hinstance,HINSTANCE hprevinstance,LPSTR lpcmdline,int ncmdshow) {
	Device myDC(hinstance);
	
	MSG msg;//��Ϣ
	PAINTSTRUCT ps;//paintstruct
	
	//������ѭ��
	while (TRUE) {
		//�����Ϣ�������Ƿ�����Ϣ������У��� PM_REMOVE ��ʽ��ȡ��
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			//����Ƿ�Ϊ�˳���Ϣ
			if (msg.message == WM_QUIT) {
				break;
			}
			//ת�����ټ�
			TranslateMessage(&msg);
			//����Ϣ���͸��󶨵Ļص�����WinProc
			DispatchMessage(&msg);
		}//end if
		//����Ϸ�����߼�
		GameMain(myDC.getHDC());
	}//end while

	//���ص�windows����ϵͳ
	return(msg.wParam);	
}//end WinMain

void GameMain(HDC hdc) {
	for (int x = 10; x < 200; x++) {
		SetPixel(hdc, x, 10, (1.0, 1.0, 1.0));
	}
	return;
}
