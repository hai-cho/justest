#include "KD_Tree.h"
#include <algorithm>
#include<math.h>
#include <iostream>

void getLChildPoints(pointVec& points, const int medium_index, pointVec& lVec) {
	pointVec::iterator index1 = points.begin(), index2 = points.begin() + medium_index;
	pointVec tempVec(index1, index2);
	lVec = tempVec;
}

void getRChildPoints(pointVec& points, const int medium_index, pointVec& rVec) {
	int offset = (int)points.size() - medium_index - 1;
	pointVec::iterator index1 = points.end() - offset , index2 = points.end();
	pointVec tempVec(index1, index2);
	rVec = tempVec;
}

bool x_comp(const sPoint *a, const sPoint *b) {
	return a->pos[0] < b->pos[0];
}

bool y_comp(const sPoint *a, const sPoint *b) {
	return a->pos[1] < b->pos[1];
}

void sortPoints(pointVec& points,const int cutting_dim) {
	if (cutting_dim == 0)
		sort(points.begin(), points.end(), x_comp);
	if (cutting_dim == 1)
		sort(points.begin(), points.end(), y_comp);
}

sPoint* buildKdTree(pointVec& points, const int &depth) {
	// 1- 判断KD树的构建过程是否到达叶子节点
	if (points.empty()) {
		// 构建KD树已到达叶子节点，返回空值
		return 0;
	}
	// 2- 判断当前应该选择哪个维度(0:x轴;1:y轴)
	int cutting_dim = depth % 2;
	// 3- 确定中位数
	int medium_index = (int)points.size() / 2;
	// 4- 对当前子树节点进行排序，而后获取当前子树的根节点
	sortPoints(points, cutting_dim);
	sPoint* node = points[medium_index];
	// 5- 将points中分属node左右两侧的节点形成新的子节点集合
	pointVec lVec, rVec;
	getLChildPoints(points, medium_index, lVec);
	getRChildPoints(points, medium_index, rVec);
	// 6- 迭代生成左右KD树，赋值给当前根节点
	node->lChild = buildKdTree(lVec, depth + 1);
	node->rChild = buildKdTree(rVec, depth + 1);
	// 7 返回
	return node;
}

void outputKDTree(const sPoint * root,const int &depth, const char* lr) {
	if (root == 0)return;
	for (int index = 0; index < depth; index++)
		cout << " ";
	cout <<lr<< " layer = " << depth;
	cout << " pos = [" << root->pos[0] << "," << root->pos[1] << "]\n";
	outputKDTree(root->lChild, depth + 1, "left");
	outputKDTree(root->rChild, depth + 1, "right");
}

void innerGetClosest(sPoint* root,// 已构建的KD树
	const int point[2],   // agent当前位置
	int res[2], // 查询结果
	int depth, // 当前层次
	int minDis // 当前查询到的最近点到agent坐标位置的距离
){
	// 当前查找的KD子树为空，返回已查找到的结果数量
	if (root==0)return;  
	// 计算agent坐标到当前节点的横纵距离
	int deltaDis[2] = {abs(point[0] - root->pos[0]),abs(point[1] - root->pos[1]) };
	int nCurDis = deltaDis[0] + deltaDis[1];
	//int nCurDis = deltaDis[0]* deltaDis[0] + deltaDis[1]* deltaDis[1];
	if (minDis < 0 || nCurDis < minDis){
		minDis = nCurDis;
		for (int i = 0; i < 2; i++)res[i] = root->pos[i];
	}
	if ((depth%2==0) && point[0] <= root->pos[0] || (depth % 2 == 1) && point[1] <= root->pos[1])
		innerGetClosest(root->lChild, point, res, ++depth, minDis);
	else
		innerGetClosest(root->rChild, point, res, ++depth, minDis);
	int rang = deltaDis[depth % 2];
	if (rang > minDis)
		return;
	sPoint* pGoInto = root->lChild;
	if ((depth % 2 == 0) && point[0] > root->pos[0] || (depth % 2 == 1) && point[1] > root->pos[1])
		pGoInto = root->rChild;
	innerGetClosest(pGoInto, point, res,++depth,minDis);
}

//___
void biserch(pointVec points, int xy, int x, int& l, int& r)
{
	l = 0, r = points.size() - 1;
	int mid;
	while (l < r)
	{
		mid = (l + r) / 2;
		if (x <= points[mid]->pos[xy]) r = mid;
		else l = mid + 1;
	}
	if (points[l]->pos[xy] == x)
	{
		//cout << l << " ";
		l = 0, r = points.size() - 1;
		while (l < r) {
			mid = (l + r + 1) / 2;
			if (points[mid]->pos[xy] <= x)
				l = mid;
			else
				r = mid - 1;
		}
		//cout << r << endl;
	}
	//二分查找值，返回所在的区间
}


void new_pei(pointVec& points, pointVec& outpoints, int* agentPos)
{
	int l, r;
	pointVec tpoi;
	int x = agentPos[0];
	int y = agentPos[1];
	int res[2] = { -1,-1 };
	sortPoints(points, 0);  
	//sort(points.begin()+100, points.begin() +1000, x_comp);
	biserch(points, 0, x, l, r); //x坐标临近的左右点
	tpoi.push_back(points[l]);
	tpoi.push_back(points[r]);//将左右点压入栈
	sortPoints(points, 1);
	//sort(points.begin()+100, points.begin() + 1000, y_comp);
	biserch(points, 1, y, l, r);
	tpoi.push_back(points[l]);
	tpoi.push_back(points[r]);
	int len[4]; int flg=0,cnt=0;
	len[0] = (tpoi[0]->pos[0] - x) * (tpoi[0]->pos[0] - x) + (tpoi[0]->pos[1] - y) * (tpoi[0]->pos[1] - y);
	//cout<<"len0 is"<<len[0] <<endl;
	for (int i = 1; i < 4; i++)
	{
		if ((tpoi[i]->pos[0] - x) * (tpoi[i]->pos[0] - x) + (tpoi[i]->pos[1] - y) * (tpoi[i]->pos[1] - y) < len[0])
		{
			len[i] = (tpoi[i]->pos[0] - x) * (tpoi[i]->pos[0] - x) + (tpoi[i]->pos[1] - y) * (tpoi[i]->pos[1] - y);
			flg = i;
		}
	}
	//得到四个点中最短距离，作圆半径，作圆的外切正方形
	//cout << "flg is" << flg << endl;
	//cout<<"len is"<<len[flg] <<endl;
	double d = sqrt(len[flg]);
	cout << "length is" << d<< endl;
	for (int i = 0; i < points.size(); i++)
	{
		if (points[i]->pos[0] <= x + d
			&& points[i]->pos[0] >= x - d
			&& points[i]->pos[1] <= y + d
			&& points[i]->pos[1] >= y - d
			)//将圆的外切正方形之内的点压入栈
		{
			outpoints.push_back(points[i]);
			cnt++;
		}
	}
	cout << "cnt is" << cnt << endl;
	if (cnt == 0)//如果区域内无点，则之前的最近点压到栈里
	{
		outpoints.push_back(tpoi[flg]);
	}
}