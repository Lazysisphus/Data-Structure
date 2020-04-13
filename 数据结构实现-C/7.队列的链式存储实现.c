/*
���е���ʽ�洢�ṹ��
    ��һ����������ʵ��
    �����ɾ�������ֱ����������ͷ����
    ����ָ��frontָ�������ͷ
    ����ָ��rearָ�������β
*/


#include<stdio.h>
#include<malloc.h>

typedef int ElementType;
typedef struct QNode *Queue;
struct Node{
	ElementType Data;
	struct Node *Next;
};
struct QNode{ // �������ṹ
	struct Node *rear;  // ָ���β���
	struct Node *front; // ָ���ͷ���
};

Queue CreateQueue(); // ��ʼ������
int IsEmpty(Queue Q); // �ж϶����Ƿ�Ϊ��
void AddQ(Queue Q, ElementType item); // ���
ElementType DeleteQ(Queue Q); // ����

// ��ʼ��
Queue CreateQueue()
{
	Queue Q;
	Q = (Queue)malloc(sizeof(struct QNode));
	Q->front = NULL;
	Q->rear = NULL;
	return Q;
}

// �Ƿ�Ϊ��
int IsEmpty(Queue Q)
{
	return (Q->front == NULL);
}

// ���
void AddQ(Queue Q, ElementType item)
{
	struct Node *node;
	node = (struct Node*)malloc(sizeof(struct Node));
	node->Data = item;
	node->Next = NULL;
	if(IsEmpty(Q))
    {
		Q->front = node;
		Q->rear = node;
	}
	else
    {
		Q->rear->Next = node; // ��������
		Q->rear = node; // rear ��Ȼ�������
	}
}

// ����
ElementType DeleteQ(Queue Q)
{
	struct Node *headNode;
	ElementType headData;
	if(IsEmpty(Q))
    {
		printf("���п�");
		return -1;
	}
	headNode = Q->front;
	if(Q->front == Q->rear)
    { // ������ֻ��һ��Ԫ�أ�ֱ�ӽ������ÿ�
		Q->front = Q->rear = NULL;
	}
	else
    {
		Q->front = Q->front->Next;
	}
	headData = headNode->Data;
	free(headNode);
	return headData;
}

void print(Queue Q)
{
    if(IsEmpty(Q))
        printf("�ӿ�");
    else
    {
        struct Node *p;
        int p_Data;
        p = Q->front;
        while(p)
        {
            printf("%d ", p->Data);
            p = p->Next ;
        }
    }
    printf("\n");
}

int main()
{
	Queue Q;
	Q = CreateQueue();
	print(Q);
	printf("���5\n");
	AddQ(Q, 5);
	print(Q);
	printf("���4\n");
	AddQ(Q, 4);
	print(Q);
	printf("���3\n");
	AddQ(Q, 3);
	print(Q);
	printf("����%d\n", DeleteQ(Q));
	print(Q);
	printf("����%d\n", DeleteQ(Q));
	print(Q);
	printf("����%d\n", DeleteQ(Q));
	print(Q);
	printf("%d\n", DeleteQ(Q));
	return 0;
}
