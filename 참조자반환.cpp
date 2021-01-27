#include <iostream>

using namespace std;

int& ReferenceReturn(int &ref);
int IntTypeReturn(int &ref);

int IntTypeReturn(int &ref)
{
	ref++;
	return ref;//*****함수가 반환이 되면 정작 지역변수 ref는 소멸이 된다. 따라서 지역변수를 참조형의 변수에 저장하는 일은 없어야 한다.
}

int& ReferenceReturn(int &ref)
{
	ref++;
	return ref;
}

int main(void)
{
	int num1=1;

	//반환형이 참조형인 ReferenceReturn함수는 반환값을 다음과 같이 두가지 형태로 저장할 수 있다.
	int &num2 = ReferenceReturn(num1);//num2라는 별칭이 추가된다.
	//int &num2 = ref// 와 동일

	int num3 = ReferenceReturn(num1);//&num1이 가리키는 값을 저장한다.	
	//int num3 = ref;// 와 동일

	//반환형 참조자는 참조자나 일반 변수에 할당이 가능하다.

	int num4 = IntTypeReturn(num1);//(O)
	//int &num4 = IntTypeReturn(num1);(X)반환형이 기본자료형으로 선언된 IntTypeReturn 함수의 반환 값은 반드시 변수에 저장해야 한다.
	//int &num4 = 2;와 동일
	//반환형이 기본자료형으로 선언된 함수의 반환 값은 반드시 변수에 저장해야 한다.
	//반환형이 기본자료형으로 선언된 함수의 반환 값은 반드시 변수에 저장해야 한다.
	//반환형이 기본자료형으로 선언된 함수의 반환 값은 반드시 변수에 저장해야 한다.
	//반환형이 기본자료형으로 선언된 함수의 반환 값은 반드시 변수에 저장해야 한다.
	//반환형이 기본자료형으로 선언된 함수의 반환 값은 반드시 변수에 저장해야 한다.
	//반환형이 기본자료형으로 선언된 함수의 반환 값은 반드시 변수에 저장해야 한다.

	const int &num5 = IntTypeReturn(num1);//(O) const int num5 = IntTypeReturn(num1)와 동일
	//C++ 컴파일러는 const 참조자를 이용해서 상수를 참조할때 '임시변수'	를 만든다.	
	//참조자에 상수의 할당은 안된다. 그러나 const 참조자에는 상수 할당이 가능
	//이 선언문은 일단 가능은 하지만 전혀 실용성이 없다.
	//이 선언문은 일단 가능은 하지만 전혀 실용성이 없다.
	//이 선언문은 일단 가능은 하지만 전혀 실용성이 없다.
	//이 선언문은 일단 가능은 하지만 전혀 실용성이 없다.
	//이 선언문은 일단 가능은 하지만 전혀 실용성이 없다.
	//이 선언문은 일단 가능은 하지만 전혀 실용성이 없다.

	//const int* pNum5 = &(IntTypeReturn(num1)); // error

	const int &ri=123;
	//http://www.soenlab.com/  > 15-4-가.변수의 별명
	//이렇게 되면 ri는 123이라는 상수값을 가지며 이후 이 값은 변경할 수 없으므로 좌변값으로 사용되지 않는다. 
	//이 선언문은 일단 가능은 하지만 전혀 실용성이 없다. 왜냐하면 const int ri=123;이라는 정수형 상수를 만드는 것과 아무런 차이가 없기 때문이다.


	num1++;
	num2++;
	num3++;

	cout<<"num1: "<<num1<<endl;
	cout<<"num2: "<<num2<<endl;
	cout<<"num3: "<<num3<<endl;
	cout<<"num4: "<<num4<<endl;
	cout<<"num5: "<<num5<<endl;
	

	system("pause");
	return 0;
}
