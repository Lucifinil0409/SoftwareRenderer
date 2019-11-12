#pragma once
#define CA2W
void OutputDebugPrintf(const char* strOutputString, ...);

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
		for (int y = start.y; y != end.y; y += dir) {
			drawPoint(targetBuffer, Coord{ start.x,y }, lineColor);
		}
	}
	else if (dy == 0) {
		int dir = (end.x - start.x) / dx;
		for (int x = start.x; x != end.x; x += dir) {
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
public:
	Vec4 fragPos;
	Vec4 fragNormal;
	Vec2 fragTexCoord;
	Vec4 fragColor;
	Coord fragScreenPos;

	Frag() = default;
	Frag(VertexArray &vao, std::vector<Coord> &screenPosVector, int index) {
		fragPos = vao.transPosition[index];
		fragNormal = vao.Normal[index];
		fragTexCoord = vao.TexCoords[index];
		fragColor = vao.Color[index];
		fragScreenPos = screenPosVector[index];
	}
	~Frag() = default;

	static Frag interpolate(Frag v0, Frag v1, Frag v2, float u, float v) {
		float w = 1.0f - u - v;
		Frag curFrag;
		curFrag.fragPos = w * v0.fragPos + u * v1.fragPos + v * v2.fragPos;
		curFrag.fragNormal = w * v0.fragNormal + u * v1.fragNormal + v * v2.fragNormal;
		curFrag.fragTexCoord = w * v0.fragTexCoord + u * v1.fragTexCoord + v * v2.fragTexCoord;
		curFrag.fragColor = w * v0.fragColor + u * v1.fragColor + v * v2.fragColor;
		return curFrag;
	}

};

#endif

#ifndef TRIBOX
#define TRIBOX
struct TriBox {
	int minX, maxX, minY, maxY;
};

int getMin(int value1, int value2, int value3) {
	int curMin;
	curMin = (value1 < value2) ? value1 : value2;
	curMin = (curMin < value3) ? curMin : value3;
	return curMin;
}
int getMax(int value1, int value2, int value3) {
	int curMax;
	curMax = (value1 > value2) ? value1 : value2;
	curMax = (curMax > value3) ? curMax : value3;
	return curMax;
}

TriBox getTriBox(Frag v0, Frag v1, Frag v2) {
	TriBox curBox;
	curBox.minX = getMin(v0.fragScreenPos.x, v1.fragScreenPos.x, v2.fragScreenPos.x);
	curBox.maxX = getMax(v0.fragScreenPos.x, v1.fragScreenPos.x, v2.fragScreenPos.x);
	curBox.minY = getMin(v0.fragScreenPos.y, v1.fragScreenPos.y, v2.fragScreenPos.y);
	curBox.maxY = getMax(v0.fragScreenPos.y, v1.fragScreenPos.y, v2.fragScreenPos.y);
	return curBox;
}

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
		//法线纠正 (以及切线坐标系？？？)
		normalCorrect(VAO, modelTrans);

		//模型坐标变换到世界坐标
		toWordCoord(VAO, modelTrans);


		//世界坐标变换到相机坐标
		toCameraCoord(VAO);


		//相机坐标变换到透视坐标
		toPerspectCoord(VAO);


		//透视坐标变换到屏幕坐标，传入vector<Coord>用于存储屏幕坐标
		std::vector<Coord> screenPos;
		toScreenCoord(VAO, screenPos);

	
		if(mode == FILL_MODE){
			//光栅化
			std::vector<Frag> fragVector;
			rasterization(VAO, screenPos, fragVector);


			//片段着色器
			fragmentProgram(fragVector);


			//进行深度测试后写入缓存
			int fragAmount = fragVector.size();
			for (int i = 0; i < fragAmount; i++) {
				int offsetInBuffer = fragVector[i].fragScreenPos.y*myDepthBuffer->viewportWidth + fragVector[i].fragScreenPos.x;
				if (fragVector[i].fragPos.z < *(myDepthBuffer->ptr + offsetInBuffer)) {
					*(myDepthBuffer->ptr + offsetInBuffer) = fragVector[i].fragPos.z;
					for (int j = 0; j < 3; j++) {
						if (fragVector[i].fragColor[j] > 1.0f) { fragVector[i].fragColor[j] = 1.0f; }
						if (fragVector[i].fragColor[j] < 0.0f) { fragVector[i].fragColor[j] = 0.0f; }
					}
					*(myColorBuffer->ptr + offsetInBuffer) = Color{ fragVector[i].fragColor.getR() * 255.0f, fragVector[i].fragColor.getG() * 255.0f, fragVector[i].fragColor.getB() * 255.0f };
				}
			}


		}
		else if (mode == LINE_MODE) {
			int vertexAmount = screenPos.size();
			for (int i = 0; i < vertexAmount; i += 3) {
				drawLine(*myColorBuffer, screenPos[i], screenPos[i + 1], Color{ 255.0f,0.0f,0.0f });
				drawLine(*myColorBuffer, screenPos[i], screenPos[i + 2], Color{ 255.0f,0.0f,0.0f });
				drawLine(*myColorBuffer, screenPos[i + 1], screenPos[i + 2], Color{ 255.0f,0.0f,0.0f });
			}
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
		Mat4x4 PerspectiveMatrix = myCamera->calPerspectiveMatrix();

		size_t pointCount = vertexData.transPosition.size();
		for (unsigned int i = 0; i < pointCount; i++) {
			vertexData.transPosition[i] = PerspectiveMatrix * vertexData.transPosition[i];
			vertexData.transPosition[i] = vertexData.transPosition[i] / vertexData.transPosition[i].w;
		}
	}

	void toScreenCoord(VertexArray &vertexData, std::vector<Coord> &screenPosVector) {
		Mat4x4 screenMatrix = myCamera->calScreenMatrix();

		size_t pointCount = vertexData.transPosition.size();
		screenPosVector = std::vector<Coord>(pointCount);

		for (unsigned int i = 0; i < pointCount; i++) {
			Vec4 temp = screenMatrix * vertexData.transPosition[i];
			screenPosVector[i].x = temp.x;
			screenPosVector[i].y = temp.y;
		}
	}

	void rasterization(VertexArray &vertexData, std::vector<Coord> &screenPosVector, std::vector<Frag> &fragData) {
		size_t pointCount = screenPosVector.size();
	
		for (unsigned int i = 0; i < pointCount; i+=3) {
			//每个三角形图元的三个顶点
			Frag v0(vertexData, screenPosVector, i);
			Frag v1(vertexData, screenPosVector, i+1);
			Frag v2(vertexData, screenPosVector, i+2);
			//每个三角形图元(屏幕像素坐标)的包围盒
			TriBox curTriBox = getTriBox(v0, v1, v2);
			//每个三角形图元的边v0_to_v1，v0_to_v2的屏幕坐标向量
			//edge0 即 v0_to_v1		edge1 即 v0_to_v2
			Vec2 edge0(v1.fragScreenPos.x - v0.fragScreenPos.x, v1.fragScreenPos.y - v0.fragScreenPos.y);
			Vec2 edge1(v2.fragScreenPos.x - v0.fragScreenPos.x, v2.fragScreenPos.y - v0.fragScreenPos.y);

			float edge0_dot_edge0 = Vec2::dot(edge0, edge0);
			float edge1_dot_edge1 = Vec2::dot(edge1, edge1);
			float edge1_dot_edge0 = Vec2::dot(edge1, edge0);
			float value_00mul11_sub_10mul01 = (edge0_dot_edge0 * edge1_dot_edge1 - edge1_dot_edge0 * edge1_dot_edge0);
			if (abs(value_00mul11_sub_10mul01) < 1e-6) { continue; }

			//判断三角形包围盒里每个像素是否在三角形中，在便进行处理，不在跳过
			for (int fragX = curTriBox.minX; fragX <= curTriBox.maxX; fragX++) {
				for (int fragY = curTriBox.minY; fragY <= curTriBox.maxY; fragY++) {
					//舍弃超出屏幕的片段
					if ((fragX < 0) || (fragX >= myColorBuffer->viewportWidth) || (fragY < 0) || (fragY >= myColorBuffer->viewportHeight)) { continue; }
					
					//通过重心法判断
					//edge2 即 v0_to_frag
					Vec2 edge2(fragX - v0.fragScreenPos.x, fragY - v0.fragScreenPos.y);

					float edge2_dot_edge2 = Vec2::dot(edge2, edge2);
					float edge2_dot_edge0 = Vec2::dot(edge2, edge0);
					float edge2_dot_edge1 = Vec2::dot(edge2, edge1);

					//解方程edge2=u*edge0+v*edge1，求出u，v
					float u = ((edge1_dot_edge1 * edge2_dot_edge0 - edge1_dot_edge0 * edge2_dot_edge1) / value_00mul11_sub_10mul01);
					float v = ((edge0_dot_edge0 * edge2_dot_edge1 - edge1_dot_edge0 * edge2_dot_edge0) / value_00mul11_sub_10mul01);

					//u>=0 && v>=0 && u+v<=1 则{fragX,fragY}在三角形内部及边上
					if ((u >= 0) && (v >= 0) && (u + v <= 1)) {
						Frag curFrag = Frag::interpolate(v0, v1, v2, u, v);
						curFrag.fragScreenPos = Coord{ fragX,fragY };

						float curFragDepth = curFrag.fragPos.z;
						int offsetInBuffer = myDepthBuffer->viewportWidth*fragY + fragX;

						if (curFragDepth < *(myDepthBuffer->ptr + offsetInBuffer)) {
							int inverseW = curFrag.fragPos.w;/////////////////////////////////////

							fragData.push_back(curFrag);
						}
						else {
							continue;
						}
					}
					else { 
						continue;
					}
				}
			}

		}

	}

	void fragmentProgram(std::vector<Frag> &fragData) {

	}


private:
	





};

#endif
