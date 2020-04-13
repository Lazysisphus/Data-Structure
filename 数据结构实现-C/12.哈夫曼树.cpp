/*
�������������������

��Ȩ·������
    ��������� n ��Ҷ�ӽ�㣬ÿ��Ҷ�ӽ�����Ȩֵ wk
    �Ӹ���㵽ÿ��Ҷ�ӽ��ĳ���Ϊ lk
    ����Ҷ�ӽ��� wklk ֮�ͼ�Ϊ WPL����Ȩ·�����ȣ�

�������������Ŷ�������
    WPL��С�Ķ�����

���������Ĺ���
    ÿ�ΰ�Ȩֵ��С�����ö������ϲ�

�����������ص�
    û�ж�Ϊ 1 �Ľ��
    n ��Ҷ�ӽ��Ĺ����������� 2n-1 �����
    ���������������Ҷ���������������֮�����ǹ�������
    ͬһ��Ȩֵ���ܴ��ڲ�ͬ���Ĺ�������

����������
    ����һ���ַ��������ַ����б��룬ʹ���ַ����ı���洢�ռ�����
    ʹ��ǰ׺���������ԣ��κ��ַ��ı��붼������һ�ַ������ǰ׺
*/

#include<iostream>
#include<malloc.h>
#define MaxSize 1000
#define MinData -1000
using namespace std;

int A[] = {13, 1, 45, 7, 20, 4, 19, 13, 40, 33, 38}; // Ԥ�ȶ����һ��Ȩֵ
int A_length = 11; // �����䳤��

typedef struct TreeNode *HuffmanTree;
struct TreeNode{       // ��������
	int weight;        // Ȩֵ
	HuffmanTree Left;  // ������
	HuffmanTree right; // ������
};

typedef struct HeapStruct *MinHeap;
struct HeapStruct{     // ʹ����С�Ѵ�Ź�������
	HuffmanTree *data; // ��ֵ������
	int size;          // �ѵĵ�ǰ��С
	int capacity;      // �������
};

MinHeap create(); // ��ʼ����
HuffmanTree Create(); // ��ʼ����������
void sort(MinHeap H, int i); // ��������С��
void adjust(MinHeap H); // ������С��
void BuildMinHeap(MinHeap H); // ����
HuffmanTree Delete(MinHeap H); // ɾ����С��Ԫ��
void Insert(MinHeap H,HuffmanTree Huff); // ������С��Ԫ��
void PreOrderTraversal(HuffmanTree Huff); // �������
HuffmanTree Huffman(MinHeap H); // ���������Ĺ���

// ��ʼ����������
HuffmanTree Create()
{
	HuffmanTree Huff;
	Huff = (HuffmanTree)malloc(sizeof(struct TreeNode));
	Huff->weight = 0;
	Huff->Left = NULL;
	Huff->right = NULL;
	return Huff;
}

// ��ʼ����
MinHeap create()
{
	MinHeap H;
	HuffmanTree Huff;
	H = (MinHeap)malloc(sizeof(struct HeapStruct));
	H->data = (HuffmanTree *)malloc((MaxSize+1)*sizeof(struct TreeNode));
	H->capacity = MaxSize;
	H->size = 0;
	// �������ڱ�
	Huff = Create();
	Huff->weight = MinData;
	H->data[0] = Huff;
	return H;
}

// ��������С��
void sort(MinHeap H, int i)
{
	int parent, child;
	int tmp = H->data[i]->weight; // ȡ����ǰ"�����"ֵ
	for(parent=i; parent*2<=H->size; parent=child)
    {
		child = 2*parent;
		if((child!=H->size) && (H->data[child+1]->weight<H->data[child]->weight))
			child++;
		if(tmp <= H->data[child]->weight)
			break;
		else
			H->data[parent] = H->data[child];
	}
	H->data[parent]->weight = tmp;
}

// ������С��
void adjust(MinHeap H)
{
	for(int i=H->size/2; i>0; i--)
		sort(H, i); // ÿ��"����С��"����
}

// ����
void BuildMinHeap(MinHeap H)
{
	// ��Ȩֵ�������
	HuffmanTree Huff;
	for(int i=0; i<A_length; i++)
    {
		Huff = Create();
		Huff->weight = A[i];
		H->data[++H->size] = Huff;
	}
	// ������
	adjust(H);
}

// ɾ����С��Ԫ��
HuffmanTree Delete(MinHeap H)
{
	int parent, child;
	HuffmanTree T = H->data[1]; // ȡ�������Ĺ�������
	HuffmanTree tmp = H->data[H->size--]; // ȡ�����һ��������������Ȩֵ
	for(parent=1; parent*2<=H->size; parent=child)
    {
		child = 2*parent;
		if((child!=H->size) && (H->data[child+1]->weight<H->data[child]->weight))
			child++;
		if(tmp->weight <= H->data[child]->weight)
			break;
		else
			H->data[parent] = H->data[child];
	}
	H->data[parent] = tmp;
	// ����һ�� HuffmanTree ��� T�����ϸղ�ȡ������Ȩֵ�����ظý��
	return T;
}

// ����һ����������
void Insert(MinHeap H,HuffmanTree Huff)
{
	int weight = Huff->weight; // ȡ��Ȩֵ
	int i = ++H->size;
	for(; H->data[i/2]->weight > weight; i/=2)
		H->data[i] = H->data[i/2];
	H->data[i] = Huff;
}

//����
void PreOrderTraversal(HuffmanTree Huff)
{
	if(Huff)
    {
		cout<<Huff->weight<<" ";
		PreOrderTraversal(Huff->Left);
		PreOrderTraversal(Huff->right);
	}
}

// ���������Ĺ��죬ʱ�临�Ӷ�O(nlogn)
HuffmanTree Huffman(MinHeap H)
{
	HuffmanTree T;
	BuildMinHeap(H); // ���ѣ����д�������ж��������
	int times = H->size;
	// �� times-1 �κϲ�
	for(int i=1; i<times; i++)
    {
		T = (HuffmanTree)malloc(sizeof(struct TreeNode));
		T->Left = Delete(H);  // �Ӷ���ɾ��һ����㣬��Ϊ�� T �����ӽ��
		T->right = Delete(H); // �Ӷ���ɾ��һ����㣬��Ϊ�� T �����ӽ��
		T->weight = T->Left->weight + T->right->weight; // ���¼���Ȩֵ
		Insert(H, T); // �ټӽ�����
	}
	T = Delete(H);
	return T;
}

int main()
{
	MinHeap H;
	HuffmanTree Huff;
	H = create();
	Huff = Huffman(H);
	PreOrderTraversal(Huff);
	return 0;
}
