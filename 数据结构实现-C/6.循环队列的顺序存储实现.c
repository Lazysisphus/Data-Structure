/*
队列

队列：
    具有一定操作约束的线性表
    只能在一端插入，在另一端删除
    数据插入：入队
    数据删除：出队
    先进先出

队列的顺序存储实现：
    由一个一维数组 && 一个记录头元素位置的变量front && 一个记录尾元素位置的变量rear
*/


#include<stdio.h>
#include<malloc.h>
#define MaxSize 5

typedef int ElementType;
typedef struct QNode *Queue;
struct QNode{
	ElementType Data[MaxSize];
	int front; // 记录队头
	int rear; // 记录队尾
};

Queue CreateQueue(); // 初始化队列
void AddQ(Queue Q, ElementType item); // 入队
int IsFull(Queue Q); // 判断队列是否已满
ElementType DeleteQ(Queue Q); // 出队
int IsEmpty(Queue Q); // 判断队列是否为空

// 初始化
Queue CreateQueue()
{
	Queue Q;
	Q = (Queue)malloc(sizeof(struct QNode));
	Q->front = -1;
	Q->rear = -1;
	return Q;
}

// 判断队列是否已满
int IsFull(Queue Q)
{   // front == rear时，队列可以是空的，也可以是满的
    // 为了进行上述两种状态的区分，可以：
    // 设置size记录队列中存放元素的个数
    // 设置tag表示最近一次操作是入队还是出队
    // 牺牲一个存储空间，如下
 	return ((Q->rear+1)%MaxSize == Q->front);
}

// 判断队列是否为空
int IsEmpty(Queue Q)
{
	return (Q->front == Q->rear);
}

// 入队，队尾指针后移，然后元素入队
void AddQ(Queue Q, ElementType item)
{
	if(IsFull(Q))
    {
		printf("队列满");
		return;
	}
	else
    {
		Q->rear = (Q->rear+1)%MaxSize;
		Q->Data[Q->rear] = item;
	}
}

// 出队，队首指针后移，然后出队
ElementType DeleteQ(Queue Q)
{
	if(IsEmpty(Q))
    {
		printf("队列空");
		return 0;
	}
	else
    {   // front指向队列头的前一个元素
        // 所以front+1后，整好指向当前要出队的元素
		Q->front = (Q->front+1)%MaxSize;
		return Q->Data[Q->front];
	}
}

void print(Queue Q)
{
    if(IsEmpty(Q))
        printf("队空");
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
	printf("3入队\n");
	print(Q);
	AddQ(Q, 5);
	printf("5入队\n");
	print(Q);
	AddQ(Q, 11);
	printf("11入队\n");
	print(Q);
	printf("%d出队\n", DeleteQ(Q));
	print(Q);
	printf("%d出队\n", DeleteQ(Q));
	print(Q);
	return 0;
}
