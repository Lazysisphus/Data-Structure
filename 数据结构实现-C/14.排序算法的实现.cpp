/*
选择排序 冒泡排序 插入排序
希尔排序 堆排序 归并排序
快速排序 表排序 物理排序 桶排序 基数排序

简单排序
    前提：
        void X_Sort(ElementType A[], int N)
        这里默认讨论从小到大的整数排序
        N 是正整数
        只讨论基于比较的排序
        只讨论内部排序，即所有的数据都可以导入内存空间，并在内存中完成排序
    稳定性：
        任意两个相等的数据，排序前后的相对位置不发生改变

时间复杂度下界
    对于下标 i<j ，如果 A[i]>A[j]，则称(i, j)是一对逆序对
    任意 N 个不同元素组成的序列平均具有 N(N-1)/4 个逆序对（定理，课程没有证明）
    任何仅以交换相邻两元素来排序的算法，其平均时间复杂度为 Ω(N^2)

    插入排序时间复杂度O（N+I），N是元素个数，I是逆序对数
    如果原始数组基本有序，使用插入排序效率更高

    如果想提高算法的效率，必须：
        每次消去不止一对逆序对，可以每次交换相隔较远的 2 个元素
        可以使用希尔排序

表排序
    不移动元素本身，只移动指针
    间接排序
    定义一个指针数组作为“表”

物理排序
    表排序完成后，需要将指针指向的实体在物理上也排好序
    N个数字的排列由若干个独立的环组成
    最好情况：初始即有序
    最坏情况：每两本书都要做交换，T=O(mN)，m是每个A元素复制的时间
*/


#include<iostream>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#define NumSize 20


int A[NumSize];
using namespace std;


// 生成随机数
void Random()
{
	for(int i=0; i<NumSize; i++)
		A[i] = rand()%NumSize+1; // 随机生成1~NumSize之间的数字（闭区间）
}


// 输出
void output()
{
	for(int i=0; i<NumSize; i++)
		cout<<A[i]<<" ";
	cout<<endl;
}


/********************************************************************

    选择排序
        将数组分为 有序+无序 两个部分
        每次选择无序部分最小元素，和有序部分末尾后一个元素交换

        时间复杂度：O(N^2)
        不稳定

********************************************************************/
void Select_sort(int N)
{   // 为前 n-1 个位置寻找对应的元素
    for(int i=0; i<N-1; i++)
    {
        int index = i;
        int j;
        // 找出最小值的元素下标
        for (j=i+1; j<N; j++)
        {
            if (A[j] < A[index])
                index = j;
        }
        swap(A[index], A[i]);
    }
}


/******************************************************************

    冒泡排序
        每趟排序，得到无序部分的最大元素，放在数组的末尾
        每趟排序内部，通过依次交换相邻的两个元素实现大元素沉淀

        时间复杂度：最好O（N），最坏O（N^2）
        稳定

******************************************************************/
void Bubble_sort(int N)
{
    // 总共 n-1 趟
	for(int p=N-1; p>=0; p--)
    {
		bool flag = false;
		for(int j=0; j<p; j++)
		{
		    // 一趟排序
			if(A[j] > A[j+1])
			{
				swap(A[j], A[j+1]);
				flag = true;
			}
		}
		if(!flag) // 全程无交换，终止排序
			break;
	}
}


/********************************************************************

    插入排序
        从数组的第二个元素开始，为每个元素寻找合适的插入位置

        时间复杂度：最好O（N），最坏O（N^2）
        稳定

********************************************************************/
void Insertion_sort(int A[], int N)
{   // 这里把数组传入，因为后面的快速排序也要用插入排序对子数组调整
    // 从下标为 1 的整数开始插入
	for(int p=1; p<N; p++)
    {
		int tmp = A[p]; // 保存当前要找位置的数字
        // 从位置 1 到位置 p，寻找一个合适位置
        int j=p; // j 不能是for循环中的局部变量
		for(; j>0&&A[j-1]>tmp; j--)
            A[j] = A[j-1]; // “腾“出位置
		A[j] = tmp; // 把合适大小的数放入
	}
}


/**************************************************************************

    原始希尔排序
        基于插入排序的思想
        改进插入排序每次只交换相邻两个元素的缺点
        每趟排序，选择一个间隔数
        例如 5 间隔，那么将对第 0、5、10...个元素构成的子序列做插入排序
        然后缩小间隔数，直至 1 间隔，进行原始的插入排序

    最坏情况：
        Θ（N^2），等于N^2
        增量元素不互质，导致小增量可能根本不起作用
        不稳定

**************************************************************************/
void Shell_sort(int N)
{
	for(int D=N/2; D>0; D/=2)
    {
		for(int p=D; p<N; p+=D)
		{
			int tmp = A[p];
			int j = p;
			// j>=D 在前，因为也许 A[j-D]已经越界
			for(; j>=D&&A[j-D]>tmp; j-=D)
				A[j] = A[j-D];
			A[j] = tmp;
		}
	}
}

// Hibbard增量序列希尔排序
// 最坏情况：Θ（N^(3/2)）
// 猜想Tavg = O（N^(5/4)）
void Hibbard_shell_sort(int N)
{
	int add[]={15,7,3,1,0};
	int i=0;
	for(int D=add[i]; D>0; D=add[++i])
    {
		for(int p=D; p<N; p+=D)
		{
			long tmp = A[p];
			int k=p;
			for(; k>=D&&tmp<A[k-D]; k-=D) // j>=D 在前，因为也许 A[j-D] 已经越界
				A[k] = A[k-D];
			A[k] = tmp;
		}
	}
}

// Sedgewick增量序列希尔排序
// 猜想：最坏情况：Θ（N^(4/3)），Tavg = O（N^(7/6)）
void Sedgewick_shell_sort(int N)
{
	int add[]= {19,5,1,0};
	int i=0;
	for(int D=add[i]; D>0; D=add[++i])
    {
		for(int p=D; p<N; p+=D)
		{
			long tmp = A[p];
			int k = p;
			for(; k>=D&&tmp<A[k-D]; k-=D)
				A[k] = A[k-D];
			A[k] = tmp;
		}
	}
}


/******************************************************************

    堆排序
        是对选择排序的改进

    方法一
        （1）在原始数组的基础上建立最小堆
        （2）顺次弹出最小堆中元素，并将它们存在临时数组中
        （3）将临时数组中元素复制回到原始数组
        时间复杂度：O（NlogN），需要额外O（N）空间
        void Heap_sort(ElementType A[], int N)
        {
            BuildHeap(A); // O(N)
            for(i=0; i<N; i++)
                TmpA = DeleteMin(A); // O(logN)
            for(i=0; i<N; i++) // O(N)
                A[i] = TmpA[i];
        }
        * 函数BulidHeap()以及DeleteMin()没有提供

    方法二
        （1）先将当前数组调整为最大堆
        （2）每次把根结点放在数组最后的位置，然后数组规模减一
        （3）在新数组上继续步骤（1）和（2），直到数组第一个数组
        时间复杂度：2NlogN - O（NloglogN），略好于O（NlogN）
        实际效果不如用Sedgewick增量序列的希尔排序

        不稳定

*******************************************************************/
// 调整成最大堆
void PrecDown(int i, int N)
{
	int child, parent;
	int tmp = A[i];  // 拿到当前"根"结点的值
	// 下标从 0 开始，注意结束范围和父子结点之间的关系
	for(parent = i; parent*2+1<=N-1; parent = child)
    {
		child = 2*parent + 1;
		if((child!=N-1) && (A[child] < A[child+1])) // 选最大的
			child++;
		if(A[child] <= tmp)
			break;
		A[parent] = A[child];
	}
	A[parent] = tmp;
}

void swap(int &a, int &b)
{
	int t = a;
	a = b;
	b = t;
}

// 方法二
void Heap_sort(int N)
{
	// buildHeap
	// i 是每次先放在根结点的结点的下标
	// N 是每次被调整的数组的规模
	for(int i=N/2; i>=0; i--)
		PrecDown(i, N);
	for(int i = N-1; i>0; i--)
    {
		swap(A[0], A[i]);
		PrecDown(0, i);
	}
}


/*******************************************************************

    归并排序（递归）
        先分治，然后合并结果

    时间复杂度：O（NlogN）
    稳定

*******************************************************************/
// 一次归并的时间复杂度O（N）
void Merge1(int A[], int tmpA[], int L, int R, int RightEnd)
{
	// L = 左边起始位置，R = 右边起始位置，RightEnd = 右边终点位置
	int LeftEnd = R-1; // 左边终点位置
	int tmp = L; // 存放结果的开始位置
	int NumElements = RightEnd - L + 1; // 归并个数
	while(L<=LeftEnd && R<=RightEnd)
    {
		if(A[L] <= A[R])
			tmpA[tmp++] = A[L++];
		else
			tmpA[tmp++] = A[R++];
	}
	// 左边有剩
	while(L<=LeftEnd)
		tmpA[tmp++] = A[L++];
	// 右边有剩
	while(R<=RightEnd)
		tmpA[tmp++] = A[R++];
	// 导回结果，从末尾位置开始导回
	for(int i=0; i<NumElements; i++, RightEnd--)
		A[RightEnd] = tmpA[RightEnd];
}

// 分治
void Msort1(int A[], int tmpA[], int L, int RightEnd)
{
	// L = 左边起始位置，RightEnd = 右边终点位置
	// 如果待排序列至少还有 2 个元素
	if(L < RightEnd)
    {
		int center = (L+RightEnd)/2;
		Msort1(A, tmpA, L, center); // 左半边
		Msort1(A, tmpA, center+1, RightEnd); // 右半边
		Merge1(A, tmpA, L, center+1, RightEnd); // center+1 是右边起点
	}
}

void Merge_sort1(int A[], int N)
{
	int tmpA[N];
	Msort1(A, tmpA, 0, N-1);
}


/*******************************************************************

    归并排序（非递归）
        先分治，然后合并结果

    时间复杂度：O（NlogN），额外使用O（N）空间
    稳定

    需要把元素在原始数组和临时数组之间交互传递
    在外部排序时特别有用

*******************************************************************/
void Merge2(int A[], int tmpA[], int L, int R, int RightEnd)
{
	// L = 左边起始位置，R = 右边起始位置，RightEnd = 右边终点位置
	int LeftEnd = R-1; // 左边终点位置
	int tmp = L;       // 存放结果的开始位置
	int NumElements = RightEnd - L + 1; // 归并个数
	while(L<=LeftEnd && R<=RightEnd)
    {
		if(A[L] <= A[R])
			tmpA[tmp++] = A[L++];
		else
			tmpA[tmp++] = A[R++];
	}
	// 左边有剩
	while(L<=LeftEnd)
		tmpA[tmp++] = A[L++];
	// 右边有剩
	while(R<=RightEnd)
		tmpA[tmp++] = A[R++];
}

// 一趟归并
void Merge_pass(int A[], int tmpA[], int N, int length)
{
	// length = 当前有序子列长度
	int i;
	for(i=0; i<=N-2*length; i+=length*2)
		Merge2(A, tmpA, i, i+length, i+2*length-1);
	if(i+length < N)
		Merge2(A, tmpA, i, i+length, N-1);
	else
		for(int j=i; j<N; j++)
			tmpA[j] = A[j];
}

void Merge_sort2(int A[], int N)
{
	int length = 1;
	int tmpA[N];
	while(length<N)
    {
		Merge_pass(A, tmpA, N, length);
		length *=2;
		Merge_pass(tmpA, A, N, length);
		length *=2;
	}
}


/****************************************************************************************

    快速排序
        分治+递归实现
        步骤：
            选取主元Pivot
            根据主元将原始数组分为小于主元的部分、主元、大于主元的部分
            对小于主元部分、大于住院部份递归执行快速排序
            将两个递归执行的结果与主元依次合并起来
            递归结束的条件是，小于主元或大于主元的部分只有一个元素，直接return
        最好情况：
            主元每次正好中分，T(N) = O(NlogN)
        选主元：
            取当前数组的第一个元素作为主元，若数据有序，效率变低，时间复杂度O(n^2)
            随机取，但是rand()函数时间成本大
            取头、中、尾三个元素中的中位数（也可以是5个数取中位数，7个数取中位数）
        选取主元后的排序过程中，如果有元素正好等于主元：
            取极端情况，所有的元素都相等
            停下来交换，会花费一些时间做交换，此时时间复杂度O(nlogn)
            不交换，继续移动指针，此时时间复杂度O(n^2)
            一般会选取继续交换
        小规模数据处理问题：
            快速排序使用递归过程，对于小规模数据，如不足100个数字做排序，开销较大
            可以使用其他排序方法对小规模的数据做排序

    时间复杂度：O（NlogN）
    稳定

*****************************************************************************************/
// 从首、中、尾三个候选者中获得主元
int GetPivot(int L, int R)
{
	int center = (L+R)/2;
	// 排序  A[L] < A[center] < A[R]
	if(A[center] < A[L])
		swap(A[L], A[center]);
    if(A[R] < A[L])
		swap(A[R], A[L]);
	if(A[R] < A[center])
		swap(A[R], A[center]);
	// 把主元藏在 R-1
	// 只需要考虑 A[Left+1] ... A[Right-2]
	swap(A[center], A[R-1]);
	return A[R-1];
}

// 快排实现
void Quicksort(int Left, int Right)
{
	int cutoff = 100;
	if( cutoff <= Right-Left)
    {
		int Pivot = GetPivot(Left, Right);
		int i = Left;
		int j = Right-1;
		while(1)
        {
			while(A[++i] < Pivot);
			while(A[--j] > Pivot);
			if(i < j)
				swap(A[i], A[j]);
			else
				break;
		}
		// 上述循环结束后，i 指向第一个大于主元的元素
		swap(A[i], A[Right-1]);
		Quicksort(Left, i-1);
		Quicksort(i+1, Right);
	}
	else
		Insertion_sort(A+Left, Right-Left+1); // 开始位置，当前待排序子数组的元素个数
}

void Quick_sort(int N)
{
	Quicksort(0, N-1);
}


/*****************************************************************************************************

    桶排序
        基数排序的一种基本情况
        用来解决的问题：
            待排序数组规模 N 远大于数组的取值范围 M
            为每个取值建立一个对应的桶，然后将数组每个元素放入对应的桶中
        时间复杂度：
            T(N,M)=O(M+N)
            当 N 远大于 M 时，线性时间复杂度
            当 M 远大于 N 时，使用基数排序，例如总共有10个待排序数字，但是取值范围是[0, 999]

    基数排序
        “基数”指的就是进制的基数，2进制的基数是2，以此类推
        当基数是10时，建立10个桶，然后使用“次位优先”或者“主位优先”策略
        次位优先：
            从低位起观察待排序数字直到所有数字的最高位，如百位
            在针对每一位的排序中，将各个数字放入对应的桶中，如十位是6，就将该数字放入 6 这个桶中
        时间复杂度：O(P(N+B))，P趟，N个数，B个桶
        特点：
            处理多关键字的排序
            其实是先按照一个指标排序，再按照另一个指标排序，即主位或者次位优先
            例如扑克牌按照花色和面值排序，面值是次位的话，次位优先比较高效

*****************************************************************************************************/
// 本程序例中，取值范围和待排序数组的规模一样大
void Bucket_Sort(int N)
{
	int count[20]; // M，范围多大桶就多少
	// 初始化每个桶
	for(int i=0; i<20; i++)
    {
		count[i] = 0;
	}
	// 每个值倒入桶中，实际上统计了每个桶中元素的个数
	for(int i=0; i<N; i++)
		count[A[i]]++;
	// 每个值取了多少次，就输出多少次该值
	for(int i=0; i<20; i++)
		if(count[i])
		{
			for(int j=0; j<count[i]; j++)
				cout<<i<<" ";
		}
}


int main()
{
	Random(); // 生成随机数
	output(); // 输出数组元素
//	Select_sort(NumSize);          // 选择排序
//	Bubble_sort(NumSize);          // 冒泡排序
//	Insertion_sort(A, NumSize);    // 插入排序
//	Shell_sort(NumSize);           // 希尔排序
//	Hibbard_shell_sort(NumSize);   // Hibbard间隔的希尔排序
//  Sedgewick_shell_sort(NumSize); // Sedgewick间隔的希尔排序
//	Heap_sort(NumSize);            // 堆排序
//	Merge_sort1(A, NumSize);       // 归并排序（递归）
//  Merge_sort2(A, NumSize);       // 归并排序（非递归）
//	Quick_sort(NumSize);           // 快速排序
	Bucket_Sort(NumSize);          // 桶排序
	return 0;
}
