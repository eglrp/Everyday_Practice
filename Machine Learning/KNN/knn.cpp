

//    KNN.cpp     K-����ڷ����㷨
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <iostream>
#include <math.h>
#include <fstream>
using namespace std;
////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    �궨��
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
#define  ATTR_NUM  4                         //������Ŀ
#define  MAX_SIZE_OF_TRAINING_SET  1000      //ѵ�����ݼ�������С
#define  MAX_SIZE_OF_TEST_SET      100       //�������ݼ�������С
#define  MAX_VALUE  10000.0                  //�������ֵ
#define  K  7
//�ṹ��
struct dataVector {
	int ID;                          //ID��
	char classLabel[15];             //������
	double attributes[ATTR_NUM];     //���� 
};
struct distanceStruct {
	int ID;                      //ID��
	double distance;             //����
	char classLabel[15];         //������
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    ȫ�ֱ���
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
struct dataVector gTrainingSet[MAX_SIZE_OF_TRAINING_SET]; //ѵ�����ݼ�
struct dataVector gTestSet[MAX_SIZE_OF_TEST_SET];         //�������ݼ�
struct distanceStruct gNearestDistance[K];                //K������ھ���
int curTrainingSetSize = 0;                                 //ѵ�����ݼ��Ĵ�С
int curTestSetSize = 0;                                     //�������ݼ��Ĵ�С
////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    �� vector1=(x1,x2,...,xn)��vector2=(y1,y2,...,yn)��ŷ����¾���
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
double Distance(struct dataVector vector1, struct dataVector vector2)
{
	double dist, sum = 0.0;
	for (int i = 0; i < ATTR_NUM; i++)
	{
		sum += (vector1.attributes[i] - vector2.attributes[i])*(vector1.attributes[i] - vector2.attributes[i]);
	}
	dist = sqrt(sum);
	return dist;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    �õ�gNearestDistance�е������룬�����±�
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
int GetMaxDistance()
{
	int maxNo = 0;
	for (int i = 1; i<K; i++)
	{
		if (gNearestDistance[i].distance>gNearestDistance[maxNo].distance) maxNo = i;
	}
	return maxNo;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    ��δ֪����Sample����
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
char* Classify(struct dataVector Sample)
{
	double dist = 0;
	int maxid = 0, freq[K], i, tmpfreq = 1;;
	char *curClassLable = gNearestDistance[0].classLabel;
	memset(freq, 1, sizeof(freq));
	//step.1---��ʼ������Ϊ���ֵ
	for (i = 0; i < K; i++)
	{
		gNearestDistance[i].distance = MAX_VALUE;
	}
	//step.2---����K-����ھ���
	for (i = 0; i < curTrainingSetSize; i++)
	{
		//step.2.1---����δ֪������ÿ��ѵ�������ľ���
		dist = Distance(gTrainingSet[i], Sample);
		//step.2.2---�õ�gNearestDistance�е�������
		maxid = GetMaxDistance();
		//step.2.3---�������С��gNearestDistance�е������룬�򽫸�������ΪK-���������
		if (dist < gNearestDistance[maxid].distance)
		{
			gNearestDistance[maxid].ID = gTrainingSet[i].ID;
			gNearestDistance[maxid].distance = dist;
			strcpy(gNearestDistance[maxid].classLabel, gTrainingSet[i].classLabel);
		}
	}
	//step.3---ͳ��ÿ������ֵĴ���
	for (i = 0; i < K; i++)
	{
		for (int j = 0; j < K; j++)
		{
			if ((i != j) && (strcmp(gNearestDistance[i].classLabel, gNearestDistance[j].classLabel) == 0))
			{
				freq[i] += 1;
			}
		}
	}
	//step.4---ѡ�����Ƶ����������
	for (i = 0; i<K; i++)
	{
		if (freq[i]>tmpfreq)
		{
			tmpfreq = freq[i];
			curClassLable = gNearestDistance[i].classLabel;
		}
	}
	return curClassLable;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    ������
//
////////////////////////////////////////////////////////////////////////////////////////////////////////

void main()
{
	char c;
	char *classLabel = "";
	int i, j, rowNo = 0, TruePositive = 0, FalsePositive = 0;
	ifstream filein("iris.data");
	FILE *fp;
	if (filein.fail()){ cout << "Can't open data.txt" << endl; return; }
	//step.1---���ļ� 
	while (!filein.eof())
	{
		rowNo++;//��һ������rowNo=1
		if (curTrainingSetSize >= MAX_SIZE_OF_TRAINING_SET)
		{
			cout << "The training set has " << MAX_SIZE_OF_TRAINING_SET << " examples!" << endl << endl;
			break;
		}
		//rowNo%3!=0��100��������Ϊѵ�����ݼ�
		if (rowNo % 3 != 0)
		{
			gTrainingSet[curTrainingSetSize].ID = rowNo;
			for (int i = 0; i < ATTR_NUM; i++)
			{
				filein >> gTrainingSet[curTrainingSetSize].attributes[i];
				filein >> c;
			}
			filein >> gTrainingSet[curTrainingSetSize].classLabel;
			curTrainingSetSize++;

		}
		//ʣ��rowNo%3==0��50�����������ݼ�
		else if (rowNo % 3 == 0)
		{
			gTestSet[curTestSetSize].ID = rowNo;
			for (int i = 0; i < ATTR_NUM; i++)
			{
				filein >> gTestSet[curTestSetSize].attributes[i];
				filein >> c;
			}
			filein >> gTestSet[curTestSetSize].classLabel;
			curTestSetSize++;
		}
	}
	filein.close();
	//step.2---KNN�㷨���з��࣬�������д���ļ�iris_OutPut.txt
	fp = fopen("iris_OutPut.txt", "w+t");
	//��KNN�㷨���з���
	fprintf(fp, "************************************����˵��***************************************\n");
	fprintf(fp, "** ����KNN�㷨��iris.data���ࡣΪ�˲������㣬�Ը����������rowNo����,��һ��rowNo=1!\n");
	fprintf(fp, "** ����150������,ѡ��rowNoģ3������0��100����Ϊѵ�����ݼ���ʣ�µ�50�����������ݼ�\n");
	fprintf(fp, "***********************************************************************************\n\n");
	fprintf(fp, "************************************ʵ����***************************************\n\n");
	for (i = 0; i < curTestSetSize; i++)
	{
		fprintf(fp, "************************************��%d������**************************************\n", i + 1);
		classLabel = Classify(gTestSet[i]);
		if (strcmp(classLabel, gTestSet[i].classLabel) == 0)//���ʱ��������ȷ
		{
			TruePositive++;
		}
		cout << "rowNo: ";
		cout << gTestSet[i].ID << "    \t";
		cout << "KNN������:      ";

		cout << classLabel << "(��ȷ����: ";
		cout << gTestSet[i].classLabel << ")\n";
		fprintf(fp, "rowNo:  %3d   \t  KNN������:  %s ( ��ȷ����:  %s )\n", gTestSet[i].ID, classLabel, gTestSet[i].classLabel);
		if (strcmp(classLabel, gTestSet[i].classLabel) != 0)//����ʱ���������
		{
			// cout<<"   ***�������***\n";
			fprintf(fp, "                                                                      ***�������***\n");
		}
		fprintf(fp, "%d-���ٽ�����:\n", K);
		for (j = 0; j < K; j++)
		{
			// cout<<gNearestDistance[j].ID<<"\t"<<gNearestDistance[j].distance<<"\t"<<gNearestDistance[j].classLabel[15]<<endl;
			fprintf(fp, "rowNo:  %3d   \t   Distance:  %f   \tClassLable:    %s\n", gNearestDistance[j].ID, gNearestDistance[j].distance, gNearestDistance[j].classLabel);
		}
		fprintf(fp, "\n");
	}
	FalsePositive = curTestSetSize - TruePositive;
	fprintf(fp, "***********************************�������**************************************\n", i);
	fprintf(fp, "TP(True positive): %d\nFP(False positive): %d\naccuracy: %f\n", TruePositive, FalsePositive, double(TruePositive) / (curTestSetSize - 1));
	fclose(fp);
	return;
}