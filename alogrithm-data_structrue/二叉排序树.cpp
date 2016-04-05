//#include <stdio.h>
//#include <stdlib.h>
//
//typedef struct node {
//	int key;
//	struct node *LChild, *RChild; //����ָ��
//}BSTNode, *BSTree;   //���������----������
//
//void CreatBST(BSTree *bst);
//BSTree SearchBST(BSTree bst, int key);
//void InsertBST(BSTree *bst, int key);
//BSTNode * DelBST(BSTree t, int k);//�����Ǻ���������
//
//void print_bst(BSTree t) //��ӡ
//{
//	if (t)//����˳���ӡ
//	{
//		print_bst(t->LChild);
//		printf("%d\t", t->key);
//		print_bst(t->RChild);
//	}
//}
//const int n = 10;
///*������*/
//void CreatBST(BSTree *bst)
//{
//	printf("������%d��������������������",n);
//	int i;
//	int key;
//	*bst = NULL;
//	for (i = 1; i <= n; i++)
//	{
//		scanf("%d", &key);
//		InsertBST(bst, key); //����   
//	};
//}
///*Ѱ��*/
//BSTree SearchBST(BSTree bst, int key)
//{
//	if (!bst)
//		return nullptr;       //bstΪ��   
//	else   if (bst->key == key)
//	{
//		printf("���ҳɹ���");
//		return bst;           //�ҵ������ؽڵ�   
//	}
//	else   if (key < bst->key)
//		return SearchBST(bst->LChild, key); //���ӵݹ���ò���       
//	else
//		return SearchBST(bst->RChild, key); //�Һ��ӵݹ�
//}
///*����*/
//void InsertBST(BSTree *bst, int key)
//{
//	BSTree t;
//	if (*bst == NULL)
//	{
//		t = (BSTree)malloc(sizeof(BSTNode)); //��Ϊ�գ�����ռ�     
//		t->key = key;
//		t->LChild = NULL;
//		t->RChild = NULL;
//		*bst = t; //���� 
//		//printf("����ɹ���");
//	}
//	else if (key <(*bst)->key)
//		InsertBST(&((*bst)->LChild), key); //�嵽������   
//	else if (key>(*bst)->key)
//		InsertBST(&((*bst)->RChild), key); //�嵽������
//}
///*ɾ��*/   //�����⣿û����⣡
//BSTNode * DelBST(BSTree t, int k)  //����LRΪ0��1,ɾ��T��p��ָ�������������
//{
//	BSTNode *p, *f, *s, *q;
//	p = t;
//	s = t;//
//	f = NULL;
//	while (p) //���ǿ�,���ҵ�key��λ��
//	{
//		if (p->key == k) //���ڵ����K       
//			break;
//		f = p;          //f��¼k���ڵĽڵ�� ˫�׽ڵ�
//		if (p->key > k) //������������         
//			p = p->LChild;
//		else
//			p = p->RChild; //��  
//	}
//	if (p == NULL) //Ϊ��     
//		return t;
//	if (p->LChild == nullptr)  //��� ���±߾���ɾ������   
//	{
//		if (f == NULL) //��ɾ�����Ϊ���ڵ�
//			t = p->RChild;
//		else if (f->LChild == p)
//			f->LChild = p->RChild;
//		else
//			f->RChild = p->RChild;
//		free(p); //�ͷſռ�   
//	}
//	else //�ң��±߾���ɾ������ 
//	{
//		q = p;
//		s = p->LChild;
//		while (s->RChild)
//		{
//			q = s;
//			s = s->RChild;
//		}
//		if (q == p)
//			q->LChild = s->LChild;
//		else
//			q->RChild = s->LChild;
//		p->key = s->key;
//		free(s); //�ͷſռ�    
//	}
//	return t;
//}
//
//int main()
//{
//	BSTNode * root=nullptr;
//	int loop, i, data;
//	loop = true;
//	while (loop)
//	{
//		printf("\n***************�����������˵�**************\n");
//		printf(" 1.����\n");
//		printf(" 2.����\n");
//		printf(" 3.����\n");
//		printf(" 4.ɾ��\n");
//		printf(" 5.��ӡ\n");
//		printf(" 0.�˳�\n");
//		scanf("%d", &i);
//		switch (i)
//		{
//		case 0:
//		{
//				  loop = false;
//				  break;
//		}
//		case 1:
//		{
//				  CreatBST(&root);
//		}break;
//		case 2:
//		{
//				  printf("Please input the data you want search.\n");
//				  scanf("%d", &data);
//				  SearchBST(root, data);
//
//		}break;
//		case 3:
//		{         printf("Please input the data you want insert.\n");
//		          scanf("%d", &data);
//		          InsertBST(&root, data);
//				  printf("����ɹ���");
//		}break;
//		case 4:
//		{
//				  printf("Please input the data you want delete.\n");
//				  scanf("%d", &data);
//				  root = DelBST(root, data);
//		}break;
//		case 5:{
//				   printf("\n");
//				   if (root != NULL)
//					   printf("The BSTree's root is:%d\n", root->key);
//				   print_bst(root);
//				   break;
//		}
//		}
//	}
//}


#include <iostream>
#include <cstring>
using namespace std;

typedef int KeyType;
#define NUM 11

class BinStree;
class BinSTreeNode
{
public:
	KeyType key;
	BinSTreeNode *lchild;
	BinSTreeNode *rchild;
	BinSTreeNode()
	{
		lchild = NULL;
		rchild = NULL;
	}
};

class BinSTree
{
public:
	BinSTreeNode *root;
	BinSTree()
	{
		root = NULL;
	}
	~BinSTree()
	{
		//delete root;
	}
	BinSTreeNode *BSTreeSearch(BinSTreeNode *bt, KeyType k, BinSTreeNode *&p);
	void BSTreeInsert(BinSTreeNode *&bt, KeyType k);
	int BSTreeDelete(BinSTreeNode *&bt, KeyType k);
	void BSTreePreOrder(BinSTreeNode *bt);
	bool IsEmpty()
	{
		return root == NULL;
	}
};

/**
*  ��������������㷨
*  �ڸ�ָ��Ϊbt�Ķ����������в���Ԫ��k�Ľڵ㣬�����ҳɹ����򷵻�ָ��ýڵ��ָ��
*  ����pָ����ҵ��Ľ�㣬���򷵻ؿ�ָ�룬����pָ��kӦ����ĸ����
*/
BinSTreeNode* BinSTree::BSTreeSearch(BinSTreeNode *bt, KeyType k, BinSTreeNode *&p)
{
	BinSTreeNode *q = NULL;
	q = bt;
	while (q)
	{
		p = q;
		if (q->key == k)
		{
			return(p);
		}
		if (q->key > k)
			q = q->lchild;
		else
			q = q->rchild;
	}
	return NULL;
}

/**
*  �����������Ĳ���ڵ��㷨
*  btָ������������ĸ���㣬����Ԫ��k�Ľ��
*/
void BinSTree::BSTreeInsert(BinSTreeNode *&bt, KeyType k)
{
	BinSTreeNode *p = NULL, *q;
	q = bt;
	if (BSTreeSearch(q, k, p) == NULL)
	{
		BinSTreeNode *r = new BinSTreeNode;
		r->key = k;
		r->lchild = r->rchild = NULL;
		if (q == NULL)
		{
			bt = r;         //������ڵ���Ϊ���ĸ��ڵ�
		}
		if (p && k < p->key)
			p->lchild = r;
		else if (p)
			p->rchild = r;
	}
}
/**
* �������
*/
void BinSTree::BSTreePreOrder(BinSTreeNode *bt)
{
	if (bt != NULL)
	{
		cout << bt->key << " ";
		BSTreePreOrder(bt->lchild);
		BSTreePreOrder(bt->rchild);
	}
}
/**
* ������������ɾ������㷨
* �ڶ�����������ɾ��Ԫ��Ϊk�Ľ�㣬*btָ������������ĸ��ڵ�
* ɾ���ɹ�����1�����ɹ�����0.
*/
int BinSTree::BSTreeDelete(BinSTreeNode *&bt, KeyType k)
{
	BinSTreeNode *f, *p, *q, *s;
	p = bt;
	f = NULL;
	//���ҹؼ���Ϊk�Ľ�㣬ͬʱ���˽���˫���ҳ���
	while (p && p->key != k)
	{
		f = p;  //fΪ˫��
		if (p->key > k)
			p = p->lchild;
		else
			p = p->rchild;
	}
	if (p == NULL)   //�Ҳ�����ɾ���Ľ��ʱ����
		return 0;
	if (p->lchild == NULL)  //��ɾ������������Ϊ��
	{
		if (f == NULL)  //��ɾ�����Ϊ���ڵ�
			bt = p->rchild;
		else if (f->lchild == p)  //��ɾ�������˫�׽�����ڵ�
			f->lchild = p->rchild;
		else
			f->rchild = p->rchild;  //��ɾ�������˫�׽����ҽڵ�
		delete p;
	}
	else                    //��ɾ����������������൱���ж����ڵ�
	{
		q = p;
		s = p->lchild;
		while (s->rchild)  //�ڴ�ɾ�������������в��������½��
		{
			q = s;
			s = s->rchild;  //�������������ֵ
		}
		if (q == p)
			q->lchild = s->lchild;
		else
			q->rchild = s->lchild;

		p->key = s->key;
		delete s;
	}
	return 1;
}
int main(void)
{
	int a[NUM] = { 34, 18, 76, 13, 52, 82, 16, 67, 58, 73, 72 };
	int i;
	BinSTree bst;
	BinSTreeNode *pBt = NULL, *p = NULL, *pT = NULL;

	for (i = 0; i < NUM; i++)
	{
		bst.BSTreeInsert(pBt, a[i]); //��������������
	}
	pT = bst.BSTreeSearch(pBt, 52, p); //�������������
	bst.BSTreePreOrder(pBt);
	cout << endl;
	bst.BSTreeDelete(pBt, 13);   //ɾ�������ӵ����
	bst.BSTreePreOrder(pBt);
	cout << endl;
	bst.BSTreeDelete(pBt, 76);   //ɾ�������ӵ����
	bst.BSTreePreOrder(pBt);
	cout << endl;
	return 0;
}