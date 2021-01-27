/*
클래스 템플릿(Class Template)
클래스를 만드는데 사용되는 템플릿

템플릿 클래스(Template Class)
클래스 템플릿을 기반으로 컴파일러가 만들어 내는 클래스
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
//위 클래스는 좌표정보를 정수로 표현하도록 정의되어 있다.
//실수의 형태로 좌표를 표현하려면?
//문자의 형태로 좌표를 표현 및 출력하려면?
//클래스를 다음과 같이 템플릿화 하면 별도의 클래스를 정의할 필요가 없다.

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
//클래스 템플릿도 멤버함수를 클래스 외부에 정의하는 것이 가능하다.

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
함수 템플릿과 마찬가지로, 컴파일러는 '클래스 템플릿'을 기반으로 '템플릿 클래스'를 만들어 낸다.

위 예제의 경우 총 3개의 템플릿 클래스가 만들어지며, 이들은 각각 다음과 같이 표현을 해서 일반 클래스와 구분을 짓는다.
Point<int> 템플릿 클래스
Point<double> 템플릿 클래스
Point<char> 템플릿 클래스
*함수 템플릿과는 다르게 클래스 템플릿 기반의 객체생성에서는 <int>,<double>,<char> 와 같이 반드시 자료형 정보를 명시해야 한다.
*/