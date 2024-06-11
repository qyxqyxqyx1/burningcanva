#pragma once
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <easyx.h>
#include <graphics.h>
#include <iostream>
#include "Grid.h"
#include <array>
#include <vector>
class ActionCanva 
{
public:
    ActionCanva();
    void draw();//draw gridArray
    void leftrotate();//左旋
    void rightrotate();//右旋
    void burn();//加热
    void burning(int t);
    int gettotalburn();
    void addtotalburn();
    void removetotal();
    void cleartotalburn();
    void quash();//撤销
    Grid* getactcanva(int x);//用于比较
    bool done();//所有方格颜料数为1时返回真，反之false
    void reset(int size,int questionnumber);//重置画布
    Grid* randcreate_q();//用于生成随机题目,并且要存入题库当中
    int getSize();
    void setSize(int s);
    void set_qnumber(int x);
    int get_qnumber();
    void generate_canva();//根据题库题目生成画布
    void hide();
    void checkhint();//查看提示
    void showhints();
    void showhintnumber();
    void reparam();
    void copyinit();
    void set_inithinnum();
private:
    void copy_record(int size,int total);
    void reduce_hintnum(int level);
private:
    Grid gridArray[12][12];//操作画布
    Grid tmp[12][12];//左旋，右旋临时存储
    int size;//画布大小
    Grid temp1[12][12];//记录加热前颜料层数>1的方格
    Grid temp2[12][12];//记录要被覆盖的方格
    int totalburn;//加热次数
    std::array<Grid[12][12],50>previous;//记录每一次加热前的画布
    int qnumber;//记录选的哪道题
    int hintnumber[4];
    Grid hint1[12][12];
    Grid hint2[12][12];
    Grid record[12][12];//随机生成题目，记录最初的题目
    //记录提示次数，不同难度提示次数不一样
    //easy模式：一次提示
    //middle模式：两次提示
    //hard模式：三次提示
    //expert模式：五次提示
    //提示次数可以动态显示在查看提示框下
    //提示次数变为0时标红！
};