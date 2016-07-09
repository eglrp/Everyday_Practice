#include <iostream>
using namespace std;

class COperator   //������Ļ���
{
public:  //
	int m_first;
	int m_second;
public:
	virtual double getResult() = 0;
	//int add(){ return m_second + m_first; } //˽�г�Ա�ڱ�����Է��ʺ���������ڲ����ⲿ�����ܷ��ʣ������ͳ�Ա�������ڲ����Է��ʣ��ⲿ���ܷ��ʣ����г�Ա�������ڲ����ⲿ���ܷ��ʣ�ǰ��Ϊ���м̳�
};

class AddOperator : public COperator
{
public:
	virtual double getResult() override
	{
		return m_first + m_second;
	}
};

class SubOperator:public COperator
{
public:
	virtual double getResult() override
	{
		return m_first - m_second;
	}
};

//�򵥹�����
class CSimpleFactory
{
public:
	static COperator* create(char ope);
};
COperator* CSimpleFactory::create(char ope)
{
	COperator* op = nullptr;
	switch (ope)
	{
	case '+':
		op = new AddOperator(); break;
	case '-':
		op = new SubOperator(); break;
	default:
		break;
	}
	return op;
}


//�ͻ���
int main()
{
	int a, b;
	cin >> a >> b;
	COperator* op = CSimpleFactory::create('+');
	op->m_first = a;
	op->m_second = b;
	cout << op->getResult() << endl;
	return 0;
}