#include "KD_Tree.h"
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include <windows.h>  
#include <time.h>
#include <algorithm>
#include <iostream>
#include <cmath>
using namespace std;
int len[4];

void main() {
	// ׼����������
	pointVec points,npoints;
	/*
	points.push_back(new sPoint(7, 2));
	points.push_back(new sPoint(2, 3));
	points.push_back(new sPoint(4, 7));
	points.push_back(new sPoint(5, 4));
	points.push_back(new sPoint(9, 6));
	points.push_back(new sPoint(8, 1));
	*/
	// ���ú�������KD_Tree
	int x=0,y=0; int res[2] = { -1,-1 };
	//freopen("data1.txt", "r", stdin);//10^6
	freopen("in.txt", "r", stdin);

	//freopen("C:\\Users\\�ᳬ\\Desktop\\num\\data2.txt", "r", stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
	//freopen("out.txt", "w", stdout);
	freopen("out1.txt", "w", stdout);
	//freopen("slowout.txt", "w", stdout);
	clock_t  clockBegin, clockEnd;
	clockBegin = clock();
	//freopen("in.txt", "r", stdin); //����ض���������ݽ�����out.txt�ļ���
	
	int agentPos[2];
	scanf("%d %d", &agentPos[0], &agentPos[1]);
	//cout<< agentPos[0] << agentPos[1] <<endl;
	while (~(scanf("%d %d",&x,&y)))//&&x!=-1&&y!=-1)
	{
		//npoints.push_back(new sPoint(x,y));
		points.push_back(new sPoint(x, y));
	}
	//new_pei(npoints,points,agentPos);
	sPoint* root = 	buildKdTree(points, 0);
	// ����������
	outputKDTree(root, 0, "root");

	// �������ڽ���ѯ
	//int agentPos[2] = { 10,10 }, 
	
	innerGetClosest(root, agentPos, res);
	cout<<"Result X:"<<res[0]<<"Y: "<<res[1]<<endl;
	double d = sqrt((res[0]-agentPos[0])* (res[0] - agentPos[0])+ (res[1] - agentPos[1])* (res[1] - agentPos[1]));
	cout<<"Distance is "<<d<<endl;
	double md = abs(res[0] - agentPos[0])  + abs(res[1] - agentPos[1]);
	cout << "Manhattan distance is"<<md<<endl;
	// ����̬�ڴ�
	for (size_t index = 0; index < points.size();index++){
		delete points[index]; points[index] = 0;
	}points.clear();

	// �˳�
	//cout << "\n ������˳�";
	//int input = 0;
	//cin >> input;
	clockEnd = clock();
	printf("using time:%d\n", clockEnd - clockBegin);
}