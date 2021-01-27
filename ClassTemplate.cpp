/*
Ŭ���� ���ø�(Class Template)
Ŭ������ ����µ� ���Ǵ� ���ø�

���ø� Ŭ����(Template Class)
Ŭ���� ���ø��� ������� �����Ϸ��� ����� ���� Ŭ����
*/
#include <iostream>
using std::cout;
using std::endl;

#if 0
class Point
{
private:
	int xpos,ypos;
public:
	Point(int x=0, int y=0):xpos(x),ypos(y)
	{

	}
	void ShowPosition() const
	{
		cout<<'['<<xpos<<", "<<ypos<<']'<<endl;
	}
};
#endif
//�� Ŭ������ ��ǥ������ ������ ǥ���ϵ��� ���ǵǾ� �ִ�.
//�Ǽ��� ���·� ��ǥ�� ǥ���Ϸ���?
//������ ���·� ��ǥ�� ǥ�� �� ����Ϸ���?
//Ŭ������ ������ ���� ���ø�ȭ �ϸ� ������ Ŭ������ ������ �ʿ䰡 ����.

template <typename T>
class Point
{
private:
	T xpos,ypos;
public:
	Point(T x=0, T y=0):xpos(x),ypos(y)
	{

	}
	void ShowPosition() const
	{
		cout<<'['<<xpos<<", "<<ypos<<']'<<endl;
	}
};
//Ŭ���� ���ø��� ����Լ��� Ŭ���� �ܺο� �����ϴ� ���� �����ϴ�.

int main(void)
{
	Point<int> pos1(3,4);
	pos1.ShowPosition();

	Point<double> pos2(2.4, 3.6);
	pos2.ShowPosition();

	Point<char> pos3('P', 'F');
	pos3.ShowPosition();

	system("pause");
	return 0;
}
/*
�Լ� ���ø��� ����������, �����Ϸ��� 'Ŭ���� ���ø�'�� ������� '���ø� Ŭ����'�� ����� ����.

�� ������ ��� �� 3���� ���ø� Ŭ������ ���������, �̵��� ���� ������ ���� ǥ���� �ؼ� �Ϲ� Ŭ������ ������ ���´�.
Point<int> ���ø� Ŭ����
Point<double> ���ø� Ŭ����
Point<char> ���ø� Ŭ����
*�Լ� ���ø����� �ٸ��� Ŭ���� ���ø� ����� ��ü���������� <int>,<double>,<char> �� ���� �ݵ�� �ڷ��� ������ ����ؾ� �Ѵ�.
*/