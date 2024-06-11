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
    void leftrotate();//����
    void rightrotate();//����
    void burn();//����
    void burning(int t);
    int gettotalburn();
    void addtotalburn();
    void removetotal();
    void cleartotalburn();
    void quash();//����
    Grid* getactcanva(int x);//���ڱȽ�
    bool done();//���з���������Ϊ1ʱ�����棬��֮false
    void reset(int size,int questionnumber);//���û���
    Grid* randcreate_q();//�������������Ŀ,����Ҫ������⵱��
    int getSize();
    void setSize(int s);
    void set_qnumber(int x);
    int get_qnumber();
    void generate_canva();//���������Ŀ���ɻ���
    void hide();
    void checkhint();//�鿴��ʾ
    void showhints();
    void showhintnumber();
    void reparam();
    void copyinit();
    void set_inithinnum();
private:
    void copy_record(int size,int total);
    void reduce_hintnum(int level);
private:
    Grid gridArray[12][12];//��������
    Grid tmp[12][12];//������������ʱ�洢
    int size;//������С
    Grid temp1[12][12];//��¼����ǰ���ϲ���>1�ķ���
    Grid temp2[12][12];//��¼Ҫ�����ǵķ���
    int totalburn;//���ȴ���
    std::array<Grid[12][12],50>previous;//��¼ÿһ�μ���ǰ�Ļ���
    int qnumber;//��¼ѡ���ĵ���
    int hintnumber[4];
    Grid hint1[12][12];
    Grid hint2[12][12];
    Grid record[12][12];//���������Ŀ����¼�������Ŀ
    //��¼��ʾ��������ͬ�Ѷ���ʾ������һ��
    //easyģʽ��һ����ʾ
    //middleģʽ��������ʾ
    //hardģʽ��������ʾ
    //expertģʽ�������ʾ
    //��ʾ�������Զ�̬��ʾ�ڲ鿴��ʾ����
    //��ʾ������Ϊ0ʱ��죡
};