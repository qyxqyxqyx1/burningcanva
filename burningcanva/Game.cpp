#include "Game.h"
#include <ctime>
#include <string>
#include <conio.h>
//getch():不是easyx函数,用于获取键盘消息
//GetAsyncKeyState(键值)：
IMAGE img;
IMAGE win;
IMAGE chdefaultava;
IMAGE chava1;
IMAGE chava2;
IMAGE chava3;
IMAGE chava4;
//使用HiEasyX;将所有的绘图代码部分加上那两行，且不要将无关代码放入其中-->失败
COLORREF colors[60] = { 235,29,29,252,144,50,255,255,0,34,139,34,
				   64,224,208,0,0,255,75,0,130,128,0,128,255,20,147,115,74,18,252,224,203 };
Game::Game()
{
	setCurrentPage(PAGE_HOME);
	calculate();//统计题库现在有多少道题
	accountcalculate();//用户信息录入系统
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


void Game::game_home()//主页
{
	draw_homepage();//画主页
	do_homepage();//主页操作
}

void Game::draw_homepage()
{
	loadimage(&img, _T("gdygbk.bmp"), 1300, 900);
	putimage(0, 0, &img);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(120, 100, _T("宋体"));
	outtextxy(270, 70, _T("燃烧的画"));
	TCHAR ss1[50] = L"登录";
	TCHAR ss2[50] = L"注册";
	set_button(500, 600, 170, 50, ss1);
	set_button(500, 700, 170, 50, ss2);

}
//此处缺提交写一个确认提交的按钮
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

				if (x >= 500 && x <= 670 && y >= 600 && y <= 650)//登录
				{
					login();
					//需要记录当前谁登录了，用于计分
					setCurrentPage(PAGE_LEVEL);
					break;
				}
				else if (x >= 500 && x <= 670 && y >= 700 && y <= 750)//注册
				{
					setCurrentPage(PAGE_RES);
					break;
				}
			}
		
		}
	}
}

void Game::game_level()//难度选择页
{
	draw_levelpage();//画游戏难度选择页
	do_gamelevel();//在此页上执行操作
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
	TCHAR ss1[50] = L"简单模式";
	TCHAR ss2[50] = L"中等模式";
	TCHAR ss3[50] = L"困难模式";
	TCHAR ss4[50] = L"专家模式";
	TCHAR ss5[50] = L"查看排行榜";
	TCHAR ss6[50] = L"返回上一级";
	TCHAR ss7[50] = L"创造题目";
	//此处缺一个能看排行榜的代码
	set_button(500, 200, 200, 50, ss1);
	set_button(500, 300, 200, 50, ss2);//更改了按钮位置
	set_button(500, 400, 200, 50, ss3);
	set_button(500, 500, 200, 50, ss4);
	set_button(500, 600, 200, 50, ss5);
	set_button(800, 0, 200, 50, ss6);
	set_button(500, 700, 200, 50, ss7);
}

void Game::gamelevel_rules()
{
	settextstyle(20, 0, _T("微软雅黑"));//需要更改下字体
	outtextxy(20, 20, _T("规则如下："));
	outtextxy(20, 40, _T("1.每个的数字代表该层颜料的层数"));
	outtextxy(20, 60, _T("2.加热：当颜料层数>1时，该层颜料向下流动，覆盖下层，"));
	outtextxy(20, 80, _T("所有颜料层数相应改变;当颜料层数=1时，"));
	outtextxy(20, 100, _T("该层颜料不再流动"));
	outtextxy(20, 120, _T("你的目标：复原目标画布"));
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
					setCurrentPage(PAGE_HOME);//回到主页
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

void Game::game_play()//玩游戏页
{
	draw_gameplay();
	start_gameplay();//点击开始游戏按钮
	do_gameplay();//只要没提交一直玩
	judge_gameplay();//提交之后，判断
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
	TCHAR ss1[50] = L"左旋";
	TCHAR ss2[50] = L"右旋";
	TCHAR ss3[50] = L"加热";
	TCHAR ss4[50] = L"撤销";
	TCHAR ss5[50] = L"开始游戏";
	TCHAR ss10[50] = L"查看提示";
	TCHAR ss6[50] = L"提交";
	TCHAR ss7[50] = L"返回上一级";
	TCHAR ss8[50] = L"再来一局";
	TCHAR ss9[50] = L"重玩这局";
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
	settextstyle(15, 0, _T("宋体"));
	outtextxy(1150, 130, _T("剩余提示次数："));
}

void Game::canva_drawplay()
{

	act.setSize(level);
	tar.set_size(level);

	//如果是1，从题库中抽题，如果是0，自动生成题目存到文件中
	set_selectq();
	if (get_selectq() == 1)
	{
		set_QuestionNumber(level);//随机抽取题号
		act.set_qnumber(get_QuestionNumber());//将题目告知操作画布
		tar.set_Questionnumber(get_QuestionNumber());//将题目告知目标画布
		act.generate_canva();//操作画布生成图形
		tar.generate_canva();//目标画布生成图形
	}
	else
	{
		if (level == 4) qtotnumber[0]++, act.set_qnumber(qtotnumber[0]), tar.set_Questionnumber(qtotnumber[0]);
		else if (level == 6) qtotnumber[1]++, act.set_qnumber(qtotnumber[1]), tar.set_Questionnumber(qtotnumber[1]);
		else if (level == 8) qtotnumber[2]++, act.set_qnumber(qtotnumber[2]), tar.set_Questionnumber(qtotnumber[2]);
		else if (level == 12) qtotnumber[3]++, act.set_qnumber(qtotnumber[3]), tar.set_Questionnumber(qtotnumber[3]);
		tar.receive_canva(act.randcreate_q());//自动生成题目，并且将一起生成的答案传递给目标画布tar
		std::fstream o("ttt.txt",std::ios::app);

		//对应画布缺一个写入文件的代码
		//此处缺一个更新题库数量
		//可以不写题库！
	}
	//点击游戏开始前，应该遮住操作画布
	act.hide();
	tar.draw();//画目标画布
}


void Game::start_gameplay()
{
	while (1)//点击游戏开始
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
					act.draw();//点击游戏开始后，再展现操作画布
					act.copyinit();
					act.showhintnumber();
					break;
				}
		}
	}
}

void Game::do_gameplay()
{
	while (1)//只要用户没有提交，就一直可以进行操作
	{
		keyEvent();
		if (get_submit() == 1) break;
	}
}

void Game::judge_gameplay()
{
	int sign = 1;
	for (int i = 0; i < level; i++)//检查是否成功还原了画布
	{    //一行行比较.第i行
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
			//目标画布
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
		//将当前更新的局数记录到后台
		AccountManage.add_won(level, currentPlayer);
		AccountManage.add_total(currentPlayer);
		HWND hnd = GetHWnd();
		MessageBox(hnd, _T("You Win:-)"), _T("提示"), MB_OKCANCEL);
	}
	else if (sign == 0)
	{
		AccountManage.add_total(currentPlayer);
		HWND hnd = GetHWnd();
		MessageBox(hnd, _T("You lose:-("), _T("提示"), MB_OKCANCEL);
	}
	//更新到文件当中
	AccountManage.update();
	act.cleartotalburn();
}

void Game::re_game()
{
	while (1)
	{
		int x, y;
		if (MouseHit())//检测鼠标
		{
			MOUSEMSG msg = GetMouseMsg();//接收信息
			x = msg.x;
			y = msg.y;
			if (msg.uMsg == WM_LBUTTONDOWN)//若信息等于点击	
			{
				if (x >= 1200&& x <= 1300 && y >= 250 && y <= 300)
				{
					setCurrentPage(PAGE_LEVEL);
					break;
				}
				else if (x >= 1200 && x <= 1300 && y >= 350 && y <= 400)
				{
					game_play();//再来一局
					break;
				}
				else if (x >= 1200 && x <= 1300 && y >= 450 && y <= 500)//重玩
				{
					set_submit(0);
					act.reset(get_level(), get_QuestionNumber());//题号
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
	//1.画图
	base_create();

	//2.用户确定难度矩阵
	select_mode = 0;
	create_canvas_size();

	//3.用户设计并提交难度矩阵:填充+撤销+提交
	posi = -1, posj = -1;
	create_submit = 0;
	satisfy = 0;
	create_input();//提交存储到actmode文件当中
	if (size == 4) qtotnumber[0]++;
	else if (size == 6) qtotnumber[1]++;
	else if (size == 8) qtotnumber[2]++;
	else if (size == 12) qtotnumber[3]++;

	//4.随机生成答案,存到hint当中
	int x=-20;
	std::fstream forans;//存答案用
	if (size == 4) x=qtotnumber[0],forans.open("easyhint.txt", std::ios::app);
	else if (size == 6) x = qtotnumber[1], forans.open("middlehint.txt", std::ios::app);
	else if (size== 8) x = qtotnumber[2], forans.open("middlehint.txt", std::ios::app);
	else if (size== 12) x = qtotnumber[3], forans.open("experthint.txt", std::ios::app);
	if (!forans)
	{
		std::cerr << "File could not be opened" << std::endl;
		exit(EXIT_FAILURE);
	}

	forans << x << std::endl;//先存入题号

	//2.题目加工得到答案
	while (!done())//只要有不为1的，说明还需要加热
	{
		//将生成答案的过程(包括初始画布)存入文件当中
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
		burning();//对forcreate数组burning
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
			forans << r << ' ' << g << ' ' << b << ' ' << forcreate[i][j].getNumber() << std::endl;//最后一步答案不想存到QBank当中了...
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
	TCHAR s1[] = L"宋体";
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

void Game::keyEvent()//用户进行左旋，右旋，加热，撤销的操作
{
	int x, y;
	while (1)//等待用户输入
	{
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();
			x = msg.x;
			y = msg.y;
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				if (x >= 1050 && x <= 1150 && y >= 700 && y <= 750)//左旋
				{

					act.leftrotate();
					act.draw();
				}
				else if (x >= 1200 && x <= 1300 && y >=700 && y <= 750)//右旋
				{
					act.rightrotate();
					act.draw();
				}
				else if (x >= 1050 && x <= 1150 && y >= 800 && y <= 850)//加热
				{
					act.burn();
					act.draw();
				}
					
				else if (x >= 1200 && x <= 1300 && y >= 800 && y <= 850)//撤销
				{
					act.quash();
					act.draw();
				}
				else if (x >= 1200 && x <= 1300 && y >= 150 && y <= 200)//提交
				{
					set_submit(1);
					act.reparam();
				}
				else if (x >= 1200 && x <= 1300 && y >= 75 && y <= 125)//查看提示
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
	if (getline(Num, templine))//如果有行，说题库有题了
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
	settextstyle(60, 40, _T("宋体"));
	outtextxy(100, 70, _T("创造属于自己的题目吧!"));
	settextstyle(20, 0, _T("宋体"));
	outtextxy(20, 200, _T("你可以做的"));
	outtextxy(20, 220, _T("1.你可以选择自己喜欢的颜色和数字"));
	outtextxy(20, 240, _T("2.你可以画出自己想要的操作画布"));
	outtextxy(20, 260, _T("3.我们可以为你生成一个相对没美观的目标画布"));
	outtextxy(20, 280, _T("您创造的题目将会加入到我们的题库当中"));
    setbkmode(TRANSPARENT);
	TCHAR ss1[50] = L"简单模式";
	TCHAR ss2[50] = L"中等模式";
	TCHAR ss3[50] = L"困难模式";
	TCHAR ss4[50] = L"专家模式";
	TCHAR ss5[50] = L"提交";
	TCHAR ss6[50] = L"撤销";
	TCHAR ss7[50] = L"返回到上一级";
	TCHAR ss8[50] = L"切换到游戏界面";
	set_button(0, 500, 100, 50, ss1);
	set_button(0, 575, 100, 50, ss2);
	set_button(0, 650, 100, 50, ss3);
	set_button(0, 725, 100, 50, ss4);
	set_button(0, 800, 100, 50, ss5);
	set_button(200, 500, 100, 50, ss6);
	set_button(900, 0, 100, 50, ss7);
	set_button(900, 75, 100, 50, ss8);

	COLORREF colors[60] = { 0,245,255,78,238,148,0,139,69,238,238,0,
					   238,173,14,255,106,106,255,127,0,255,20,147,255,187,255,0,0,128 };//10种颜色
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
		//难点：如何根据创造的题目生成?-->似乎已经解决，现在代码实现
		int x, y;
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();
			x = msg.x;
			y = msg.y;
			if (msg.uMsg == WM_LBUTTONDOWN)
			{

				COLORREF colo;
				//1.提交并成功
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
					MessageBox(hnd, _T("Success submit :-)"), _T("提示"), MB_OKCANCEL);
					create_submit = 1;
					openbank << '\n';
				}
				//2.提交并失败
				else if (x >= 0 && x <= 100 && y >= 800 && y <= 850 && !checkcreate())
				{
					HWND hnd = GetHWnd();
					MessageBox(hnd, _T("You don't finish :-("), _T("提示"), MB_OKCANCEL);
				}
				//3.撤销
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
				//4.选择了不同颜色，放到图当中
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
		//substr:第一个参数是开始位置，第二个是长度
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
		Player tmp(id, name, pwd, avatmp,easywon,middlewon,hardwon,expertwon,tot);//提取出文件中的所有账号
		AccountManage.Insert(tmp);//将账号都存入到hashtable当中
	}
	foracc.close();
}

void Game::login()
{
	//此处要写一个光标的代码
    // 光标可以写头像吗？
    //此处还要写一个enter之后可以清空之前输入的信息
	//判定
	//返回正确or错误信息，更新标红
	settextstyle(20, 0, _T("宋体"));
	outtextxy(0, 300, _T("请输入您的用户名"));
	settextstyle(20, 0, _T("宋体"));
	outtextxy(0, 450, _T("请输入您的密码"));
	while (1)
	{
		//加密目的显而易见，数据库中的密码都是保密的，无法被破解
		//异或加密
		char icname = ' ';
		char icpwd = ' ';
		int posname = 60, pospwd = 60;
		std::string inname = "";
		std::string inpwd = "";
		setfillcolor(WHITE);
		fillrectangle(50, 400, 350, 350);//
		setfillcolor(WHITE);
		fillrectangle(50, 525, 350, 475);//输入密码的框
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
		//2.玩家输入密码
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
		//3. 密码加密
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
			//通过用户成功登录的密码和账户，在后台找到该用户信息，并记录在currentPlayer当中
			currentPlayer = AccountManage.get_nowplayerinfo(currentplayer);
			MessageBox(hnd, _T("Successful login! Now enjoy yourself in game"), _T("提示"), MB_OKCANCEL);
			setCurrentPage(PAGE_LEVEL);
			break;
		}
		else
		{
			HWND hnd = GetHWnd();
			MessageBox(hnd, _T("Your name or password input is wrong.\n Please input again"), _T("提示"), MB_OKCANCEL);
		}
	}
}

void Game::base_drawres()
{
	cleardevice();
	putimage(0, 0, &img);
	setbkmode(TRANSPARENT);
	settextstyle(20, 0, _T("宋体"));
	outtextxy(600, 350, _T("请在下方输入您的用户名(输入完成后要点击enter):"));
	setfillcolor(WHITE);
	fillrectangle(600, 450,900, 400);
	settextstyle(20, 0, _T("宋体"));
	outtextxy(600, 500, _T("请在下方输入您的密码(输入完成后要点击enter):"));
	setfillcolor(WHITE);
	fillrectangle(600, 600, 900, 550);
	settextstyle(20, 0, _T("宋体"));
	outtextxy(100, 200, _T("请选择您的头像:"));
	putimage(150, 250, &chava1);
	putimage(150, 400, &chava2);
	putimage(150, 550, &chava3);
	putimage(150,700, &chava4);
	setbkmode(TRANSPARENT);
	settextstyle(20, 0, _T("宋体"));
	outtextxy(150, 850, _T("是否选择默认头像？"));
	outtextxy(900, 0, _T("Tips:"));
	outtextxy(900, 20, _T("请先填写用户名和密码"));
	outtextxy(900, 50, _T("如果想重新填写信息，请先将所有信息"));
	outtextxy(900, 80, _T("填写完整后点击重新注册"));
	TCHAR ss1[50] = L"是";
	TCHAR ss2[50] = L"否";
	set_button(380, 850, 30, 30, ss1);
	set_button(480, 850, 30, 30, ss2);
	TCHAR ss0[50] = L"提交";
	TCHAR ss3[50] = L"重新注册";
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
	//此处要写一个光标的代码
	// 光标可以写头像吗？
	//此处还要写一个enter之后可以清空之前输入的信息
	//密码的正则表达式
	//判定
	//返回正确信息
	//选择头像
	//成功注册
	char icname=' ';
	char icpwd = ' ';
	int posname=610, pospwd=610;
	std::string inname="";
	std::string inpwd="";
	while (icname != '\r')
	{
		if (_kbhit())
		{
		//	fillrectangle(600, 450, 900, 400);用户名输入框
	    //	fillrectangle(600, 600, 900, 550);密码输入框
			icname = _getch();
			if (icname != '\r')
			{
				inname += icname;
				outtextxy(posname, 425, icname);
				posname += 10;
			}
		}
	}
	//此处缺一个用户名命名规范判定
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
	while (1)//等待用户点击提交
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
					//此处写一个加密操作，将密码加密后存入到数据库当中
					char pwds[240] = "helloburningcanvas";
					for (int i = 0; i < inpwd.length(); i++)
						inpwd[i] ^= pwds[i];
					Player anewplayer(newid, inname, inpwd, newavarnum);
					AccountManage.Insert(anewplayer);
					HWND hnd = GetHWnd();
					MessageBox(hnd, _T("Successful sign-up!Now enjoy your game!"), _T("提示"), MB_OKCANCEL);
					setCurrentPage(PAGE_HOME);
					//密码加密后再存储
					//加密--->解密操作
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
	//什么时候用户数会有更新？-->注册+玩完一局
	AccountManage.update();
}

void Game::game_rank()
{
	cleardevice();
	putimage(0, 0, &img);
	setbkmode(TRANSPARENT);
	settextstyle(60, 0, _T("宋体"));
	outtextxy(570, 30, _T("排行榜"));
	TCHAR ss0[50] = L"返回上一级";
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
				if (x >= 0 && x <= 100)//选择难度
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
	for (int i = 0; i < size; i++)//列
		for (int j = 0; j < size; j++)//行
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
			//temp1记录数字为1和>1的方格
			//temp2记录需要被覆盖的方格
			//temp2中，0表示没有被覆盖
			if (forcreate[i][j].getNumber() == 1)
			{
				temp1[i][j].setGrid(forcreate[i][j].getColor(), 0);//temp1记录数字为1的方格
			}
			else if (forcreate[i][j].getNumber() > 1)
			{
				temp1[i][j].setGrid(forcreate[i][j].getColor(), 1);//temp1记录数字>1的方格(被加热了)
				if (i != size - 1)
				{
					temp2[i + 1][j].setGrid(forcreate[i][j].getColor(), forcreate[i][j].getNumber() - 1);
				}
			}
		}
	}
	//合并temp1和temp2数组
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{

			if (temp2[i][j].getNumber() != 0)//原颜料层被上层覆盖
			{

				forcreate[i][j].setGrid(temp2[i][j].getColor(), temp2[i][j].getNumber());
			}
			else if (temp1[i][j].getNumber() == 0)
			{
				//原颜料层为1且没有被上层覆盖：do nothing
			   /*	gridArray[i][j].setGrid(gridArray[i][j].getColor(), 1);*/

			}
			else if (temp1[i][j].getNumber() == 1)
			{
				//原颜料层>1且没有被上层覆盖：
				forcreate[i][j].setGrid(temp1[i][j].getColor(), 1);
			}
		}
	}
}
