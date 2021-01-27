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
	SimpleFuncObj(obj);//복사 생성자를 통한 객체가 생성된다. 만약에 멤버로 string의 객체라도 갖고 있다면 string객체의 복사 생성자도 호출된다...
	SimpleFuncRef(obj);//복사 생성자를 통한 객체 생성이 없음. const는 빼도 상관 없다.

	cout<<endl;
	SoSimple tempRef = SimpleFuncObj(obj);//
	//SoSimple &tempRef = SimpleFuncObj(obj);//위 표현식과 같은 결과, 임시객체는.cpp 참고, 객체의 경우 참조자를 임시객체로 초기화가 가능하군요.
	cout<<"Return Obj : "<<&tempRef<<endl;


	cout<<endl<<endl;
	//cout<<"Return Obj : "<<tempRef<<endl;//오류;;;;;;;;;;;;
	tempRef.ShowInfo();
	
	SoSimple *pTemp = &tempRef;
	cout<<"pTemp : "<<pTemp<<endl;
	(*pTemp).ShowInfo();//정상적으로 7이 찍힘....
	pTemp->ShowInfo();

	//기본자료형의 예1
	int num1=1;
	int &ref = num1;
	int num2 = num1;
	//함수의 반환값이 참조자일경우의 예
	int &ref2 = ReturnRef(num2);//반환값이 상수일경우는 에러
	int num3 = ReturnRef(num1);

	
	//int &ref3 = ReturnInt(num1);//Error. 'int'에서 'int &'(으)로 변환할 수 없습니다. 기본 자료형은 int &ref3 = 1과 같이 참조자를 임시 변수로 초기화 할수 없군
	
	const int &ref3 = 1;//단 const 참조자는 우항에 있는 상수 1을 임시변수화 해서 초기화 가능

	//하지만 객체의 경우는 위 SoSimple &tempRef = SimpleFuncObj(obj); 경우와 같이 잘 된다.

	system("pause");
	
}

/*
New Object : 0042F9E8//obj(7)
New Copy obj : 0042F8D8//ob = obj,ob의 복사 생성자 호출
Param ADR : 0042F8D8//ob의 주소
New Copy obj : 0042F904//임시객체 생성후 ob로 초기화 그리고 임시객체의 복사생성자 호출
Destory obj : 0042F8D8//ob 소멸
Destory obj : 0042F904//임시객체 소멸

New Copy obj : 0042F8D8
Param ADR : 0042F8D8
New Copy obj : 0042F9DC//SoSimple 크리만큼의 메모리 공간을 할당, ob를 대입함으로써 복사 생성자 호출
Destory obj : 0042F8D8//ob 소멸자 호출
Return Obj : 0042F9DC//tempRef는 임시객체의 또다른 별명, 즉 tempRef라는 객체를 추가로 생성하지 않음.

*/

#endif