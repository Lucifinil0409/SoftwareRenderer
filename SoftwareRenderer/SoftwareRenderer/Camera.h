#pragma once

#ifndef CAMERA
#define CAMERA

#include "Mat.h"

class Camera {
public: 
	int state;//相机状态
	int attr;//相机属性

	Vec3 cameraPos;
	Vec3 viewDirection;
	Vec3 U, V, N;
	
	float cameraFov;
	float viewDistance;

	float viewplaneWidth;
	float viewplaneHeight;
	float viewportWidth;
	float viewportHeight;
	float aspectRatio;

	float nearClipZ;
	float farClipZ;

	Mat4x4 mCam;
	Mat4x4 mPer;
	Mat4x4 mScr;

	Camera();
	Camera(Vec3 pos, Vec3 dir, float fov, float width, float height, float nearZ, float farZ) {
		cameraPos = pos;
		viewDirection = dir;

		Vec3 viewTarget(0, 0, 0);
		float r = cos(dir.x / 180 * MY_PI);
		viewTarget.x = r * sin(dir.y / 180 * MY_PI);
		viewTarget.y = sin(dir.x / 180 * MY_PI);
		viewTarget.x = r * cos(dir.y / 180 * MY_PI);

		//U,V,N
		N = (viewTarget - cameraPos).normalize();
		Vec3 up(0.0f, 1.0f, 0.0f);
		U = cross(up, N).normalize();
		V = cross(N, U);

		cameraFov = fov;
		aspectRatio = width / height;
		nearClipZ = nearZ;
		farClipZ = farZ;

		viewplaneWidth = 2;
		viewplaneHeight = 2 / aspectRatio;
		viewDistance = 1 / tan(fov / 2 / 180 * MY_PI);

		viewportWidth = width;
		viewportHeight = height;
		
	}
	~Camera();

	void UpdateCamera() {

	}

	Mat4x4 calViewMatrix() {
		Mat4x4 viewMat(0);
		viewMat.a[0][0] = U.x;	viewMat.a[0][1] = U.y;	viewMat.a[0][2] = U.z;	viewMat.a[0][3] = -cameraPos.x;
		viewMat.a[1][0] = V.x;	viewMat.a[1][1] = V.y;	viewMat.a[1][2] = V.z;	viewMat.a[1][3] = -cameraPos.y;
		viewMat.a[2][0] = N.x;	viewMat.a[2][1] = N.y;	viewMat.a[2][2] = N.z;	viewMat.a[2][3] = -cameraPos.z;
		viewMat.a[3][0] = 0;	viewMat.a[3][1] = 0;	viewMat.a[3][2] = 0;	viewMat.a[3][3] = 1;

		return viewMat;
	}
	Mat4x4 calProjectionMatrix() {
		Mat4x4 projectMat(0);
		projectMat.a[0][0] = viewDistance;
		projectMat.a[1][1] = viewDistance * aspectRatio;
		projectMat.a[2][2] = 1;
		projectMat.a[3][2] = 1;
		return projectMat;

		//待修改
	}


};




#endif



