
//�򵥵��ַ���ƥ���㷨

#include <iostream>

using namespace std;

int Index_BF(char s[], char T[], int pos)
{
	int i = pos, j = 0;
	while (s[i+j]!='\0'&&T[j]!='\0')
	{
		if (s[i+j]==T[j])
		{
			j++;    //�����ȽϺ�һ�ַ�
		}
		else
		{
			i++;
			j = 0;   //���¿�ʼ��һ�ֵ�ƥ��
		}
	}
	if (T[j] == '\0')
	{
		return i; //ƥ��ɹ������±�
	}
	else
		return -1; //��s�У���pos���ַ��𣩲����ںʹ�T��ͬ���Ӵ�
}

int matchString(const string& target,const string& pattern)
{
	int target_size = target.size();
	int pattern_size = pattern.size();
	int target_index = 0;
	int pattern_index = 0;
	if (target_size<=0||pattern_size<=0||target_size<pattern_size)
	{
		return -1;
	}
	while (target_index<target_size&&pattern_index<pattern_size)//  �����е��ں�
	{
		if (target[target_index]==pattern[pattern_index])
		{
			target_index++;
			pattern_index++;
		}
		else
		{
			target_index = target_index - pattern_index + 1;  //��ǰ��־-ƥ��ĳ���+1
			pattern_index = 0;
		}
	}
	if (pattern_index==pattern_size&&target_index<=target_size)
	{
		return target_index - pattern_size ;
	}
	else
	{
		return -1;
	}
}

void compute_overlay(const string& pattern)   //���㸲�Ǻ���ֵk,�����Ӵ������Ҹ��ǳ̶�
{
	const int pattern_length = pattern.size();
	int* overlay_function = new int[pattern_length];

	int index;
	overlay_function[0] = -1;
	for (int i = 1; i < pattern_length;i++)
	{
		index = overlay_function[i - 1];  //�洢��ǰƥ��ʧ�ܵ�λ��
		while (index>=0&&pattern[i]!=pattern[index+1])  // pattern[i]!=pattern[index+1]
		{
			index = overlay_function[index];  //
		}
		if (pattern[i]==pattern[index+1])
		{
			overlay_function[i] = index + 1;
		}
		else
		{
			overlay_function[i] = -1;
		}
	}

	for (int i = 0; i < pattern_length;i++)
	{
		cout << overlay_function[i] << endl;
	}
	delete[] overlay_function;
}

int kmp_find(const string& target,const string& pattern)
{
	const int target_length = target.size();
	const int pattern_length = pattern.size();
	int* overlay_value = new int[pattern_length];
	int index;
	overlay_value[0] = -1;
	for (int i = 1; i < pattern_length; i++)
	{
		index = overlay_value[i - 1];  //�洢��ǰƥ��ʧ�ܵ�λ��
		while (index >= 0 && pattern[i] != pattern[index + 1])  // pattern[i]!=pattern[index+1]
		{
			index = overlay_value[index];  //
		}
		if (pattern[i] == pattern[index + 1])
		{
			overlay_value[i] = index + 1;
		}
		else
		{
			overlay_value[i] = -1;
		}
	}
	//ƥ���㷨
	int pattern_index = 0;
	int target_index = 0;
	while (pattern_index<pattern_length&&target_index<target_length)
	{
		if (target[target_index]==pattern[pattern_index])
		{
			++target_index;
			++pattern_index;
		}
		else if (pattern_index==0)
		{
			++target_index;
		}
		else
		{
			pattern_index = overlay_value[pattern_index - 1] + 1;
		}
	}
	if (pattern_index == pattern_length)
	{
		return target_index - pattern_index;
	}
	else
		return -1;
	delete[] overlay_value;

}

int main()
{
	string source = "annbcdanacadsannannabnna";
	string pattern = "annacanna";
	cout << "��һ�ַ�����" << Index_BF("banananobano", "nano", 0) << endl;

	cout << "�ڶ��ַ�����" << matchString(source, pattern) << endl;

	cout << "kmp:" << kmp_find(source,pattern) << endl;;
	string pattern1 = "abaabcaba";
	compute_overlay(pattern1);

	return 0;
}


