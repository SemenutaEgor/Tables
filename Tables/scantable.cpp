#include "scantable.h"

bool TScanTable::FindRecord(TKey k) // найти запись
{
	int i;
	for (i = 0; i < DataCount; i++)
		if (pRecs[i].Key == k)
			break;
	Efficiency = i + 1;
	if (i < DataCount)
	{
		CurrPos = i;
		return true;
	}
	return false;
}

int TScanTable::InsRecord(TKey k, TValue pVal) // вставить запись
{
	if (IsFull()) {
		return TabFull;
	}
	else
	{
		//pRecs[DataCount] = new TTabRecord(k, pVal);
		pRecs[DataCount].Key = k;
		pRecs[DataCount].pValue = pVal;
		DataCount++;          
		return TabOK;
	}
}

int TScanTable::DelRecord(TKey k) // удалить запись
{
	int temp = FindRecord(k);                                
	if (temp != 0) {
		return temp;
	}
	else
	{
		pRecs[CurrPos] = pRecs[DataCount - 1];
		DataCount--;
		//pRecs[--DataCount] = NULL;
		return TabOK;
	}                                                                 
}