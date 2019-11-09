#define CA2W

//include////////////////////////////////////////////
#include<Windows.h>
#include<iostream>
#include"constant.h"
#include"device.h"
#include"Vertex.h"
#include"Camera.h"
#include"Shader.h"

//constant////////////////////////////////////////////
static bool first = true;
//function////////////////////////////////////////////
void GameMain(Device myDevice);

void OutputDebugPrintf(const char* strOutputString, ...)
{
	char strBuffer[4096] = { 0 };
	va_list vlArgs;
	va_start(vlArgs, strOutputString);
	_vsnprintf_s(strBuffer, sizeof(strBuffer) - 1, strOutputString, vlArgs);
	//vsprintf(strBuffer,strOutputString,vlArgs);
	va_end(vlArgs);
	OutputDebugString(CA2W(strBuffer));
}

//WINMAIN////////////////////////////////////////////
int WINAPI WinMain(HINSTANCE hinstance,HINSTANCE hprevinstance,LPSTR lpcmdline,int ncmdshow) {
	Device myDC(hinstance,800,600);
	
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
		GameMain(myDC);
	}//end while

	//返回到windows操作系统
	return(msg.wParam);	
}//end WinMain

void GameMain(Device myDevice) {

	//相机参数
	Vec3 cameraPos(0, 0, -1);
	Vec3 cameraDir(0, 0, 0);
	float cameraFov = 90;
	float cameraNearZ = 10;
	float cameraFarZ = 500;
	Camera mainCamera(cameraPos, cameraDir, cameraFov, myDevice.getWidth(), myDevice.getHeight(), cameraNearZ, cameraFarZ);

	//创建buffer
	Buffer buffer(myDevice.getWidth(), myDevice.getHeight());
	buffer.clearBuffer(Color{ 255.0f,255.0f,255.0f });
	DepthBuffer depthBuffer(myDevice.getWidth(), myDevice.getHeight());
	depthBuffer.clearBuffer(-2.0f);

	
	char str[512];
	if (first) {
		sprintf_s(str, "%f    ", depthBuffer[0]);
		OutputDebugPrintf(str);
		first = false;
	}
	
	
	//立方体数据
	float vertices[] = {
		// pos					//normal			//color				//uv
		-0.5f, -0.5f, -0.5f,   0.0f, 0.0f, -1.0f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f, // bottom-left
		0.5f, -0.5f, -0.5f,   0.0f, 0.0f, -1.0f,	0.0f, 1.0f, 0.0f,	1.0f, 0.0f,  // bottom-right
		0.5f, 0.5f, -0.5f,   0.0f, 0.0f, -1.0f,		1.0f, 0.0f, 0.0f,	1.0f, 1.0f,  // top-right
		0.5f, 0.5f, -0.5f,   0.0f, 0.0f, -1.0f,		1.0f, 0.0f, 0.0f,	1.0f, 1.0f, // top-right
		-0.5f, 0.5f, -0.5f,   0.0f, 0.0f, -1.0f,	0.0f, 1.0f, 0.0f,	0.0f, 1.0f,  // top-left
		-0.5f, -0.5f, -0.5f,   0.0f, 0.0f, -1.0f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f,  // bottom-left	
	};
	VertexArray VAO;
	VAO.setPosition(vertices, sizeof(vertices), 0, 3, 11);
	VAO.setNormal(vertices, sizeof(vertices), 3, 3, 11);
	VAO.setColor(vertices, sizeof(vertices), 6, 3, 11);
	VAO.setTexCoords(vertices, sizeof(vertices), 9, 2, 11);

	//立方体顶点变换
	std::vector<Vec4> newPosition;


	//drawLine(buffer, Coord{ 0,0 }, Coord{ 799,599 }, Color{ 0.0f,0.0f,0.0f });
	//drawLine(buffer, Coord{ 0,0 }, Coord{ 599,599 }, Color{ 0.0f,0.0f,0.0f });
	drawLine(buffer, Coord{ 200,200 }, Coord{ 400,400 }, Color{ 0.0f,0.0f,0.0f });
	drawLine(buffer, Coord{ 100,500 }, Coord{ 500,100 }, Color{ 0.0f,0.0f,0.0f });
	//drawLine(buffer, Coord{ 0,0 }, Coord{ 300,100 }, Color{ 0.0f,0.0f,0.0f });
	//drawLine(buffer, Coord{ 10,50 }, Coord{ 10,300 }, Color{ 0.0f,0.0f,0.0f });
	//drawLine(buffer, Coord{ 10,50 }, Coord{ 10,300 }, Color{ 0.0f,0.0f,0.0f });


	myDevice.draw(buffer);
	return;
}
