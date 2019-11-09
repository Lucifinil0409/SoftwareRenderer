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
		int dir = (end.y - start.y) / dy;
		Coord curPoint;
		if (start.x < end.x) {
			curPoint = { start.x, start.y };
		}
		else {
			curPoint = { end.x, end.y };
		}
		drawPoint(targetBuffer, curPoint, lineColor);

		for (int i = 0; i < dx; i++) {
			curPoint.x += 1;
			curPoint.y += dir;
			drawPoint(targetBuffer, curPoint, lineColor);
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



#ifndef SHADER
#define SHADER

class Shader {

};

#endif
