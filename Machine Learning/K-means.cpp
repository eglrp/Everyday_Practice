#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define k 3//�ص���Ŀ
using namespace std;
//���Ԫ���������Ϣ
typedef vector<double> Tuple;//�洢ÿ�����ݼ�¼

int dataNum;//���ݼ������ݼ�¼��Ŀ
int dimNum;//ÿ����¼��ά��

//��������Ԫ����ŷ�������
double getDistXY(const Tuple& t1, const Tuple& t2)
{
	double sum = 0;
	for (int i = 1; i <= dimNum; ++i)
	{
		sum += (t1[i] - t2[i]) * (t1[i] - t2[i]);
	}
	return sqrt(sum);
}

//�������ģ�������ǰԪ�������ĸ���
int clusterOfTuple(Tuple means[], const Tuple& tuple){
	double dist = getDistXY(means[0], tuple);
	double tmp;
	int label = 0;//��ʾ������һ����
	for (int i = 1; i < k; i++){
		tmp = getDistXY(means[i], tuple);
		if (tmp < dist) { dist = tmp; label = i; }
	}
	return label;
}
//��ø����ؼ���ƽ�����
double getVar(vector<Tuple> clusters[], Tuple means[]){
	double var = 0;
	for (int i = 0; i < k; i++)
	{
		vector<Tuple> t = clusters[i];
		for (int j = 0; j < t.size(); j++)
		{
			var += getDistXY(t[j], means[i]);
		}
	}
	//cout<<"sum:"<<sum<<endl;
	return var;

}
//��õ�ǰ�صľ�ֵ�����ģ�
Tuple getMeans(const vector<Tuple>& cluster){

	int num = cluster.size();
	Tuple t(dimNum + 1, 0);
	for (int i = 0; i < num; i++)
	{
		for (int j = 1; j <= dimNum; ++j)
		{
			t[j] += cluster[i][j];
		}
	}
	for (int j = 1; j <= dimNum; ++j)
		t[j] /= num;
	return t;
	//cout<<"sum:"<<sum<<endl;
}

void print(const vector<Tuple> clusters[])
{
	for (int lable = 0; lable < k; lable++)
	{
		cout << "��" << lable + 1 << "���أ�" << endl;
		vector<Tuple> t = clusters[lable];
		for (int i = 0; i < t.size(); i++)
		{
			cout << i + 1 << ".(";
			for (int j = 0; j <= dimNum; ++j)
			{
				cout << t[i][j] << ", ";
			}
			cout << ")\n";
		}
	}
}

void KMeans(vector<Tuple>& tuples){
	vector<Tuple> clusters[k];//k����
	Tuple means[k];//k�����ĵ�
	int i = 0;
	//һ��ʼ���ѡȡk����¼��ֵ��Ϊk���ص����ģ���ֵ��
	srand((unsigned int)time(NULL));
	for (i = 0; i < k;){
		int iToSelect = rand() % tuples.size();
		if (means[iToSelect].size() == 0)
		{
			for (int j = 0; j <= dimNum; ++j)
			{
				means[i].push_back(tuples[iToSelect][j]);
			}
			++i;
		}
	}
	int lable = 0;
	//����Ĭ�ϵ����ĸ��ظ�ֵ
	for (i = 0; i != tuples.size(); ++i){
		lable = clusterOfTuple(means, tuples[i]);
		clusters[lable].push_back(tuples[i]);
	}
	double oldVar = -1;
	double newVar = getVar(clusters, means);
	cout << "��ʼ�ĵ��������ƽ����Ϊ��" << newVar << endl;
	int t = 0;
	while (abs(newVar - oldVar) >= 1) //���¾ɺ���ֵ����1��׼����ֵ���������Ա仯ʱ���㷨��ֹ
	{
		cout << "�� " << ++t << " �ε�����ʼ��" << endl;
		for (i = 0; i < k; i++) //����ÿ���ص����ĵ�
		{
			means[i] = getMeans(clusters[i]);
		}
		oldVar = newVar;
		newVar = getVar(clusters, means); //�����µ�׼����ֵ
		for (i = 0; i < k; i++) //���ÿ����
		{
			clusters[i].clear();
		}
		//�����µ����Ļ���µĴ�
		for (i = 0; i != tuples.size(); ++i){
			lable = clusterOfTuple(means, tuples[i]);
			clusters[lable].push_back(tuples[i]);
		}
		cout << "�˴ε���֮����������ƽ����Ϊ��" << newVar << endl;
	}

	cout << "The result is:\n";
	print(clusters);
}
int main(){

	char fname[256] = "iris.txt";   //�ļ�ÿ�������Կո�ֿ�����һ��Ϊ��ǩ�������ĸ�Ϊ����
	//cout << "�����������ݵ��ļ����� ";
	//cin >> fname;
	//cout << endl << " ����������: ά�� ������Ŀ" << endl;
	//cout << endl << " ά��dimNum: ";
	//cin >> dimNum;
	//cout << endl << " ������ĿdataNum: ";
	//cin >> dataNum;
	dimNum = 4;
	dataNum = 150;
	ifstream infile(fname);
	if (!infile){
		cout << "���ܴ�������ļ�" << fname << endl;
		return 0;
	}
	vector<Tuple> tuples;
	//���ļ����ж�������
	for (int i = 0; i < dataNum && !infile.eof(); ++i)
	{
		string str;
		getline(infile, str);
		istringstream istr(str);
		Tuple tuple(dimNum + 1, 0);//��һ��λ�ô�ż�¼��ţ���2��dimNum+1��λ�ô��ʵ��Ԫ��
		tuple[0] = i + 1; //����ۼ�
		for (int j = 1; j <= dimNum; ++j)
		{
			istr >> tuple[j];
		}
		tuples.push_back(tuple);
	}

	cout << endl << "��ʼ����" << endl;
	KMeans(tuples);


	vector<vector<int> > vec;
	return 0;
}
