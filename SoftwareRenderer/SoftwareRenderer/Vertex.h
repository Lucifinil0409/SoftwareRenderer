#pragma once
#ifndef VERTEX
#define VERTEX

#include"Vec.h"
#include<vector>

class VertexArray {
public:
	std::vector<Vec4> Position;
	std::vector<Vec4> Normal;
	std::vector<Vec4> Color;
	std::vector<Vec2> TexCoords;





	// tangent
	std::vector<Vec3> Tangent;
	// bitangent
	std::vector<Vec3> Bitangent;

	VertexArray() = default;
	~VertexArray(){}


	void setPosition(float* dataPtr, int dataSize, int startPos, int vectorDimension, int step) {
		setData(Position, dataPtr, dataSize, startPos, vectorDimension, step);
	}
	void setNormal(float* dataPtr, int dataSize, int startPos, int vectorDimension, int step) {
		setData(Normal, dataPtr, dataSize, startPos, vectorDimension, step);
	}
	void setColor(float* dataPtr, int dataSize, int startPos, int vectorDimension, int step) {
		setData(Color, dataPtr, dataSize, startPos, vectorDimension, step);
	}
	void setTexCoords(float* dataPtr, int dataSize, int startPos, int vectorDimension, int step) {
		setData(TexCoords, dataPtr, dataSize, startPos, vectorDimension, step);
	}

private:
	template <typename T>
	void setData(std::vector<T> &dataPart, float* dataPtr, int dataSize, int startPos, int vectorDimension, int step) {
		dataPart = std::vector<T>(dataSize / step);
		for (int i = 0; i < dataSize / step; i++) {
			for (int j = 0; j < vectorDimension; j++) {
				dataPart[i][j] = dataPtr[startPos + i * step + j];
			}
			for (int j = vectorDimension; j < dataPart[i].size(); j++) {
				dataPart[i][j] = 1.0f;
			}
		}
	}

};


#endif // ! VERTEX


