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
	//���ô�����
	WNDCLASSEX winclass;//�����Ĵ�����
	winclass.cbSize = sizeof(WNDCLASSEX);//�ýṹ�Ĵ�С
	winclass.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC | CS_DBLCLKS;//��ʽ���
	winclass.lpfnWndProc = WinProc;//ָ��ʱ�䴦�����ĺ���ָ��
	winclass.cbClsExtra = 0;//���������Ϣ
	winclass.cbWndExtra = 0;//����Ĵ�����Ϣ
	winclass.hInstance = hinstance;//Ӧ�ó���ʵ��
	winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//��ͼ�꣬ϵͳĬ��
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);//��꣬Ĭ�ϼ�ͷ
	winclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//���ڻ��ƴ��ڵı���ˢ
	winclass.lpszMenuName = NULL;//�˵�����
	winclass.lpszClassName = "WINCLASS1";//����
	winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);//Сͼ�꣬ϵͳĬ��
	
	//ע�ᴰ����
	if (!RegisterClassEx(&winclass)) {
		return(0);
	}

	//��������
	HWND hwnd = NULL;//��Ϣ���
	hwnd = CreateWindowEx(
		NULL,//��չ��ʽ
		"WINCLASS1",//������
		"SoftwareRenderer",//����
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,//������ʽ
		0, 0,//���ڵĳ�ʼλ�ã����Ͻ�Ϊ��0,0��
		800, 600,//���ڵĳ�ʼ��Ⱥ͸߶�
		NULL,//�����ھ��
		NULL,//�˵����
		hinstance,//Ӧ�ó���ʵ��
		NULL);//����Ĵ�������
	if (!hwnd) {
		return 0;
	}

	//������ѭ��
	MSG msg;//��Ϣ
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
		//GameMain();
	}//end while

	//���ص�windows����ϵͳ
	return(msg.wParam);	
}//end WinMain


//ϵͳ������Ϣ����ص�����
LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	PAINTSTRUCT ps;//used in WM_PAINT
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