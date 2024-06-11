#include "TargetCanva.h"
#include "Grid.h"
#include <random>
#include <stdexcept>
#include <cstring>
#include <string>
#include <sstream>
#include "HiEasyX.h"

TargetCanva::TargetCanva()
{
}
void TargetCanva::draw()//画目标画布,Tar
{
	setbkmode(TRANSPARENT);
	setlinecolor(BLACK);
	for (int i = 0; i <get_size(); i++)
	{
		for (int j = 0; j <get_size(); j++)
		{
			setfillcolor(Tar[i][j].getColor());
			fillrectangle(j * 30, (i + 1) * 30+400, (j + 1) * 30, i * 30+400);
			settextcolor(BLACK);
		}
	}
}

int TargetCanva::get_Qustionnumber()
{
	return this->Questionnumber;
}

Grid* TargetCanva::gettarcanva(int x)
{
	return Tar[x];
}

void TargetCanva::set_size(int s)
{
	this->size = s;

}

int TargetCanva::get_size()
{
	return this->size;
}
void TargetCanva::get_q(Grid* temp)
{
	int k = 0, s = 0;
	for (int i = 0; i < get_size() * get_size(); i++)
	{
		k++;
		if (k == get_size() - 1) k = 0, s++;
		Tar[s][k].setGrid(temp[i].getColor(), temp[i].getNumber());
	}
}


void TargetCanva::receive_canva(Grid* temp)
{
	int l = get_size();
	int m=0, n = 0;
	for (int i = 0; i < l * l; i++)
	{
		Tar[m][n].setGrid(temp[i].getColor(), temp[i].getNumber());
		if (n == l - 1) n = 0, m++;
		else n++;
	}
	//在这里将生成的题目存到文件当中
	std::ofstream myFile;
	if (l == 4) myFile.open("easyQuestionbank.txt", std::ios::app);
	else if (l == 6) myFile.open("middleQuestionbank.txt", std::ios::app);
	else if (l == 8) myFile.open("hardQuestionbank.txt", std::ios::app);
	else if (l == 12) myFile.open("expertQuestionbank.txt", std::ios::app);
	int x = Questionnumber;
	myFile.seekp(x * l * l + x, std::ios::beg);
	for (int i = 0; i < l; i++)
	{
		for (int j = 0; j < l; j++)
		{
			//将colorRRef转化成int类型
			BYTE R = GetRValue(Tar[i][j].getColor());
			BYTE G = GetGValue(Tar[i][j].getColor());
			BYTE B = GetBValue(Tar[i][j].getColor());
			
			int r = static_cast<int>(R);
			int g = static_cast<int>(G);
			int b = static_cast<int>(B);

			myFile << r << ' ' << g << ' ' << ' ' << b <<std::endl;
		}
	}
	myFile << '\n';
	myFile.close();
}


void TargetCanva::generate_canva()
{
	int x = get_Qustionnumber();//题号
	int y = get_size();//大小
	std::ifstream myFile;
	//目标画布使用write和read读写文件:必须要以二进制写入
	if (y == 4) myFile.open("easyQuestionbank.txt", std::ios::in);
	else if (y == 6) myFile.open("middleQuestionbank.txt", std::ios::in);
	else if (y == 8) myFile.open("hardQuestionbank.txt", std::ios::in);
	else if (y == 12) myFile.open("expertQuestionbank.txt", std::ios::in);
	if (!myFile)
	{
		std::cerr << "File could not be opend" << std::endl;
		exit(EXIT_FAILURE);
	}	std::string line;
	int i = 0, j = 0;
	int k = 0;
	while (getline(myFile, line))
	{
		if (k >= x * y * y + x && k < (x + 1) * y * y + x)
		{
			int space1 = 0, space2 = 0, space3 = 0;
			for (int i = 0; i < line.size(); i++)
			{
				if (line[i] == ' ')
				{
					if (space1 == 0) space1 = i;
					else if (space2 == 0)space2 = i;
					else space3 = i;
				}
			}
			std::string sub1, sub2, sub3, sub4;
			sub1 = line.substr(0, space1 - 0);
			sub2 = line.substr(space1 + 1, space2 - space1 - 1);
			sub3 = line.substr(space2 + 1, space3 - space2 - 1);
			sub4 = line.substr(space3 + 1, line.size() - space3 - 1);
			int r = std::stoi(sub1);
			int g = std::stoi(sub2);
			int b = std::stoi(sub3);
			int numtmp = std::stoi(sub4);
			COLORREF colo = RGB(r, g, b);
			Tar[i][j].setGrid(colo, numtmp);
			if (j != get_size() - 1) j++;
			else j = 0, i++;
		}
		else if (k < x * y * y + x) k++;
		else break;
	}
}

void TargetCanva::set_Questionnumber(int q)
{
	this->Questionnumber = q;
}