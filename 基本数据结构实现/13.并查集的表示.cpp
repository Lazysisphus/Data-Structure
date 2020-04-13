/*
集合的表示及查找

并查集
    把集合并起来，然后查某个元素属于什么集合

    例子：
        有 10 台电脑，然后某些电脑之间直接相连
        问：某两台不是直接相连的电脑是否存在连接？
    解决思路：
        （1）将10台电脑看成10个集合{1}，{2}，{3}，...，{10}
        （2）如果两台电脑存在连接，就将两台电脑属于的集合并在一起
        （3）查询两台电脑是否连接，就是判别他们是否属于同一集合

    可以用树结构表示集合，树的每个结点表示一个集合元素
        （1）使用链表存储：树使用双亲表示法，孩子指向双亲
        （2）使用数组存储，采用结构体，存储结点的值和双亲下标
*/

#include<iostream>
#include<cstring>
#define MaxSize 10
using namespace std;

typedef int ElementType;
typedef struct{
	ElementType Data; // 存值
	int parent;       // 指向父结点在数组中的下标
}SetType;

// 查找某个元素所在的集合，该集合用树的根结点表示
int Find(SetType s[], ElementType x)
{
	int i;
	// 找到数组中该值对应的下标
	for(i=0; i<MaxSize&&s[i].Data!=x; i++);
	if(i >= MaxSize) // 如果没有找到，返回 -1
		return -1;
	// 找到该结点的根结点
	for(; s[i].parent>=0; i=s[i].parent);
	return i; // 返回根结点在数组 s 中的下标
}

// 并
void Union(SetType s[], ElementType x1, ElementType x2)
{
	int root1 = Find(s, x1); // 找到 x1 的根结点下标
	int root2 = Find(s, x2); // 找到 x2 的根结点下标
	// 如果根结点的下标不同，说明不是一个集合
	if(root1 != root2)
    {
		s[root1].parent = root2; // 把 x1 挂到 x2 的集合
	}
}

int main()
{
	SetType s[MaxSize];
	// 初始化数组，父结点全部指向 -1
	for(int i=0; i<MaxSize; i++)
    {
		s[i].Data = i + 1;
		s[i].parent = -1;
	}
    // 如果父结点指向 -1，该节点所属集合是其自身的下标
	cout<<Find(s, 5)<<endl; // 4
	Union(s, 3, 5);
	cout<<Find(s, 4)<<endl; // 3
	cout<<Find(s, 3)<<endl; // 4
	Union(s, 1, 3); // {1, 3, 5}
	Union(s, 2, 4); // {2, 4}
	Union(s, 8, 6); // {8, 6}
	cout<<Find(s, 6)<<endl; // 5
	cout<<Find(s, 8)<<endl; // 5
	return 0;
}
