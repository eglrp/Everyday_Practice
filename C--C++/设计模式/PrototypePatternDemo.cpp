/*****************************************************
* \file PrototypePatternDemo.cpp
* \date 2016/07/21 21:17
* \author ranjiewen
* \contact: ranjiewen@outlook.com 

//ԭ��ģʽ�ͽ�����ģʽ����������ģʽһ���������ڴ�����ģʽ��һ�֡��򵥵���˵������ʹ��ԭ��ģʽ������Ϊ�˴�������
//���ĳ������Ҫʵ��Clone���ܣ���ֻ��Ҫ�̳�Prototype�࣬Ȼ����д�Լ���Ĭ�ϸ��ƹ��캯���ͺ��ˡ�

*****************************************************/

#include <iostream>
using namespace std;

//�ӿ�
class Prototype
{
public:
	Prototype(){}
	virtual ~Prototype(){}
	virtual Prototype* clone() = 0;
};
//ʵ��
class ConcretePrototype :public Prototype
{
public:
	ConcretePrototype(){}
	virtual ~ConcretePrototype(){}
	//�������캯��
	ConcretePrototype(const ConcretePrototype& rhs)
	{
		this->m_counter = rhs.m_counter;
	}
	virtual ConcretePrototype* clone()
	{
	//���ÿ������캯��
		return new ConcretePrototype(*this);
	}
private:
	int m_counter;
};

int main()
{
	ConcretePrototype* conProA = new ConcretePrototype();
	ConcretePrototype* conProB = conProA->clone();
	delete conProA;
	conProA = nullptr;
	delete conProB;
	conProB = nullptr;
	return 0;
}