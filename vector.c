#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAGIC 34567

int* ResizeArray(int* _items,size_t newSize);
int IsResizeNeeded(Vector* _vector);
void ChangeSize(Vector* _vector);

struct Vector
{
	int* m_items;
	size_t m_originalSize;
	size_t m_size;
	size_t m_nItems;
	size_t m_blockSize;
	int m_magic;
};

Vector* VectorCreate(size_t _initialSize, size_t _extensionBblockSize)
{
	Vector* newVec = NULL;
	int* newItems = NULL;
	if(_extensionBblockSize <1)
	{
		return NULL;
	}
	newVec = (Vector*)malloc(sizeof(Vector));
	if(NULL == newVec)
	{
		return newVec;
	}
	newItems = (int*)malloc(sizeof(int)*_initialSize);
	if(NULL == newItems)
	{
		free(newVec);
		return NULL;
	}
	newVec->m_originalSize = _initialSize;
	newVec->m_size = _initialSize;
	newVec->m_nItems = 0;
	newVec->m_blockSize = _extensionBblockSize;
	newVec->m_items = newItems;
	newVec->m_magic = MAGIC;

	return newVec;
}

void VectorDestroy(Vector* _vector)
{
	if(_vector && _vector->m_magic == MAGIC)
	{
		if(_vector->m_items)
		{
			free(_vector->m_items);
		}
		_vector->m_magic = 0;
		free(_vector);
	}
}

void VectorPrint(Vector* _vector)
{
	int i;
	
	if(_vector != NULL && _vector->m_items != NULL)
	{	
		for(i=0;i<_vector->m_nItems;i++)
		{
			printf("(%d) %d\n",i,_vector->m_items[i]);
		}
	}
}

ADTErr VectorAddEnd(Vector* _vector,int _item)
{
	int* newItems = NULL;
	if(_vector == NULL || _vector->m_items == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(_vector->m_nItems >= _vector->m_size)
	{
		if(_vector->m_blockSize == 0)
		{
			return ERR_OVERFLOW;
		}
		newItems = ResizeArray(_vector->m_items,_vector->m_size+_vector->m_blockSize);
		if(NULL == newItems)
		{
			return ERR_REALLOCATION_FAILED;
		}
		_vector->m_items = newItems;
		_vector->m_size += _vector->m_blockSize;
	}
	_vector->m_items[_vector->m_nItems] = _item;
	++_vector->m_nItems;
	return ERR_OK;
}

ADTErr VectorDeleteEnd(Vector* _vector,int* _item)
{
	if(_vector && _vector->m_items && _item)
	{
		if(_vector->m_nItems >= 1)
		{
			*_item = _vector->m_items[_vector->m_nItems-1];
			--_vector->m_nItems;
			
			if(IsResizeNeeded(_vector))
			{
				ChangeSize(_vector);
			}
			return ERR_OK;
		}
		return ERR_UNDERFLOW;
	}
	return ERR_NOT_INITIALIZED;
}

void ChangeSize(Vector* _vector)
{
	if(_vector)
	{
		int* newItems = NULL;
		size_t newSize;
		
		newSize = _vector->m_size + _vector->m_blockSize;
		newItems = ResizeArray(_vector->m_items,newSize);
		if(newItems)
		{
			_vector->m_items = newItems;
			_vector->m_size = newSize;
		}
	}
}

int IsResizeNeeded(Vector* _vector)
{
	if(_vector->m_size > _vector->m_originalSize+_vector->m_blockSize &&_vector->m_size > _vector->m_nItems+_vector->m_blockSize)
	{
		return 1;
	}
	return 0;
}

ADTErr VectorItemsNum(Vector* _vector,int* _numOfItems)
{
	if(_vector && _vector->m_items && _numOfItems)
	{
		*_numOfItems = _vector->m_nItems;
		return ERR_OK;
	}
	return ERR_NOT_INITIALIZED;
}

ADTErr VectorGet(Vector* _vector,size_t _index,int *_item)
{
	if(_vector && _vector->m_items && _item)
	{
		if(_index >= 0 && _index < _vector->m_nItems)
		{
			*_item = _vector->m_items[_index];
			return ERR_OK;
		}
		return ERR_WRONG_INDEX;
	}
	return ERR_NOT_INITIALIZED;
}

ADTErr VectorSet(Vector* _vector,size_t _index,int _item)
{
	if(_vector && _vector->m_items)
	{
		if(_index >= 0 && _index < _vector->m_nItems)
		{
			_vector->m_items[_index] = _item;
			return ERR_OK;
		}
		return ERR_WRONG_INDEX;
	}
	return ERR_NOT_INITIALIZED;
}

ADTErr VectorGetLast(Vector* _vector,int* _item)
{
	if(_vector && _vector->m_items && _item)
	{
		if(_vector->m_nItems >0)
		{
			*_item = _vector->m_items[_vector->m_nItems-1];
			return ERR_OK;
		}
		return ERR_UNDERFLOW;
	}
	return ERR_NOT_INITIALIZED;
}

int* ResizeArray(int* _items,size_t newSize)
{
	return (int*)realloc(_items,newSize * sizeof(int));
}

