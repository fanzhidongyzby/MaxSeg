/*
���⣺�������������ܺ͵�����Ƭ��
������õ��������Ƭ��λ�ú��ܺ�
�㷨˼�룺ͨ��һ�α����ķ�ʽ���ӵ�һ��������ʼ�������ۼ�����Ƭ���ܺͣ����ֵ����ֻ�Ӳ���ԭ��
	��ʱ�ܺ����С��0�����������ֵ������Ƭ��λ�ã����¼��㡣
�ѵ㣺�ܺͼ���򵥣�����ȷ������λ�ñȽ��鷳����Ҫ����������Ϣ�������Ƿ�ˢ�����ܺ��Լ��Ƿ�������
*/
#include<iostream>
#include<time.h>
using namespace std;

/*
������
	data������
	len�����鳤��
	startIndex����������Ƭ�ο�ʼλ��
	endIndex����������Ƭ�ν���λ��
����ֵ��
	�������Ƭ���ܺ�
*/
template<class T>
T getMaxDataSeg(T data[],unsigned int len
	,unsigned int &startIndex,unsigned int &endIndex)
{
	T maxSum=0;//��¼����Ƭ���ܺ����ֵ
	T tempSum=0;//��¼��ǰ��������ݵ��ܺ�
	T maxValueIndex=0;//��¼�������ֵ��������ֹȫ��ֵ������������
	startIndex=-1;
	bool tryingFlag=true;//�Ƿ��޸Ŀ�ʼλ�ñ��
	T tempStartIndex=-1;
	for(unsigned int i=0;i<len;++i)
	{
		if(data[i]>data[maxValueIndex])
			maxValueIndex=i;//��¼���ֵλ��
		tempSum+=data[i];//ȡ�������һ��Ԫ��,�ۼ�
		if(tempSum<=0)//��ʼԪ���Ǹ�ֵ/0������ǰ�˵�����Ƭ�ζ��ܺ��޹���
		{
			tempSum=0;//����ܺ���Ϣ
			tempStartIndex=-1;
			tryingFlag=true;//�����ۼӺ͸�ֵ����Ҫ���Ժ�������ܺ��Ƿ�ˢ�����ֵ
		}
		else
		{
			if(tempStartIndex==-1)//��¼���ܻ������������ʼ�ۼ�ˢ�µ����
				tempStartIndex=i;
			if(tempSum>maxSum)
			{
				if(tryingFlag)//���Ժ�������ܺ������ɹ�
				{
					startIndex=i;
					tryingFlag=false;
					if(tempStartIndex!=-1)
					{
						startIndex=tempStartIndex;//������ʼλ��
						tempStartIndex=-1;
					}
				}
				endIndex=i;//���ָ��ߵ��ܺ�ʱ��ʱ��¼����λ��
				maxSum=tempSum;//ˢ�����ֵ
			}			
		}
	}
	//ѭ�����������startIndex=-1�������û������������ʱ�������ֵ����
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
		data[i]=rand()%10+1;//�������10������
		if(rand()%2!=0)//�����������
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