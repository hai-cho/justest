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

// 构建KD树
sPoint* buildKdTree(pointVec& points,const int &depth);
// 输出KD树
void outputKDTree(const sPoint * root,const int &depth,const char* lr);
// K临近查询(默认为最邻近查询)
void innerGetClosest(sPoint* root,// 已构建的KD树
	const int point[2],   // agent当前位置
	int res[2], // 查询结果
	int depth=0,
	int minDis=-1 // 当前查询到的最近点到agent坐标位置的距离
);
void biserch(pointVec points, int xy, int x, int& l, int& r);
void new_pei(pointVec& points, pointVec& outpoints, int* agentPos);


#endif
