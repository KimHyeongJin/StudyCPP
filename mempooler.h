#pragma once
#include <Windows.h>
#include <assert.h>

// Edited from C8MemPool class (Hitel, gma 7 3) - 1CoinClear -



template<class Type>
class MemPooler
{

public:
	// ������ 
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

    // �Ҹ���
	~MemPooler()
	{
		Destroy();
	}

	// �޸� Ǯ���� ��밡���� �޸� ������ �ּҸ� ��ȯ 
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
        const int AllocationSize=(m_nListBlockSize) * m_nNumofBlock; // �޸� �Ҵ��� ũ�� 
        m_pMemBlock=VirtualAlloc(NULL,AllocationSize,MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
		assert(m_pMemBlock);

		BlockNode* pNode=reinterpret_cast<BlockNode*>(m_pMemBlock);

		pNode =reinterpret_cast<BlockNode*>((reinterpret_cast<DWORD>(pNode))+(m_nNumofBlock-1)* (m_nListBlockSize) );//�Ҵ� ���� ������ ��带 ���Ѵ�.
		for(int i=m_nNumofBlock-1; i>=0; i--)
		{
			pNode->pNext=m_pFreeList; // ó������ NULL , �� Tail �� NULL �� �Ѵ�.
			m_pFreeList=pNode;//pNode�� ���� �ּҸ� �����ϰ�, m_pFreeList�� m_pMemBlock�� ��ġ�ϰڱ�...
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
	// ��ũ�� ����Ʈ ó�� ������ ���� ��� Ÿ��
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
	BlockNode* m_pFreeList; // ���� �ִ� �޸� �� ����Ʈ
	void* m_pMemBlock;

	int m_nNumofBlock;      // �޸� �Ҵ��� �� ��
	int m_nListBlockSize;   // �� �� ������ 
	int m_nAllocCount;      // �Ҵ�� �޸� �� ����

	CRITICAL_SECTION m_cs;  // For Thread-Safe;
};
/*
�Ӱ� ����(Critical Section)

class critical_section�� "non-reentrant mutex which is explicitly aware of the Concurrency Runtime"
Non-Reentrant ��, ���� �����尡 �ߺ��ؼ� ���� ������ �� ������ �ǹ��Ѵ�.


//������ ����
InitializeCriticalSection(&m_cs);//CRITICAL_SECTION ��ü �ʱ�ȭ

//�Ҹ��� ����
DeleteCriticalSection(&m_cs);//CRITICAL_SECTION ��ü�� OS�� ��ȯ

//���������� ������ �츮�� ��ȣ�ؾ� �� �κ��� ���� �ݴ� ������ �̿��� �����Ѵ�.
EnterCriticalSection(&m_cs);

//��ȣ�ؾ� �� ����

LeaveCriticalSection(&m_cs);


EnterCriticalSection()�� LeaveCriticalSection()�� �׻� ¦�� �̷�� ��
������ Enter�� �� �����̸� �ش��ϴ� �κ��� Leave�� �ϱ� �������� ������ ������ �� ���� ���°� �Ǵµ�,
Enter�� �� ���¿��� Leave�� �ϱ����� return, exit���� ������ �� ���� ������ ������ ��츦 ����� ������ �ȴ�.

��, �������ڸ� Critical Section���� ������( EnterCriticalSection ) 
�ݵ�� Process�� ����Ǳ� ���� Critical Section�� ������ �Ѵ�( LeaveCriticalSection )

����, CRITICAL_SECTION�� ������κ��� ���� HANDLE �̹Ƿ� �ݵ�� �ݳ��� ���ְ� ����Ǿ�� �Ѵ�.
//http://blog.naver.com/PostView.nhn?blogId=dong880510&logNo=140155223667
*/