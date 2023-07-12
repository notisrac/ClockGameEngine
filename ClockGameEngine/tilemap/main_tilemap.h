#pragma once
#include "..\Arduino.h"

#define MAIN_TILEMAP_HEIGHT 8
#define MAIN_TILEMAP_WIDTH 48

int main_tile_map[] PROGMEM = {
	//       0   1   2   3   4   5   6   7   0   1   2   3   4   5   6   7   0   1   2   3   4   5   6   7   0   1   2   3   4   5   6   7   0   1   2   3   4   5   6   7   0   1   2   3   4   5   6   7
	//       0   1   2   3   4   5   6   7   8   9   0   1   2   3   4   5   6   7   8   9   0   1   2   3   4   5   6   7   8   9   0   1   2   3   4   5   6   7   8   9   0   1   2   3   4   5   6   7 
	/* 1 */ 56, 57, 58, 59, 60, 61, 62, 63,255,  9, 10, 11,255,255,255,255,255,255,255,255,255,  9, 10, 11,255,255,255,255,255,255,255,255,255,  9, 10, 11,255,255,255,255,255,255,255,255,255,255,255,201,
	/* 2 */ 64, 65, 66, 67, 68, 69, 70, 71,255, 23, 24, 25,255,255,  9, 10, 11,255,255,255,255, 23, 24, 25,255,255,255,  9, 10, 10, 10, 11,255, 23, 24, 25,255,255,202,255,255,200,255,255,255,255,255,255,
	/* 3 */ 72, 73, 74, 75, 76, 77, 78, 79,255,255,255,255,255,255, 23, 24, 25,255,255,255,255,255,255,255,255,255,255, 23, 24, 24, 24, 25,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
	/* 4 */ 80, 81, 82, 83, 84, 85, 86, 87,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
	/* 5 */ 88, 89, 90, 91, 92, 93, 94, 95,255,255,255,255,255,255,255,255,  5,255,255,255,255,255,255,255,255,255,255,255,  5,255,255,255,255,255,255,255,255,255,255,255,  5,255,255,255,255,255,255,255,
	/* 6 */  3,  4,255,255,255,255,255,255,255,255,255,255,255,255,255,  0,  3,  4,255,255,255,255,255,255,255,255,255,  0,  3,  4,255,255,255,255,255,255,255,255,255,  0,  3,  4,255,255,255,255,255,255,
	/* 7 */  1,  2,  4,255,255,255,255,  6,  7,  7,  8,255,255,255,  0,  2,  1,  2,  4,255,  6,  7,  7,  7,  8,255,  0,  2,  1,  2,  4,  6,  7,  7,  8,255,255,255,  0,  2,  1,  2,  4,255,255,  6,  7,  7,
	/* 8 */ 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38,
};