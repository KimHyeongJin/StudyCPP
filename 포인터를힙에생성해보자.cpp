#include <iostream>


int main()
{
	int num = 999;
	int* pNum = &num;
	int** ppNum = new int*;//���� ������ ������ ���� �����Ѵ�.
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