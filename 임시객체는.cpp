#include <iostream>

//#include <conio.h>

using namespace std;

class Temporary
{
private:
	int num;
public:
	Temporary(int n=0):num(n)
	{
		cout<<this<<" create obj : "<<num<<endl;
	}
	~Temporary()
	{
		cout<<"destory obj : "<<num<<endl;
	}

	void ShowTempInfo()
	{
		cout<<"My num is : "<<num<<endl;
	}

};

class Position
{
private:
	int x;
	int y;

public:
	Position() {
		x=0;
		y=0;
	}
	void OutPosition() {
		cout<<"x : "<<x<<endl;
		cout<<"y : "<<y<<endl;
	}
};
#if 1
void main()
{
	Temporary(100);//�ӽ� ��ü�� ���� ����
	cout<<"*********** after make!"<<endl<<endl;

	Temporary(200).ShowTempInfo();//�ӽð�ü�� �����ϰ�, �̾ �� ��ü�� ������� ShowTempInfo �Լ��� ȣ��
	cout<<"*********** after make!"<<endl<<endl;

	
	const Temporary &ref = Temporary(300);//ref�� �ӽð�ü ������ ���ѵǴ� '���� ��'�� ������ ref�� ���޵Ǿ�, ref�� �ӽð�ü�� �����ϰ� �ȴ�.
	//��� �����δ� const Temporary ref = Temporary(300);�͵���
	cout<<"*********** end of main!"<<endl<<endl;

	cout<<"*********** �׷��ٸ� �ӽð�ü�� ���� �����Ϸ��� ????"<<endl;
	//Temporary &ref2 = Temporary(300);//������ �Ϲ� ����ó�� ���Ǳ⶧���� �Ʒ� ��ü���� ������ �ٸ��� ����
	Temporary ref2 = Temporary(300);
	cout<<&ref2<<endl;//���������� �ּҰ���� �׷��� ref2�� ���� �����Ϸ��� �ϸ� ������ ���� �߻�, Temporary �� << �����ڰ� �������̵� �Ǿ� ���� �ʱ� ����
	Temporary *pTemp = &ref2;
	ref2.ShowTempInfo();
	pTemp->ShowTempInfo();
	cout<<"*********** ????"<<endl<<endl;

	const char &refChar = 'a';
	const int &refInt = 30;
	//���� ������ �����Ҽ� �ֵ���, const �����ڸ� �̿��ؼ������ ������ �� '�ӽú���'��� ���� �����.
	//�׸��� �� ��ҿ� ��� 30�� �����ϰ� �����ڰ� �̸� �����ϰԲ� �Ѵ�.
	//"�� �ӽú������ �� �� ������ �ʴ� ������� ����鿩�� ����� ������ �����ϰ� �ߴ��?"
	//�̴� ���� �Լ� �ϳ��� ���� �ɵ��ϴ�.
	/*
	int Adder( const int &num1, const int &num2)
	{
		return num1+num2;
	}
	���� ���� ���ǵ� �Լ��� ������ ������ �������� ������ �����Ѵٴ� ���� �ſ� ���ŷο� ���� �ƴ� �� ����.
	ex) int num1 = 3; int num2= 4; Adder(num1,num2)
	�׷��� �ӽú����� ������ ����  const �������� ��������� ��������ν�, ���� �Լ��� ������ ���� �ſ� ������ ȣ���� ����������.
	Adder(3, 4);
	*/

	int val = 20;//c������ �ʱ�ȭ ���
	int(val2) = 222;//�̷��� ������ �ʱ�ȭ�� �ǳ�;;;;
	cout<<val2<<endl;
	//int val(20);//c++�ʱ�ȭ ���	
	Temporary(int(val));//�ӽð�ü ����

	//Temporary(val);//== Temporary val; ����Ʈ �����ڰ� �����Ƿ� ����, Temporary(int n=0):num(n) ���ָ� val�̶�� ��ü�� �����ϰ� ��
	Temporary(good);// Temporary good;�� ���� �� �ӽð�ü�� �����ϴ°� �ƴ϶� ��ü�� �����Ϸ��� �õ� �׷��� ����Ʈ �����ڰ� �����Ƿ� ����,Temporary(int n=0):num(n) �̷��� ����Ʈ �Ű������� �����ϸ� good��� ��ü�� ������
	cout<<&good<<endl;//003EF834

/*
	www.soenlab.com > 26-2-��.����Ʈ ������ 
	����Ʈ �����ڰ� �ִ� ��ü�� ������ ���� ������ ���� ���� ���� ����� ����� �� �ִ�.

	1. Position Here;
	2. Position Here=Position();
	3. Position *pPos=new Position;
	4. Position *pPos=new Position();
	5. Position(Here);
	6. Position Here();
	6�� ������ ������ �ʴ´�. �ֳ��ϸ� �� ������ Position ��ü�� �����ϰ� �μ��� ������ �ʴ� Here �Լ��� ������ �����ϴ� ������ ��ü ������ �ƴϱ� �����̴�.

	
*/
	Position(oh);
	//cout<<oh<<endl;//������ ����, ���� cout<<ref2<<endl;�ϰ��� ���� ����, ��ü oh�� �⺻ �ڷ����� ���� ���ٸ� �߻����� �ʾ��� ����....oh��� ��ü�� �����ִ� ��������� ����Լ����� �����̱� ����..?
	//ostream�� friend �Լ�<< �� friend ostream& operator<<(ostream& os, int num)�� ���� �⺻ �ڷ������� �Ѱ� �޵��� �����ε� �Ǿ� �ִ� ��, ��������� Ŭ����,����ü�� ���ڷ� �ްԵǸ� ������ �߻��Ѵ�.
	//�÷��þ׼ǽ�ũ��Ʈ������ [Object Object]��� �αװ� ����...
	oh.OutPosition();
	system("pause");
}
/*
Temporary(200).ShowTempInfo();
Ŭ���� �ܺο��� ��ü�� ��� �Լ��� ȣ���ϱ� ���� �ʿ��� ���� ���� �������� �ϳ��̴�.
1. ��ü�� �ٿ��� �̸�
2. ��ü�� ���� ��(��ü ������ ���Ǵ� ����)
3. ��ü�� �ּ� ��
�׷��� �ӽð�ü�� ������ ��ġ���� �ӽð�ü�� ���� ���� ��ȯ�ȴ�. �� �� ������ ��� ���� �ӽð�ü�� �����Ǹ� ������ ���°� �ȴ�.
(�ӽð�ü�� ���� ��).ShowTempInfo();
�׷���, �̾ ��� �Լ��� ȣ���� �����Ѱ�. ���� �̷��� '���� ��'�� ��ȯ�Ǳ� ������ ������ ���� ������ ������ ������ ���̴�.
const Temporary &ref = Temporary(300);

�׸��� �ռ� ���� ���� ReturnObjCopycon.cpp�� ���� ����(35���� �Ϻ�) ������ ������ ������, �����δ� �ӽð�ü��
��°�� ��ȯ�Ǿ�� �ƴ϶�, �ӽð�ü�� �޸𸮿� ����ǰ�, �� ��ü�� ���� ���� ��ȯ�Ǿ��� �����̴�.
SimpleFuncObj(obj).AddNum(30);
��, ��ȯ�� ���ؼ� �ӽð�ü�� ������ ������, �� ��ü�� �޸� ������ �����ϰ�, �� ��ü�� ���� ���� ��ȯ�Ǿ AddNum �Լ��� ȣ���� �����
���̴�.
�������� ���� ������ �ִ� ��� �ΰ���
1. �ӽð�ü�� ���� �����γѾ�� �ٷ� �Ҹ�Ǿ� ������.
2. �����ڿ� �����Ǵ� �ӽð�ü�� �ٷ� �Ҹ���� �ʴ´�.



����
L-value(left-value): ���� ������ �����ϴ� expression
	Ư�� �޸� ��ġ�� ����Ű�� �ִ� ��
	� ���� assign�� �� �ִ� ��
	& �����ڸ� ���� �ش� �޸��� �ּҰ��� ������ �� �ִ� ��

R-value(right-value) : left-value�� �ƴ� expression
	���� ���� �� ���� (can't assign)
	L-value�� ���� ��� ���� �ӽ�(temporary)�� ������ expression
	��, �ӽ������� ǥ������ ������ �������� ���� (���� �ٿ��� �����)
	& �����ڸ� ���� �ش� �޸��� �ּ� ���� ������ �� ����

����					L-value					R-value 
���					�Ұ���					���(��� �� �� ��ü)
�����ڰ� �ִ� ����		�Ұ���					���(������ �����)
�ܼ� ���� V				�ڽ��� ���� ��ġ		����(V�� ��ϵ� ��)
������ ���� P			P �ڽ��� ���� ��ġ	P�� ����Ű�� �������� ��ġ
�迭 A[i]				A���� i��° ��ġ		A���� i��° ��ġ�� ��ϵ� ��

*/
#endif