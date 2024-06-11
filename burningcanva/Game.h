#pragma once
#include "ActionCanva.h"
#include "TargetCanva.h"
#include "Player.h"
#include "Grid.h"
#include <iostream>
//定义页面变量编号:
const int PAGE_HOME = 1;//主页
const int PAGE_LEVEL = 2;//难度选择页
const int PAGE_GAME=3;//游戏页面
const int PAGE_RES =4;//注册页
const int PAGE_CREATE = 5;//自己创造游戏页
const int PAGE_RANK = 6;//排行榜
//定义游戏难度编号:
const int EASY = 4;//4*4,目标画布4种颜色
const int MIDDLE=6 ;//6*6,目标画布5种颜色
const int HARD = 8;//8*8，目标画布7种颜色
const int EXPERT = 12;//12*12，目标画布10种颜色
class Game
{
public:
	Game();
	void create_window();
	void game_controll();
private:
	void keyEvent();
	void draw_homepage();
	void draw_levelpage();
	void game_home();
	void game_level();
	void set_button(int x, int y, int w, int h, TCHAR* text);
	void game_play();
	void setCurrentPage(int c);
	int  getCurrentPage();
	void set_QuestionNumber(int level);
	int get_QuestionNumber();
	void do_homepage();
	void do_gamelevel();
	void draw_gameplay();
	void start_gameplay();
	void do_gameplay();
	void set_level(int l);
	int get_level();
	void judge_gameplay();
	void set_submit(int s);
	int get_submit();
	void re_game();
	void set_selectq();
	void base_drawplay();
	void canva_drawplay();
	int get_selectq();
	void gamelevel_buttons();
	void gamelevel_rules();
	void calculate();
	void calculate(int size);
	void game_create();//自己创造题目
	void base_create();//创造题目页的画面
	void create_input();//创造题目的输入
	bool checkcreate();//检查是否创造成功题目
	void accountcalculate();
	void login();
	void base_drawres();
	void game_res();
	void signup();
	void game_rank();
	void chooseava();
	void create_canvas_size();
private:
	int currentPage = PAGE_HOME;//默认为主页
	ActionCanva act;//操作画布
	TargetCanva tar;//目标画布
	int level;//游戏难度
	int questionnumber;//如果是从题库中选的题，选择的是第几道题
	int submit;//用户提交状态
	//int test;
	HashTable AccountManage;//利用hash表管理用户数据
	int selectq;//1：从题库中抽题，0：编一个题目
	int qtotnumber[4];
	bool select;//记录用户是否选择创建题目
	int posi, posj;//创建题目时的位置,i,j最大值是11
	int size;
	Grid forcreate[12][12];
	bool select_mode;//创造题目时必须先选择题目
	bool create_submit;//
	std::string nowplayer;
	std::string nowpwd;
	int nowwon;
	int nowtotal;
	int newavarnum;//当前正在注册的用户选择的头像
	Player currentPlayer;
	bool satisfy;
};

