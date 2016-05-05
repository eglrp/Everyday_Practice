
#include <iostream>
using namespace std;

#define MAX 26
typedef struct TrieNode
{
	bool isStr; //��Ǹýڵ㴦�Ƿ񹹳ɵ���
	struct TrieNode *next[MAX];//���ӷ�֧
}Trie;

void insert(Trie *root,const char *s)
{
	if (root==nullptr||*s=='\0')
	{
		return;
	}
	int i;
	Trie *p = root;
	while (*s!='\0')
	{
		if (p->next[*s-'a']==nullptr)
		{
			Trie *temp = (Trie*)malloc(sizeof(Trie));
			for (i = 0; i < MAX;i++)
			{
				temp->next[i] = nullptr;
			}
			temp->isStr = false;
			p->next[*s - 'a'] = temp;
			p = p->next[*s - 'a'];
		}
		else
		{
			p = p->next[*s - 'a'];
		}
		s++;
	}
	p->isStr = true;//���ʽ�����λ�ñ�Ǵ˴����Թ���һ������
}

int search(Trie* root, const char *s)
{
	Trie *p = root;
	while (p!=nullptr&&*s!='\0')
	{
		p = p->next[*s-'a'];
		s++;
	}
	return (p!=nullptr&&p->isStr==true);
}

void del(Trie *root)
{
	for (int i = 0; i < MAX;i++)
   {
		if (root->next[i]!=nullptr)
		{
			del(root->next[i]);
		}
   }
	free(root);
}



int main(int argc, char *argv[])
{
	int n, m;//nΪ����Trie������ĵ�������mΪҪ���ҵĵ�����
	FILE *p;
	char s[100];
	Trie *root = (Trie*)malloc(sizeof(Trie));
	for (int i = 0; i < MAX;++i)
	{
		root->next[i] = nullptr;
	}
	root->isStr = false;
	cout << "����n:\n";
	cin >> n;
	//getchar();
	cout << "����"<<n<<"�����ʣ�\n";
	for (int i = 0; i < n;++i)
	{
		cin >> s;
		insert(root, s);
		
	}
	while (scanf("%d",&m)!=EOF)
	{
		cout << "����m�����ʲ��ң�����ʾ�����\n";
		for (int i = 0; i < m;++i)
		{
			cin >> s;
			if (search(root,s)==1)
			{
				cout << "YES\n";
			}
			else
			{
				cout << "NO\n";
			}
		}
	}
	del(root);
	return 0;
}



//int main()
//{
//	char str='a';
//	cout << (int)str << endl;
//}