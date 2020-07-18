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
	// 准备测试数据
	pointVec points,npoints;
	/*
	points.push_back(new sPoint(7, 2));
	points.push_back(new sPoint(2, 3));
	points.push_back(new sPoint(4, 7));
	points.push_back(new sPoint(5, 4));
	points.push_back(new sPoint(9, 6));
	points.push_back(new sPoint(8, 1));
	*/
	// 调用函数构建KD_Tree
	int x=0,y=0; int res[2] = { -1,-1 };
	//freopen("data1.txt", "r", stdin);//10^6
	freopen("in.txt", "r", stdin);

	//freopen("C:\\Users\\裴超\\Desktop\\num\\data2.txt", "r", stdin); //输入重定向，输入数据将从in.txt文件中读取
	//freopen("out.txt", "w", stdout);
	freopen("out1.txt", "w", stdout);
	//freopen("slowout.txt", "w", stdout);
	clock_t  clockBegin, clockEnd;
	clockBegin = clock();
	//freopen("in.txt", "r", stdin); //输出重定向，输出数据将保存out.txt文件中
	
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
	// 输出构建结果
	outputKDTree(root, 0, "root");

	// 测试最邻近查询
	//int agentPos[2] = { 10,10 }, 
	
	innerGetClosest(root, agentPos, res);
	cout<<"Result X:"<<res[0]<<"Y: "<<res[1]<<endl;
	double d = sqrt((res[0]-agentPos[0])* (res[0] - agentPos[0])+ (res[1] - agentPos[1])* (res[1] - agentPos[1]));
	cout<<"Distance is "<<d<<endl;
	double md = abs(res[0] - agentPos[0])  + abs(res[1] - agentPos[1]);
	cout << "Manhattan distance is"<<md<<endl;
	// 清理动态内存
	for (size_t index = 0; index < points.size();index++){
		delete points[index]; points[index] = 0;
	}points.clear();

	// 退出
	//cout << "\n 任意键退出";
	//int input = 0;
	//cin >> input;
	clockEnd = clock();
	printf("using time:%d\n", clockEnd - clockBegin);
}