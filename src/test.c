#include <assert.h>
#include <stdio.h>

#include <deque.h>

int main(void)
{
	Deque* deque = Deque_Create(10);
	assert(Deque_GetSize(deque) == 0);
	assert(Deque_GetCapacity(deque) == 10);

	for (int i = 0; i < 10; ++i)
	{
		if (i % 2 == 0)
			Deque_PushBack(deque, i);
		else
			Deque_PushFront(deque, i);
	}

	assert(Deque_GetSize(deque) == 10);
	assert(Deque_GetCapacity(deque) == 10);

	//even numbers pushed back, odd numbers front
	//=> 9753102468
		
	assert(Deque_PopFront(deque) == 9);
	assert(Deque_PopFront(deque) == 7);
	assert(Deque_PopFront(deque) == 5);
	assert(Deque_PopFront(deque) == 3);

	//should be 102468 now
	assert(Deque_PopBack(deque) == 8);
	assert(Deque_PopBack(deque) == 6);
	assert(Deque_PopBack(deque) == 4);

	//should be 102 now
	assert(Deque_PopFront(deque) == 1);
	assert(Deque_PopFront(deque) == 0);
	assert(Deque_PopFront(deque) == 2);

	assert(Deque_GetSize(deque) == 0);
	assert(Deque_GetCapacity(deque) == 10);

	Deque_Resize(deque, 0);
	assert(Deque_GetSize(deque) == 0);
	assert(Deque_GetCapacity(deque) == 0);

	Deque_Resize(deque, 5);
	assert(Deque_GetSize(deque) == 0);
	assert(Deque_GetCapacity(deque) == 5);

	Deque_PushBack(deque, 1);
	Deque_PushBack(deque, 2);
	Deque_PushBack(deque, 3);
	// [1] [2] [3] [-] [-]
	//  ^       ^
	//front    back

	Deque_PopFront(deque);
	Deque_PopFront(deque);
	// [-] [-] [3] [-] [-]
	//          ^
	//      front+back

	Deque_PushBack(deque, 4);
	Deque_PushBack(deque, 5);
	Deque_PushBack(deque, 6);
	Deque_PushBack(deque, 7);
	// [6] [7] [3] [4] [5]
	//      ^   ^
	//    back front

	assert(Deque_GetSize(deque) == 5);
	assert(Deque_GetCapacity(deque) == 5);

	assert(Deque_PeekFront(deque) == 3);
	assert(Deque_PeekBack(deque) == 7);
	assert(Deque_GetSize(deque) == 5);

	Deque_Resize(deque, 7);
	// [3] [4] [5] [6] [7] [-] [-]
	//  ^               ^
	// front           back

	assert(Deque_GetSize(deque) == 5);
	assert(Deque_GetCapacity(deque) == 7);

	//popping from front to back should result in numbers from 3 to 7
	assert(Deque_PopFront(deque) == 3);
	assert(Deque_PopFront(deque) == 4);
	assert(Deque_PopFront(deque) == 5);
	assert(Deque_PopFront(deque) == 6);
	assert(Deque_PopFront(deque) == 7);

	assert(Deque_GetSize(deque) == 0);
	assert(Deque_GetCapacity(deque) == 7);

#ifdef DYNAMIC_DEQUE
	for(int i = 0; i < 7; ++i)
		Deque_PushBack(deque, i);

	assert(Deque_GetSize(deque) == 7);
	assert(Deque_GetCapacity(deque) == 7);

	Deque_PushBack(deque, 10);

	assert(Deque_GetSize(deque) == 8);
	assert(Deque_GetCapacity(deque) == 10); // floor(7 * 1,5) = 10

	Deque_PushBack(deque, 10);
	Deque_PushBack(deque, 10);

	assert(Deque_GetSize(deque) == 10);
	assert(Deque_GetCapacity(deque) == 10);

	Deque_PushBack(deque, 10);

	assert(Deque_GetCapacity(deque) == 15);
#endif

	Deque_Destroy(deque);
	
	return 0;
}
