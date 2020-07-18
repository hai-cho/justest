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
	// 1- �ж�KD���Ĺ��������Ƿ񵽴�Ҷ�ӽڵ�
	if (points.empty()) {
		// ����KD���ѵ���Ҷ�ӽڵ㣬���ؿ�ֵ
		return 0;
	}
	// 2- �жϵ�ǰӦ��ѡ���ĸ�ά��(0:x��;1:y��)
	int cutting_dim = depth % 2;
	// 3- ȷ����λ��
	int medium_index = (int)points.size() / 2;
	// 4- �Ե�ǰ�����ڵ�������򣬶����ȡ��ǰ�����ĸ��ڵ�
	sortPoints(points, cutting_dim);
	sPoint* node = points[medium_index];
	// 5- ��points�з���node��������Ľڵ��γ��µ��ӽڵ㼯��
	pointVec lVec, rVec;
	getLChildPoints(points, medium_index, lVec);
	getRChildPoints(points, medium_index, rVec);
	// 6- ������������KD������ֵ����ǰ���ڵ�
	node->lChild = buildKdTree(lVec, depth + 1);
	node->rChild = buildKdTree(rVec, depth + 1);
	// 7 ����
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

void innerGetClosest(sPoint* root,// �ѹ�����KD��
	const int point[2],   // agent��ǰλ��
	int res[2], // ��ѯ���
	int depth, // ��ǰ���
	int minDis // ��ǰ��ѯ��������㵽agent����λ�õľ���
){
	// ��ǰ���ҵ�KD����Ϊ�գ������Ѳ��ҵ��Ľ������
	if (root==0)return;  
	// ����agent���굽��ǰ�ڵ�ĺ��ݾ���
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
	//���ֲ���ֵ���������ڵ�����
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
	biserch(points, 0, x, l, r); //x�����ٽ������ҵ�
	tpoi.push_back(points[l]);
	tpoi.push_back(points[r]);//�����ҵ�ѹ��ջ
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
	//�õ��ĸ�������̾��룬��Բ�뾶����Բ������������
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
			)//��Բ������������֮�ڵĵ�ѹ��ջ
		{
			outpoints.push_back(points[i]);
			cnt++;
		}
	}
	cout << "cnt is" << cnt << endl;
	if (cnt == 0)//����������޵㣬��֮ǰ�������ѹ��ջ��
	{
		outpoints.push_back(tpoi[flg]);
	}
}