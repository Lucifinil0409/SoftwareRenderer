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

	//创建Shader
	Shader myShader(&mainCamera, &buffer, &depthBuffer);

	
	char str[512];
	if (first) {
		sprintf_s(str, "%f    ", depthBuffer[0]);
		OutputDebugPrintf(str);
		first = false;
	}
	
	
	//立方体数据
	//float vertices[] = {
	//	// pos					//normal				//color					//uv
	//	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, -1.0f,		0.0f, 0.0f, 1.0f,		0.0f, 0.0f,		// bottom-left
	//	0.5f, -0.5f, -0.5f,		0.0f, 0.0f, -1.0f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,		// bottom-right
	//	0.5f, 0.5f, -0.5f,		0.0f, 0.0f, -1.0f,		1.0f, 0.0f, 0.0f,		1.0f, 1.0f,		// top-right
	//	0.5f, 0.5f, -0.5f,		0.0f, 0.0f, -1.0f,		1.0f, 0.0f, 0.0f,		1.0f, 1.0f,		// top-right
	//	-0.5f, 0.5f, -0.5f,		0.0f, 0.0f, -1.0f,		0.0f, 1.0f, 0.0f,		0.0f, 1.0f,		// top-left
	//	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, -1.0f,		0.0f, 0.0f, 1.0f,		0.0f, 0.0f,		// bottom-left	
	//};
	float vertices[] = {
		// positions          // normals			//color				// texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,	0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,	1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,	1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,	1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,	0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,	0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,	0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,	1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,	1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,	1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,	0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,	0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f, 1.0f,	1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f, 1.0f,	1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f, 1.0f,	0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f, 1.0f,	0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f, 1.0f,	0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f, 1.0f,	1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f, 1.0f,	1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f, 1.0f,	1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f, 1.0f,	0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f, 1.0f,	0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f, 1.0f,	0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f, 1.0f,	1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,	0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,	1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,	1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,	1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,	0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,	0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,	0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,	1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,	1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,	1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,	0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,	0.0f,  1.0f
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


	//设置模型顶点变换矩阵（旋转-》缩放-》平移）
	Mat4x4 transformMat = Mat4x4::unitMat();
	transformMat = matRotate(transformMat, 45, Vec3(0.0f, 1.0f, 0.0f));
	transformMat = matScale(transformMat, 1.0f);
	transformMat = matTranslate(transformMat, Vec3(2.0f, 0.0f, 2.0f));

	


	//绘制图像到buffer
	myShader.Draw(VAO, transformMat, LINE_MODE);

	
	


	myDevice.draw(buffer);
	return;
}
