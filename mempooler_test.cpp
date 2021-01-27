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
		printf_s("%d 번째 주소 = %d\n",i, vec[i]);		
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
		
	//재 할당으로 주소가 그대로 인지?
	Allocate(pool, vec, poolSize);
	ShowAddress(vec);

	return 0;
}

/*
Output
sizeof(BlockNode) -> 4
m_nListBlockSize -> 532
0 번째 주소 = 196612
1 번째 주소 = 197144
2 번째 주소 = 197676
3 번째 주소 = 198208
4 번째 주소 = 198740
5 번째 주소 = 199272
6 번째 주소 = 199804
7 번째 주소 = 200336
8 번째 주소 = 200868
9 번째 주소 = 201400
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

0 번째 주소 = 196612
1 번째 주소 = 197144
2 번째 주소 = 197676
3 번째 주소 = 198208
4 번째 주소 = 198740
5 번째 주소 = 199272
6 번째 주소 = 199804
7 번째 주소 = 200336
8 번째 주소 = 200868
9 번째 주소 = 201400




*/