#pragma once
#include "ActionCanva.h"
#include "TargetCanva.h"
#include "Player.h"
#include "Grid.h"
#include <iostream>
//����ҳ��������:
const int PAGE_HOME = 1;//��ҳ
const int PAGE_LEVEL = 2;//�Ѷ�ѡ��ҳ
const int PAGE_GAME=3;//��Ϸҳ��
const int PAGE_RES =4;//ע��ҳ
const int PAGE_CREATE = 5;//�Լ�������Ϸҳ
const int PAGE_RANK = 6;//���а�
//������Ϸ�Ѷȱ��:
const int EASY = 4;//4*4,Ŀ�껭��4����ɫ
const int MIDDLE=6 ;//6*6,Ŀ�껭��5����ɫ
const int HARD = 8;//8*8��Ŀ�껭��7����ɫ
const int EXPERT = 12;//12*12��Ŀ�껭��10����ɫ
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
	void game_create();//�Լ�������Ŀ
	void base_create();//������Ŀҳ�Ļ���
	void create_input();//������Ŀ������
	bool checkcreate();//����Ƿ���ɹ���Ŀ
	void accountcalculate();
	void login();
	void base_drawres();
	void game_res();
	void signup();
	void game_rank();
	void chooseava();
	void create_canvas_size();
private:
	int currentPage = PAGE_HOME;//Ĭ��Ϊ��ҳ
	ActionCanva act;//��������
	TargetCanva tar;//Ŀ�껭��
	int level;//��Ϸ�Ѷ�
	int questionnumber;//����Ǵ������ѡ���⣬ѡ����ǵڼ�����
	int submit;//�û��ύ״̬
	//int test;
	HashTable AccountManage;//����hash������û�����
	int selectq;//1��������г��⣬0����һ����Ŀ
	int qtotnumber[4];
	bool select;//��¼�û��Ƿ�ѡ�񴴽���Ŀ
	int posi, posj;//������Ŀʱ��λ��,i,j���ֵ��11
	int size;
	Grid forcreate[12][12];
	bool select_mode;//������Ŀʱ������ѡ����Ŀ
	bool create_submit;//
	std::string nowplayer;
	std::string nowpwd;
	int nowwon;
	int nowtotal;
	int newavarnum;//��ǰ����ע����û�ѡ���ͷ��
	Player currentPlayer;
	bool satisfy;
};

