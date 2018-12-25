#include "deque.h"

#ifdef DYNAMIC_DEQUE
#include <math.h>
#endif

#include <stdlib.h>
#include <string.h>

#ifdef DYNAMIC_DEQUE
static const float RESIZE_FACTOR = 1.5f;
static void Deque_EnsureCapacity(Deque* deque, const SizeType capacity);
#endif

struct Deque
{
	SizeType capacity;
	SizeType size;
	SizeType head;
	SizeType tail;
	ItemType* data;
};

Deque* Deque_Create(const SizeType capacity)
{
	Deque* deque = malloc(sizeof(Deque));
	if (!deque) return NULL;

	deque->capacity = capacity;
	deque->size = 0;
	deque->head = 0;
	deque->tail = 0;
	deque->data = malloc(deque->capacity * sizeof(ItemType));

	if (!deque->data)
	{
		free(deque);
		return NULL;
	}

	return deque;
}

void Deque_Destroy(Deque* deque)
{
	if (deque)
	{
		if(deque->data)
			free(deque->data);

		free(deque);
	}
}

SizeType Deque_GetCapacity(Deque* deque)
{
	return deque->capacity;
}

SizeType Deque_GetSize(Deque* deque)
{
	return deque->size;
}

void Deque_PushBack(Deque* deque, const ItemType item)
{
#ifdef DYNAMIC_DEQUE
	Deque_EnsureCapacity(deque, deque->size + 1);
#endif
	deque->data[deque->tail] = item;
	deque->tail = (deque->tail + 1) % deque->capacity;
	deque->size++;
}

void Deque_PushFront(Deque* deque, const ItemType item)
{
#ifdef DYNAMIC_DEQUE
	Deque_EnsureCapacity(deque, deque->size + 1);
#endif

	if (deque->head == 0)
		deque->head = deque->capacity - 1;
	else
		deque->head--;

	deque->data[deque->head] = item;
	deque->size++;
}

ItemType Deque_PopBack(Deque* deque)
{
	if (deque->size == 0)
		return (ItemType)0;

	if (deque->tail == 0)
		deque->tail = deque->capacity - 1;
	else
		deque->tail--;

	ItemType item = deque->data[deque->tail];
	deque->data[deque->tail] = (ItemType)0;
	deque->size--;
	return item;
}

ItemType Deque_PopFront(Deque* deque)
{
	if (deque->size == 0)
		return (ItemType)0;

	ItemType item = deque->data[deque->head];
	deque->data[deque->head] = (ItemType)0;
	deque->head = (deque->head + 1) % deque->capacity;
	deque->size--;
	return item;
}

ItemType Deque_PeekBack(Deque* deque)
{
	if (deque->size == 0)
		return (ItemType)0;

	return deque->data[deque->tail - 1];
}

ItemType Deque_PeekFront(Deque* deque)
{
	if (deque->size == 0)
		return (ItemType)0;

	return deque->data[deque->head];
}

void Deque_Resize(Deque* deque, const SizeType capacity)
{
	if (capacity != deque->capacity)
	{
		if (capacity == 0)
		{
			deque->size = 0;
			free(deque->data);
			deque->data = NULL;
		}
		else if (deque->capacity == 0)
		{
			deque->data = malloc(capacity * sizeof(ItemType));
		}
		else 
		{
			if (deque->head >= deque->tail)
			{
				//example:
				//old array (size 5): [4] [5] [1] [2] [3]   (head 1   tail 5)
				//new array (size 8): [1] [2] [3] [4] [5] [-] [-] [-]
				void** newData = malloc(capacity * sizeof(ItemType));
				//copy [1] [2] [3] 
				memcpy(newData, deque->data + deque->head, (deque->capacity - deque->head) * sizeof(ItemType));
				//copy [4] [5]
				memcpy(newData + deque->capacity - deque->head, deque->data, deque->tail * sizeof(ItemType));
				deque->tail = deque->capacity - deque->head + deque->tail;
				deque->head = 0;
				free(deque->data);
				deque->data = newData;
			}
			else
			{
				void** newData = malloc(capacity * sizeof(ItemType));
				memcpy(newData, deque->data, deque->capacity * sizeof(ItemType));
				free(deque->data);
				deque->data = newData;
			}
		}

		deque->capacity = capacity;
	}
}

#ifdef DYNAMIC_DEQUE
static void Deque_EnsureCapacity(Deque* deque, const SizeType capacity)
{
	if (capacity > deque->capacity)
	{
		SizeType newCapacity = deque->capacity;
		while (capacity > newCapacity)
			newCapacity = (SizeType)floor(newCapacity * RESIZE_FACTOR);

		Deque_Resize(deque, newCapacity);
	}
}
#endif
