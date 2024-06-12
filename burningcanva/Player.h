#pragma once
#include <iostream>
#include <vector>
#include "ActionCanva.h"
#include <array>
#include <cstddef>
#include <algorithm>
struct Player
{
	int id;//自增id
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
	bool contains(const Player& x)const;//查找是否有该账户
	void makeEmpty();//初始清空
	bool Insert(const Player & x);//增
	bool Delete(const Player & x);//删
	bool Change_name(std::string new_name, Player x);//更改账号信息
	bool Change_pwd(std::string new_pwd, Player x);
	Player get_nowplayerinfo(Player& x);//用于返回当前玩家信息
	enum EntryType{ACTIVE,EMPTY,DELETED};
	size_t get_arraysize();//总表大小
	size_t get_currentsize();
	void update();//更新文件
	void forrank();//查看排名
	void add_won(int level,Player& x);
	void add_total(Player& x);
private:
	struct HashEntry//内嵌类
	{
		Player player1;
		EntryType info;
		HashEntry(const Player & p=Player{},EntryType i= EMPTY)
			:player1{p},info{i}{}
	};
    std::vector<HashEntry>hasharray;
	size_t currentSize;
	bool isActive(size_t currentPos) const;//该账户账号账号状态是否活跃
	size_t findPos(const Player& tmp) const;//查找该账户在hash表中的位置
	void rehash();//再hash
	size_t myhash(const Player& tmp) const;//hash函数
	void add_currentsize();
	void reduce_currentsize();
	size_t nextPrime(size_t num);
};
//hash函数，insert,delete,change,find,isactive,rehash,