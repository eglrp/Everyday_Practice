#include <iostream>
using namespace std;
#include <vector>

class Observer;
//���۲��߽ӿ�
class Account
{
protected:
	vector<Observer*> observers;
	double balance;
public:
	virtual void add_observers(Observer*) = 0;
	virtual void remove_observers(Observer*) = 0;
	virtual void notify_observers() = 0;
	virtual void set_balance(double balance) = 0;
	virtual double get_balance() = 0;
public:
	virtual ~Account()
	{
		cout << "in the destructor of Account" << endl;
	}
};

//Observer ������ӿ�
class Observer
{
protected:
	Account* account;
public:
	Observer(Account* _account) :account(_account){}
	virtual void handle_event() = 0;
	virtual void set_account_balance(double balance) = 0;
	virtual ~Observer()
	{
		cout << "in the destructor of Account" << endl;
	}
};

//BankAccount������
class BankAccount :public Account
{
public:
	~BankAccount(){ cout << "in the destructor of bankAccount"; }
public:
	void add_observers(Observer* o)
	{
		observers.push_back(o);
	}
	void remove_observers(Observer* o)
	{
		for (auto it = observers.begin(); it != observers.end(); it++)
		{
			if (*it == o)
			{
				observers.erase(it);
				return;
			}
		}
	}
	void notify_observers()
	{
		for (vector<Observer*>::const_iterator it = observers.begin(); it != observers.end(); it++)
		{
			(*it)->handle_event();
		}
	}
	void set_balance(double balance)
	{
		this->balance = balance;
		notify_observers();
	}
	double get_balance()
	{
		return balance;
	}
};


class ATM :public Observer
{
public:
	ATM(Account* _account) :Observer(_account){}
	~ATM()
	{
		cout << "int the destructor of ATM" << endl;
	}
public:
	void handle_event()
	{
		cout << "ATM:the balance of bank accont is changed to" << account->get_balance() << endl;
	}
	void set_account_balance(double balance)
	{
		account->set_balance(balance);
	}
};

class InternetBankService :public Observer
{
public:
	InternetBankService(Account* _account) :Observer(_account){}
	~InternetBankService()
	{
		cout << "in the destructor InternetBankService" << endl;
	}
public:
	void handle_event()
	{
		cout << "IBS��the balance of bank account is changed to" << account->get_balance() << endl;
	}
	void set_account_balance(double balance)
	{
		account->set_balance(balance);
	}
};

int main()
{ 
	Account* account = new BankAccount();   //��������ı��۲���
	Observer* atm_observer = new ATM(account);  //��������Ĺ۲���
	Observer* ibs_observer = new InternetBankService(account);
	account->add_observers(atm_observer);   //һ�Զ�Ĺ�ϵ���ܶ�۲��߹۲�һ������
	account->add_observers(ibs_observer);

	account->set_balance(1000.12);  //���۲��߱仯���������й۲��߱仯

	cout << "Event is triggered by atm_observer" << endl;
	cout << "==============" << endl;
	atm_observer->set_account_balance(1000.34);   //ĳһ���۲������𱻹۲��߱仯��Ҳ���������Ĺ۲��߱仯

	cout << "Event is triggered by ibs_observer" << endl;
	cout << "==============" << endl;
	ibs_observer->set_account_balance(1000.78);

	delete atm_observer;
	delete ibs_observer;
	return 0;
}