#pragma once

#ifndef BUFFER
#define BUFFER
#include <iostream>
#include"constant.h"
#include "Vec.h"

class Buffer {
public:
	int viewportWidth, viewportHeight;
	Color *ptr = NULL;

	Color operator[](int loc) const {
		return ptr[loc];
	}
	Color& operator[](int loc) {
		return ptr[loc];
	}

	Buffer() = default;
	Buffer(int width, int height) {
		viewportWidth = width;
		viewportWidth = height;
		try {
			ptr = new Color[width*height];
		}
		catch(std::bad_alloc){
			std::cout << "Bad alloc: memory alloc failed!" << std::endl;
			ptr = NULL;
		}

		if (ptr) {
			Color defaultColor = { 0.0f, 0.0f, 0.0f, 1.0f };
			std::fill(ptr, ptr + viewportWidth * viewportHeight, defaultColor);

		}
	}
	~Buffer() {
		Color defaultColor = { 0.0f, 0.0f, 0.0f, 1.0f };
		std::fill(ptr, ptr + viewportWidth * viewportHeight, defaultColor);
		delete[] ptr;
		ptr = NULL;
	}

	bool resizeBuffer(int newWidth, int newHeight) {
		viewportWidth = newWidth;
		viewportWidth = newHeight;

		Color* temp = ptr;
		
		try {
			ptr = new Color[newWidth * newHeight];
		}
		catch (std::bad_alloc) {
			std::cout << "Bad alloc: memory alloc failed!" << std::endl;
			ptr = NULL;
		}

		if (ptr) {
			Color defaultColor = { 0.0f, 0.0f, 0.0f, 1.0f };
			std::fill(ptr, ptr + viewportWidth * viewportHeight, defaultColor);
			delete[] temp;
			temp = NULL;
			return true;
		}
		else {
			std::cout << "Change size failed!" << std::endl;
			ptr = temp;
			temp = NULL;
			return false;
		}
	}

	void clearBuffer(Color clearColor) {
		std::fill(ptr, ptr + viewportWidth * viewportHeight, clearColor);
	}


};


class DepthBuffer {
public:
	int viewportWidth, viewportHeight;
	float *ptr = NULL;

	float operator[](int loc) const {
		return ptr[loc];
	}
	float& operator[](int loc) {
		return ptr[loc];
	}


	DepthBuffer() {
		viewportWidth = -1;
		viewportWidth = -1;
		ptr = NULL;
	}
	DepthBuffer(int width, int height) {
		viewportWidth = width;
		viewportWidth = height;
		try {
			ptr = new float[width * height];
		}
		catch (std::bad_alloc) {
			std::cout << "Bad alloc: memory alloc failed!" << std::endl;
			ptr = NULL;
		}

		if (ptr) {
			std::fill(ptr, ptr + viewportWidth * viewportHeight, -2);
		}
	}
	~DepthBuffer() {
		std::fill(ptr, ptr + viewportWidth * viewportHeight, -2);
		delete[] ptr;
		ptr = NULL;
	}

	bool resizeBuffer(int newWidth, int newHeight) {
		viewportWidth = newWidth;
		viewportWidth = newHeight;

		float* temp = ptr;

		try {
			ptr = new float[newWidth * newHeight];
		}
		catch (std::bad_alloc) {
			std::cout << "Bad alloc: memory alloc failed!" << std::endl;
			ptr = NULL;
		}

		if (ptr) {
			std::fill(ptr, ptr + viewportWidth * viewportHeight, -2);
			delete[] temp;
			temp = NULL;
			return true;
		}
		else {
			std::cout << "Change size failed!" << std::endl;
			ptr = temp;
			temp = NULL;
			return false;
		}
	}

	void clearBuffer(float clearDepth) {
		std::fill(ptr, ptr + viewportWidth * viewportHeight, clearDepth);
	}

};

#endif
