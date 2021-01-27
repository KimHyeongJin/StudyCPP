#include <iostream>


int main()
{
	int num = 999;
	int* pNum = &num;
	int** ppNum = new int*;//이중 포인터 변수를 힙에 생성한다.
	*ppNum = pNum;
	if (NULL != ppNum)
	{
		delete ppNum;
	}

	int *p = &num;
	void** vpp = new void*[5];
	for (int i = 0;i<5;i++)
	{
		vpp[i] = p;
		std::cout << *(int*)vpp[i] << std::endl;
	}

	delete[]vpp;
	return 0;
}