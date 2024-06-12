#pragma once
#include <iostream>
#include <vector>
#include "ActionCanva.h"
#include <array>
#include <cstddef>
#include <algorithm>
struct Player
{
	int id;//����id
	std::string name;
	std::string password;
	int Avatar;
	int woneasy;
	int wonmiddle;
	int wonhard;
	int wonexpert;
	int total;
	Player(int idtmp,std::string n, std::string pwd, int ava=0,int woeasy=0,int womiddle=0,int wohard=0,int woexpert=0, int to=0) :id(idtmp),name(n),password(pwd),Avatar(ava),
		woneasy(woeasy),wonmiddle(womiddle),wonhard(wohard),wonexpert(woexpert),total(to){}
	Player() {};
	std::string get_name();
	int get_id();
	int get_ava();
	void set_account(int idnow,std::string name,std::string pwd,int ava,int woeasy= 0,int womiddle=0,int wohard=0,int woexpert=0,int total= 0);
	void change_name(std::string new_name);
	void change_pwd(std::string new_pwd);
	void add_woneasy();
	void add_wonmiddle();
	void add_wonhard();
	void add_wonexpert();
	void add_tot();
};
class HashTable
{
public:
	explicit HashTable(int size = 101) :hasharray(nextPrime(size))
	{
		makeEmpty();
	}
	bool contains(const Player& x)const;//�����Ƿ��и��˻�
	void makeEmpty();//��ʼ���
	bool Insert(const Player & x);//��
	bool Delete(const Player & x);//ɾ
	bool Change_name(std::string new_name, Player x);//�����˺���Ϣ
	bool Change_pwd(std::string new_pwd, Player x);
	Player get_nowplayerinfo(Player& x);//���ڷ��ص�ǰ�����Ϣ
	enum EntryType{ACTIVE,EMPTY,DELETED};
	size_t get_arraysize();//�ܱ��С
	size_t get_currentsize();
	void update();//�����ļ�
	void forrank();//�鿴����
	void add_won(int level,Player& x);
	void add_total(Player& x);
private:
	struct HashEntry//��Ƕ��
	{
		Player player1;
		EntryType info;
		HashEntry(const Player & p=Player{},EntryType i= EMPTY)
			:player1{p},info{i}{}
	};
    std::vector<HashEntry>hasharray;
	size_t currentSize;
	bool isActive(size_t currentPos) const;//���˻��˺��˺�״̬�Ƿ��Ծ
	size_t findPos(const Player& tmp) const;//���Ҹ��˻���hash���е�λ��
	void rehash();//��hash
	size_t myhash(const Player& tmp) const;//hash����
	void add_currentsize();
	void reduce_currentsize();
	size_t nextPrime(size_t num);
};
//hash������insert,delete,change,find,isactive,rehash,