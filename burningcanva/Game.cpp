#include "Game.h"
#include <ctime>
#include <string>
#include <conio.h>
//getch():����easyx����,���ڻ�ȡ������Ϣ
//GetAsyncKeyState(��ֵ)��
IMAGE img;
IMAGE win;
IMAGE chdefaultava;
IMAGE chava1;
IMAGE chava2;
IMAGE chava3;
IMAGE chava4;
//ʹ��HiEasyX;�����еĻ�ͼ���벿�ּ��������У��Ҳ�Ҫ���޹ش����������-->ʧ��
COLORREF colors[60] = { 235,29,29,252,144,50,255,255,0,34,139,34,
				   64,224,208,0,0,255,75,0,130,128,0,128,255,20,147,115,74,18,252,224,203 };
Game::Game()
{
	setCurrentPage(PAGE_HOME);
	calculate();//ͳ����������ж��ٵ���
	accountcalculate();//�û���Ϣ¼��ϵͳ
	this->select = 0;
	posi = 0, posj = 0;
	loadimage(&chava1, _T("avatar1.jpg"), 100, 100);
	loadimage(&chava2, _T("avatar2.jpg"), 100, 100);
	loadimage(&chava3, _T("avatar3.jpg"), 100, 100);
	loadimage(&chava4, _T("avatar4.jpg"), 100, 100);
	loadimage(&chdefaultava, _T("defaultacatar.jpg"), 100, 100);
}

void Game::game_controll()
{
	int nowpage = getCurrentPage();
	if (nowpage == PAGE_HOME) game_home();
	else if (nowpage == PAGE_LEVEL) game_level();
	else if (nowpage == PAGE_GAME) game_play();
	else if (nowpage == PAGE_CREATE) game_create();
	else if (nowpage == PAGE_RES) game_res();
	else if (nowpage == PAGE_RANK) game_rank();
}


void Game::game_home()//��ҳ
{
	draw_homepage();//����ҳ
	do_homepage();//��ҳ����
}

void Game::draw_homepage()
{
	loadimage(&img, _T("gdygbk.bmp"), 1300, 900);
	putimage(0, 0, &img);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(120, 100, _T("����"));
	outtextxy(270, 70, _T("ȼ�յĻ�"));
	TCHAR ss1[50] = L"��¼";
	TCHAR ss2[50] = L"ע��";
	set_button(500, 600, 170, 50, ss1);
	set_button(500, 700, 170, 50, ss2);

}
//�˴�ȱ�ύдһ��ȷ���ύ�İ�ť
void Game::do_homepage()
{
	ExMessage msg;
	int x, y;
	while (1)
	{
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();
			x = msg.x;
			y = msg.y;
			if (msg.uMsg == WM_LBUTTONDOWN)
			{

				if (x >= 500 && x <= 670 && y >= 600 && y <= 650)//��¼
				{
					login();
					//��Ҫ��¼��ǰ˭��¼�ˣ����ڼƷ�
					setCurrentPage(PAGE_LEVEL);
					break;
				}
				else if (x >= 500 && x <= 670 && y >= 700 && y <= 750)//ע��
				{
					setCurrentPage(PAGE_RES);
					break;
				}
			}
		
		}
	}
}

void Game::game_level()//�Ѷ�ѡ��ҳ
{
	draw_levelpage();//����Ϸ�Ѷ�ѡ��ҳ
	do_gamelevel();//�ڴ�ҳ��ִ�в���
}

void Game::draw_levelpage()
{
	gamelevel_buttons();
	gamelevel_rules();
}
void Game::gamelevel_buttons()
{
	cleardevice();
	putimage(0, 0, &img);
	setbkmode(TRANSPARENT);
	TCHAR ss1[50] = L"��ģʽ";
	TCHAR ss2[50] = L"�е�ģʽ";
	TCHAR ss3[50] = L"����ģʽ";
	TCHAR ss4[50] = L"ר��ģʽ";
	TCHAR ss5[50] = L"�鿴���а�";
	TCHAR ss6[50] = L"������һ��";
	TCHAR ss7[50] = L"������Ŀ";
	//�˴�ȱһ���ܿ����а�Ĵ���
	set_button(500, 200, 200, 50, ss1);
	set_button(500, 300, 200, 50, ss2);//�����˰�ťλ��
	set_button(500, 400, 200, 50, ss3);
	set_button(500, 500, 200, 50, ss4);
	set_button(500, 600, 200, 50, ss5);
	set_button(800, 0, 200, 50, ss6);
	set_button(500, 700, 200, 50, ss7);
}

void Game::gamelevel_rules()
{
	settextstyle(20, 0, _T("΢���ź�"));//��Ҫ����������
	outtextxy(20, 20, _T("�������£�"));
	outtextxy(20, 40, _T("1.ÿ�������ִ���ò����ϵĲ���"));
	outtextxy(20, 60, _T("2.���ȣ������ϲ���>1ʱ���ò��������������������²㣬"));
	outtextxy(20, 80, _T("�������ϲ�����Ӧ�ı�;�����ϲ���=1ʱ��"));
	outtextxy(20, 100, _T("�ò����ϲ�������"));
	outtextxy(20, 120, _T("���Ŀ�꣺��ԭĿ�껭��"));
}

void Game::do_gamelevel()
{
	ExMessage msg;
	int x, y;
	while (1)
	{
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();
			x = msg.x;
			y = msg.y;
			if (msg.uMsg == WM_LBUTTONDOWN) {
				if (x >= 500 && x <= 700 && y >= 200 && y <= 250)
				{
					set_level(EASY);
					setCurrentPage(PAGE_GAME);
					break;
				}
				else if (x >= 500 && x <= 700 && y >= 300 && y <= 350)
				{
                    set_level(MIDDLE);
					setCurrentPage(PAGE_GAME);
					break;
				}
				else if (x >= 500 && x <= 700 && y >= 400 && y <= 450)
				{
                     set_level(HARD);
					 setCurrentPage(PAGE_GAME);
					 break;
				}
				else if (x >= 500 && x <= 700 && y >= 500 && y <= 550)
				{
					set_level(EXPERT);
					setCurrentPage(PAGE_GAME);
					break;
				}
				else if (x >= 500 && x <= 700 && y >= 700 && y <= 750)
				{
					setCurrentPage(PAGE_CREATE);
					break;
				}
				else if (x >= 800 && x <= 1000 && y >= 0 && y <= 50)
				{
					setCurrentPage(PAGE_HOME);//�ص���ҳ
					break;
				}
				//	set_button(800, 0, 200, 50, ss6);
				else if (x >= 800 && x <= 1000 && y >= 0 && y <= 50)
				{
					setCurrentPage(PAGE_HOME);
					break;
				}
				//set_button(500, 600, 200, 50, ss5);
				else if (x >= 500 && x <= 700 && y >= 600 && y <= 650)
				{
					setCurrentPage(PAGE_RANK);
					break;
				}
			}
		}
	}
}

void Game::game_play()//����Ϸҳ
{
	draw_gameplay();
	start_gameplay();//�����ʼ��Ϸ��ť
	do_gameplay();//ֻҪû�ύһֱ��
	judge_gameplay();//�ύ֮���ж�
	re_game();
}

void Game::draw_gameplay()
{
	base_drawplay();
	canva_drawplay();
}

void Game::base_drawplay()
{
	cleardevice();
	putimage(0, 0, &img);
	setbkmode(TRANSPARENT);
	TCHAR ss1[50] = L"����";
	TCHAR ss2[50] = L"����";
	TCHAR ss3[50] = L"����";
	TCHAR ss4[50] = L"����";
	TCHAR ss5[50] = L"��ʼ��Ϸ";
	TCHAR ss10[50] = L"�鿴��ʾ";
	TCHAR ss6[50] = L"�ύ";
	TCHAR ss7[50] = L"������һ��";
	TCHAR ss8[50] = L"����һ��";
	TCHAR ss9[50] = L"�������";
	set_button(1050, 700, 100, 50, ss1);
	set_button(1200, 700, 100, 50, ss2);
	set_button(1050, 800, 100, 50, ss3);
	set_button(1200, 800, 100, 50, ss4);
	set_button(1200, 0, 100, 50, ss5);
	set_button(1200, 75, 100, 50, ss10);
	set_button(1200, 150, 100, 50, ss6);
	set_button(1200, 250, 100, 50, ss7);
	set_button(1200, 350, 100, 50, ss8);
	set_button(1200, 450, 100, 50, ss9);
	settextstyle(15, 0, _T("����"));
	outtextxy(1150, 130, _T("ʣ����ʾ������"));
}

void Game::canva_drawplay()
{

	act.setSize(level);
	tar.set_size(level);

	//�����1��������г��⣬�����0���Զ�������Ŀ�浽�ļ���
	set_selectq();
	if (get_selectq() == 1)
	{
		set_QuestionNumber(level);//�����ȡ���
		act.set_qnumber(get_QuestionNumber());//����Ŀ��֪��������
		tar.set_Questionnumber(get_QuestionNumber());//����Ŀ��֪Ŀ�껭��
		act.generate_canva();//������������ͼ��
		tar.generate_canva();//Ŀ�껭������ͼ��
	}
	else
	{
		if (level == 4) qtotnumber[0]++, act.set_qnumber(qtotnumber[0]), tar.set_Questionnumber(qtotnumber[0]);
		else if (level == 6) qtotnumber[1]++, act.set_qnumber(qtotnumber[1]), tar.set_Questionnumber(qtotnumber[1]);
		else if (level == 8) qtotnumber[2]++, act.set_qnumber(qtotnumber[2]), tar.set_Questionnumber(qtotnumber[2]);
		else if (level == 12) qtotnumber[3]++, act.set_qnumber(qtotnumber[3]), tar.set_Questionnumber(qtotnumber[3]);
		tar.receive_canva(act.randcreate_q());//�Զ�������Ŀ�����ҽ�һ�����ɵĴ𰸴��ݸ�Ŀ�껭��tar
		std::fstream o("ttt.txt",std::ios::app);

		//��Ӧ����ȱһ��д���ļ��Ĵ���
		//�˴�ȱһ�������������
		//���Բ�д��⣡
	}
	//�����Ϸ��ʼǰ��Ӧ����ס��������
	act.hide();
	tar.draw();//��Ŀ�껭��
}


void Game::start_gameplay()
{
	while (1)//�����Ϸ��ʼ
	{
		int x, y;
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();
			x = msg.x;
			y = msg.y;
			if (msg.uMsg == WM_LBUTTONDOWN)
				if (x >= 1200 && x <= 1300 && y >= 0 && y <= 50)
				{
					set_submit(0);
					act.draw();//�����Ϸ��ʼ����չ�ֲ�������
					act.copyinit();
					act.showhintnumber();
					break;
				}
		}
	}
}

void Game::do_gameplay()
{
	while (1)//ֻҪ�û�û���ύ����һֱ���Խ��в���
	{
		keyEvent();
		if (get_submit() == 1) break;
	}
}

void Game::judge_gameplay()
{
	int sign = 1;
	for (int i = 0; i < level; i++)//����Ƿ�ɹ���ԭ�˻���
	{    //һ���бȽ�.��i��
		Grid* acttmp = act.getactcanva(i);
		Grid* tartmp = tar.gettarcanva(i);
		for (int j = 0; j < level; j++)
		{
			BYTE r1 = GetRValue(acttmp[j].getColor());
			BYTE g1 = GetGValue(acttmp[j].getColor());
			BYTE b1 = GetBValue(acttmp[j].getColor());
			int R1 = static_cast<int>(r1);
			int G1 = static_cast<int>(g1);
			int B1 = static_cast<int>(b1);
			//Ŀ�껭��
			BYTE r2 = GetRValue(tartmp[j].getColor());
			BYTE g2 = GetGValue(tartmp[j].getColor());
			BYTE b2 = GetBValue(tartmp[j].getColor());
			int R2 = static_cast<int>(r2);
			int G2 = static_cast<int>(g2);
			int B2 = static_cast<int>(b2);
			if (R1 != R2 || G1 != G2 || B1 != B2)
			{
				sign = 0;
				break;
			}
		}
		if (sign == 0) break;
	}
	if (sign == 1)
	{
		nowwon++;
		nowtotal++;
		//����ǰ���µľ�����¼����̨
		AccountManage.add_won(level, currentPlayer);
		AccountManage.add_total(currentPlayer);
		HWND hnd = GetHWnd();
		MessageBox(hnd, _T("You Win:-)"), _T("��ʾ"), MB_OKCANCEL);
	}
	else if (sign == 0)
	{
		AccountManage.add_total(currentPlayer);
		HWND hnd = GetHWnd();
		MessageBox(hnd, _T("You lose:-("), _T("��ʾ"), MB_OKCANCEL);
	}
	//���µ��ļ�����
	AccountManage.update();
	act.cleartotalburn();
}

void Game::re_game()
{
	while (1)
	{
		int x, y;
		if (MouseHit())//������
		{
			MOUSEMSG msg = GetMouseMsg();//������Ϣ
			x = msg.x;
			y = msg.y;
			if (msg.uMsg == WM_LBUTTONDOWN)//����Ϣ���ڵ��	
			{
				if (x >= 1200&& x <= 1300 && y >= 250 && y <= 300)
				{
					setCurrentPage(PAGE_LEVEL);
					break;
				}
				else if (x >= 1200 && x <= 1300 && y >= 350 && y <= 400)
				{
					game_play();//����һ��
					break;
				}
				else if (x >= 1200 && x <= 1300 && y >= 450 && y <= 500)//����
				{
					set_submit(0);
					act.reset(get_level(), get_QuestionNumber());//���
					act.draw();
					start_gameplay();
					do_gameplay();
					judge_gameplay();
					re_game();
					break;
				}
			}
		}
	}
}

void  Game::game_create()
{
	//1.��ͼ
	base_create();

	//2.�û�ȷ���ѶȾ���
	select_mode = 0;
	create_canvas_size();

	//3.�û���Ʋ��ύ�ѶȾ���:���+����+�ύ
	posi = -1, posj = -1;
	create_submit = 0;
	satisfy = 0;
	create_input();//�ύ�洢��actmode�ļ�����
	if (size == 4) qtotnumber[0]++;
	else if (size == 6) qtotnumber[1]++;
	else if (size == 8) qtotnumber[2]++;
	else if (size == 12) qtotnumber[3]++;

	//4.������ɴ�,�浽hint����
	int x=-20;
	std::fstream forans;//�����
	if (size == 4) x=qtotnumber[0],forans.open("easyhint.txt", std::ios::app);
	else if (size == 6) x = qtotnumber[1], forans.open("middlehint.txt", std::ios::app);
	else if (size== 8) x = qtotnumber[2], forans.open("middlehint.txt", std::ios::app);
	else if (size== 12) x = qtotnumber[3], forans.open("experthint.txt", std::ios::app);
	if (!forans)
	{
		std::cerr << "File could not be opened" << std::endl;
		exit(EXIT_FAILURE);
	}

	forans << x << std::endl;//�ȴ������

	//2.��Ŀ�ӹ��õ���
	while (!done())//ֻҪ�в�Ϊ1�ģ�˵������Ҫ����
	{
		//�����ɴ𰸵Ĺ���(������ʼ����)�����ļ�����
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				BYTE R = GetRValue(forcreate[i][j].getColor());
				BYTE G = GetGValue(forcreate[i][j].getColor());
				BYTE B = GetBValue(forcreate[i][j].getColor());
				int r = static_cast<int>(R);
				int g = static_cast<int>(G);
				int b = static_cast<int>(B);
				forans << r << ' ' << g << ' ' << b << ' ' << forcreate[i][j].getNumber() << std::endl;
			}
		}
		forans << '\n';
		int rnum = rand() % 3;
		for (int i = 0; i < rnum; i++)
			leftrotate();
		burning();//��forcreate����burning
	}
	std::fstream forbank;
	if (size == 4) forbank.open("easyQuestionbank.txt", std::ios::app);
	else if (size == 6) forbank.open("middleQuestionbank.txt", std::ios::app);
	else if (size == 8) forbank.open("hardQuestionbank.txt", std::ios::app);
	else if (size == 12) forbank.open("expertQuestionbank.txt", std::ios::app);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			BYTE R = GetRValue(forcreate[i][j].getColor());
			BYTE G = GetGValue(forcreate[i][j].getColor());
			BYTE B = GetBValue(forcreate[i][j].getColor());
			int r = static_cast<int>(R);
			int g = static_cast<int>(G);
			int b = static_cast<int>(B);
			forans << r << ' ' << g << ' ' << b << ' ' << forcreate[i][j].getNumber() << std::endl;//���һ���𰸲���浽QBank������...
			forbank << r << ' ' << g << ' ' << b << std::endl;
		}
	}
	forans << '\n';
	forbank << '\n';
	forans.close();
	forbank.close();

	while (1)
	{
			int x, y;
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();
			x = msg.x;
			y = msg.y;
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
			//set_button(900, 0, 100, 50, ss7);
			//set_button(900, 75, 100, 50, ss8);
				if (x >= 900 && x <= 1000 && y >= 0 && y <= 50)
			{
					setCurrentPage(PAGE_HOME);
					break;
			}
				else if (x >= 900 && x <= 1000 && y >= 75 && y <= 125)
				{
					setCurrentPage(PAGE_LEVEL);
					break;
		}
	}
}
	}
}

void Game::create_window()
{
	initgraph(1300, 900);
	setbkcolor(WHITE);
	cleardevice();
}

void Game::set_button(int x, int y, int w, int h, TCHAR* text)
{
	setlinecolor(BLACK);
	setbkmode(TRANSPARENT);
	setfillcolor(0xa1afc9);
	fillroundrect(x, y, x + w, y + h, 10, 10);
	TCHAR s1[] = L"����";
	settextstyle(20, 0, s1);
	int tx = x + (w - textwidth(text)) / 2;
	int ty = y + (h - textheight(text)) / 2;
	outtextxy(tx, ty, text);
}

void Game::setCurrentPage(int c)
{
	this->currentPage = c;
}

int Game::getCurrentPage()
{
	return this->currentPage;
}

void Game::set_QuestionNumber(int level)
{
	srand((unsigned)time(NULL));
	int r=0;
	if (level == 4) r = rand() % qtotnumber[0];
	else if (level == 6) r = rand() % qtotnumber[1];
	else if (level == 8) r = rand() % qtotnumber[2];
	else if (level == 12) r = rand() % qtotnumber[3];
	this->questionnumber = r;
}

int Game::get_QuestionNumber() {return this->questionnumber;}


void Game::set_level(int l)
{
	this->level = l;
}

int Game::get_level()
{
	return this->level;
}

void Game::set_submit(int s)
{
	this->submit=s;
}

int Game::get_submit()
{
	return this->submit;
}

void Game::keyEvent()//�û��������������������ȣ������Ĳ���
{
	int x, y;
	while (1)//�ȴ��û�����
	{
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();
			x = msg.x;
			y = msg.y;
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				if (x >= 1050 && x <= 1150 && y >= 700 && y <= 750)//����
				{

					act.leftrotate();
					act.draw();
				}
				else if (x >= 1200 && x <= 1300 && y >=700 && y <= 750)//����
				{
					act.rightrotate();
					act.draw();
				}
				else if (x >= 1050 && x <= 1150 && y >= 800 && y <= 850)//����
				{
					act.burn();
					act.draw();
				}
					
				else if (x >= 1200 && x <= 1300 && y >= 800 && y <= 850)//����
				{
					act.quash();
					act.draw();
				}
				else if (x >= 1200 && x <= 1300 && y >= 150 && y <= 200)//�ύ
				{
					set_submit(1);
					act.reparam();
				}
				else if (x >= 1200 && x <= 1300 && y >= 75 && y <= 125)//�鿴��ʾ
				{
					act.checkhint();
					act.showhints();
					act.showhintnumber();
				}
				break;
			}
		}
	}
}


void Game::set_selectq()
{
	srand((unsigned)time(NULL));
	selectq = rand() % 1;
}

int Game::get_selectq() { return this->selectq; }

void Game::calculate()
{
	calculate(4);
	calculate(6);
	calculate(8);
	calculate(12);
}

void Game::calculate(int size)
{
	std::fstream Num;
	if (size == 4) Num.open("easyQuestionbank.txt");
	else if(size==6) Num.open("middleQuestionbank.txt");
	else if(size==8) Num.open("hardQuestionbank.txt");
	else if(size==12) Num.open("expertQuestionbank.txt");
	if (!Num)
	{
		std::cerr << "File could not be opend" << std::endl;
		exit(EXIT_FAILURE);
	}
	std::string templine;
	if (getline(Num, templine))//������У�˵���������
	{
		std::string line;
		int num = 0;
		while (getline(Num, line))
		{
			if (line.empty()) num++;
		}
		if (size == 4) qtotnumber[0] = num;
		else if (size == 6) qtotnumber[1] = num;
		else if (size == 8) qtotnumber[2] = num;
		else if (size == 12) qtotnumber[3] = num;
	}
	else
	{
		if (size == 4) qtotnumber[0] = 0;
		else if (size == 6) qtotnumber[1] = 0;
		else if (size == 8) qtotnumber[2] = 0;
		else if (size == 12) qtotnumber[3] = 0;
	}
	std::fstream omyg("ogmymymy.txt", std::ios::app);
}

void Game::base_create()
{
	loadimage(&img, _T("gdygbk.bmp"), 1300, 900);
	putimage(0, 0, &img);
	settextcolor(BLACK);
	settextstyle(60, 40, _T("����"));
	outtextxy(100, 70, _T("���������Լ�����Ŀ��!"));
	settextstyle(20, 0, _T("����"));
	outtextxy(20, 200, _T("���������"));
	outtextxy(20, 220, _T("1.�����ѡ���Լ�ϲ������ɫ������"));
	outtextxy(20, 240, _T("2.����Ի����Լ���Ҫ�Ĳ�������"));
	outtextxy(20, 260, _T("3.���ǿ���Ϊ������һ�����û���۵�Ŀ�껭��"));
	outtextxy(20, 280, _T("���������Ŀ������뵽���ǵ���⵱��"));
    setbkmode(TRANSPARENT);
	TCHAR ss1[50] = L"��ģʽ";
	TCHAR ss2[50] = L"�е�ģʽ";
	TCHAR ss3[50] = L"����ģʽ";
	TCHAR ss4[50] = L"ר��ģʽ";
	TCHAR ss5[50] = L"�ύ";
	TCHAR ss6[50] = L"����";
	TCHAR ss7[50] = L"���ص���һ��";
	TCHAR ss8[50] = L"�л�����Ϸ����";
	set_button(0, 500, 100, 50, ss1);
	set_button(0, 575, 100, 50, ss2);
	set_button(0, 650, 100, 50, ss3);
	set_button(0, 725, 100, 50, ss4);
	set_button(0, 800, 100, 50, ss5);
	set_button(200, 500, 100, 50, ss6);
	set_button(900, 0, 100, 50, ss7);
	set_button(900, 75, 100, 50, ss8);

	COLORREF colors[60] = { 0,245,255,78,238,148,0,139,69,238,238,0,
					   238,173,14,255,106,106,255,127,0,255,20,147,255,187,255,0,0,128 };//10����ɫ
	COLORREF colortemp;
	for (int i = 0; i < 11; i++)
	{
		colortemp = RGB(colors[3 * i], colors[3 * i + 1], colors[3 * i + 2]);
		setfillcolor(colortemp);
		fillrectangle(i * 30, 430, (i + 1) * 30, 400);
	}

}


void Game::create_input()
{
	while (create_submit == 0)
	{
		//�ѵ㣺��θ��ݴ������Ŀ����?-->�ƺ��Ѿ���������ڴ���ʵ��
		int x, y;
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();
			x = msg.x;
			y = msg.y;
			if (msg.uMsg == WM_LBUTTONDOWN)
			{

				COLORREF colo;
				//1.�ύ���ɹ�
				if (x >= 0 && x <= 100 && y >= 800 && y <= 850 && checkcreate())
				{
					std::fstream openbank;
					if (size == 4) openbank.open("easyactmode.txt", std::ios::app);
					else if (size == 6) openbank.open("middleactmode.txt", std::ios::app);
					else if (size == 8) openbank.open("hardactmode.txt", std::ios::app);
					else if (size == 12) openbank.open("expertactmode.txt", std::ios::app);
					for (int i = 0; i < size; i++)
					{
						for (int j = 0; j < size; j++)
						{
							BYTE R = GetRValue(forcreate[i][j].getColor());
							BYTE G = GetGValue(forcreate[i][j].getColor());
							BYTE B = GetBValue(forcreate[i][j].getColor());
							int r = static_cast<int>(R);
							int g = static_cast<int>(G);
							int b = static_cast<int>(B);
							openbank << r << ' ' << g << ' ' << b <<' '<<forcreate[i][j].getNumber()<<std::endl;
						}
					}
					HWND hnd = GetHWnd();
					MessageBox(hnd, _T("Success submit :-)"), _T("��ʾ"), MB_OKCANCEL);
					create_submit = 1;
					openbank << '\n';
				}
				//2.�ύ��ʧ��
				else if (x >= 0 && x <= 100 && y >= 800 && y <= 850 && !checkcreate())
				{
					HWND hnd = GetHWnd();
					MessageBox(hnd, _T("You don't finish :-("), _T("��ʾ"), MB_OKCANCEL);
				}
				//3.����
				else if (x >= 200 && x <= 300 && y >= 500 && y <= 550)
				{
					if (posj != 0&&posj>0)
					{
						setfillcolor(WHITE);
						fillrectangle(posj * 30 + 700, (posi + 1) * 30 + 500, (posj + 1) * 30 + 700, posi * 30 + 500);
						forcreate[posi][posj].setGrid(WHITE, 1);
						posj--;
					}
					else if (posj == 0&&posi!=0)
					{
						setfillcolor(WHITE);
						fillrectangle(posj * 30 + 700, (posi + 1) * 30 + 500, (posj + 1) * 30 + 700, posi * 30 + 500);
						forcreate[posi][posj].setGrid(WHITE, 1);
						posj = size - 1, posi--;
				}
					else if (posj == 0 && posi == 0)
						{
							setfillcolor(WHITE);
						fillrectangle(700, 530, 730, 500);
						forcreate[0][0].setGrid(WHITE, 1);
						posj--, posi--;
					}
				}
				//4.ѡ���˲�ͬ��ɫ���ŵ�ͼ����
				else if (y >= 400 && y <= 430)
				{
					int num;
					if (posi == -1 && posj == -1) { posi++, posj++; }
					else if (posi == 0 && posj == 0) posj++;
					else if (posj != size - 1) posj++;
					else if (posj == size - 1&&posi!=size-1) posi++, posj = 0;
					else if (posi == size - 1 && posj == size - 1) satisfy = 1;
					std::fstream ss("d.txt", std::ios::app);
					ss << "This is a testa" << std::endl;
					if (x >= 0 && x <= 30) colo = RGB(colors[0], colors[1], colors[2]);
					else if (x >= 30 && x <= 60) colo = RGB(colors[3], colors[4], colors[5]);
					else if (x >= 60 && x <= 90) colo = RGB(colors[6], colors[7], colors[8]);
				    else if (x >= 90 && x <= 120) colo = RGB(colors[9], colors[10], colors[11]);
				    else if (x >= 120 && x <= 150) colo = RGB(colors[12], colors[13], colors[14]);
					else if (x >= 120 && x <= 150) colo = RGB(colors[12], colors[13], colors[14]);
					else if (x >= 150 && x <= 180) colo = RGB(colors[15], colors[16], colors[17]);
					else if (x >= 180 && x <= 210) colo = RGB(colors[18], colors[19], colors[20]);
					else if (x >= 210 && x <= 240) colo = RGB(colors[21], colors[22], colors[23]);
					else if (x >= 240 && x <= 270) colo = RGB(colors[24], colors[25], colors[26]);
					else if (x >= 270 && x <= 300)  colo = RGB(colors[27], colors[28], colors[29]);
					else if (x >= 300 && x <= 330) colo = RGB(colors[30], colors[31], colors[32]);
					setfillcolor(colo);
					fillrectangle(posj * 30 + 700, (posi + 1) * 30 + 500, (posj + 1) * 30 + 700, posi * 30 + 500);
					if(size==4) num = rand() % 8+ 1;
					else if(size==6)  num = rand() % 10 + 1;
					else if (size == 8)  num = rand() % 13 + 1;
					else if (size == 12)  num = rand() % 20 + 1;
					forcreate[posi][posj].setGrid(colo, num);
				}
			}
		}
		break;
	}
}

bool Game::checkcreate()
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (forcreate[i][j].getColor() == WHITE) return 0;
	return 1;
}

void Game::accountcalculate()
{
	std::fstream foracc("account.txt",std::ios::in|std::ios::app);
	std::string line;
	while (getline(foracc, line))
	{
		std::string sub1, sub2, sub3, sub4,sub5,sub6,sub7,sub8,sub9;
		int sp1=0, sp2=0, sp3=0, sp4=0,sp5=0,sp6=0,sp7=0,sp8=0;
		for (int i = 0; i < line.size(); i++)
		{
			if (line[i] == ' ' && sp1 == 0) sp1 = i;
			else if (line[i] == ' ' && sp2 == 0) sp2 = i;
			else if (line[i] == ' ' && sp3 == 0) sp3 = i;
			else if (line[i] == ' ' && sp4 == 0) sp4 = i;
			else if (line[i] == ' ' && sp5 == 0) sp5 = i;
			else if (line[i] == ' ' && sp6 == 0) sp6 = i;
			else if (line[i] == ' ' && sp7 == 0) sp7 = i;
			else if (line[i] == ' ' && sp8 == 0) sp8 = i;
		}
		//substr:��һ�������ǿ�ʼλ�ã��ڶ����ǳ���
		sub1 = line.substr(0, sp1);//id
		sub2 = line.substr(sp1 + 1, sp2 - sp1-1);//name;
		sub3 = line.substr(sp2 + 1, sp3 -sp2-1);//password
		sub4 = line.substr(sp3 + 1, sp4 -sp3-1);//avatar
		sub5 = line.substr(sp4 + 1, sp5-sp4-1);//easywon
		sub6 = line.substr(sp5 + 1, sp6 - sp5 - 1);//middlewon
		sub7 = line.substr(sp6 + 1, sp7 - sp6 - 1);//hardwon
		sub8 = line.substr(sp7 + 1, sp8 - sp7 - 1);//expertwon
		sub9 = line.substr(sp8 + 1, line.size() - sp8- 1);//totwon

		int id = stoi(sub1);
		std::string name = sub2;
		std::string pwd = sub3;
		int avatmp = stoi(sub4);
		int easywon = stoi(sub5);
		int middlewon = stoi(sub6);
		int hardwon = stoi(sub7);
		int expertwon = stoi(sub8);
		int tot = stoi(sub9);
		Player tmp(id, name, pwd, avatmp,easywon,middlewon,hardwon,expertwon,tot);//��ȡ���ļ��е������˺�
		AccountManage.Insert(tmp);//���˺Ŷ����뵽hashtable����
	}
	foracc.close();
}

void Game::login()
{
	//�˴�Ҫдһ�����Ĵ���
    // ������дͷ����
    //�˴���Ҫдһ��enter֮��������֮ǰ�������Ϣ
	//�ж�
	//������ȷor������Ϣ�����±��
	settextstyle(20, 0, _T("����"));
	outtextxy(0, 300, _T("�����������û���"));
	settextstyle(20, 0, _T("����"));
	outtextxy(0, 450, _T("��������������"));
	while (1)
	{
		//����Ŀ���Զ��׼������ݿ��е����붼�Ǳ��ܵģ��޷����ƽ�
		//������
		char icname = ' ';
		char icpwd = ' ';
		int posname = 60, pospwd = 60;
		std::string inname = "";
		std::string inpwd = "";
		setfillcolor(WHITE);
		fillrectangle(50, 400, 350, 350);//
		setfillcolor(WHITE);
		fillrectangle(50, 525, 350, 475);//��������Ŀ�
		while (icname != '\r')
		{
			if (_kbhit())
			{
				icname = _getch();
				if (icname != '\r')
				{
					inname += icname;
					outtextxy(posname, 375, icname);
					posname += 10;
				}
			}
		}
		//2.�����������
		while (icpwd != '\r')
		{
			if (_kbhit())
			{
				icpwd = _getch();
				if (icpwd != '\r')
				{
					inpwd += icpwd;
					outtextxy(pospwd, 500, '*');
					pospwd += 10;
				}
			}
		}
		//3. �������
		char pwds[240] = "helloburningcanvas";
		for (int i = 0; i < inpwd.length(); i++)
			inpwd[i] ^= pwds[i];
		Player currentplayer(0, inname, inpwd);
		if (AccountManage.contains(currentplayer))
		{
			HWND hnd = GetHWnd();
			nowplayer = inname;
			nowpwd = inpwd;
			currentPlayer.set_account(0, inname, nowpwd,0);
			//ͨ���û��ɹ���¼��������˻����ں�̨�ҵ����û���Ϣ������¼��currentPlayer����
			currentPlayer = AccountManage.get_nowplayerinfo(currentplayer);
			MessageBox(hnd, _T("Successful login! Now enjoy yourself in game"), _T("��ʾ"), MB_OKCANCEL);
			setCurrentPage(PAGE_LEVEL);
			break;
		}
		else
		{
			HWND hnd = GetHWnd();
			MessageBox(hnd, _T("Your name or password input is wrong.\n Please input again"), _T("��ʾ"), MB_OKCANCEL);
		}
	}
}

void Game::base_drawres()
{
	cleardevice();
	putimage(0, 0, &img);
	setbkmode(TRANSPARENT);
	settextstyle(20, 0, _T("����"));
	outtextxy(600, 350, _T("�����·����������û���(������ɺ�Ҫ���enter):"));
	setfillcolor(WHITE);
	fillrectangle(600, 450,900, 400);
	settextstyle(20, 0, _T("����"));
	outtextxy(600, 500, _T("�����·�������������(������ɺ�Ҫ���enter):"));
	setfillcolor(WHITE);
	fillrectangle(600, 600, 900, 550);
	settextstyle(20, 0, _T("����"));
	outtextxy(100, 200, _T("��ѡ������ͷ��:"));
	putimage(150, 250, &chava1);
	putimage(150, 400, &chava2);
	putimage(150, 550, &chava3);
	putimage(150,700, &chava4);
	setbkmode(TRANSPARENT);
	settextstyle(20, 0, _T("����"));
	outtextxy(150, 850, _T("�Ƿ�ѡ��Ĭ��ͷ��"));
	outtextxy(900, 0, _T("Tips:"));
	outtextxy(900, 20, _T("������д�û���������"));
	outtextxy(900, 50, _T("�����������д��Ϣ�����Ƚ�������Ϣ"));
	outtextxy(900, 80, _T("��д������������ע��"));
	TCHAR ss1[50] = L"��";
	TCHAR ss2[50] = L"��";
	set_button(380, 850, 30, 30, ss1);
	set_button(480, 850, 30, 30, ss2);
	TCHAR ss0[50] = L"�ύ";
	TCHAR ss3[50] = L"����ע��";
	set_button(1200, 800, 70, 40, ss0);
	set_button(1100, 850, 130, 40, ss3);
}

void Game::game_res()
{
	base_drawres();
	signup();
}
void Game::signup()
{
	//�˴�Ҫдһ�����Ĵ���
	// ������дͷ����
	//�˴���Ҫдһ��enter֮��������֮ǰ�������Ϣ
	//�����������ʽ
	//�ж�
	//������ȷ��Ϣ
	//ѡ��ͷ��
	//�ɹ�ע��
	char icname=' ';
	char icpwd = ' ';
	int posname=610, pospwd=610;
	std::string inname="";
	std::string inpwd="";
	while (icname != '\r')
	{
		if (_kbhit())
		{
		//	fillrectangle(600, 450, 900, 400);�û��������
	    //	fillrectangle(600, 600, 900, 550);���������
			icname = _getch();
			if (icname != '\r')
			{
				inname += icname;
				outtextxy(posname, 425, icname);
				posname += 10;
			}
		}
	}
	//�˴�ȱһ���û��������淶�ж�
	while (icpwd != '\r')
	{
		if (_kbhit())
		{
			icpwd = _getch();
			if (icpwd != '\r')
			{
				inpwd += icpwd;
				outtextxy(pospwd, 575, '*');
				pospwd += 10;
			}
		}
	}
	while (1)
	{
		int x, y;
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();
			x = msg.x;
			y = msg.y;
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				if (x >= 380 && x <= 410 && y >= 850 && y <= 880)
				{
					newavarnum = 0;
					break;
				}
				else if (x >= 480 && x <= 510 && y >= 850 && y <= 880)
				{
					chooseava();
					break;
				}
			}
		}
	}
	while (1)//�ȴ��û�����ύ
	{
		int x, y;
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();
			x = msg.x;
			y = msg.y;
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
			//	set_button(1200, 800, 70, 40, ss0);
				if (x >= 1200 && x <= 1270 && y >= 800 && y <= 840)
				{
					int newid = AccountManage.get_currentsize() + 1;
					//�˴�дһ�����ܲ�������������ܺ���뵽���ݿ⵱��
					char pwds[240] = "helloburningcanvas";
					for (int i = 0; i < inpwd.length(); i++)
						inpwd[i] ^= pwds[i];
					Player anewplayer(newid, inname, inpwd, newavarnum);
					AccountManage.Insert(anewplayer);
					HWND hnd = GetHWnd();
					MessageBox(hnd, _T("Successful sign-up!Now enjoy your game!"), _T("��ʾ"), MB_OKCANCEL);
					setCurrentPage(PAGE_HOME);
					//������ܺ��ٴ洢
					//����--->���ܲ���
					break;
				}
				//	set_button(1100, 850, 130, 40, ss3);
				else if (x >= 1100 && x <= 1230 && y >= 850 && y <= 890)
				{
					setfillcolor(WHITE);
					fillrectangle(600, 450, 900, 400);
					setfillcolor(WHITE);
					fillrectangle(600, 600, 900, 550);
					signup();
					break;
				}
			}
		}
	}
	//ʲôʱ���û������и��£�-->ע��+����һ��
	AccountManage.update();
}

void Game::game_rank()
{
	cleardevice();
	putimage(0, 0, &img);
	setbkmode(TRANSPARENT);
	settextstyle(60, 0, _T("����"));
	outtextxy(570, 30, _T("���а�"));
	TCHAR ss0[50] = L"������һ��";
	set_button(1100, 0, 150, 50, ss0);
	AccountManage.forrank();
	while(1)
	{
		int x, y;
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();
			x = msg.x, y = msg.y;
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				if (x >= 1100 && x <= 1250 && y >= 0 && y <= 50)
				{
					setCurrentPage(PAGE_LEVEL);
					break;
				}
			}
		}
	}
}

void Game::chooseava()
{
	while (1)
	{
		int x, y;
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();
			x = msg.x;
			y = msg.y;
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				if (x >= 150 && x <= 250 && y >= 250 && y <= 350)
				{
					newavarnum = 1;
					break;
				}
				else if (x >= 150 && x <= 250 && y >= 400 && y <= 500)
				{
					newavarnum = 2;
					break;
				}
				else if (x >= 150 && x <= 250 && y >= 550 && y <= 650)
				{
					newavarnum = 3;
					break;
				}
				else if (x >= 150 && x <= 250 && y >= 700 && y <= 800)
				{
					newavarnum = 4;
					break;
				}
			}
		}
	}
}

void Game::create_canvas_size()
{
	while (select_mode == 0)
	{
		int x, y;
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();
			x = msg.x;
			y = msg.y;
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				if (x >= 0 && x <= 100)//ѡ���Ѷ�
				{
					if (y >= 500 && y <= 550) size = 4;
					else if (y >= 575 && y <= 625) size = 6;
					else if (y >= 650 && y <= 700) size = 8;
					else if (y >= 725 && y <= 775) size = 12;
					for (int i = 0; i < size; i++)
					{
						for (int j = 0; j < size; j++)
						{
							setfillcolor(WHITE);
							fillrectangle(j * 30 + 700, (i + 1) * 30 + 500, (j + 1) * 30 + 700, i * 30 + 500);
							forcreate[i][j].setGrid(WHITE, 1);
						}
					}
					select_mode = 1;
				}
			}
		}
	}
}

void Game::leftrotate()
{
	for (int i = 0; i < size; i++)//��
		for (int j = 0; j < size; j++)//��
			tmp[i][j] = forcreate[j][size - 1 - i];

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			forcreate[i][j].setGrid(tmp[i][j].getColor(), tmp[i][j].getNumber());
		}
	}
}

bool Game::done()
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (forcreate[i][j].getNumber() != 1)return 0;
	return 1;
}

void Game::burning()
{

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			temp2[i][j].setGrid(forcreate[i][j].getColor(), 0);
		}
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			//temp1��¼����Ϊ1��>1�ķ���
			//temp2��¼��Ҫ�����ǵķ���
			//temp2�У�0��ʾû�б�����
			if (forcreate[i][j].getNumber() == 1)
			{
				temp1[i][j].setGrid(forcreate[i][j].getColor(), 0);//temp1��¼����Ϊ1�ķ���
			}
			else if (forcreate[i][j].getNumber() > 1)
			{
				temp1[i][j].setGrid(forcreate[i][j].getColor(), 1);//temp1��¼����>1�ķ���(��������)
				if (i != size - 1)
				{
					temp2[i + 1][j].setGrid(forcreate[i][j].getColor(), forcreate[i][j].getNumber() - 1);
				}
			}
		}
	}
	//�ϲ�temp1��temp2����
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{

			if (temp2[i][j].getNumber() != 0)//ԭ���ϲ㱻�ϲ㸲��
			{

				forcreate[i][j].setGrid(temp2[i][j].getColor(), temp2[i][j].getNumber());
			}
			else if (temp1[i][j].getNumber() == 0)
			{
				//ԭ���ϲ�Ϊ1��û�б��ϲ㸲�ǣ�do nothing
			   /*	gridArray[i][j].setGrid(gridArray[i][j].getColor(), 1);*/

			}
			else if (temp1[i][j].getNumber() == 1)
			{
				//ԭ���ϲ�>1��û�б��ϲ㸲�ǣ�
				forcreate[i][j].setGrid(temp1[i][j].getColor(), 1);
			}
		}
	}
}
