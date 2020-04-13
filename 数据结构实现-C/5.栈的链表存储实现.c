/*
��ջ����ʽ�洢��
    ջ����ʽ�洢�ṹʵ���Ͼ���һ��������������ջ
    �����ɾ������ֻ��������ջ������
    Ϊ�˷���Ԫ�صĲ����ɾ����ջ��ָ��Topָ�������ͷ
*/

#include<stdio.h>
#include<malloc.h>
typedef int ElementType;
typedef struct SNode *Stack;
struct SNode{
	ElementType Data;
	Stack Next;
};

Stack CreateStack(); // ��ʼ����ջ
int IsEmpty(Stack S); // �ж���ջ�Ƿ�Ϊ��
void Push(Stack S, ElementType item); // ��ջ
ElementType Pop(Stack S); // ��ջ


// ��ʼ����ͷ��㲻�����κ�Ԫ��
// S(top) -> node1 -> node2 -> node3 ...
Stack CreateStack()
{
	Stack S;
	S = (Stack)malloc(sizeof(struct SNode));
	S->Next = NULL; // ���ʹ�� S=NULL ��ʼ������ʾͷ��㱣��Ԫ��
	return S;
}

// �ж��Ƿ�Ϊ��
int IsEmpty(Stack S)
{
	return (S->Next == NULL);
}

// ��ջ
void Push(Stack S, ElementType item)
{
	Stack tmp;
	tmp = (Stack)malloc(sizeof(struct SNode));
	tmp->Data = item;
	tmp->Next = S->Next;
	S->Next = tmp;
}

// ��ջ
ElementType Pop(Stack S)
{
	Stack popNode;
	ElementType popVal;
	if(IsEmpty(S))
    {
		printf("��ջ��");
		return;
	}
	else
    {
		popNode = S->Next; // ��ջ��һ��Ԫ����ջ��Ԫ�غ���
		S->Next = popNode->Next; // �ѵ�һ��Ԫ�ش���ջɾ��
		popVal = popNode->Data; // ȡ����ɾ������ֵ
		free(popNode); // �ͷſռ�
		return popVal;
	}
}

void print(Stack S)
{
    printf("��ӡ��ǰ��ջ����ջ����ջ�������ǣ���");
    if(IsEmpty(S))
        printf("ջ��");
    else
    {
        Stack p = S->Next;
        while(p)
        {
            int tmp = p->Data;
            printf("%d ", tmp);
            p = p->Next;
        }
    }
    printf("\n");
}

int main()
{
	Stack S;
	S = CreateStack();
	printf("5��ջ\n");
	Push(S, 5);
	print(S);
	printf("7��ջ\n");
	Push(S, 7);
	print(S);
	printf("66��ջ\n");
	Push(S, 66);
	print(S);
	printf("%d��ջ\n", Pop(S));
    print(S);
	printf("%d��ջ\n", Pop(S));
    print(S);
	return 0;
}
