
//��֪����A��B��Ԫ�طֱ��ò���ͷ���ĵ�����洢������difference()������⼯��A��B�Ĳ��������������ڼ���A�ĵ������С�
//���磬������A = { 5, 10, 20, 15, 25, 30 }������B = { 5, 15, 35, 25 }����ɼ����A = { 10, 20, 30 }��

#include<stdio.h>
#include<stdlib.h>
struct node
{
	int elem;
	node* next;
};

void difference(node** LA, node* LB)
{
	node *pa, *pb, *pre, *q;
	pre = nullptr;
	pa = *LA; //1   
	while (pa)  
	{
		pb = LB;
		while (pb&&pb->elem!=pa->elem)   //2   
			pb = pb->next;
		if (pb)    //��Ϊ�գ�˵������ͬ�ģ�Ϊ�ռ�û����ͬ��             
		{
			if (!pre)  //Ϊ��
				*LA = pa->next;     //4   
			else
				*LA = pre->next;     //5
			q = pa;
			pa = pa->next;
			free(q);
		}
		else  
		{
			pre=pa;             //6   
			pa = pa->next;
		}
	}
}


