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
	int  get_Qustionnumber();//�õ���ȡ�����
	Grid* gettarcanva(int x);//���ںͲ��������Ƚ�
	void set_size(int s);
	int get_size();
	void get_q(Grid* temp);//���������������Ŀ
	void generate_canva();
	void receive_canva(Grid* temp);
	void set_Questionnumber(int q);
private:
	int Questionnumber;//���
	Grid Tar[12][12];//Ŀ�껭��
	int size;//Ŀ�껭����С
//ÿ����������е���Ŀ������Ҫ�ǣ�ֻ��¼��ǰ��Ŀ����ż���(д�����)
};

