#define CA2W

//include////////////////////////////////////////////
#include<Windows.h>
#include<iostream>
#include"constant.h"
#include"Camera.h"
#include"device.h"
#include"Vertex.h"
#include"Shader.h"

//constant////////////////////////////////////////////
//相机参数
Camera mainCamera;
Vec3 cameraPos(0, 0, -3);
Vec3 cameraDir(0, 0, 0);
float cameraFov = 90;
float cameraNearZ = 0.1f;
float cameraFarZ = 100.0f;


static bool first = true;
//function////////////////////////////////////////////
void GameMain(Device &myDevice);

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
	myDC.releaseWindow();
	return(msg.wParam);	
}//end WinMain

void GameMain(Device &myDevice) {

	mainCamera = Camera(cameraPos, cameraDir, cameraFov, myDevice.getWidth(), myDevice.getHeight(), cameraNearZ, cameraFarZ);

	//创建buffer
	Buffer buffer(myDevice.getWidth(), myDevice.getHeight());
	buffer.clearBuffer(Color{ 255.0f,255.0f,255.0f });
	DepthBuffer depthBuffer(myDevice.getWidth(), myDevice.getHeight());
	depthBuffer.clearBuffer(2.0f);

	//创建Shader
	Shader myShader(&mainCamera, &buffer, &depthBuffer);
	
	char str[512];
	if (first) {
		sprintf_s(str, "%f    ", depthBuffer[0]);
		OutputDebugPrintf(str);
		first = false;
	}
	
	//立方体数据
	float vertices[] = {
		// positions          // normals			//color				// texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f, 1.0f,	0.0f,  0.0f,		//左下前
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f, 0.0f,	1.0f,  0.0f,		//右下前
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,	1.0f,  1.0f,		//右上前
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,	1.0f,  1.0f,		//右上前
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f, 0.0f,	0.0f,  1.0f,		//左上前
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f, 1.0f,	0.0f,  0.0f,		//左下前

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,	0.0f,  0.0f,		//左下后
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f, 1.0f,	1.0f,  0.0f,		//右下后
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,	1.0f,  1.0f,		//右上后
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,	1.0f,  1.0f,		//右上后
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,	0.0f,  1.0f,		//左上后
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,	0.0f,  0.0f,		//左下后

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f, 0.0f,	1.0f,  0.0f,		//左上后
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,	1.0f,  1.0f,		//左上前
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,	0.0f,  1.0f,		//左下前
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,	0.0f,  1.0f,		//左下前
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f, 0.0f,	0.0f,  0.0f,		//左下后
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f, 0.0f,	1.0f,  0.0f,		//左上后

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f, 1.0f,	1.0f,  0.0f,		//右上后
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f, 1.0f,	1.0f,  1.0f,		//右上前
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f,	0.0f,  1.0f,		//右下前
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f,	0.0f,  1.0f,		//右下前
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,	0.0f,  0.0f,		//右下后
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f, 1.0f,	1.0f,  0.0f,		//右上后

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f, 1.0f,	0.0f,  1.0f,		//左下前
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f, 0.0f,	1.0f,  1.0f,		//右下前
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f, 1.0f,	1.0f,  0.0f,		//右下后
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f, 1.0f,	1.0f,  0.0f,		//右下后
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,	0.0f,  0.0f,		//左下后
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f, 1.0f,	0.0f,  1.0f,		//左下前

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f, 0.0f,	0.0f,  1.0f,		//左上前
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,	1.0f,  1.0f,		//右上前
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,	1.0f,  0.0f,		//右上后
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,	1.0f,  0.0f,		//右上后
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,	0.0f,  0.0f,		//左上后
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f, 0.0f,	0.0f,  1.0f			//左上前
	};

	int VertexLength = 11;
	int VertexSize = sizeof(vertices) / sizeof(float);
	int pointAmount = VertexSize / VertexLength;
	VertexArray VAO;
	VAO.setPosition(vertices, VertexSize, 0, 3, VertexLength);
	VAO.setNormal(vertices, VertexSize, 3, 3, VertexLength);
	VAO.setColor(vertices, VertexSize, 6, 3, VertexLength);
	VAO.setTexCoords(vertices, VertexSize, 9, 2, VertexLength);

	std::vector<int> indices(pointAmount);
	for (int i = 0; i < pointAmount; i++) {
		indices[i] = i;
	}
	VAO.setTBN(indices);


	//设置模型顶点变换矩阵（缩放-》旋转-》平移）!!!!!!!!!!
	Mat4x4 transformMat = Mat4x4::unitMat();
	transformMat = matScale(transformMat, 2.0f);
	transformMat = matRotate(transformMat, 45.0f, Vec3(0.0f, 1.0f, 0.0f));
	transformMat = matTranslate(transformMat, Vec3(0.0f, 0.0f, 1.0f));

	
	//绘制图像到buffer
	//myShader.Draw(VAO, transformMat, LINE_MODE);
	myShader.Draw(VAO, transformMat, FILL_MODE);

	myDevice.draw(buffer);
	return;
}

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

	case WM_KEYDOWN: {
		switch (wparam) {
		case 'S': {
			Vec3 moveDir = mainCamera.N;
			cameraPos -= moveDir * 0.1f;
			//mainCamera.UpdateCamera();
			break;
		}
		case 'W': {
			Vec3 moveDir = mainCamera.N;
			cameraPos += moveDir * 0.1f;
			//mainCamera.UpdateCamera();

			char str[512];
			sprintf_s(str, "mainCamera.cameraPos(%f,%f,%f)\n", mainCamera.cameraPos.x, mainCamera.cameraPos.y, mainCamera.cameraPos.z);
			OutputDebugPrintf(str);

			break;
		}
		case 'A': {
			Vec3 moveDir = mainCamera.U;
			cameraPos -= moveDir * 0.1f;
			//mainCamera.UpdateCamera();
			break;
		}
		case 'D': {
			Vec3 moveDir = mainCamera.U;
			cameraPos += moveDir * 0.1f;
			//mainCamera.UpdateCamera();
			break;
		}
		default: {
			break;
		}

		}break;
	}


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
