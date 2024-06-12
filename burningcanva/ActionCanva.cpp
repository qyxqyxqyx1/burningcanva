#include "ActionCanva.h"
#include "Grid.h"
#include <fstream>
#include <string>
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <cstring>
//û�����Զ��忽��������vector����ʱ�����
//��дһ��vector���鷳����Ҫ�Զ����࣬�����Ⲣ���Ǳ���ģ� �ȸĳ�array�����а���˺���ɣ���ʱ���������vecotr
COLORREF basecolor[60] = {0,245,255,78,238,148,0,139,69,238,238,0,
238,173,14,255,106,106,255,127,0,255,20,147,255,187,255,0,0,128};//10����ɫ
//
ActionCanva::ActionCanva()
{
	this->totalburn = 0;
	set_inithinnum();//��ʼ����ʾ����
}

void ActionCanva::burn()
{
	int tmpsize = getSize();
	//ÿ�μ���ǰ���ȼ�¼�û���
	addtotalburn();
	copy_record(tmpsize, totalburn);//
	burning(tmpsize);
	//��¼�ļ��ȴ�����1;
	//tset:
}

void ActionCanva::leftrotate()//���������£�ִֻ�в�������չʾ
{
	int tmpsize = getSize();
	for (int i = 0; i < tmpsize; i++)//��
		for (int j = 0; j < tmpsize; j++)//��
			tmp[i][j] = gridArray[j][tmpsize -1- i];

	for (int i = 0; i < tmpsize; i++)
	{
		for (int j = 0; j < tmpsize; j++)
		{
			gridArray[i][j].setGrid(tmp[i][j].getColor(), tmp[i][j].getNumber());
		}
	}
}

void ActionCanva::rightrotate()//����
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

void ActionCanva::quash()//����
{
	int tmpsize = getSize();
	if (gettotalburn() > 0)//��ǰ���ȴ���>0�����ܳ������Ȳ���
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

void ActionCanva::draw()//��Ŀ�껭��
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
			settextstyle(15, 0, _T("����"));
			TCHAR snum[5];
			swprintf_s(snum, _T("%d"),gridArray[i][j].getNumber());//������ת��Ϊ�ַ�
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

Grid* ActionCanva::getactcanva(int x)//���������һ�е��׵�ַ
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


void ActionCanva::copy_record(int size,int total)//total:totalburn==1,��Ҫ������ԭ������¼��totalburn-1�Ķ�Ӧ���鵱�� 
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			previous[total-1][i][j].setGrid(gridArray[i][j].getColor(), gridArray[i][j].getNumber());//ȼ�յĵ�total�Σ�ȼ��ǰ�Ļ�����¼��total-1��λ��
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
			settextstyle(15, 0, _T("����"));
			TCHAR snum[5];
			swprintf_s(snum, _T("%d"), hint1[i][j].getNumber());//������ת��Ϊ�ַ�
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
			settextstyle(15, 0, _T("����"));
			TCHAR snum[5];
			swprintf_s(snum, _T("%d"), hint2[i][j].getNumber());//������ת��Ϊ�ַ�
			outtextxy(30 * j + 15 + 500, 30 * i + 15+400, snum);
		}
	}
}

void ActionCanva::showhintnumber()
{
	int l = getSize();
	settextstyle(15, 0, _T("����"));
	if (l == 4) outtextxy(1250, 130, hintnumber[0] + '0');//������ת��Ϊ�ַ�
	else if (l == 6)  outtextxy(1250, 130, hintnumber[1] + '0');
	else if(l==8)  outtextxy(1250, 130, hintnumber[2] + '0');
	else if(l==9)  outtextxy(1250, 130, hintnumber[3] + '0');
}

void ActionCanva::reparam()
{
	//���ò���1����ʾ����
	hintnumber[0] =9;
	hintnumber[1] = 2;
	hintnumber[2] = 3;
	hintnumber[3] = 5;

	//��ʾ��Ҫ������
	hide();
}

void ActionCanva::copyinit()
{
	for (int i = 0; i < getSize(); i++)
		for (int j = 0; j < getSize(); j++)
			previous[0][i][j].setGrid(gridArray[i][j].getColor(), gridArray[i][j].getNumber());
}

Grid* ActionCanva::randcreate_q()//���������Ŀ
{
	int x=-20;//���
	int l = getSize();
	std::fstream forans;//�����
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
	else forans << x << std::endl;//�������
	//1.���������Ŀ
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
				//bug:��ɫ������Ҫ����
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
			gridArray[i][j].setGrid(colo, n);//��Ŀ
		}
	}

	for (int i = 0; i < l; i++)
		for (int j = 0; j < l; j++)
			record[i][j].setGrid(gridArray[i][j].getColor(), gridArray[i][j].getNumber());

	//2.��Ŀ�ӹ��õ���
	while (!done())//ֻҪ�в�Ϊ1�ģ�˵������Ҫ����
	{
		//�����ɴ𰸵Ĺ���(������ʼ����)�����ļ�����
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
		burning(getSize());//��gridArray����burning
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
			forans << r << ' ' << g << ' ' << b << ' ' << gridArray[i][j].getNumber() << std::endl;//��Ҳ��һ��
		}
	}
	forans << '\n';
	forans.close();
	//������Ŀ�ɹ���Ĳ�������Ҫdebug
	Grid temp[12 * 12];//�洢���ɵ�Ŀ��
	for (int i = 0; i < l; i++)
	{
		for (int j = 0; j < l; j++)
			temp[i * l+j].setGrid(gridArray[i][j].getColor(),gridArray[i][j].getNumber());
	}

	//3.�����ɵ���Ŀд������������ļ�
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
	//debug:��ʾ������������Ҫdebug;
	//������������Ҫ����
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
	return temp;//����Ŀ�껭��
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
			//temp1��¼����Ϊ1��>1�ķ���
			//temp2��¼��Ҫ�����ǵķ���
			//temp2�У�0��ʾû�б�����
			if (gridArray[i][j].getNumber() == 1)
			{
				temp1[i][j].setGrid(gridArray[i][j].getColor(), 0);//temp1��¼����Ϊ1�ķ���
			}
			else if (gridArray[i][j].getNumber() > 1)
			{
				temp1[i][j].setGrid(gridArray[i][j].getColor(), 1);//temp1��¼����>1�ķ���(��������)
				if (i != tmpsize - 1)
				{
					temp2[i + 1][j].setGrid(gridArray[i][j].getColor(), gridArray[i][j].getNumber() - 1);
				}
			}
		}
	}
	//�ϲ�temp1��temp2����
	for (int i = 0; i < tmpsize; i++)
	{
		for (int j = 0; j < tmpsize; j++)
		{

			if (temp2[i][j].getNumber() != 0)//ԭ���ϲ㱻�ϲ㸲��
			{

				gridArray[i][j].setGrid(temp2[i][j].getColor(), temp2[i][j].getNumber());
			}
			else if (temp1[i][j].getNumber() == 0)
			{
				//ԭ���ϲ�Ϊ1��û�б��ϲ㸲�ǣ�do nothing
			   /*	gridArray[i][j].setGrid(gridArray[i][j].getColor(), 1);*/

			}
			else if (temp1[i][j].getNumber() == 1)
			{
				//ԭ���ϲ�>1��û�б��ϲ㸲�ǣ�
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
	int x = get_qnumber();//���
	int y = getSize();//��С
	std::ifstream myFile;
	//���ԣ���������ʹ��seekg��seekp��д�ļ�
	//Ŀ�껭��ʹ��write��read��д�ļ�
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
	settextstyle(15, 0, _T("����"));
	outtextxy(level * 2, level * 14, _T("������ʼ��Ϸ"));

	setbkmode(TRANSPARENT);
	setlinecolor(BLACK);
	putimage(500, 0, &i1);
	settextcolor(BLACK);
	settextstyle(15, 0, _T("����"));
	outtextxy(500 + level * 2, level * 14, _T("��ʾ1"));

	setbkmode(TRANSPARENT);
	setlinecolor(BLACK);
	putimage(500,400 , &i1);
	settextcolor(BLACK);
	settextstyle(15, 0, _T("����"));
	outtextxy(500 + level * 2, level * 14 + 400, _T("��ʾ2"));
}

void ActionCanva::checkhint()//չʾ��ʾ
{
	std::fstream abc("abc.txt",std::ios::app);
	int l = getSize();//������С
	int x = get_qnumber();//���
	for (int i = 0; i < 4; i++) if (hintnumber[i] == 0) return;//�������ʾΪ0 ��ֱ�ӷ���,���¶�����ִ��
	std::fstream openhint;//�򿪴�
	int hints;//��ʾĿǰ�ǵڶ��ٴ���ʾ
	if (l == 4) openhint.open("easyhint.txt"), hints =10-hintnumber[0];
	else if (l == 6) openhint.open("middlehint.txt"), hints = 3-hintnumber[1];
	else if (l == 8) openhint.open("hardhint.txt"), hints = 4-hintnumber[2];
	else if (l == 12) openhint.open("experthint.txt"), hints = 6-hintnumber[3];
	std::string line;
	int turn = 1;
	bool mark= 0;//����ҵ����������,0��ʾû�ҵ���1��ʾ�ҵ�
	bool forhint1 = 1, forhint2 = 0;
	int m = 0, n = 0;
	int crossline = 0;
	while (getline(openhint, line))
	{
		if (mark == 0)//û�ҵ����
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
					mark = 1;//�ҵ������
				}
			}
		}
		//3.
		else if (mark == 1 && turn == hints )//�ҵ���Ų����ҵ��ö�ȡ��ͼ
		{
			//�����߼�������debug
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
				else break;//������ȡ�ļ���ѭ��
			}
		}
		else if (mark == 1 && turn != hints)
		{
			if (crossline == turn * l * l * 2 + 2 * turn-1) turn++;
			else crossline++;
		}
		//����ʾ��Ϣ��turn,hints��д���ļ�����

	}
	openhint.close();
	reduce_hintnum(l);
}
