#include "utilFuncs.h"
#include <string.h>
#include "../vector/vector.h"

static void Reverse(char s[]);
static int Partition(Vector* _vec, int left, int right);

void MyItoa(int _n, char s[])
{
     int i, sign;
 
     if ((sign = _n) < 0)
     {
         _n = -_n;
     }
     i = 0;
     do 
     {
		s[i++] = _n % 10 + '0';
     }while ((_n /= 10) > 0);
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     Reverse(s);
}

static void Reverse(char s[])
{
	int i, j;
	char c;
 
	for (i = 0, j = strlen(s)-1; i<j; i++, j--)
	{
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

static int Partition(Vector* _vec, int left, int right)
{
	int pVal,lVal,rVal;
	int pivot = left;
	VectorGet(_vec,pivot,&pVal);
	
	while(right > left)
	{
		VectorGet(_vec,left,&lVal);
		while(lVal <= pVal && left <= right)
		{
			++left;
			VectorGet(_vec,left,&lVal);
		}
		VectorGet(_vec,right,&rVal);
		while(rVal > pVal)
		{
			--right;
			VectorGet(_vec,right,&rVal);
		}
		if(left < right)
		{
			VectorSet(_vec,left,rVal);
			VectorSet(_vec,right,lVal);
		}
	}
	VectorGet(_vec,right,&rVal);
	VectorSet(_vec,right,pVal);
	VectorSet(_vec,pivot,rVal);
	return right;
}

void QuickSortRec(Vector* _vec, int start, int end)
{
	int pivot;
	if(_vec == NULL)
	{
		return;
	}
	if(start < end)
	{
		pivot = Partition(_vec, start, end);
		if(pivot > start)
		{
			QuickSortRec(_vec, start, pivot - 1);
		}
		if(pivot < end)
		{
			QuickSortRec(_vec, pivot + 1, end);
		}
	}
}

