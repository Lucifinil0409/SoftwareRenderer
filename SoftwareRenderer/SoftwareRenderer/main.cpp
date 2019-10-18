//include////////////////////////////////////////////
#include<Windows.h>
#include<iostream>


//constant////////////////////////////////////////////


//window constant////////////////////////////////////////////


//global variable////////////////////////////////////////////


//function////////////////////////////////////////////
LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);


//WINMAIN////////////////////////////////////////////
int WINAPI WinMain(HINSTANCE hinstance,HINSTANCE hprevinstance,LPSTR lpcmdline,int ncmdshow) {
	//设置窗口类
	WNDCLASSEX winclass;//创建的窗口类
	winclass.cbSize = sizeof(WNDCLASSEX);//该结构的大小
	winclass.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC | CS_DBLCLKS;//样式标记
	winclass.lpfnWndProc = WinProc;//指向时间处理程序的函数指针
	winclass.cbClsExtra = 0;//额外的类信息
	winclass.cbWndExtra = 0;//额外的窗口信息
	winclass.hInstance = hinstance;//应用程序实例
	winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//主图标，系统默认
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);//鼠标，默认箭头
	winclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//用于绘制窗口的背景刷
	winclass.lpszMenuName = NULL;//菜单名称
	winclass.lpszClassName = "WINCLASS1";//类名
	winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);//小图标，系统默认
	
	//注册窗口类
	if (!RegisterClassEx(&winclass)) {
		return(0);
	}

	//创建窗口
	HWND hwnd = NULL;//消息句柄
	hwnd = CreateWindowEx(
		NULL,//扩展样式
		"WINCLASS1",//窗口类
		"SoftwareRenderer",//标题
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,//窗口样式
		0, 0,//窗口的初始位置，左上角为（0,0）
		800, 600,//窗口的初始宽度和高度
		NULL,//父窗口句柄
		NULL,//菜单句柄
		hinstance,//应用程序实例
		NULL);//额外的创建参数
	if (!hwnd) {
		return 0;
	}

	//进入主循环
	MSG msg;//消息
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
		//GameMain();
	}//end while

	//返回到windows操作系统
	return(msg.wParam);	
}//end WinMain


//系统的主消息处理回调函数
LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	PAINTSTRUCT ps;//used in WM_PAINT
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