/*
���Ķ��壺
    �� + ��������һ�ֵݹ�ķ�ʽ����
    �����ǲ��ཻ��
    ���˸�����⣬ÿ��������ҽ���һ�������
    һ�� N ���ڵ������ N-1 ����
    �涨������ڵ� 1 ��

���ı�ʾ��
    �������ʾ�Ƚ�����
    ������ʵ�ֱȽϷ��㣬����ÿ�����Ľṹ����������Ŀ�Ĳ�ͬ����ͬ
    �������ṹһ�£�����ɿռ��ϵ��˷�

    ����ʹ�á�����-�ֵܱ�ʾ����
    ��ָ��ָ���һ�����ӣ���ָ��ָ����һ���ֵ�
    ������һ�������ת�����˶�����

�������Ķ��壺
    ������Ͽ���Ϊ��
    ����Ϊ�գ������ɸ��������������������������ཻ�Ķ��������
    ������������������˳��֮��

����Ķ�������
    б������
    ����/��������
    ��ȫ������

�������ļ�����Ҫ���ʣ�
    �������� i ����������Ϊ 2^(i-1) ��i>=1 �������ӵ�һ�㿪ʼ����
    ���Ϊk�Ķ������������Ϊ 2^k-1 ��k>=1
    n0��ʾҶ�������n2��ʾ��Ϊ2�Ľ������n0 = n2 + 1

�������ı�����
    �������
    �������
    �������
    ����ǰ��ͺ������У��޷�Ψһȷ��������
    ��α���
*/


#include<stdio.h>
#include<malloc.h>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;


typedef struct TreeNode *BinTree;
struct TreeNode{
	int Data;      // ��ֵ
	BinTree Left;  // ����ӽ��
	BinTree Right; // �Ҷ��ӽ��
};
BinTree CreatBinTree();    // ����һ��������
bool IsEmpty(BinTree BT);  // �ж��� BT �Ƿ�Ϊ��
void PreOrderTraversal_1(BinTree BT);  // ���������������
void PreOrderTraversal_2(BinTree BT);  // ���������������
void InOrderTraversal_1(BinTree BT);   // ��������������
void InOrderTraversal_2(BinTree BT);   // ��������������
void PostOrderTraversal_1(BinTree BT); // ������������Ҹ�
void PostOrderTraversal_2(BinTree BT); // ������������Ҹ�


typedef struct SNode *Stack;
struct SNode{
	BinTree Data;
	Stack Next;
};
Stack CreateStack();   // ��ʼ����ջ
int IsEmpty(Stack S);  // �ж���ջ�Ƿ�Ϊ��
void Push(Stack S,BinTree item); // ��ջ
BinTree Pop(Stack S);  // ��ջ


// ��ʼ��
Stack CreateStack()
{
	Stack S;
	S = (Stack)malloc(sizeof(struct SNode));
	S->Next = NULL; // ͷ��㲻����Ԫ��
	return S;
}

// �ж��Ƿ�Ϊ��
int IsEmpty(Stack S)
{
	return (S->Next == NULL);
}

// ��ջ
void Push(Stack S, BinTree item)
{
	Stack tmp;
	tmp = (Stack)malloc(sizeof(struct SNode));
	tmp->Data = item;
	tmp->Next = S->Next;
	S->Next = tmp;
}

// ��ջ
BinTree Pop(Stack S)
{
	Stack popNode;
	BinTree popVal;
	if(IsEmpty(S))
    {
		printf("��ջ��");
		return 0;
	}
	else
    {
		popNode = S->Next;
		S->Next = popNode->Next;
		popVal = popNode->Data; // ȡ����ɾ������ֵ
		free(popNode); // �ͷſռ�
		return popVal;
	}
}

BinTree Insert(int Data)
{
	BinTree BT;
	BT =  (BinTree)malloc(sizeof(struct TreeNode));
	BT->Data = Data;
	BT->Left = NULL;
	BT->Right = NULL;
	return BT;
}

// ��ʼ��������
BinTree CreatBinTree()
{
	BinTree BT;
	BT =  (BinTree)malloc(sizeof(struct TreeNode));
	BT->Data = 1;
	BT->Left = Insert(2);
	BT->Right = Insert(3);
	BT->Left->Left = Insert(4);
	BT->Left->Right = Insert(6);
	BT->Left->Right->Left = Insert(5);
	BT->Right->Left = Insert(7);
	BT->Right->Right = Insert(9);
	BT->Right->Left->Right = Insert(8);
	return BT;
}

// ����ǰ�����г�ʼ��������
// 1 2 4 0 0 6 5 0 0 0 3 7 0 8 0 0 9 0 0
void CreatBinTreeFomPreorder(BinTree &BT)
{
    int val;
    scanf("%d", &val);
    if(val == 0)
        BT = NULL;
    else
    {
        BT = (BinTree)malloc(sizeof(struct TreeNode));
        BT->Data = val;
        CreatBinTreeFomPreorder(BT->Left);
        CreatBinTreeFomPreorder(BT->Right);
    }
}

// ����ݹ�
void PreOrderTraversal_1(BinTree BT)
{
	if(BT)
    {
		printf("%d", BT->Data);       // ��ӡ��
		PreOrderTraversal_1(BT->Left);  // ����������
		PreOrderTraversal_1(BT->Right); // ����������
	}
}

// ����ǵݹ�
void PreOrderTraversal_2(BinTree BT)
{
	BinTree T = BT;
	Stack S = CreateStack(); // ��������ʼ����ջ S
	while(T || !IsEmpty(S))  // ������Ϊ�ջ��ջ����
    {
		while(T)
		{
			Push(S, T);    // ѹջ����һ�������ý��
			printf("%d", T->Data); // ���ʽ��
			T = T->Left;   // ����������
		}
		if(!IsEmpty(S))    // ����ջ����
		{
			T = Pop(S);    // ��ջ���ڶ��������ý��
			T = T->Right;  // �����ҽ��
		}
	}
}

// ����ݹ�
void InOrderTraversal_1(BinTree BT)
{
	if(BT)
    {
		InOrderTraversal_1(BT->Left);  // ����������
		printf("%d", BT->Data);      // ��ӡ��
		InOrderTraversal_1(BT->Right); // ����������
	}
}

// ����ǵݹ�
void InOrderTraversal_2(BinTree BT)
{
	BinTree T = BT;
	Stack S = CreateStack(); // ��������ʼ����ջ S
	while(T || !IsEmpty(S))  // ������Ϊ�ջ��ջ����
    {
		while(T)
		{
			Push(S, T);    // ѹջ
			T = T->Left;   // ����������
		}
		if(!IsEmpty(S))    // ����ջ����
		{
			T = Pop(S);    // ��ջ
			printf("%d", T->Data); // ���ʽ��
			T = T->Right;  // �����ҽ��
		}
	}
}

// ����ݹ�
void PostOrderTraversal_1(BinTree BT)
{
	if(BT)
    {
		PostOrderTraversal_1(BT->Left);  // ����������
		PostOrderTraversal_1(BT->Right); // ����������
		printf("%d",BT->Data);         // ��ӡ��
	}
}

// ����ǵݹ�
void PostOrderTraversal_2(BinTree BT)
{
	BinTree T = BT;
	Stack S = CreateStack(); // ��������ʼ����ջ S
	vector<BinTree> v;
	Push(S, T);
	while(!IsEmpty(S)) // ��ǰ���ǿ�
    {
		T = Pop(S);
		v.push_back(T);
		if(T->Left)
			Push(S, T->Left);
		if(T->Right)
			Push(S, T->Right);
	}
	reverse(v.begin(), v.end()); // ��ת
	for(int i=0; i<v.size(); i++)
		printf("%d", v[i]->Data);
}

// ��α���
void LevelOrderTraversal(BinTree BT)
{
	queue<BinTree> q;
	BinTree T;
	if(!BT)
		return;

	q.push(BT); // BT ���
	while(!q.empty())
    {
		T = q.front();  // ���ʶ���Ԫ��
		q.pop();        // ����
		printf("%d", T->Data);
		if(T->Left)
			q.push(T->Left);
	 	if(T->Right)
	 		q.push(T->Right);
	}
}

// ���Ҷ�ӽ��
void  FindLeaves(BinTree BT)
{
	if(BT)
    {
		if(!BT->Left && !BT->Right)
			printf("%d", BT->Data); // ��ӡҶ�ӽ��
		FindLeaves(BT->Left);  // ����������
		FindLeaves(BT->Right); // ����������
	}
}

// �����߶�
int  GetHeight(BinTree BT)
{
	int hl, hr, maxh;
	if(BT)
    {
		hl = GetHeight(BT->Left);  // ���������߶�
		hr = GetHeight(BT->Right); // ���������߶�
		maxh = (hl>hr)?hl:hr;
		return maxh + 1;  // ��ǰ���߶�Ϊ�����������ĸ߶�+1
	}
	else
		return 0;
}

int main()
{
	BinTree BT, ST;

	printf("�밴��ǰ������������������ս����0��ʾ�����֮���ÿո�ָ���\n");
	// CreatBinTreeFomPreorder(BT);
	BT = CreatBinTree();

	printf("���������\n");
	PreOrderTraversal_1(BT);
	printf("\n");
	PreOrderTraversal_2(BT);

	printf("\n���������\n");
	InOrderTraversal_1(BT);
	printf("\n");
	InOrderTraversal_2(BT);

	printf("\n���������\n");
	PostOrderTraversal_1(BT);
	printf("\n");
	PostOrderTraversal_2(BT);

	printf("\n��α�����");
	LevelOrderTraversal(BT);

	printf("\n���Ҷ�ӽ��:");
	FindLeaves(BT);

	printf("\n������ĸ߶ȣ�%d", GetHeight(BT));
	return 0;
}
