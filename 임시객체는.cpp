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
	Temporary(100);//임시 객체를 직접 생성
	cout<<"*********** after make!"<<endl<<endl;

	Temporary(200).ShowTempInfo();//임시객체를 생성하고, 이어서 이 객체를 대상으로 ShowTempInfo 함수를 호출
	cout<<"*********** after make!"<<endl<<endl;

	
	const Temporary &ref = Temporary(300);//ref는 임시객체 생성시 반한되는 '참조 값'이 참조자 ref에 전달되어, ref가 임시객체를 참조하게 된다.
	//결과 적으로는 const Temporary ref = Temporary(300);와동일
	cout<<"*********** end of main!"<<endl<<endl;

	cout<<"*********** 그렇다면 임시객체의 값을 참조하려면 ????"<<endl;
	//Temporary &ref2 = Temporary(300);//선언후 일반 변수처럼 사용되기때문에 아래 객체생성 구문과 다를게 없음
	Temporary ref2 = Temporary(300);
	cout<<&ref2<<endl;//정상적으로 주소값출력 그러나 ref2와 같이 참조하려고 하면 컴파일 에러 발생, Temporary 에 << 연산자가 오버라이드 되어 있지 않기 때문
	Temporary *pTemp = &ref2;
	ref2.ShowTempInfo();
	pTemp->ShowTempInfo();
	cout<<"*********** ????"<<endl<<endl;

	const char &refChar = 'a';
	const int &refInt = 30;
	//위의 문장이 성립할수 있도록, const 참조자를 이용해서상수를 참조할 때 '임시변수'라는 것을 만든다.
	//그리고 이 장소에 상수 30을 저장하고선 참조자가 이를 참조하게끔 한다.
	//"왜 임시변수라는 잘 와 닿지도 않는 개념까지 끌어들여서 상수의 참조가 가능하게 했대요?"
	//이는 다음 함수 하나로 답이 될듯하다.
	/*
	int Adder( const int &num1, const int &num2)
	{
		return num1+num2;
	}
	위와 같이 정의된 함수에 인자의 전달을 목적으로 변수를 선언한다는 것은 매우 번거로운 일이 아닐 수 없다.
	ex) int num1 = 3; int num2= 4; Adder(num1,num2)
	그러나 임시변수의 생성을 통한  const 참조자의 상수참조를 허용함으로써, 위의 함수는 다음과 같이 매우 간단히 호출이 가능해진다.
	Adder(3, 4);
	*/

	int val = 20;//c에서의 초기화 방법
	int(val2) = 222;//이렇게 생성및 초기화가 되네;;;;
	cout<<val2<<endl;
	//int val(20);//c++초기화 방법	
	Temporary(int(val));//임시객체 생성

	//Temporary(val);//== Temporary val; 디폴트 생성자가 없으므로 오류, Temporary(int n=0):num(n) 해주면 val이라는 객체를 생성하게 됨
	Temporary(good);// Temporary good;과 동일 즉 임시객체를 생성하는게 아니라 객체를 생성하려고 시도 그러나 디폴트 생성자가 없으므로 오류,Temporary(int n=0):num(n) 이렇게 디폴트 매개변수를 선언하면 good라는 객체가 생성됨
	cout<<&good<<endl;//003EF834

/*
	www.soenlab.com > 26-2-가.디폴트 생성자 
	디폴트 생성자가 있는 객체를 선언할 때는 다음과 같은 여러 가지 방법을 사용할 수 있다.

	1. Position Here;
	2. Position Here=Position();
	3. Position *pPos=new Position;
	4. Position *pPos=new Position();
	5. Position(Here);
	6. Position Here();
	6번 형식은 허용되지 않는다. 왜냐하면 이 선언문은 Position 객체를 리턴하고 인수를 가지지 않는 Here 함수의 원형을 선언하는 것이지 객체 선언문이 아니기 때문이다.

	
*/
	Position(oh);
	//cout<<oh<<endl;//컴파일 에러, 위의 cout<<ref2<<endl;일경우와 같은 에러, 객체 oh가 기본 자료형의 변수 였다면 발생하지 않았을 오류....oh라는 객체가 연관있는 멤버변수와 멤버함수들의 집합이기 때문..?
	//ostream의 friend 함수<< 는 friend ostream& operator<<(ostream& os, int num)과 같이 기본 자료형만을 넘겨 받도록 오버로딩 되어 있다 즉, 사용자정의 클래스,구조체를 인자로 받게되면 오류가 발생한다.
	//플래시액션스크립트에서는 [Object Object]라는 로그가 찍힘...
	oh.OutPosition();
	system("pause");
}
/*
Temporary(200).ShowTempInfo();
클래스 외부에서 객체의 멤버 함수를 호출하기 위해 필요한 것은 다음 세가지중 하나이다.
1. 객체에 붙여진 이름
2. 객체의 참조 값(객체 참조에 사용되는 정보)
3. 객체의 주소 값
그런데 임시객체가 생성된 위치에는 임시객체의 참조 값이 반환된다. 즉 위 문장의 경우 먼저 임시객체가 생성되면 다음의 형태가 된다.
(임시객체의 참조 값).ShowTempInfo();
그래서, 이어서 멤버 함수의 호출이 가능한것. 또한 이렇듯 '참조 값'이 반환되기 때문에 다음과 같은 문장의 구성도 가능한 것이다.
const Temporary &ref = Temporary(300);

그리고 앞서 보인 예제 ReturnObjCopycon.cpp의 다음 문장(35행의 일부) 구성이 가능한 이유도, 실제로는 임시객체가
통째로 반환되어서가 아니라, 임시객체는 메모리에 저장되고, 그 객체의 참조 값이 반환되었기 때문이다.
SimpleFuncObj(obj).AddNum(30);
즉, 반환을 위해서 임시객체가 생성은 되지만, 이 객체는 메모리 공간에 존재하고, 이 객체의 참조 값이 반환되어서 AddNum 함수의 호출이 진행된
것이다.
실행결과를 통해 내릴수 있는 결론 두가지
1. 임시객체는 다음 행으로넘어가면 바로 소멸되어 버린다.
2. 참조자에 참조되는 임시객체는 바로 소멸되지 않는다.



참고
L-value(left-value): 다음 조건을 만족하는 expression
	특정 메모리 위치를 가리키고 있는 것
	어떤 값을 assign할 수 있는 것
	& 연산자를 통해 해당 메모리의 주소값을 가져올 수 있는 것

R-value(right-value) : left-value가 아닌 expression
	값을 담을 수 없음 (can't assign)
	L-value에 값을 담기 위해 임시(temporary)로 생성된 expression
	즉, 임시적으로 표현식이 끝나면 없어지는 값들 (다음 줄에서 사라짐)
	& 연산자를 통해 해당 메모리의 주소 값을 가져올 수 없음

구분					L-value					R-value 
상수					불가능					기능(상수 값 그 자체)
연산자가 있는 수식		불가능					기능(수식의 결과값)
단순 변수 V				자신이 기억된 위치		가능(V에 기록된 값)
포인터 변수 P			P 자신이 기억된 위치	P가 가리키는 기억장소의 위치
배열 A[i]				A에서 i번째 위치		A에서 i번째 위치에 기록된 값

*/
#endif