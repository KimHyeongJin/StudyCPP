#pragma once
#include <Windows.h>
#include <assert.h>

// Edited from C8MemPool class (Hitel, gma 7 3) - 1CoinClear -



template<class Type>
class MemPooler
{

public:
	// 생성자 
	MemPooler(int nNumOfBlock):m_nNumofBlock(nNumOfBlock),
		                       m_pFreeList(NULL),
							   m_pMemBlock(NULL),
							   m_nAllocCount(0)
	{
		assert(nNumOfBlock>0);
		m_nListBlockSize=sizeof(BlockNode)+sizeof(Type);

		printf( "sizeof(BlockNode) -> %d\n", sizeof(BlockNode) );
		printf( "m_nListBlockSize -> %d\n", m_nListBlockSize );

		Create();
	}

    // 소멸자
	~MemPooler()
	{
		Destroy();
	}

	// 메모리 풀에서 사용가능한 메모리 영역의 주소를 반환 
	Type* Alloc()
	{
	    BlockNode* pNode=NULL;
		Type* pRet=NULL;

		EnterCriticalSection(&m_cs);
		////////////////////////////

        pNode=m_pFreeList;
		if(pNode!=NULL)
		{
			m_pFreeList=m_pFreeList->pNext;
			m_nAllocCount++;
			pRet=reinterpret_cast<Type*>(pNode+1);
		}

		////////////////////////////
		LeaveCriticalSection(&m_cs);

		return pRet;
	};//Alloc

	BOOL Free(Type* freeBlock)
	{
		BlockNode* pNode=NULL;
        BOOL bRet=FALSE;

		EnterCriticalSection(&m_cs);
		///////////////////////////

		pNode=( reinterpret_cast<BlockNode*>(freeBlock) )-1;
		if(m_nAllocCount>0)
		{
			pNode->pNext=m_pFreeList;
			m_pFreeList=pNode;
			m_nAllocCount--;
            bRet=TRUE;
		}

		///////////////////////////
		LeaveCriticalSection(&m_cs);
		
		return bRet;
	}//Free

	int GetCount()
	{
		return m_nAllocCount;
	}
	
	
protected:
     void Create()
	 {		
        const int AllocationSize=(m_nListBlockSize) * m_nNumofBlock; // 메모리 할당할 크기 
        m_pMemBlock=VirtualAlloc(NULL,AllocationSize,MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
		assert(m_pMemBlock);

		BlockNode* pNode=reinterpret_cast<BlockNode*>(m_pMemBlock);

		pNode =reinterpret_cast<BlockNode*>((reinterpret_cast<DWORD>(pNode))+(m_nNumofBlock-1)* (m_nListBlockSize) );//할당 받은 마지막 노드를 구한다.
		for(int i=m_nNumofBlock-1; i>=0; i--)
		{
			pNode->pNext=m_pFreeList; // 처음에는 NULL , 즉 Tail 은 NULL 로 한다.
			m_pFreeList=pNode;//pNode의 현재 주소를 저장하고, m_pFreeList는 m_pMemBlock와 일치하겠군...
			pNode=reinterpret_cast<BlockNode*>((reinterpret_cast<DWORD>(pNode))-m_nListBlockSize);//pNode = pNode - m_nListBlockSize
		}

		InitializeCriticalSectionAndSpinCount(&m_cs,4000);

	 }//Create

	 void Destroy()
	 {        

		if(m_pMemBlock)
		{
			VirtualFree(m_pMemBlock,0,MEM_RELEASE);
		}
		
		DeleteCriticalSection(&m_cs);
	 }

    ///////////////////////////////////////////
	// 링크드 리스트 처럼 관리를 위한 노드 타입
	struct BlockNode
	{
		BlockNode* pNext;
		BlockNode()
		{
			pNext=NULL;
		}
	};
	//////////////////////////////////////////

protected:
	BlockNode* m_pFreeList; // 남아 있는 메모리 블럭 리스트
	void* m_pMemBlock;

	int m_nNumofBlock;      // 메모리 할당할 블럭 수
	int m_nListBlockSize;   // 한 블럭 사이즈 
	int m_nAllocCount;      // 할당된 메모리 블럭 갯수

	CRITICAL_SECTION m_cs;  // For Thread-Safe;
};
/*
임계 영역(Critical Section)

class critical_section은 "non-reentrant mutex which is explicitly aware of the Concurrency Runtime"
Non-Reentrant 즉, 동일 쓰레드가 중복해서 락에 진입할 수 없음을 의미한다.


//생성자 내부
InitializeCriticalSection(&m_cs);//CRITICAL_SECTION 객체 초기화

//소멸자 내부
DeleteCriticalSection(&m_cs);//CRITICAL_SECTION 객체를 OS에 반환

//마지막으로 실제로 우리가 보호해야 할 부분을 열고 닫는 문장을 이용해 응용한다.
EnterCriticalSection(&m_cs);

//보호해야 할 영역

LeaveCriticalSection(&m_cs);


EnterCriticalSection()와 LeaveCriticalSection()는 항상 짝을 이뤄야 함
이유는 Enter가 된 상태이면 해당하는 부분은 Leave를 하기 전까지는 누구도 접근할 수 없는 상태가 되는데,
Enter가 된 상태에서 Leave를 하기전에 return, exit등이 있으면 이 또한 굉장히 위험한 경우를 만드는 행위가 된다.

즉, 정리하자면 Critical Section으로 들어갔으면( EnterCriticalSection ) 
반드시 Process가 종료되기 전에 Critical Section을 떠나야 한다( LeaveCriticalSection )

또한, CRITICAL_SECTION은 윈도우로부터 밭은 HANDLE 이므로 반드시 반납을 해주고 종료되어야 한다.
//http://blog.naver.com/PostView.nhn?blogId=dong880510&logNo=140155223667
*/