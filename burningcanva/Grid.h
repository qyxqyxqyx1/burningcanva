#pragma once
#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <easyx.h>
#include <iostream>
extern COLORREF Color[10];
struct Grid
{
private:
	COLORREF color;
	int number;
public:
	void setGrid(COLORREF col,int num);
	COLORREF getColor();
	int getNumber();
};

