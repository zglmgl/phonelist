#include <iostream>
#include <string>
#include <cstdlib>
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
	bool remove(Elme&);
	bool setpos(int pos);
	bool setstart() { fence = head; rightcnt += leftcnt; leftcnt = 0; }
	bool setend() { fence = tail; leftcnt += rightcnt; rightcnt = 0; }
	bool Isempty() { if (leftcnt == rightcnt == 0)return true; return false; }
	Elme getfence() { return fence->element; }
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

 template<class Elme> bool list<Elme>::insert(const Elme &it)//使用常引用既可以提高效率又可以保护实参不被修改
{
	 if (leftcnt==0&&rightcnt == 0)
	 {
		 node<Elme>*first=new node<Elme>(it);
		 //node<Elme> first(it);
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
	 rightcnt++;
	 return true;
}
 template<class Elme> bool list<Elme>::remove( Elme&it)
 {
	 if (leftcnt == 0 && rightcnt == 0)return false;
	 else 
	 {
		it = fence->element;
		fence->pre->next = fence->next;
		fence->next->pre = fence->pre;
		fence = fence->pre;
		if (fence == tail)
		{
			tail = fence->pre;
			fence = fence->pre;
		}
		 rightcnt--;
		 return true;
	 }
	 
 }

 template<class Elme> bool list<Elme>::setpos(int pos)
 {
	 if (pos<0 || pos>(rightcnt + leftcnt))return false;
	 fence = head;
	 for (int i = 0; i < pos; i++)
	 {
		 fence = fence->next;
	 }
	 return true;
 }





class student
{
public:
	void add(list<student> &directory);
static	void printnow(list<student> &directory, int num);


private:
	string name;
	unsigned int id;
	unsigned int phone;
	string addr;
};



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
	directory.insert(*this);
}

void student::printnow(list<student> &directory, int num)
{
	if (num<=0)cout << "输入大于零的整数位置" << endl;
	if (!directory.Isempty()) cout << "通讯录为空" << endl;
	directory.setpos(num);
	cout << "姓名：" << directory.getfence().name << endl << "学号：" << directory.getfence().id << endl << "电话："
		<< directory.getfence().phone <<endl<< "地址：" << directory.getfence().addr << endl;
}

list<student> directory;

void addnew()
{
	student a;
	a.add(directory);
}

//void show(list<student> &directory, int num)
//{
//	if (num<=0)cout << "输入大于零的整数位置" << endl;
//	if (!directory.Isempty()) cout << "通讯录为空" << endl;
//	directory.setpos(num);
//	cout << "姓名：" << directory.getfence().name << endl << "学号：" << directory.getfence().id << endl << "电话："
//		<< directory.getfence().phone <<endl<< "地址：" << directory.getfence().addr << endl;
//}

int main()
{
	int i;
	while (1)
	{
		cout << "新建联系人请输入1" << endl;
		cout << "显示联系人请输入2" << endl;
		cin >> i;
		switch (i)
		{
		case 1:
			addnew();
			cout << "新建成功，返回主菜单" << endl;
			break;
		case 2:
			//show(directory,);
			student::printnow(directory,1);
			cout << "返回主菜单" << endl;

	}

		


	}

}

