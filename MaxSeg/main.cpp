/*
问题：求解数组中最大总和的数据片段
结果：得到最大数据片段位置和总和
算法思想：通过一次遍历的方式，从第一个正数开始，不断累加数据片段总和，最大值保持只加不减原则，
	临时总和如果小于0，则重置最大值和数据片段位置，重新计算。
难点：总和计算简单，但是确定索引位置比较麻烦，需要辅助数据信息来管理是否刷新了总和以及是否保留正项
*/
#include<iostream>
#include<time.h>
using namespace std;

/*
参数：
	data：数组
	len：数组长度
	startIndex：返回数据片段开始位置
	endIndex：返回数据片段结束位置
返回值：
	最大数据片段总和
*/
template<class T>
T getMaxDataSeg(T data[],unsigned int len
	,unsigned int &startIndex,unsigned int &endIndex)
{
	T maxSum=0;//记录数据片段总和最大值
	T tempSum=0;//记录当前计算的数据的总和
	T maxValueIndex=0;//记录数组最大值索引，防止全负值数组的意外情况
	startIndex=-1;
	bool tryingFlag=true;//是否修改开始位置标记
	T tempStartIndex=-1;
	for(unsigned int i=0;i<len;++i)
	{
		if(data[i]>data[maxValueIndex])
			maxValueIndex=i;//记录最大值位置
		tempSum+=data[i];//取出数组的一个元素,累加
		if(tempSum<=0)//开始元素是负值/0，或者前端的数据片段对总和无贡献
		{
			tempSum=0;//清除总和信息
			tempStartIndex=-1;
			tryingFlag=true;//出现累加和负值，需要测试后边数据总和是否刷新最大值
		}
		else
		{
			if(tempStartIndex==-1)//记录可能会以这个索引开始累加刷新的情况
				tempStartIndex=i;
			if(tempSum>maxSum)
			{
				if(tryingFlag)//测试后边数据总和增长成功
				{
					startIndex=i;
					tryingFlag=false;
					if(tempStartIndex!=-1)
					{
						startIndex=tempStartIndex;//修正开始位置
						tempStartIndex=-1;
					}
				}
				endIndex=i;//出现更高的总和时随时记录结束位置
				maxSum=tempSum;//刷新最大值
			}			
		}
	}
	//循环结束后，如果startIndex=-1，则表明没出现正数，这时给出最大负值返回
	if(startIndex==-1)
	{
		startIndex=endIndex=maxValueIndex;
		return data[maxValueIndex];
	}
	else
	{
		return maxSum;
	}
}

template<class T>
void printData(T data[],unsigned int len)
{
	cout<<"[";
	unsigned int i;
	for(i=0;i<len-1;++i)
	{
		cout<<data[i]<<",";
	}
	cout<<data[i]<<"]";
}

int main()
{
	srand((unsigned int)time(0));
	unsigned int len=10;
	unsigned int maxValue=100;
	L:
	int *data=new int[len];
	for(unsigned int i=0;i<len;++i)
	{
		data[i]=rand()%10+1;//随机产生10内数字
		if(rand()%2!=0)//随机产生负数
		{
			data[i]=-data[i];
		}
	}
	int sum;
	unsigned int start,end;
	sum=getMaxDataSeg(data,10,start,end);
	printData(data,10);
	cout<<"\t("<<start<<","<<end<<")="<<sum<<endl;
	delete []data;
	getchar();
	goto L;
	return 0;
}