#include <iostream>

int main()
{
	int N0 = 1;
	int N1 = 10;

	//다음 두 포인터는 같은가?
	int* const pN1 = &N0;
	const int* pN2 = &N1;
	//pN1 = &N1;//error
	pN2 = &N1;
	// 다르다~!


	// 의문:상수 키워드가 있는 2차원 포인터는 어떤 스타일의 1차원 포인터의 주소를 저장 할 수 있는가?

	// 팁:가장 우측에 있는 *는 해당 변수가 포인터 변수라는 것을 의미한다?(당연한거 아닌가...)

	//상수 키워드 위치에 따라 2차원 포인터들이 저장 할 수 있는 1차원 포인터, 1차원 포인터가 저장 할 수 있는 변수가 다르다.
	//2중 포인터 1
	const int N2 = 1000;
	const int* pN2_0 = &N2;
	const int** pN2_1 = &pN2_0;

	//2중 포인터 2
	int N3 = 1000;
	int * const pN3_0 = &N3 ;//const는 포인터 자기자신(pN3_0)을 상수화 한다. 그러르모 상수 변수를 저장 할 수 없다.
	int * const * pN3_1 = &pN3_0;//int* const를 U로 치환 U* N
	
	//2중 포인터 3	
	int N4 = 1;
	int* pN4_0 = &N4;
	int** const pN4_1 = &pN4_0;// int*를 U로 치환, U* C N

	//3중 포인터?
	int** const* pN5 = &pN4_1;

	//포인터가 자가 자신을 상수화 한다는 것은 상수변수의 주소를 담을 수 없다는 것을 의미 한다.
	return 0;
}