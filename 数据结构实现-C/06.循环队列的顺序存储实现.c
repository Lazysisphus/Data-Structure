/*
����

���У�
    ����һ������Լ�������Ա�
    ֻ����һ�˲��룬����һ��ɾ��
    ���ݲ��룺���
    ����ɾ��������
    �Ƚ��ȳ�

���е�˳��洢ʵ�֣�
    ��һ��һά���� && һ����¼ͷԪ��λ�õı���front && һ����¼βԪ��λ�õı���rear
*/


#include<stdio.h>
#include<malloc.h>
#define MaxSize 5

typedef int ElementType;
typedef struct QNode *Queue;
struct QNode{
	ElementType Data[MaxSize];
	int front; // ��¼��ͷ
	int rear; // ��¼��β
};

Queue CreateQueue(); // ��ʼ������
void AddQ(Queue Q, ElementType item); // ���
int IsFull(Queue Q); // �ж϶����Ƿ�����
ElementType DeleteQ(Queue Q); // ����
int IsEmpty(Queue Q); // �ж϶����Ƿ�Ϊ��

// ��ʼ��
Queue CreateQueue()
{
	Queue Q;
	Q = (Queue)malloc(sizeof(struct QNode));
	Q->front = -1;
	Q->rear = -1;
	return Q;
}

// �ж϶����Ƿ�����
int IsFull(Queue Q)
{   // front == rearʱ�����п����ǿյģ�Ҳ����������
    // Ϊ�˽�����������״̬�����֣����ԣ�
    // ����size��¼�����д��Ԫ�صĸ���
    // ����tag��ʾ���һ�β�������ӻ��ǳ���
    // ����һ���洢�ռ䣬����
 	return ((Q->rear+1)%MaxSize == Q->front);
}

// �ж϶����Ƿ�Ϊ��
int IsEmpty(Queue Q)
{
	return (Q->front == Q->rear);
}

// ��ӣ���βָ����ƣ�Ȼ��Ԫ�����
void AddQ(Queue Q, ElementType item)
{
	if(IsFull(Q))
    {
		printf("������");
		return;
	}
	else
    {
		Q->rear = (Q->rear+1)%MaxSize;
		Q->Data[Q->rear] = item;
	}
}

// ���ӣ�����ָ����ƣ�Ȼ�����
ElementType DeleteQ(Queue Q)
{
	if(IsEmpty(Q))
    {
		printf("���п�");
		return 0;
	}
	else
    {   // frontָ�����ͷ��ǰһ��Ԫ��
        // ����front+1������ָ��ǰҪ���ӵ�Ԫ��
		Q->front = (Q->front+1)%MaxSize;
		return Q->Data[Q->front];
	}
}

void print(Queue Q)
{
    if(IsEmpty(Q))
        printf("�ӿ�");
    else
    {
        int i=Q->front;
        while(i != Q->rear)
        {
            i = (i+1)%MaxSize;
            printf("%d ", Q->Data[i]);
        }
    }
    printf("\n");
}

int main()
{
	Queue Q;
	Q = CreateQueue();
	print(Q);
	AddQ(Q, 3);
	printf("3���\n");
	print(Q);
	AddQ(Q, 5);
	printf("5���\n");
	print(Q);
	AddQ(Q, 11);
	printf("11���\n");
	print(Q);
	printf("%d����\n", DeleteQ(Q));
	print(Q);
	printf("%d����\n", DeleteQ(Q));
	print(Q);
	return 0;
}
