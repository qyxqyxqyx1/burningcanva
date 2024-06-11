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
	//������ʽ:score=5%*easywon+10%*middlewon+15%*hardwon+70%*expertwon;
	int score_a = 0.05 * a.woneasy + 0.1 * a.wonmiddle + 0.15 * a.wonhard + 0.7 * a.wonexpert;
	int score_b = 0.05 * b.woneasy + 0.15 * b.wonmiddle + 0.15 * b.wonhard + 0.7 * b.wonexpert;
	if (score_a>score_b) return score_a>score_b;
	//���ݷ�������Ȼ��������ֲ������û����ݣ����Ǽ������û����Ѷ���ľ���
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

void::HashTable::makeEmpty()//��ʼhash����Ϊ��
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
size_t HashTable::myhash(const Player& tmp )const//hash����
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
	size_t offset = 1;//������f(i)
	size_t hashx = myhash(tmp);
	size_t currentPos = hashx;
	/*
	   ����ע����û�
	   ��¼�ɹ����û�
	   ��¼ʧ�ܵ��û�
	*/
	while (hasharray[currentPos].info != EMPTY &&
		(hasharray[currentPos].player1.name != tmp.name||
		hasharray[currentPos].player1.password!=tmp.password))//�������û��������û����˺Ż�����������ˣ��ͻ�һֱ�ң��ҵ���λ�ã����ص�Ҳ��empty
	{
		currentPos += offset;
		offset += 2;//ƽ�����⺯��
		if (currentPos >= currentSize) currentPos -= currentSize;
	}
	return currentPos;
}
bool HashTable::Insert(const Player& tmp)//�������û�
{
	size_t insertPos = findPos(tmp);//�ҵ�һ����λ
	if (isActive(insertPos)) return 0;
	hasharray[insertPos].info = ACTIVE;
	hasharray[insertPos].player1.set_account(tmp.id,tmp.name,tmp.password,tmp.Avatar,tmp.woneasy,tmp.wonmiddle,tmp.wonhard,tmp.wonexpert,tmp.total);
	add_currentsize();
	if (get_currentsize() >= get_arraysize() / 2)  rehash();
}
bool HashTable::Delete(const Player& tmp)//ɾ���û�
{
	if (contains(tmp))
	{
		size_t deletePos = findPos(tmp);
		hasharray[deletePos].info = DELETED;
		reduce_currentsize();
		return 1;
	}
	else return 0;
}//����hashtable,��Ҫ�����ݴ洢���ļ�����?
//�Զ�������ʽ��д�ļ�
bool HashTable::Change_name(std::string n,Player tmp)//�����û���
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

Player HashTable::get_nowplayerinfo(Player& x)//������Ҳ�������Ϣ������ͳ����Ϸ��Ӯ�ľ���,����һ�����ҵ������
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
	Player tmp[100];//ֻ��ʾǰ100���û��ĳɼ�
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
	//���Ʊ�ͷ
	std::sort(tmp + 0, tmp + k, cmp);
	int left = 300, len = 100;
	setlinecolor(BLACK);
	for (int i = 0; i < 9; i++)
		line(235 + i * 100, 100, 235 + i * 100, 150 + k * 50);//�п�100
	for (int i = 0; i <= k + 1; i++)
		line(235, 100 + i * 50, 235 + 8 * 100, 100 + i * 50);//�п�50
	outtextxy(240, 125, _T("ID")),outtextxy(350, 125, _T("Avatar")),outtextxy(450, 125, _T("Name")),
	outtextxy(550, 125, _T("Easy")), outtextxy(650, 125, _T("Middle")), outtextxy(750, 125, _T("Hard")), outtextxy(850, 125, _T("Expert")),
	outtextxy(950,125, _T("Total"));
	//������������ת���������
	wchar_t* outname = NULL;
	for (int i = 0; i < k; i++)//ǰk���û��ĳɼ�
	{
		//�û�id,�û������û�Ӯ�þ������û����˵��ܾ���
		//�˴��������Ը���������ʽ���ۺϴ�������ģʽռ�Ȳ�ͬ
		//1 id����ת��
		int id = tmp[i].id;
		TCHAR snum1[5];
		swprintf_s(snum1, _T("%d"), id);

		//2 name����ת��
		std::string name = tmp[i].get_name();
		size_t size = name.length();
		outname = new wchar_t[size + 1];
		MultiByteToWideChar(CP_ACP, 0, name.c_str(), size+1, outname, size * sizeof(wchar_t)+1);

		//3. Ӯ�ü򵥾�������ת��
		int woneasy = tmp[i].woneasy;
		TCHAR snum2[5];
		swprintf_s(snum2, _T("%d"), woneasy);

		//4.Ӯ���еȾ�������ת��
		int wonmiddle = tmp[i].wonmiddle;
		TCHAR snum3[5];
		swprintf_s(snum3, _T("%d"), wonmiddle);

		//5.Ӯ�����Ѿ�������ת��
		int wonhard = tmp[i].wonhard;
		TCHAR snum4[5];
		swprintf_s(snum4, _T("%d"), wonhard);

		//6.Ӯ��ר�Ҿ�������ת��
		int wonexpert = tmp[i].wonexpert;
		TCHAR snum5[5];
		swprintf_s(snum5, _T("%d"), wonexpert);

		//7.���˵��ܾ�������ת��
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
	int nowpos = findPos(x);//�����û����������ҵ����û�
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