//���������

//����Ŀ�������������Ч�ؼ������ĸߴη��ġ������ص�o��n����ʱ�临�Ӷȣ�����log��n����

#include<iostream>
using namespace std;
int N;
struct matrix
{
	int a[3][3];
}origin,res;

matrix multiply(matrix x, matrix y)
{
	matrix temp;
	memset(temp.a,0,sizeof(temp.a));
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			for (size_t k = 0; k < 3; k++)
			{
				temp.a[i][j] += x.a[i][k] * y.a[k][j];
			}
		}
	}
	return temp;
}

void init()
{
	printf("����������£�\n");
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			origin.a[i][j] = rand() % 10;
			printf("%d",origin.a[i][j]);
			printf("\t");
		}
		printf("\n");
	}
	printf("\n");
	memset(res.a,0,sizeof(res.a));
	res.a[0][0] = res.a[1][1] = res.a[2][2]=1; //��ʼ��Ϊ��λ����
}

void calc(int n)
{
	printf("%d���ݽ�����£�\n", n);
	while (n)
	{
		if (n&1)
		{
			res = multiply(res,origin);  //��λ������κξ�����˵��ھ����� A^156=>(A^4)*(A^8)*(A^16)*(A^128) ��ȡ���õ�origin�������
		}
		n >>= 1;
		origin = multiply(origin, origin);  //���ﻹ�����۳�
	}

	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			printf("%d",res.a[i][j]);
			printf("\t");
		}
		printf("\n");
	}
	printf("\n");
}

int main()
{
	while (cin>>N)
	{
		init();
		calc(N);
	}
	return 0;
}