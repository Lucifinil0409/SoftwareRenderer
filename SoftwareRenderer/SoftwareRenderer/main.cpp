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
//�������
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
		GameMain(myDC);
	}//end while

	//���ص�windows����ϵͳ
	myDC.releaseWindow();
	return(msg.wParam);	
}//end WinMain

void GameMain(Device &myDevice) {

	mainCamera = Camera(cameraPos, cameraDir, cameraFov, myDevice.getWidth(), myDevice.getHeight(), cameraNearZ, cameraFarZ);

	//����buffer
	Buffer buffer(myDevice.getWidth(), myDevice.getHeight());
	buffer.clearBuffer(Color{ 255.0f,255.0f,255.0f });
	DepthBuffer depthBuffer(myDevice.getWidth(), myDevice.getHeight());
	depthBuffer.clearBuffer(2.0f);

	//����Shader
	Shader myShader(&mainCamera, &buffer, &depthBuffer);
	
	char str[512];
	if (first) {
		sprintf_s(str, "%f    ", depthBuffer[0]);
		OutputDebugPrintf(str);
		first = false;
	}
	
	//����������
	float vertices[] = {
		// positions          // normals			//color				// texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f, 1.0f,	0.0f,  0.0f,		//����ǰ
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f, 0.0f,	1.0f,  0.0f,		//����ǰ
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,	1.0f,  1.0f,		//����ǰ
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,	1.0f,  1.0f,		//����ǰ
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f, 0.0f,	0.0f,  1.0f,		//����ǰ
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f, 1.0f,	0.0f,  0.0f,		//����ǰ

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,	0.0f,  0.0f,		//���º�
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f, 1.0f,	1.0f,  0.0f,		//���º�
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,	1.0f,  1.0f,		//���Ϻ�
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,	1.0f,  1.0f,		//���Ϻ�
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,	0.0f,  1.0f,		//���Ϻ�
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,	0.0f,  0.0f,		//���º�

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f, 0.0f,	1.0f,  0.0f,		//���Ϻ�
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,	1.0f,  1.0f,		//����ǰ
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,	0.0f,  1.0f,		//����ǰ
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,	0.0f,  1.0f,		//����ǰ
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f, 0.0f,	0.0f,  0.0f,		//���º�
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f, 0.0f,	1.0f,  0.0f,		//���Ϻ�

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f, 1.0f,	1.0f,  0.0f,		//���Ϻ�
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f, 1.0f,	1.0f,  1.0f,		//����ǰ
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f,	0.0f,  1.0f,		//����ǰ
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f,	0.0f,  1.0f,		//����ǰ
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,	0.0f,  0.0f,		//���º�
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f, 1.0f,	1.0f,  0.0f,		//���Ϻ�

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f, 1.0f,	0.0f,  1.0f,		//����ǰ
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f, 0.0f,	1.0f,  1.0f,		//����ǰ
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f, 1.0f,	1.0f,  0.0f,		//���º�
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f, 1.0f,	1.0f,  0.0f,		//���º�
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,	0.0f,  0.0f,		//���º�
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f, 1.0f,	0.0f,  1.0f,		//����ǰ

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f, 0.0f,	0.0f,  1.0f,		//����ǰ
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,	1.0f,  1.0f,		//����ǰ
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,	1.0f,  0.0f,		//���Ϻ�
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,	1.0f,  0.0f,		//���Ϻ�
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,	0.0f,  0.0f,		//���Ϻ�
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f, 0.0f,	0.0f,  1.0f			//����ǰ
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


	//����ģ�Ͷ���任��������-����ת-��ƽ�ƣ�!!!!!!!!!!
	Mat4x4 transformMat = Mat4x4::unitMat();
	transformMat = matScale(transformMat, 2.0f);
	transformMat = matRotate(transformMat, 45.0f, Vec3(0.0f, 1.0f, 0.0f));
	transformMat = matTranslate(transformMat, Vec3(0.0f, 0.0f, 1.0f));

	
	//����ͼ��buffer
	//myShader.Draw(VAO, transformMat, LINE_MODE);
	myShader.Draw(VAO, transformMat, FILL_MODE);

	myDevice.draw(buffer);
	return;
}

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
