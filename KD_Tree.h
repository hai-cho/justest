#ifndef KT_TREE_H
#define KT_TREE_H

#include <vector>

using namespace std;
struct sPoint{
public:
	sPoint(const int &x, const int &y) {
		pos[0] = x;
		pos[1] = y;
		lChild = 0;
		rChild = 0;
	}
	sPoint *lChild, *rChild;
	int pos[2];
};
typedef vector<sPoint*> pointVec;

// ����KD��
sPoint* buildKdTree(pointVec& points,const int &depth);
// ���KD��
void outputKDTree(const sPoint * root,const int &depth,const char* lr);
// K�ٽ���ѯ(Ĭ��Ϊ���ڽ���ѯ)
void innerGetClosest(sPoint* root,// �ѹ�����KD��
	const int point[2],   // agent��ǰλ��
	int res[2], // ��ѯ���
	int depth=0,
	int minDis=-1 // ��ǰ��ѯ��������㵽agent����λ�õľ���
);
void biserch(pointVec points, int xy, int x, int& l, int& r);
void new_pei(pointVec& points, pointVec& outpoints, int* agentPos);


#endif
