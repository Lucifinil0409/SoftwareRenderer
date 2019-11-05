#pragma once

#include"constant.h"
#include"Buffer.h"

void drawPoint(Buffer targetBuffer, Coord point, Color pointColor) {
	targetBuffer[point.x*targetBuffer.viewportWidth + point.y] = pointColor;
}

void drawLine(Buffer targetBuffer, Coord start, Coord end, Color lineColor) {
	int dx = abs(end.x - start.x), dy = abs(end.y - start.y);
	if (dx == 0 && dy == 0) {
		drawPoint(targetBuffer, start, lineColor);
	}
	else if (dx == 0) {
		for (int y = start.y; y <= end.y; y++) {
			drawPoint(targetBuffer, Coord{ start.x,y }, lineColor);
		}
	}
	else if (dy == 0) {
		for (int x = start.x; x <= end.x; x++) {
			drawPoint(targetBuffer, Coord{ x,start.y }, lineColor);
		}
	}
	else {
		float lineK = (end.x - start.x) / (end.y - start.y);
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

			int p = 2 * dy - dx;
			drawPoint(targetBuffer, curPoint, lineColor);

			for (int j = 0; j < dy; j++) {
				if (p < 0) {
					curPoint.y += 1;
					drawPoint(targetBuffer, curPoint, lineColor);

					p += 2 * dy;
				}
				else {
					curPoint.y += 1;
					curPoint.x += delta;
					drawPoint(targetBuffer, curPoint, lineColor);
					p += 2 * dy - 2 * dx;
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
