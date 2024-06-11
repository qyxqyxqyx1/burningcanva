#pragma once
#include <easyx.h>
#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include "Grid.h"
#include <array>
#include <fstream>
#include <ctime>
#include <vector>
class TargetCanva
{
public:
	TargetCanva();
	void draw();
	int  get_Qustionnumber();//得到抽取的题号
	Grid* gettarcanva(int x);//用于和操作画布比较
	void set_size(int s);
	int get_size();
	void get_q(Grid* temp);//接收随机产生的题目
	void generate_canva();
	void receive_canva(Grid* temp);
	void set_Questionnumber(int q);
private:
	int Questionnumber;//题号
	Grid Tar[12][12];//目标画布
	int size;//目标画布大小
//每个画布题库中的题目数量不要记，只记录当前题目的题号即可(写入答案用)
};

