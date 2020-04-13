/*
���ϵı�ʾ������

���鼯
    �Ѽ��ϲ�������Ȼ���ĳ��Ԫ������ʲô����

    ���ӣ�
        �� 10 ̨���ԣ�Ȼ��ĳЩ����֮��ֱ������
        �ʣ�ĳ��̨����ֱ�������ĵ����Ƿ�������ӣ�
    ���˼·��
        ��1����10̨���Կ���10������{1}��{2}��{3}��...��{10}
        ��2�������̨���Դ������ӣ��ͽ���̨�������ڵļ��ϲ���һ��
        ��3����ѯ��̨�����Ƿ����ӣ������б������Ƿ�����ͬһ����

    ���������ṹ��ʾ���ϣ�����ÿ������ʾһ������Ԫ��
        ��1��ʹ������洢����ʹ��˫�ױ�ʾ��������ָ��˫��
        ��2��ʹ������洢�����ýṹ�壬�洢����ֵ��˫���±�
*/

#include<iostream>
#include<cstring>
#define MaxSize 10
using namespace std;

typedef int ElementType;
typedef struct{
	ElementType Data; // ��ֵ
	int parent;       // ָ�򸸽���������е��±�
}SetType;

// ����ĳ��Ԫ�����ڵļ��ϣ��ü��������ĸ�����ʾ
int Find(SetType s[], ElementType x)
{
	int i;
	// �ҵ������и�ֵ��Ӧ���±�
	for(i=0; i<MaxSize&&s[i].Data!=x; i++);
	if(i >= MaxSize) // ���û���ҵ������� -1
		return -1;
	// �ҵ��ý��ĸ����
	for(; s[i].parent>=0; i=s[i].parent);
	return i; // ���ظ���������� s �е��±�
}

// ��
void Union(SetType s[], ElementType x1, ElementType x2)
{
	int root1 = Find(s, x1); // �ҵ� x1 �ĸ�����±�
	int root2 = Find(s, x2); // �ҵ� x2 �ĸ�����±�
	// ����������±겻ͬ��˵������һ������
	if(root1 != root2)
    {
		s[root1].parent = root2; // �� x1 �ҵ� x2 �ļ���
	}
}

int main()
{
	SetType s[MaxSize];
	// ��ʼ�����飬�����ȫ��ָ�� -1
	for(int i=0; i<MaxSize; i++)
    {
		s[i].Data = i + 1;
		s[i].parent = -1;
	}
    // ��������ָ�� -1���ýڵ�������������������±�
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
