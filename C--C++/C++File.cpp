#include <io.h>
#include <iostream>
#include <fstream>
using namespace std;

bool transfer(string fileName, int exeNum );
void dfsFolder(string folderPath, ofstream &fout);

int main()
{
	_finddata_t file;
	int k;
	long HANDLE;
	k = HANDLE = _findfirst("*.*", &file);
	while (k != -1)
	{
		cout << file.name << endl;
		k = _findnext(HANDLE, &file);
	}
	_findclose(HANDLE);

	transfer("C:\\Windows\\*.exe", 0);
	ofstream o_fstream;

	dfsFolder("E:\\\WHU\\Study", o_fstream);


	return 0;
}

//_findfirst �������ص���ƥ�䵽�ļ��ľ������������Ϊlong��
//�������̿���ָ���ļ����ͣ���ͨ��FileName�ĸ�ֵ��ʵ�֣�����Ҫ����C : \WINDOWS�µ�����.exe�ļ�

bool transfer(string fileName , int exeNum)
{
	_finddata_t fileInfo;
	long handle = _findfirst(fileName.c_str(), &fileInfo);

	if (handle == -1L)
	{
		cerr << "failed to transfer files" << endl;
		return false;
	}

	do
	{
		exeNum++;
		cout << fileInfo.name << endl;
	} while (_findnext(handle, &fileInfo) == 0);
	cout << " .exe files' number:  " << exeNum << endl;

	return true;
}

//�����ļ��м������ļ����������ļ�������ϵͳ���ļ���Ŀ¼����״�ṹ��ʹ������������Ա��������ļ����õ�_A_SUBDIR����


//���ж�������Ŀ¼��if��֧�У�����ϵͳ�ڽ���һ����Ŀ¼ʱ��ƥ�䵽��ͷ�����ļ�(��)��"."(��ǰĿ¼)��".."(��һ��Ŀ¼)��
//��Ҫ���Ե����������������Ҫ�Ա��������ļ�������ʱ����else��֧�������Ӧ�Ĵ���ͺ�

void dfsFolder(string folderPath, ofstream &fout)
{
	_finddata_t FileInfo;
	string strfind = folderPath + "\\*";
	long Handle = _findfirst(strfind.c_str(), &FileInfo);

	if (Handle == -1L)
	{
		cerr << "can not match the folder path" << endl;
		exit(-1);
	}
	do{
		//�ж��Ƿ�����Ŀ¼  
		if (FileInfo.attrib & _A_SUBDIR)
		{
			//���������Ҫ  
			if ((strcmp(FileInfo.name, ".") != 0) && (strcmp(FileInfo.name, "..") != 0))
			{
				string newPath = folderPath + "\\" + FileInfo.name;
				dfsFolder(newPath, fout);
			}
		}
		else
		{
			fout<<folderPath.c_str() << "\\" << FileInfo.name << " ";
			cout << folderPath.c_str() << "\\" << FileInfo.name << endl;
		}
	} while (_findnext(Handle, &FileInfo) == 0);

	_findclose(Handle);
	fout.close();
}


//#include <iostream>    
//#include <string>    
//#include <io.h>    
//using namespace std;
//
//int main()
//{
//	_finddata_t file;
//	long longf;
//	string tempName;
//	//_findfirst���ص���long��; long __cdecl _findfirst(const char *, struct _finddata_t *)    
//	if ((longf = _findfirst("E:\\WHU\\Study\\*.*", &file)) == -1l)
//	{
//		cout << "�ļ�û���ҵ�!\n";
//		return 0;
//	}
//	do
//	{
//		cout << "�ļ��б�:\n";
//		tempName = file.name;
//		if (tempName[0] == '.')
//			continue;
//		cout << file.name<<endl;
//
//		if (file.attrib == _A_NORMAL)
//		{
//			cout << "  ��ͨ�ļ�  ";
//		}
//		else if (file.attrib == _A_RDONLY)
//		{
//			cout << "  ֻ���ļ�  ";
//		}
//		else if (file.attrib == _A_HIDDEN)
//		{
//			cout << "  �����ļ�  ";
//		}
//		else if (file.attrib == _A_SYSTEM)
//		{
//			cout << "  ϵͳ�ļ�  ";
//		}
//		else if (file.attrib == _A_SUBDIR)
//		{
//			cout << "  ��Ŀ¼  ";
//		}
//		else
//		{
//			cout << "  �浵�ļ�  ";
//		}
//		cout << endl;
//	} while (_findnext(longf, &file) == 0);//int __cdecl _findnext(long, struct _finddata_t *);����ҵ��¸��ļ������ֳɹ��Ļ��ͷ���0,���򷵻�-1   
//
//	_findclose(longf);
//
//	return 0;
//}


#include<iostream>   
#include<fstream>  
using namespace std;
//����Ҫɾ�����кŸ�ʽ�����涨���������: #0001 ���к�  
const int LINE_NUM_LENGTH = 5;
const char LINE_NUM_START = ��#��;
int main(int argc, char *argv[])
{
	fstream f;
	char *s = NULL;
	int n;
	for (int i = 1; i < argc; i) {
		cout << "Processing file " << argv[i] << "......";
		f.open(argv[i], ios::in | ios::binary);
		if (!f.is_open()){
			cout << "CANNOT OPEN" << endl;
			continue;
		}
		f.seekg(0, ios::end);
		n = f.tellg(); // �ļ���С  
		s = new char[n 1];
		f.seekg(0, ios::beg);
		f.read(s, n);
		s[n] = ��\0��;
		f.close();
		// ����һ�ּ򵥵��жϣ�����LINE_NUM_START���һ�����֣�  
		// ����Ϊ����һ���к�.  
		for (int j = 0; j < n; j) {
			if (s[j] == LINE_NUM_START && (s[j 1] >= ��0�� && s[j 1] <= ��9��)) {
				for (int k = j; k < j LINE_NUM_LENGTH; k)
					s[k] = �� ��;
			}
		}
		f.open(argv[i], ios::out | ios::binary);
		if (!f.is_open()) {
			cout << "CANNOT OPEN" << endl;
			delete[] s;
			continue;
		}
		f.write(s, n);
		f.close();
		cout << "OK" << endl;
		delete[] s;
	}
	return 0;
}