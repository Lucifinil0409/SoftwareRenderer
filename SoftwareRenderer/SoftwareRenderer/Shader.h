#pragma once

#include"constant.h"
#include"Buffer.h"

void drawPoint(Buffer &targetBuffer, Coord point, Color pointColor) {
	*(targetBuffer.ptr + point.y * targetBuffer.viewportWidth + point.x) = pointColor;
}

void drawLine(Buffer &targetBuffer, Coord start, Coord end, Color lineColor) {
	int dx = abs(end.x - start.x), dy = abs(end.y - start.y);
	if (dx == 0 && dy == 0) {
		drawPoint(targetBuffer, start, lineColor);
	}
	else if (dx == 0) {
		int dir = (end.y - start.y) / dy;
		for (int y = start.y; y <= end.y; y += dir) {
			drawPoint(targetBuffer, Coord{ start.x,y }, lineColor);
		}
	}
	else if (dy == 0) {
		int dir = (end.x - start.x) / dx;
		for (int x = start.x; x <= end.x; x += dir) {
			drawPoint(targetBuffer, Coord{ x,start.y }, lineColor);
		}
	}
	else if (dy == dx) {
		int dirX = (end.x - start.x) / dx;
		int dirY = (end.y - start.y) / dy;
		for (int i = start.x, j = start.y; (i != end.x && j != end.y); i += dirX, j += dirY) {
			drawPoint(targetBuffer, Coord{ i,j }, lineColor);
		}
	}
	else {
		float lineK = (float)(end.y - start.y) / (float)(end.x - start.x);
		int delta = (lineK > 0) ? 1 : -1;
		if (abs(lineK) <= 1) {
			Coord curPoint;
			if (start.x < end.x) {
				curPoint = { start.x, start.y };
			}
			else {
				curPoint = { end.x, end.y };
			}

			int p = 2 * dy - dx;
			drawPoint(targetBuffer, curPoint, lineColor);
			for (int i = 0; i < dx; i++) {
				if (p < 0) {
					curPoint.x += 1;
					drawPoint(targetBuffer, curPoint, lineColor);

					p += 2 * dy;
				}
				else {
					curPoint.x += 1;
					curPoint.y += delta;
					drawPoint(targetBuffer, curPoint, lineColor);
					p += 2 * dy - 2 * dx;
				}
			}	
		}
		else {
			Coord curPoint;
			if (start.y < end.y) {
				curPoint = { start.x, start.y };
			}
			else {
				curPoint = { end.x, end.y };
			}

			int p = 2 * dx - dy;
			drawPoint(targetBuffer, curPoint, lineColor);
			for (int j = 0; j < dy; j++) {
				if (p < 0) {
					curPoint.y += 1;
					drawPoint(targetBuffer, curPoint, lineColor);
					p += 2 * dx;
				}
				else {
					curPoint.y += 1;
					curPoint.x += delta;
					drawPoint(targetBuffer, curPoint, lineColor);
					p += 2 * dx - 2 * dy;
				}
			}
		}
	}
}

#ifndef FRAG
#define FRAG
class Frag {


};

#endif



#ifndef SHADER
#define SHADER

class Shader {
public:
	Camera* myCamera;
	Buffer* myColorBuffer;
	DepthBuffer* myDepthBuffer;

	Shader(Camera* _myCamera, Buffer* _myColorBuffer, DepthBuffer* _myDepthBuffer = NULL) :myCamera(_myCamera), myColorBuffer(_myColorBuffer), myDepthBuffer(_myDepthBuffer){}
	~Shader(){}


	void Draw(VertexArray& VAO, Mat4x4 modelTrans, DRAW_MODE mode) {
		//法线纠正
		normalCorrect(VAO, modelTrans);

		//模型坐标变换到世界坐标
		toWordCoord(VAO, modelTrans);


		//世界坐标变换到相机坐标
		toCameraCoord(VAO);


		//相机坐标变换到透视坐标
		toPerspectCoord(VAO);


		//透视坐标变换到屏幕坐标
		toScreenCoord(VAO);



		if (mode == LINE_MODE) {
			int vertexAmount = VAO.transPosition.size();
			std::vector<Coord> screenPos = std::vector<Coord>(vertexAmount);
			for (int i = 0; i < vertexAmount; i++) {
				screenPos[i].x = VAO.transPosition[i].x;
				screenPos[i].y = VAO.transPosition[i].y;
			}

			for (int i = 0; i < vertexAmount; i++) {
				for (int j = 0; j < vertexAmount; j++) {
					drawLine(*myColorBuffer, screenPos[i], screenPos[j], Color{ 255.0f,0.0f,0.0f });
				}
			}
		}
		else if(mode == FILL_MODE){



		}
	}

	void normalCorrect(VertexArray &vertexData, Mat4x4 modelMat) {
		Mat4x4 normalCorrectMat = modelMat.inverse().transpose();
		//纠正法线
		applyTrans(normalCorrectMat, vertexData.Normal);
		//纠正切线坐标系？？？？？？
		applyTrans(normalCorrectMat, vertexData.Tangent);
		applyTrans(normalCorrectMat, vertexData.Bitangent);
	}

	void toWordCoord(VertexArray &vertexData, Mat4x4 mat) {
		size_t pointCount = vertexData.Position.size();
		vertexData.transPosition = std::vector<Vec4>(pointCount);
		for (unsigned int i = 0; i < pointCount; i++) {
			vertexData.transPosition[i] = mat * vertexData.Position[i];
		}
	}

	void toCameraCoord(VertexArray &vertexData) {
		Mat4x4 viewMatrix = myCamera->calViewMatrix();

		size_t pointCount = vertexData.transPosition.size();
		for (unsigned int i = 0; i < pointCount; i++) {
			vertexData.transPosition[i] = viewMatrix * vertexData.transPosition[i];
		}
	}

	void toPerspectCoord(VertexArray &vertexData) {
		Mat4x4 projectionMatrix = myCamera->calProjectionMatrix();

		size_t pointCount = vertexData.transPosition.size();
		for (unsigned int i = 0; i < pointCount; i++) {
			vertexData.transPosition[i] = projectionMatrix * vertexData.transPosition[i];
			vertexData.transPosition[i] = vertexData.transPosition[i] / vertexData.transPosition[i].w;
		}
	}

	void toScreenCoord(VertexArray &vertexData) {
		Mat4x4 screenMatrix = myCamera->calScreenMatrix();

		size_t pointCount = vertexData.transPosition.size();
		for (unsigned int i = 0; i < pointCount; i++) {
			vertexData.transPosition[i] = screenMatrix * vertexData.transPosition[i];
		}
	}

private:
	





};

#endif
