#include "Player.h"
#include <easyx.h>
#include <graphics.h>
#include <iomanip>
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <fstream>
#include <tchar.h>
#include <string>
IMAGE ava1;
IMAGE ava2;
IMAGE ava3;
IMAGE ava4;
bool cmp(const Player&a,const Player& b)
{
	//排名公式:score=5%*easywon+10%*middlewon+15%*hardwon+70%*expertwon;
	int score_a = 0.05 * a.woneasy + 0.1 * a.wonmiddle + 0.15 * a.wonhard + 0.7 * a.wonexpert;
	int score_b = 0.05 * b.woneasy + 0.15 * b.wonmiddle + 0.15 * b.wonhard + 0.7 * b.wonexpert;
	if (score_a>score_b) return score_a>score_b;
	//根据分数排序，然后这个积分不计入用户数据，而是计入了用户各难度玩的局数
	else if (a.total != b.total) return a.total < b.total;
	else return a.name < b.name;
}
std::string Player::get_name(){return this->name;}

int Player::get_id(){return this->id;}

int Player::get_ava(){return this->Avatar;}

void Player::change_name(std::string n){this->name = n;}

void Player::change_pwd(std::string n){this->password = n;}

void Player::add_woneasy(){woneasy++;}

void Player::add_wonmiddle(){wonmiddle++;}

void Player::add_wonhard(){wonhard++;}

void Player::add_wonexpert(){wonexpert++;}

void Player::add_tot(){total++;}

void::HashTable::makeEmpty()//初始hash数组为空
{
	currentSize = 0;
	for (auto& entry : hasharray)
	{
		entry.info = EMPTY;
	}
}

void Player::set_account(int idnow,std::string nametmp,std::string pwd,int ava, int woeasy,int womiddle,int wohard,int woexpert,int tot)
{
	this->id = idnow;
	this->name = nametmp;
	this->password = pwd;
	this->Avatar = ava;
	this->woneasy = woeasy;
	this->wonmiddle = womiddle;
	this->wonhard = wohard;
	this->wonexpert = woexpert;
	this->total = tot;
}

bool HashTable::contains(const Player& x)const
{
	return isActive(findPos(x));
}
size_t HashTable::myhash(const Player& tmp )const//hash函数
{
	size_t t = 0;
	for (int i = 0; i < tmp.name.size(); i++)
	{
		t = tmp.name[i] + 37 * t;
	}
	return t % hasharray.size();
}
size_t HashTable::findPos(const Player& tmp)const
{
	size_t offset = 1;//即函数f(i)
	size_t hashx = myhash(tmp);
	size_t currentPos = hashx;
	/*
	   考虑注册的用户
	   登录成功的用户
	   登录失败的用户
	*/
	while (hasharray[currentPos].info != EMPTY &&
		(hasharray[currentPos].player1.name != tmp.name||
		hasharray[currentPos].player1.password!=tmp.password))//插入新用户，查找用户，账号或者密码填错了，就会一直找，找到空位置，返回的也是empty
	{
		currentPos += offset;
		offset += 2;//平方消解函数
		if (currentPos >= currentSize) currentPos -= currentSize;
	}
	return currentPos;
}
bool HashTable::Insert(const Player& tmp)//插入新用户
{
	size_t insertPos = findPos(tmp);//找到一个空位
	if (isActive(insertPos)) return 0;
	hasharray[insertPos].info = ACTIVE;
	hasharray[insertPos].player1.set_account(tmp.id,tmp.name,tmp.password,tmp.Avatar,tmp.woneasy,tmp.wonmiddle,tmp.wonhard,tmp.wonexpert,tmp.total);
	add_currentsize();
	if (get_currentsize() >= get_arraysize() / 2)  rehash();
}
bool HashTable::Delete(const Player& tmp)//删除用户
{
	if (contains(tmp))
	{
		size_t deletePos = findPos(tmp);
		hasharray[deletePos].info = DELETED;
		reduce_currentsize();
		return 1;
	}
	else return 0;
}//不用hashtable,不要把数据存储到文件当中?
//以二进制形式读写文件
bool HashTable::Change_name(std::string n,Player tmp)//更改用户名
{
	if (contains(tmp))
	{
		size_t t = findPos(tmp);
		hasharray[t].player1.change_name(n);
		return 1;
	}
	return 0;
}

bool HashTable::Change_pwd(std::string n, Player tmp)
{
	if (contains(tmp))
	{
		size_t t=findPos(tmp);
		hasharray[t].player1.change_pwd(n);
		return 1;
	}
	return 0;
}

Player HashTable::get_nowplayerinfo(Player& x)//查找玩家并返回信息，用于统计游戏输赢的局数,所以一定能找到该玩家
{

	if (contains(x))
	{
	 int nowpos = findPos(x);
	  return hasharray[nowpos].player1;
	}
}

bool HashTable::isActive(size_t pos)const
{
	if (hasharray[pos].info == ACTIVE) return 1;
	else return 0;
}
size_t HashTable::get_currentsize()
{
	return this->currentSize;
}
void HashTable::update()
{
	std::fstream updateacc("account.txt", std::ios::out);
	for (int i = 0; i < get_arraysize(); i++)
	{
		if (hasharray[i].info == ACTIVE)
		{
			updateacc << hasharray[i].player1.id << ' '
				<< hasharray[i].player1.get_name() << ' '
				<< hasharray[i].player1.password << ' '
				<<hasharray[i].player1.Avatar<<' '
				<< hasharray[i].player1.woneasy << ' '
				<<hasharray[i].player1.wonmiddle<<' '
				<<hasharray[i].player1.wonhard<<' '
				<<hasharray[i].player1.wonexpert<<' '
				<< hasharray[i].player1.total << std::endl;
		}
	}
	updateacc.close();
}
void HashTable::forrank()
{
	loadimage(&ava1, _T("avatar1.jpg"), 49, 49);
	loadimage(&ava2, _T("avatar2.jpg"), 49, 49);
	loadimage(&ava3, _T("avatar3.jpg"), 49, 49);
	loadimage(&ava4, _T("avatar4.jpg"), 49, 49);
	Player tmp[100];//只显示前100名用户的成绩
	int k = 0;
	for (int i = 0; i < hasharray.size(); i++)
	{
		if (hasharray[i].info == ACTIVE)
		{
			tmp[k].set_account(hasharray[i].player1.get_id(), hasharray[i].player1.get_name(),
				hasharray[i].player1.password,hasharray[i].player1.Avatar,
				hasharray[i].player1.woneasy,hasharray[i].player1.wonmiddle,hasharray[i].player1.wonhard,
				hasharray[i].player1.wonexpert,hasharray[i].player1.total);
			k++;
		}
	}
	//绘制表头
	std::sort(tmp + 0, tmp + k, cmp);
	int left = 300, len = 100;
	setlinecolor(BLACK);
	for (int i = 0; i < 9; i++)
		line(235 + i * 100, 100, 235 + i * 100, 150 + k * 50);//列宽100
	for (int i = 0; i <= k + 1; i++)
		line(235, 100 + i * 50, 235 + 8 * 100, 100 + i * 50);//行宽50
	outtextxy(240, 125, _T("ID")),outtextxy(350, 125, _T("Avatar")),outtextxy(450, 125, _T("Name")),
	outtextxy(550, 125, _T("Easy")), outtextxy(650, 125, _T("Middle")), outtextxy(750, 125, _T("Hard")), outtextxy(850, 125, _T("Expert")),
	outtextxy(950,125, _T("Total"));
	//进行数据类型转换处理并输出
	wchar_t* outname = NULL;
	for (int i = 0; i < k; i++)//前k名用户的成绩
	{
		//用户id,用户名，用户赢得局数，用户玩了的总局数
		//此处后续可以更改排名公式，综合处理，各个模式占比不同
		//1 id类型转换
		int id = tmp[i].id;
		TCHAR snum1[5];
		swprintf_s(snum1, _T("%d"), id);

		//2 name类型转换
		std::string name = tmp[i].get_name();
		size_t size = name.length();
		outname = new wchar_t[size + 1];
		MultiByteToWideChar(CP_ACP, 0, name.c_str(), size+1, outname, size * sizeof(wchar_t)+1);

		//3. 赢得简单局数类型转换
		int woneasy = tmp[i].woneasy;
		TCHAR snum2[5];
		swprintf_s(snum2, _T("%d"), woneasy);

		//4.赢得中等局数类型转换
		int wonmiddle = tmp[i].wonmiddle;
		TCHAR snum3[5];
		swprintf_s(snum3, _T("%d"), wonmiddle);

		//5.赢得困难局数类型转换
		int wonhard = tmp[i].wonhard;
		TCHAR snum4[5];
		swprintf_s(snum4, _T("%d"), wonhard);

		//6.赢得专家局数类型转换
		int wonexpert = tmp[i].wonexpert;
		TCHAR snum5[5];
		swprintf_s(snum5, _T("%d"), wonexpert);

		//7.玩了的总局数类型转换
		int tot = tmp[i].total;
		TCHAR snum6[5];
		swprintf_s(snum6, _T("%d"), tot);
		outtextxy(290, 175 + i * 50, snum1);//id
		outtextxy(450, 175 + i * 50, outname);//name
		std::fstream chech("check.txt", std::ios::app);
		chech << tmp[i].Avatar << std::endl;
		if (tmp[i].Avatar == 1) putimage(351, 151 + i * 50, &ava1);
		else if (tmp[i].Avatar == 2)putimage(351, 151 + i * 50, &ava2);
		else if (tmp[i].Avatar == 3)putimage(351, 151+ i * 50, &ava3);
		else if (tmp[i].Avatar == 4)putimage(351, 151 + i * 50, &ava4);
		setbkmode(TRANSPARENT);
		outtextxy(540, 175 + i * 50, snum2);//easy
		outtextxy(640, 175 + i * 50, snum3);//middle
		outtextxy(740, 175 + i * 50, snum4);//hard
		outtextxy(840, 175 + i * 50, snum5);//expert
		outtextxy(940, 175 + i * 50, snum6);//total
	}
	delete[] outname;
}

void HashTable::add_won(int level,Player& x)
{
	int nowpos = findPos(x);//根据用户名和密码找到该用户
	if (level == 4) hasharray[nowpos].player1.add_woneasy();
	else if (level == 6) hasharray[nowpos].player1.add_wonmiddle();
	else if (level == 8) hasharray[nowpos].player1.add_wonhard();
	else if (level == 12) hasharray[nowpos].player1.add_wonexpert();
}


void HashTable::add_total(Player& x)
{
	int nowpos = findPos(x);
	hasharray[nowpos].player1.add_tot();
}
void HashTable::add_currentsize()
{
	currentSize = currentSize + 1;
}
void HashTable::reduce_currentsize()
{
	currentSize = currentSize - 1;
}
size_t HashTable::get_arraysize()
{
	return hasharray.size();
}
void HashTable::rehash()
{
	std::vector<HashEntry>oldarray = hasharray;
	hasharray.resize(nextPrime(get_arraysize()));
	for (auto& entry : oldarray)
	{
		if (entry.info == ACTIVE)
		{
			Insert(std::move(entry.player1));
		}
	}
}
size_t HashTable::nextPrime(size_t tmp)
{
	if (tmp % 2 == 0) tmp++;
	return tmp;
}