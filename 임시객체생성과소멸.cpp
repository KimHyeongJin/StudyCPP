#include <iostream>

//#include <conio.h>

using namespace std;

class SoSimple
{
private:
	int num;
public:
	SoSimple(int n):num(n)
	{
		cout<<"New Object : "<<this<<endl;
	}
	SoSimple(const SoSimple &copy):num(copy.num)
	{
		cout<<"New Copy obj : "<<this<<endl;
	}
	~SoSimple()
	{
		cout<<"Destory obj : "<<this<<endl;
	}
	void ShowInfo()
	{
		cout<<"num : "<<num<<endl;	
	}

};

SoSimple SimpleFuncObj(SoSimple ob)
{
	cout<<"Param ADR : "<<&ob<<endl;
	return ob;
}

void SimpleFuncRef(const SoSimple& ref)
{
	cout<<"SimpleFuncRef : "<<&ref<<endl;
}

int& ReturnRef(int& ref)
{
	return ref;
}

int ReturnInt(int& num)
{
	return num;
}

#if 1
void main()
{
	SoSimple obj(7);
	SimpleFuncObj(obj);//���� �����ڸ� ���� ��ü�� �����ȴ�. ���࿡ ����� string�� ��ü�� ���� �ִٸ� string��ü�� ���� �����ڵ� ȣ��ȴ�...
	SimpleFuncRef(obj);//���� �����ڸ� ���� ��ü ������ ����. const�� ���� ��� ����.

	cout<<endl;
	SoSimple tempRef = SimpleFuncObj(obj);//
	//SoSimple &tempRef = SimpleFuncObj(obj);//�� ǥ���İ� ���� ���, �ӽð�ü��.cpp ����, ��ü�� ��� �����ڸ� �ӽð�ü�� �ʱ�ȭ�� �����ϱ���.
	cout<<"Return Obj : "<<&tempRef<<endl;


	cout<<endl<<endl;
	//cout<<"Return Obj : "<<tempRef<<endl;//����;;;;;;;;;;;;
	tempRef.ShowInfo();
	
	SoSimple *pTemp = &tempRef;
	cout<<"pTemp : "<<pTemp<<endl;
	(*pTemp).ShowInfo();//���������� 7�� ����....
	pTemp->ShowInfo();

	//�⺻�ڷ����� ��1
	int num1=1;
	int &ref = num1;
	int num2 = num1;
	//�Լ��� ��ȯ���� �������ϰ���� ��
	int &ref2 = ReturnRef(num2);//��ȯ���� ����ϰ��� ����
	int num3 = ReturnRef(num1);

	
	//int &ref3 = ReturnInt(num1);//Error. 'int'���� 'int &'(��)�� ��ȯ�� �� �����ϴ�. �⺻ �ڷ����� int &ref3 = 1�� ���� �����ڸ� �ӽ� ������ �ʱ�ȭ �Ҽ� ����
	
	const int &ref3 = 1;//�� const �����ڴ� ���׿� �ִ� ��� 1�� �ӽú���ȭ �ؼ� �ʱ�ȭ ����

	//������ ��ü�� ���� �� SoSimple &tempRef = SimpleFuncObj(obj); ���� ���� �� �ȴ�.

	system("pause");
	
}

/*
New Object : 0042F9E8//obj(7)
New Copy obj : 0042F8D8//ob = obj,ob�� ���� ������ ȣ��
Param ADR : 0042F8D8//ob�� �ּ�
New Copy obj : 0042F904//�ӽð�ü ������ ob�� �ʱ�ȭ �׸��� �ӽð�ü�� ��������� ȣ��
Destory obj : 0042F8D8//ob �Ҹ�
Destory obj : 0042F904//�ӽð�ü �Ҹ�

New Copy obj : 0042F8D8
Param ADR : 0042F8D8
New Copy obj : 0042F9DC//SoSimple ũ����ŭ�� �޸� ������ �Ҵ�, ob�� ���������ν� ���� ������ ȣ��
Destory obj : 0042F8D8//ob �Ҹ��� ȣ��
Return Obj : 0042F9DC//tempRef�� �ӽð�ü�� �Ǵٸ� ����, �� tempRef��� ��ü�� �߰��� �������� ����.

*/

#endif