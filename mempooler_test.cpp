#include <iostream>
#include <vector>
#include "mempooler.h"

typedef struct tagMemPoolTest
{
	int		num;
	double	fNum;
	char	buffer[512];
	tagMemPoolTest()
	{
		num = 0;
		fNum = 0;
		ZeroMemory(buffer, 512);
	};
}MEMPOOLTEST;

void ShowAddress( std::vector<MEMPOOLTEST*>& vec )
{
	std::vector<MEMPOOLTEST*>::size_type size = vec.size();
	for (int i = 0;i< size ;i++)
	{
		printf_s("%d ��° �ּ� = %d\n",i, vec[i]);		
	}
}

void Allocate( MemPooler<MEMPOOLTEST>& pool, std::vector<MEMPOOLTEST*>& vec, std::vector<MEMPOOLTEST*>::size_type size  )
{
	for ( int i = 0 ; i< size ; i++ )
	{
		MEMPOOLTEST* pTest = pool.Alloc();
		vec.push_back(pTest);
	}
}

int main(void)
{
	const INT poolSize = 10;
	MemPooler<MEMPOOLTEST> pool(poolSize);
	std::vector< MEMPOOLTEST* > vec;

	Allocate(pool, vec, poolSize);
	ShowAddress(vec);

	printf_s("vec.size() = %d\n",vec.size());
	printf_s("pool count = %d\n",pool.GetCount());
	std::cout<<std::endl;
	
	for ( int i = 10-1;i >= 0;i-- )
	{
		BOOL b = pool.Free(vec.at(i));
		if (b)
		{
			vec.pop_back();
		}
		printf_s("Free Success ? = %d\n",b);
	}

	printf_s("vec.size() = %d\n",vec.size());
	printf_s("pool count = %d\n",pool.GetCount());
	std::cout<<std::endl;
		
	//�� �Ҵ����� �ּҰ� �״�� ����?
	Allocate(pool, vec, poolSize);
	ShowAddress(vec);

	return 0;
}

/*
Output
sizeof(BlockNode) -> 4
m_nListBlockSize -> 532
0 ��° �ּ� = 196612
1 ��° �ּ� = 197144
2 ��° �ּ� = 197676
3 ��° �ּ� = 198208
4 ��° �ּ� = 198740
5 ��° �ּ� = 199272
6 ��° �ּ� = 199804
7 ��° �ּ� = 200336
8 ��° �ּ� = 200868
9 ��° �ּ� = 201400
vec.size() = 10
pool count = 10

Free Success ? = 1
Free Success ? = 1
Free Success ? = 1
Free Success ? = 1
Free Success ? = 1
Free Success ? = 1
Free Success ? = 1
Free Success ? = 1
Free Success ? = 1
Free Success ? = 1
vec.size() = 0
pool count = 0

0 ��° �ּ� = 196612
1 ��° �ּ� = 197144
2 ��° �ּ� = 197676
3 ��° �ּ� = 198208
4 ��° �ּ� = 198740
5 ��° �ּ� = 199272
6 ��° �ּ� = 199804
7 ��° �ּ� = 200336
8 ��° �ּ� = 200868
9 ��° �ּ� = 201400




*/