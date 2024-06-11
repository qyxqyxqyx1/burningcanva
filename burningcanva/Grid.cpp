#include "Grid.h"
COLORREF Color[10] = { 0x66CDAA,0x0000CD,0x00BFFF,0x2F4F4F,0xFF3030
,0x00FF00 ,0xCD6839 ,0xEEAD0E ,0x8B7355, 0xFF1493 };
void Grid::setGrid(COLORREF col, int num)
{
	color = col;
	number = num;
}

COLORREF Grid::getColor()
{
	return color;
}

int Grid::getNumber()
{
	return number;
}

