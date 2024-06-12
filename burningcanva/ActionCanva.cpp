#include "ActionCanva.h"
#include "Grid.h"
#include <fstream>
#include <string>
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <cstring>
//没有用自定义拷贝函数，vector运行时会崩溃
//再写一个vector好麻烦，还要自定义类，况且这并不是必须的， 先改成array把排行榜和账号完成，有时间再做这个vecotr
COLORREF basecolor[60] = {0,245,255,78,238,148,0,139,69,238,238,0,
238,173,14,255,106,106,255,127,0,255,20,147,255,187,255,0,0,128};//10种颜色
//
ActionCanva::ActionCanva()
{
	this->totalburn = 0;
	set_inithinnum();//初始化提示次数
}

void ActionCanva::burn()
{
	int tmpsize = getSize();
	//每次加热前，先记录好画布
	addtotalburn();
	copy_record(tmpsize, totalburn);//
	burning(tmpsize);
	//记录的加热次数加1;
	//tset:
}

void ActionCanva::leftrotate()//左旋，更新：只执行操作，不展示
{
	int tmpsize = getSize();
	for (int i = 0; i < tmpsize; i++)//列
		for (int j = 0; j < tmpsize; j++)//行
			tmp[i][j] = gridArray[j][tmpsize -1- i];

	for (int i = 0; i < tmpsize; i++)
	{
		for (int j = 0; j < tmpsize; j++)
		{
			gridArray[i][j].setGrid(tmp[i][j].getColor(), tmp[i][j].getNumber());
		}
	}
}

void ActionCanva::rightrotate()//右旋
{
	int tmpsize = getSize();
	for (int i = 0; i < tmpsize; i++)
		for (int j = 0; j < tmpsize; j++)
			tmp[i][j] = gridArray[tmpsize -1- j][i];
			/*tmp[2-i][j] = gridArray[i][j];*/

	for (int i = 0; i < tmpsize; i++)
	{
		for (int j = 0; j < tmpsize; j++)
		{
			gridArray[i][j].setGrid(tmp[i][j].getColor(), tmp[i][j].getNumber());
		}
	}
}

void ActionCanva::quash()//撤销
{
	int tmpsize = getSize();
	if (gettotalburn() > 0)//当前加热次数>0，才能撤销加热操作
	{
		for (int i = 0; i < tmpsize; i++)
		{
			for (int j = 0; j < tmpsize; j++)
			{
				gridArray[i][j].setGrid((previous[gettotalburn() - 1])[i][j].getColor(), (previous[gettotalburn() - 1])[i][j].getNumber());
			}
		}
		removetotal();
	}
}

void ActionCanva::draw()//画目标画布
{
	int tmpsize = size;
	setbkmode(TRANSPARENT);
	setlinecolor(BLACK);
	for (int i = 0; i < tmpsize; i++)
	{
		for (int j = 0; j < tmpsize; j++)
		{
			setfillcolor(gridArray[i][j].getColor());
			fillrectangle(j * 30, (i + 1) * 30, (j + 1) * 30, i * 30);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("宋体"));
			TCHAR snum[5];
			swprintf_s(snum, _T("%d"),gridArray[i][j].getNumber());//将数字转化为字符
			outtextxy(30 * j + 15, 30 * i + 15, snum);
		}
	}
}

int ActionCanva::getSize()
{
	return this->size;
}

void ActionCanva::setSize(int s)
{
	this->size = s;
}

int ActionCanva::gettotalburn()
{
	return this->totalburn;
}

void ActionCanva::addtotalburn()
{
	int tmp = gettotalburn();
	this->totalburn = tmp + 1;
}

void ActionCanva::removetotal()
{
	if (gettotalburn() > 0)
	{
		int tmp = gettotalburn();
		this->totalburn = tmp - 1;
	}
}

void ActionCanva::cleartotalburn()
{
    this->totalburn = 0;
}

Grid* ActionCanva::getactcanva(int x)//返回数组第一行的首地址
{
	return gridArray[x];
}

void ActionCanva::reset(int size,int questionnumber)
{
    int n = questionnumber;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			gridArray[i][j].setGrid(previous[0][i][j].getColor(), previous[0][i][j].getNumber());
		}
	}
	totalburn = 0;
}


void ActionCanva::copy_record(int size,int total)//total:totalburn==1,若要撤销到原来，记录在totalburn-1的对应数组当中 
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			previous[total-1][i][j].setGrid(gridArray[i][j].getColor(), gridArray[i][j].getNumber());//燃烧的第total次，燃烧前的画布记录到total-1的位置
}

void ActionCanva::set_inithinnum()
{
	hintnumber[0] = 2, hintnumber[1] = 3,
	hintnumber[2] = 4, hintnumber[3] = 5;
}

void ActionCanva::user_create()
{

}

void ActionCanva::reduce_hintnum(int level)
{
	if (level == 4) hintnumber[0]--;
	else if (level == 6) hintnumber[1]--;
	else if (level == 8) hintnumber[2]--;
	else if (level == 12) hintnumber[3]--;
}

void ActionCanva::showhints()
{
	int tmpsize = size;
	setbkmode(TRANSPARENT);
	setlinecolor(BLACK);
	for (int i = 0; i < tmpsize; i++)
	{
		for (int j = 0; j < tmpsize; j++)
		{
			setfillcolor(hint1[i][j].getColor());
			fillrectangle(j * 30+500, (i + 1) * 30, (j + 1) * 30+500, i * 30);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("宋体"));
			TCHAR snum[5];
			swprintf_s(snum, _T("%d"), hint1[i][j].getNumber());//将数字转化为字符
			outtextxy(30 * j + 15+500, 30 * i + 15, snum);
		}
	}

	for (int i = 0; i < tmpsize; i++)
	{
		for (int j = 0; j < tmpsize; j++)
		{
			setfillcolor(hint2[i][j].getColor());
			fillrectangle(j * 30 + 500, (i + 1) * 30+400, (j + 1) * 30 + 500, i * 30+400);
			settextcolor(BLACK);
			settextstyle(15, 0, _T("宋体"));
			TCHAR snum[5];
			swprintf_s(snum, _T("%d"), hint2[i][j].getNumber());//将数字转化为字符
			outtextxy(30 * j + 15 + 500, 30 * i + 15+400, snum);
		}
	}
}

void ActionCanva::showhintnumber()
{
	int l = getSize();
	settextstyle(15, 0, _T("宋体"));
	if (l == 4) outtextxy(1250, 130, hintnumber[0] + '0');//将数字转化为字符
	else if (l == 6)  outtextxy(1250, 130, hintnumber[1] + '0');
	else if(l==8)  outtextxy(1250, 130, hintnumber[2] + '0');
	else if(l==9)  outtextxy(1250, 130, hintnumber[3] + '0');
}

void ActionCanva::reparam()
{
	//重置参数1：提示次数
	hintnumber[0] =9;
	hintnumber[1] = 2;
	hintnumber[2] = 3;
	hintnumber[3] = 5;

	//提示需要被隐藏
	hide();
}

void ActionCanva::copyinit()
{
	for (int i = 0; i < getSize(); i++)
		for (int j = 0; j < getSize(); j++)
			previous[0][i][j].setGrid(gridArray[i][j].getColor(), gridArray[i][j].getNumber());
}

Grid* ActionCanva::randcreate_q()//随机生成题目
{
	int x=-20;//题号
	int l = getSize();
	std::fstream forans;//存答案用
	if (l == 4) x = qnumber, forans.open("easyhint.txt",std::ios::app);
	else if (l == 6) x = qnumber, forans.open("middlehint.txt",std::ios::app);
	else if (l == 8) x = qnumber, forans.open("middlehint.txt",std::ios::app);
	else if (l == 12) x = qnumber, forans.open("experthint.txt",std::ios::app);
	if (!forans)
	{
		std::cerr << "File could not be opened" << std::endl;
		exit(EXIT_FAILURE);
	}
	if (x == -20)
	{
		forans << 2 << std::endl;
	}
	else forans << x << std::endl;//存入题号
	//1.随机生成题目
	srand((unsigned)time(NULL));
	int r, n;
	for (int i = 0; i < l; i++)
	{
		for (int j = 0; j < l; j++)
		{
			if (l == 4)
			{
				 r = rand() % 10;
				 n = rand() % 8 + 1;
			}
			else if (l == 6)
			{
				//bug:颜色数量需要增加
				 r = rand() % 10;
				 n = rand() % 10 + 1;
			}
			else if (l == 8)
			{
				 r = rand() % 10;
				 n = rand() % 13 + 1;
			}
			else if (l==12)
			{
				 r = rand() % 10;
				 n = rand() % 20 + 1;
			}
			COLORREF colo =RGB(basecolor[r*3], basecolor[r*3+1], basecolor[r*3+2]);
			gridArray[i][j].setGrid(colo, n);//题目
		}
	}

	for (int i = 0; i < l; i++)
		for (int j = 0; j < l; j++)
			record[i][j].setGrid(gridArray[i][j].getColor(), gridArray[i][j].getNumber());

	//2.题目加工得到答案
	while (!done())//只要有不为1的，说明还需要加热
	{
		//将生成答案的过程(包括初始画布)存入文件当中
		for (int i = 0; i < l; i++)
		{
			for (int j = 0; j < l; j++)
			{
				BYTE R = GetRValue(gridArray[i][j].getColor());
				BYTE G = GetGValue(gridArray[i][j].getColor());
				BYTE B = GetBValue(gridArray[i][j].getColor());
				int r = static_cast<int>(R);
				int g = static_cast<int>(G);
				int b = static_cast<int>(B);
				forans << r << ' ' << g << ' ' << b << ' ' << gridArray[i][j].getNumber() << std::endl;
			}
		}
		forans << '\n';
		int rnum = rand() % 3;
		for (int i = 0; i < rnum; i++)
			leftrotate();//
		burning(getSize());//对gridArray数组burning
	}
	for (int i = 0; i < l; i++)
	{
		for (int j = 0; j < l; j++)
		{
			BYTE R = GetRValue(gridArray[i][j].getColor());
			BYTE G = GetGValue(gridArray[i][j].getColor());
			BYTE B = GetBValue(gridArray[i][j].getColor());
			int r = static_cast<int>(R);
			int g = static_cast<int>(G);
			int b = static_cast<int>(B);
			forans << r << ' ' << g << ' ' << b << ' ' << gridArray[i][j].getNumber() << std::endl;//答案也存一下
		}
	}
	forans << '\n';
	forans.close();
	//生成题目成功后的操作仍需要debug
	Grid temp[12 * 12];//存储生成的目标
	for (int i = 0; i < l; i++)
	{
		for (int j = 0; j < l; j++)
			temp[i * l+j].setGrid(gridArray[i][j].getColor(),gridArray[i][j].getNumber());
	}

	//3.将生成的题目写入操作画布和文件
	for (int i = 0; i < l; i++)
		for (int j = 0; j < l; j++)
			gridArray[i][j].setGrid(record[i][j].getColor(), record[i][j].getNumber());

	std::fstream myFile;
	if (size == 4) myFile.open("easyactmode.txt", std::ios::app);
	else if (size == 6) myFile.open("middleactmode.txt", std::ios::app);
	else if (size == 8) myFile.open("hardactmode.txt", std::ios::app);
	else if (size == 12) myFile.open("expertactmode.txt", std::ios::app);
	if (!myFile)
	{
		std::cerr << "File could not be opend" << std::endl;
		exit(EXIT_FAILURE);
	}
	std::string line;
	int mark = 0;
	//debug:提示哪那里的题号需要debug;
	//输入框的问题需要改善
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			BYTE R = GetRValue(gridArray[i][j].getColor());
			BYTE G = GetGValue(gridArray[i][j].getColor());
			BYTE B = GetBValue(gridArray[i][j].getColor());
			int r = static_cast<int>(R);
			int g = static_cast<int>(G);
			int b = static_cast<int>(B);
			int numtmp = gridArray[i][j].getNumber();
			myFile << r << ' ' << g << ' ' << b <<' '<<numtmp << std::endl;
		}
	}
	myFile << '\n';
	myFile.close();
	return temp;//返回目标画布
}

void ActionCanva::burning(int tmpsize)
{

	for (int i = 0; i < tmpsize; i++)
	{
		for (int j = 0; j < tmpsize; j++)
		{
			temp2[i][j].setGrid(gridArray[i][j].getColor(), 0);
		}
	}
	for (int i = 0; i < tmpsize; i++)
	{
		for (int j = 0; j < tmpsize; j++)
		{
			//temp1记录数字为1和>1的方格
			//temp2记录需要被覆盖的方格
			//temp2中，0表示没有被覆盖
			if (gridArray[i][j].getNumber() == 1)
			{
				temp1[i][j].setGrid(gridArray[i][j].getColor(), 0);//temp1记录数字为1的方格
			}
			else if (gridArray[i][j].getNumber() > 1)
			{
				temp1[i][j].setGrid(gridArray[i][j].getColor(), 1);//temp1记录数字>1的方格(被加热了)
				if (i != tmpsize - 1)
				{
					temp2[i + 1][j].setGrid(gridArray[i][j].getColor(), gridArray[i][j].getNumber() - 1);
				}
			}
		}
	}
	//合并temp1和temp2数组
	for (int i = 0; i < tmpsize; i++)
	{
		for (int j = 0; j < tmpsize; j++)
		{

			if (temp2[i][j].getNumber() != 0)//原颜料层被上层覆盖
			{

				gridArray[i][j].setGrid(temp2[i][j].getColor(), temp2[i][j].getNumber());
			}
			else if (temp1[i][j].getNumber() == 0)
			{
				//原颜料层为1且没有被上层覆盖：do nothing
			   /*	gridArray[i][j].setGrid(gridArray[i][j].getColor(), 1);*/

			}
			else if (temp1[i][j].getNumber() == 1)
			{
				//原颜料层>1且没有被上层覆盖：
				gridArray[i][j].setGrid(temp1[i][j].getColor(), 1);
			}
		}
	}
}

bool ActionCanva::done()
{
	for (int i = 0; i < getSize(); i++)
		for (int j = 0; j < getSize(); j++)
			if (gridArray[i][j].getNumber() != 1)return 0;
	return 1;
}

void ActionCanva::set_qnumber(int x)  {this->qnumber = x;}

int ActionCanva::get_qnumber() { return this->qnumber; }

void ActionCanva::generate_canva()
{
	int x = get_qnumber();//题号
	int y = getSize();//大小
	std::ifstream myFile;
	//尝试：操作画布使用seekg和seekp读写文件
	//目标画布使用write和read读写文件
	if (y == 4) myFile.open("easyactmode.txt", std::ios::in);
	else if (y == 6) myFile.open("middleactmode.txt", std::ios::in);
	else if (y == 8) myFile.open("hardactmode.txt", std::ios::in);
	else if (y == 12) myFile.open("expertactmode.txt", std::ios::in);
	if (!myFile)
	{
		std::cerr << "File could not be opend" << std::endl;
		exit(EXIT_FAILURE);
	}
	std::string line;
	int k = 0;
	int i = 0, j = 0;
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
			gridArray[i][j].setGrid(colo, numtmp);
			if (j != getSize() - 1) j++;
			else j = 0, i++;
			k++;

		}
		else if (k < x * y * y + x) k++;
		else
		{
			break;
		}
	}
}

void ActionCanva::hide()
{
	IMAGE i1;
	IMAGE i2;
	int level = getSize();
	setbkmode(TRANSPARENT);
	setlinecolor(BLACK);
	loadimage(&i1, _T("111.jpg"), level * 30, level * 30);
	loadimage(&i2, _T("222.jpg"), level * 30, level * 30);
	putimage(0, 0, &i2);
	settextcolor(BLACK);
	settextstyle(15, 0, _T("宋体"));
	outtextxy(level * 2, level * 14, _T("请点击开始游戏"));

	setbkmode(TRANSPARENT);
	setlinecolor(BLACK);
	putimage(500, 0, &i1);
	settextcolor(BLACK);
	settextstyle(15, 0, _T("宋体"));
	outtextxy(500 + level * 2, level * 14, _T("提示1"));

	setbkmode(TRANSPARENT);
	setlinecolor(BLACK);
	putimage(500,400 , &i1);
	settextcolor(BLACK);
	settextstyle(15, 0, _T("宋体"));
	outtextxy(500 + level * 2, level * 14 + 400, _T("提示2"));
}

void ActionCanva::checkhint()//展示提示
{
	std::fstream abc("abc.txt",std::ios::app);
	int l = getSize();//画布大小
	int x = get_qnumber();//题号
	for (int i = 0; i < 4; i++) if (hintnumber[i] == 0) return;//如果有提示为0 ，直接返回,以下都不会执行
	std::fstream openhint;//打开答案
	int hints;//表示目前是第多少次提示
	if (l == 4) openhint.open("easyhint.txt"), hints =10-hintnumber[0];
	else if (l == 6) openhint.open("middlehint.txt"), hints = 3-hintnumber[1];
	else if (l == 8) openhint.open("hardhint.txt"), hints = 4-hintnumber[2];
	else if (l == 12) openhint.open("experthint.txt"), hints = 6-hintnumber[3];
	std::string line;
	int turn = 1;
	bool mark= 0;//标记找到题号所在行,0表示没找到，1表示找到
	bool forhint1 = 1, forhint2 = 0;
	int m = 0, n = 0;
	int crossline = 0;
	while (getline(openhint, line))
	{
		if (mark == 0)//没找到题号
		{
			int check = 1;
			if (line.empty()) check = 0;
			else 
			{
				for (int i = 0; i < line.size(); i++)
				{
					if (line[i] == ' ')
					{
						check = 0;
						break;
					}
				}
			}
			if (check == 1)
			{
				int qtmp = std::stoi(line);
				if (qtmp == x)
				{
					mark = 1;//找到该题号
				}
			}
		}
		//3.
		else if (mark == 1 && turn == hints )//找到题号并且找到该读取的图
		{
			//代码逻辑可以再debug
			if (line.empty() || line == "\n")
			{
				abc << '\n' << std::endl;
				continue;
			}
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
			abc << r << ' ' << g << ' ' << b << ' ' << numtmp << std::endl;
			COLORREF colo = RGB(r, g, b);
			if (forhint1)
			{
				hint1[m][n].setGrid(colo, numtmp), n++;
                
			}
			if (forhint2)
			{
				hint2[m][n].setGrid(colo, numtmp), n++;
			}

			if (m<l-1 && n == l) n = 0, m++;
			if (m == l - 1 && n==l)
			{
				if (forhint2 == 0)forhint1 = 0, forhint2 = 1, m = 0, n = 0;
				else break;//结束读取文件的循环
			}
		}
		else if (mark == 1 && turn != hints)
		{
			if (crossline == turn * l * l * 2 + 2 * turn-1) turn++;
			else crossline++;
		}
		//将提示信息，turn,hints都写到文件当中

	}
	openhint.close();
	reduce_hintnum(l);
}
