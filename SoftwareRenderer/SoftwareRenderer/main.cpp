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
	
	MSG msg;//消息
	PAINTSTRUCT ps;//paintstruct
	
	//进入主循环
	while (TRUE) {
		//检测消息队列中是否有消息，如果有，以 PM_REMOVE 方式读取它
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			//检测是否为退出消息
			if (msg.message == WM_QUIT) {
				break;
			}
			//转换加速键
			TranslateMessage(&msg);
			//将消息发送给绑定的回调函数WinProc
			DispatchMessage(&msg);
		}//end if
		//主游戏处理逻辑
		GameMain(myDC.getHDC());
	}//end while

	//返回到windows操作系统
	return(msg.wParam);	
}//end WinMain

void GameMain(HDC hdc) {
	for (int x = 10; x < 200; x++) {
		SetPixel(hdc, x, 10, (1.0, 1.0, 1.0));
	}
	return;
}
