#ifndef _VACTOR_H_
#define _VACTOR_H_
#include <stdlib.h> /* size_t */

typedef enum
{
/* General ADT Errors */
ERR_OK =0,
ERR_GENERAL,
ERR_NOT_INITIALIZED,
ERR_ALLOCATION_FAILED,
ERR_REALLOCATION_FAILED,
ERR_UNDERFLOW,
ERR_OVERFLOW,
ERR_WRONG_INDEX

} ADTErr;


typedef struct Vector Vector;

Vector* VectorCreate(size_t _initialSize, size_t _extensionBblockSize);
void VectorDestroy(Vector* _vector);
void VectorPrint(Vector* _vector);
ADTErr VectorAddEnd(Vector* _vector, int _item);
ADTErr VectorDeleteEnd(Vector* _vector,int* _item);
ADTErr VectorDeleteByKey(Vector* _vector,int* _item);
ADTErr VectorItemsNum(Vector* _vector,int* _numOfItems);
ADTErr VectorGet(Vector* _vector,size_t _index,int *_item);
ADTErr VectorSet(Vector* _vector,size_t _index,int _item);
#endif
