#include <iostream>
#include <string>
#include <cstdlib>
#include "phonelist.h"
using namespace std;



template <class Elme> class node
{
public:
	Elme element;
	node*next;
	node*pre;
	node(const Elme&ele, node*nextval = NULL, node*preval = NULL)
	{
		element = ele;
		next = nextval;
		pre = preval;
	}
	node( node*nextval = NULL, node*preval = NULL)
	{
		next = nextval;
		pre = preval;
	}
};

template<class Elme>class list
{
private:
	node<Elme>*head;
	node<Elme>*tail;
	node<Elme>*fence;
	int leftcnt;
	int rightcnt;
public:
	list()
	{
		fence = tail = head =new node<Elme>;
		leftcnt = rightcnt = 0;
	}
	~list()
	{
		while (fence != NULL)
		{
			fence = head;
			head = head->next;
			delete fence;
		}
	}
	void clear() { list(); ~list(); }
	bool insert(const Elme&);
	bool setpos(int pos);
	bool deletenode();
	void setstart() { fence = head; rightcnt += leftcnt; leftcnt = 0; }
	void setend() { fence = tail; leftcnt += rightcnt; rightcnt = 0; }
	bool Isempty() { if (leftcnt == rightcnt == 0)return true; return false; }
	Elme getfence() { return fence->element; }
	node<Elme>* getfencenode() { return fence; }
	int getlen() { return rightcnt + leftcnt; }
	void movetonext() { fence = fence->next; }
	void next() 
	{
		fence = fence->next;
		if (fence != tail)
		{
			rightcnt--;
			leftcnt++;
		}
		else setstart();
		

	}
		bool getvalue(Elme &it)
	{
		if (leftcnt == rightcnt == 0)
		return false;
		else
			it = fence->element;
		return true;
		
	}

};

class student
{
public:
	//student(string name1, long long id1, long long phone1, string addr1);
	//student();
	void p() { cout << this->name << endl << id << endl << phone << endl << addr; };

	void add(list<student> &directory);
	void change();
	static	void printnow(list<student> &directory, int num);
	static  int show(list<student> &directory);
	static  void edit(list<student> &directory, int num);

private:
	string name;
	long long id;
	long long phone;
	string addr;
};

 template<class Elme> bool list<Elme>::insert(const Elme &it)//使用常引用既可以提高效率又可以保护实参不被修改
{
	 if (leftcnt==0&&rightcnt == 0)
	 {
		 node<Elme>*first=new node<Elme>(it);
		 fence->next = first;
		 first->next = fence->next;
		 first->pre = fence->next;
	 }
	 else
	 {
		 fence->next = new node<Elme>(it, fence->next, fence);
		 fence->next->next->pre = fence->next;
	 }
	 if (fence == tail) tail = fence->next;
	 leftcnt++;
	 return true;
}

 template<class Elme> bool list<Elme>::setpos(int pos)
 {
	 if (pos<0 || pos>(rightcnt + leftcnt))return false;
	 fence = head;
	 rightcnt = leftcnt + rightcnt - pos;
	 leftcnt = pos;
	 for (int i = 0; i < pos; i++)
	 {
		 fence = fence->next;
	 }
	 return true;
 }

 template<class Elme> bool list<Elme>::deletenode()
 {
	 if (leftcnt == 0 && rightcnt == 0)return false;
	 if (head->next == fence)
	 {
		 head->next = fence->next;
	 }
	 fence->pre->next = fence->next;
	 fence->next->pre = fence->pre;
	 fence = fence->pre;
	 rightcnt--;
	
 }

// student::student(string name1, long long id1, long long phone1, string addr1)
//{
//	name=name1;
//	id=id1;
//	phone=phone1;
//	addr=addr1;
//
//}
//
// student::student() {};
//

void student::add(list<student> &directory)
{
	cout << "学生姓名" << endl;
	cin>>name;
	cout << "学生号" << endl;
	cin >> id;
	cout << "手机号" << endl;
	cin >> phone;
	cout << "宿舍" << endl;
	cin >> addr;
	directory.setend();
	directory.insert(*this);
	directory.movetonext();
}

void student::change()
{
	string new_name;
	long long new_id;
	long long new_phone;
	string new_addr;
	cout << "学生姓名" << endl;
	cin >> new_name;
	cout << "学生号" << endl;
	cin >> new_id;
	cout << "手机号" << endl;
	cin >> new_phone;
	cout << "宿舍" << endl;
	cin >> new_addr;
	this->name = new_name;
	this->id = new_id;
	this->phone=new_phone;
	this->addr= new_addr;
}

int student::show(list<student> &directory)
{
	int num;
	num = directory.getlen();
	if (num == 0)
	{
		cout << "通讯录为空" << endl;
		return 0;
	}
	else
	{
		directory.setstart();
		for (int i = 0; i < num; i++)
		{
			directory.movetonext();
			cout << "序号" << i + 1<<":" << directory.getfence().name << endl;
		}

	}
	return 1;
}

void student::edit(list<student> &directory, int num)
{
	int n;
	student::printnow(directory, num);
	directory.setpos(num);
	cout << "需要删除请输入1，需要编辑请输入2" << endl;
	cin >> n;
	if (n == 1)
	{
		directory.deletenode();
	}
	if (n == 2)
	{
	directory.getfencenode()->element.change();
	}
	if(n != 1&& n != 2)cout << "输入错误" << endl;
}

void student::printnow(list<student> &directory, int num)
{
	if (num<=0)cout << "输入大于零的整数位置" << endl;
	if (!directory.Isempty()) cout << "通讯录为空" << endl;
	else 
	{
		directory.setpos(num);
		cout << "姓名：" << directory.getfence().name << endl << "学号：" << directory.getfence().id << endl << "电话："
			<< directory.getfence().phone << endl << "地址：" << directory.getfence().addr << endl;
	}
	
}


list<student> directory;

void addnew()
{
	student a;
	a.add(directory);
}

int main()
{
	int i;
	while (1)
	{
		cout << "新建联系人请输入1" << endl;
		cout << "显示联系人请输入2" << endl;
		cout << "编辑联系人请输入3" << endl;
		cin >> i;
		switch (i)
		{
		case 1:
			addnew();
			cout << "新建成功，返回主菜单" << endl;
			break;
		case 2:
			int num1;
			if (student::show(directory))
			{
				cout << "请输入要显示的序号" << endl;
				cin >> num1;
				student::printnow(directory, num1);
			}
			cout << "返回主菜单" << endl;
			break;
		case 3:
			int num2;
			student::show(directory);
			cout << "请输入要编辑的序号" << endl;
			cin >> num2;
			student::edit(directory,num2);
			cout << "返回主菜单" << endl;
			break;
	}

		


	}



}

