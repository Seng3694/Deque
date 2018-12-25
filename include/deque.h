#ifndef COLLECTIONS_DEQUE_H
#define COLLECTIONS_DEQUE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

typedef void* ItemType;
typedef size_t SizeType;
typedef struct Deque Deque;

Deque* Deque_Create(const SizeType capacity);
void Deque_Destroy(Deque* deque);

SizeType Deque_GetCapacity(Deque* deque);
SizeType Deque_GetSize(Deque* deque);

void Deque_PushBack(Deque* deque, const ItemType item);
void Deque_PushFront(Deque* deque, const ItemType item);

ItemType Deque_PopBack(Deque* deque);
ItemType Deque_PopFront(Deque* deque);

ItemType Deque_PeekBack(Deque* deque);
ItemType Deque_PeekFront(Deque* deque);

void Deque_Resize(Deque* deque, const SizeType capacity);

#ifdef __cplusplus
}
#endif

#endif
