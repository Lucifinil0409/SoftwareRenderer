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
	//setTBN计算Tangent，Bitangent
	std::vector<Vec4> Tangent;
	std::vector<Vec4> Bitangent;

	//存储变换后的数据
	std::vector<Vec4> transPosition;


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
	void setTBN(const std::vector<int> &indices) {////////////////////////////////////////////////////
		const int size = Position.size();
		Tangent = std::vector<Vec4>(size);
		Bitangent = std::vector<Vec4>(size);

		const int idx_size = indices.size();
		for (int i = 2; i < idx_size; i += 3) {
			Vec4 v0 = Position[indices[i - 2]],
				 v1 = Position[indices[i - 1]],
				 v2 = Position[indices[i]];
			Vec3 edge1 = (v1 - v0).toVec3(), edge2 = (v2 - v0).toVec3();
			Vec2 deltaUV1 = TexCoords[i - 1] - TexCoords[i - 2], deltaUV2 = TexCoords[i] - TexCoords[i - 2];
			Vec4 tangent, biTangent;
			float delta = deltaUV1.getU()*deltaUV2.getV() - deltaUV1.getV()*deltaUV2.getU();
			if (abs(delta) < 1e-6) {
				std::cout << "Calculate TBN failed." << std::endl;
				return;
			}
			else {
				delta = 1.f / delta;
				tangent = Vec4(delta * (deltaUV2.getV()*edge1 - deltaUV1.getV()*edge2), 0.0f).normalize();
				biTangent = Vec4(delta * (deltaUV1.getU()*edge2 - deltaUV2.getU()*edge1), 0.0f).normalize();
				for (int j = 0; j < 3; ++j) {
					Tangent[indices[i - j]] = tangent;
					Bitangent[indices[i - j]] = biTangent;
				}
			}
		}
		return;
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


