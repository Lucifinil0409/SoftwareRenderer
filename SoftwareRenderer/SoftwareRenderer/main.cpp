//include////////////////////////////////////////////
#include<Windows.h>
#include<iostream>
#include"constant.h"
#include"device.h"
#include"Vertex.h"
#include"Camera.h"
#include"Shader.h"

//constant////////////////////////////////////////////

//function////////////////////////////////////////////
void GameMain(Device myDevice);

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
		GameMain(myDC);
	}//end while

	//���ص�windows����ϵͳ
	return(msg.wParam);	
}//end WinMain

void GameMain(Device myDevice) {

	//�������
	Vec3 cameraPos(0, 0, -1);
	Vec3 cameraDir(0, 0, 0);
	float cameraFov = 90;
	float cameraNearZ = 10;
	float cameraFarZ = 500;
	Camera mainCamera(cameraPos, cameraDir, cameraFov, myDevice.getWidth(), myDevice.getHeight(), cameraNearZ, cameraFarZ);

	//����buffer
	Buffer buffer(myDevice.getWidth(), myDevice.getHeight());
	buffer.clearBuffer(Color{ 1.0f,1.0f,1.0f,1.0f });
	
	//����������
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

	//�����嶥��任
	std::vector<Vec4> newPosition;


	for (int x = 10; x < 200; x++) {
		//SetPixel(myDevice.getHDC(), x, 10, (1.0, 1.0, 1.0));
		drawPoint(buffer, Coord{ x,10 }, Color{ 0.0f,0.0f,0.0f,1.0f });
	}


	myDevice.draw(buffer);
	return;
}
