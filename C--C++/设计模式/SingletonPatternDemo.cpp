/*****************************************************
* \file     SingletonPatternDemo.cpp
* \date     2016/07/13 18:20
* \author   ranjiewen
* \contact: ranjiewen@outlook.com 
*****************************************************/

#include <iostream>
using namespace  std;
class Singleton
{
public:
	static Singleton* GetInstance()
	{
		if (m_Instance == nullptr)
		{
			//Lock(); // C++û��ֱ�ӵ�Lock��������ʹ���������Lock������Boost���˴���Ϊ��˵��
			m_Instance = new Singleton();
			//UnLock();
		}
		return m_Instance;
	}
	//�ڶ��ַ�ʽ
	static Singleton* GetInstance()
	{
		return const_cast<Singleton*>m_Instance;
	}

	static void Destory()
	{
		if (m_Instance != nullptr)
		{
			delete m_Instance;
			m_Instance = nullptr;
		}
	}
	//this is just a operation example
	int GetTest()
	{
		return m_test;
	}
private:
	//�����У�Ҫ����һ��ʵ�����ͱ��������Ĺ��캯������ˣ�Ϊ�˷�ֹ���ⲿ������Ĺ��캯��������ʵ����
	//��Ҫ�����캯���ķ���Ȩ�ޱ��Ϊprotected��private��
	Singleton(int _test = 10) :m_test(_test){}  //���캯��  
	int m_test;
	static Singleton* m_Instance;
	//static int point;
	//�ڶ��ַ�ʽ
	static const Singleton* m_Instance;
};

Singleton *Singleton::m_Instance = nullptr;
const Singleton *Singleton::m_Instance = new Singleton();
//int Singleton::point=0;


int main(int argc, char* argv[])
{
	Singleton* singletonObj = Singleton::GetInstance();
	std::cout << singletonObj->GetTest() << std::endl;
	Singleton::Destory();
	return 0;
}


