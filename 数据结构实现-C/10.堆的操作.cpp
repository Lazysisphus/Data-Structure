/*
���ȶ���
    ����ġ����С���ȡ��Ԫ�ص�˳������Ԫ�ص�����Ȩ��С
    ������Ԫ�ؽ�����е��Ⱥ�˳��

���ȶ��е�ʵ��
    ���Բ������顢�����������顢��������ʵ�����ȶ���
    �����������ݽṹ�������ɾ����ʱ�临�ӶȻ���Ӱ�죬����һ��
    ���������ȫ�������洢�ṹ

��
    �ṹ�ԣ��������ʾ����ȫ������
    �����ԣ���һ���Ĺؼ��������������н������ֵ������Сֵ��
*/

#include<stdio.h>
#include<malloc.h>
#define MaxData 100000
#define ERROR -1

typedef int ElementType;
typedef struct HeapStruct *MaxHeap;
struct HeapStruct{
	ElementType *Elements;   // �洢��Ԫ�ص�����
	int Size;                // �ѵĵ�ǰԪ�ظ���
	int Capacity;            // �ѵ��������
};

MaxHeap Create(int MaxSize); // ����
bool IsFull(MaxHeap H);      // �ж϶��Ƿ���
bool Insert(MaxHeap H,ElementType item); // ����Ԫ��
bool IsEmpty(MaxHeap H);     //  �ж϶��Ƿ�Ϊ��
ElementType DeleteMax(MaxHeap H);        // ɾ�������ض������Ԫ��
void LevelOrderTraversal(MaxHeap H);     // �������

// ����
MaxHeap Create(int MaxSize)
{
	MaxHeap H = (MaxHeap)malloc(sizeof(struct HeapStruct));
	// Elements[0] ��Ϊ�ڱ�����Ԫ�ش�  Elements[1] ��ʼ���
	// "�ڱ�"���ڶ������п��ܵ�ֵ
	H->Elements = (ElementType *)malloc((MaxSize+1)*sizeof(ElementType));
	H->Elements[0] = MaxData;
	H->Size = 0;
	H->Capacity = MaxSize;
	return H;
}

// ���룺����ȫ�����������һ��λ�ò���
// ��Ϊ�ڱ������Ϊ����㣬ȡ��һ�����ֵ�������²���Ľ�㲻��ת�Ƶ������
bool Insert(MaxHeap H, ElementType item)
{
	if(IsFull(H))
    {
		printf("���������޷����룡\n");
		return false;
	}
	int i = ++H->Size; // ָ��������һ��λ�ã�������ܸķ���˳��
	// ���ڱ������ڣ�����Ҫ������� i>1 ������
	for(; item>H->Elements[i/2]; i/=2) // �����ұ� item С�Ľ��
		H->Elements[i] = H->Elements[i/2]; // ��������¸�ֵ
	H->Elements[i] = item; // �ҵ�������ղ����λ�ã��� item ֵ�Ž�ȥ
	return true;
}

// ɾ���������ڵ㵯��
// ����ѿգ��޷�ɾ��
// ����Ѳ���
//     �ȵõ��ѵ����ֵ�������� Max ��
//     Ȼ���� tmp �õ��ѵ�ĩβԪ�أ��⽫����ڸ���㴦
//     tmp ��ֵ��һ���Ǵ�ʱ���е����ֵ��ͨ��ѭ��Ѱ�� tmp Ӧ�����λ�ã�����Ϊ parent
//         ��ѭ���У��жϵ�ǰ parent λ�õ�Ԫ���Ƿ������Ӽ��Һ���
//         ����к��ӣ��ҵ�ֵ���ĺ��ӣ�����Ϊ child
//         ��� tmp ��ֵ�Ѿ����� child ��ֵ����ǰ parent ��λ�ü�Ϊ tmp ������λ��
//         ���򣬽� child ���� parent ����parent �ƶ��� child λ�ã�����Ѱ��
ElementType DeleteMax(MaxHeap H)
{
	int parent, child;
	ElementType Max, tmp;
	if(IsEmpty(H))
    {
		printf("��Ϊ�գ��޷�ɾ����\n");
		return ERROR;
	}
	Max = H->Elements[1];
	tmp = H->Elements[H->Size--];
	// �б�������parent �Ƿ������ӽ��
	for(parent=1; parent*2<=H->Size; parent=child)
	{
		// �� child �������Һ�����ֵ�����һ��
		child = 2*parent;  // ���ӽ��
		// child!=H->Size ��ʾ child ��Ϊ��ǰ���һ����㣬�� parent ���Һ��ӽ��
		if((child!=H->Size) && (H->Elements[child]<H->Elements[child+1]))
			child++;
		// �� tmp �Ҹ����ʵ�λ��
		// �����ǰ���Һ��ӽ��� tmp ��С��˵�� tmp λ�ÿ��Ա����ڵ�ǰ parent λ��
		if(tmp > H->Elements[child])
			break;
		else // ����ѽϴ�ĺ��ӽ����������parent�Լ�������ȥ��
			H->Elements[parent] = H->Elements[child];
	}
	H->Elements[parent] = tmp; // �ں��ʵ�λ�ð� tmp �Ž�ȥ
	return Max;
}

// �ж϶���
bool IsFull(MaxHeap H)
{
	return (H->Size == H->Capacity);
}

// �ж��Ƿ�Ϊ��
bool IsEmpty(MaxHeap H)
{
	return !H->Size;
}

// �������
void LevelOrderTraversal(MaxHeap H)
{
	int i;
	printf("��������Ľ���ǣ�");
	for(i = 1; i<=H->Size; i++)
    {
		printf("%d ", H->Elements[i]);
	}
	printf("\n");
}

int main()
{
	MaxHeap H;
	int MaxSize = 100;
	H = Create(MaxSize);
	Insert(H, 55);
	Insert(H, 66);
	Insert(H, 44);
	Insert(H, 33);
	Insert(H, 11);
	Insert(H, 22);
	Insert(H, 88);
	Insert(H, 99);
	/*
		 99
		/  \
	   88  66
	  / \  / \
	 55 11 22 44
	/
   33
	*/
	LevelOrderTraversal(H);
	DeleteMax(H);
	LevelOrderTraversal(H);
	DeleteMax(H);
	LevelOrderTraversal(H);
	DeleteMax(H);
	LevelOrderTraversal(H);
	DeleteMax(H);
	LevelOrderTraversal(H);
	return 0;
}
