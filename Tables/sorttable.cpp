//sorttable.cpp

#include "sorttable.h"

TSortTable& TSortTable::operator=(const TScanTable &tab)
{
	if (pRecs != NULL)
	{
		delete[] pRecs;
		delete[] pBuff;
		pRecs = NULL;
	}
	TabSize = tab.GetTabSize();
	DataCount = tab.GetDataCount();
	pRecs = new TTabRecord[TabSize];
	pBuff = new TTabRecord[TabSize];
	for (int i = 0; i < DataCount; i++) {
		pRecs[i] = tab.pRecs[i];
	}
	SortData();
	CurrPos = 0;
	return *this;
} 

bool TSortTable::FindRecord(TKey k) {
	int i, i1 = 0, i2 = DataCount - 1; 
	Efficiency = 0;                                                   
	while (i1 <= i2) {
		Efficiency++;
		i = (i1 + i2) >> 1;
		if (pRecs[i].Key == k){
			i1 = i + 1;
			i2 = i;
			break;
		}
		if (pRecs[i].Key > k)
			i2 = i - 1;
		else
			i1 = i + 1;
	}
	if ((i2 < 0) || (pRecs[i2].Key < k))
		i2++;
	CurrPos = i2;
	if ((i2 < DataCount) && (pRecs[i].Key == k)) {
		//return pRecs[i2].pValue;
		return true;
	}
	return false;                                                      
} 

int TSortTable::InsRecord(TKey k, TValue pVal) {
	if (IsFull()) {
		cerr << " TabFull " << endl;
		return TabFull;
	}
	else if (FindRecord(k) == true) {
		cerr << " TabRecDbl " << endl;
		return TabRecDbl;
	}
	else {
		int temp = FindRecord(k);
		Efficiency++;
			for (int i = DataCount; i > CurrPos; i--)
				pRecs[i] = pRecs[i - 1]; 
			pRecs[CurrPos].Key = k;
			pRecs[CurrPos].pValue = pVal;
			//pRecs[CurrPos] = new TTabRecord(k, pVal);
			DataCount++;
	}
} 
int TSortTable::DelRecord(TKey k) {
	bool temp = FindRecord(k);       
	if (temp == 0) {
		cerr << "TabNoRec" << endl;
		return temp;
	}
	else {
		for (int i = CurrPos; i < DataCount - 1; i++)
			pRecs[i] = pRecs[i + 1];
		DataCount--;
		return TabOK;
	}
} 

void TSortTable::SortData() {
	Efficiency = 0;
	switch (SortMethod)
	{
	case INSERT_SORT:
		InsertSort(pRecs, DataCount); 
		break;
	/*case MERGE_SORT:
		MergeSort(pRecs, DataCount); 
		break;
	case QUICK_SORT:
		QuickSort(pRecs, DataCount);  
		break;*/
	}
} 

void TSortTable::InsertSort(TTabRecord *pRecs, int DataCount) {
	TTabRecord pR;
	Efficiency = DataCount;
	for (int i = 1, j; i < DataCount; i++) {
		pR = pRecs[i]; 
		for (j = i - 1; j > -1; j--)
			if (pRecs[j].Key > pR.Key) {
				pRecs[j + 1] = pRecs[j]; 
				Efficiency++;
			}
			else
				break;
		pRecs[j + 1] = pR; 
	}
} 

/*void TSortTable::MergeSort(TTabRecord *pRecs, int DataCount) {
	TTabRecord *pData = pRecs;
	TTabRecord *pBuff = new TTabRecord[DataCount];
	TTabRecord *pTemp = pBuff;
	MergeSorter(pData, pBuff, DataCount);
	if (pData == pTemp) 
		for (int i = 0; i < DataCount; i++)
			pBuff[i] = pData[i];
	delete pTemp;
} 

void TSortTable::MergeSorter(TTabRecord *&pData, TTabRecord *&pBuff, int Size) {
	int n1 = (Size + 1) / 2;
	int n2 = Size - n1;
	if (Size > 2) {
		TTabRecord *pDat2 = pData + n1, *pBuff2 = pBuff + n1;
		MergeSorter(pData, pBuff, n1); 
		MergeSorter(pDat2, pBuff2, n2);
	}
	MergeData(pData, pBuff, n1, n2); 
} 


void TSortTable::MergeData(TTabRecord *&pData, TTabRecord *&pBuff, int n1, int n2) {
	int i = 0, i1 = 0, i2 = 0;                                        
	TTabRecord *pDat1 = pData, *pDat2 = pData + n1;
	while ((i1 < n1) && (i2 < n2)) {
		if (pDat1[i1].Key < pDat2[i2].Key)
			pBuff[i++] = pDat1[i1++];
		else
			pBuff[i++] = pDat2[i2++];
	}
	
	while (i1 < n1)
		pBuff[i++] = pDat1[i1++];
	while (i2 < n2)
		pBuff[i++] = pDat2[i2++];
	pData = pBuff;
	pBuff = pDat1;
	Efficiency += n1 + n2;                                          
}

void TSortTable::QuickSort(TTabRecord *pRecs, int DataCount) {
	int pivot;  // индекс ведущего элемента
	int n1, n2; // размеры разделенных блоков данных
	if (DataCount > 1) {
		QuickSplit(pRecs, DataCount, pivot); // разделение
		n1 = pivot + 1;
		n2 = DataCount - n1;
		QuickSort(pRecs, n1 - 1);  // сортировка разделенных блоков массива
		QuickSort(pRecs + n1, n2);
	}
} 

// быстрая сортировка - выбор ведущего элемента и разделение данных
void TSortTable::QuickSplit(TTabRecord *pData, int Size, int &Pivot) {
	TTabRecord pPivot = pData[0]; // pPivot - указатель на ведущий элемент
	TTabRecord pTemp;
	int i1 = 1, i2 = Size - 1; // индексы левого (i1) и правого (i2) блоков
	while (i1 <= i2) { // цикл, пока блоки не пересекутся

		// пока pData[i1]->Key не превышает ключа вед. эл-та, переход вправо
		while ((i1 < Size) && !(pData[i1].Key > pPivot.Key))
			i1++;
		// пока pData[i2]->Key меньше ключа вед. эл-та, переход влево
		while (pData[i2].Key > pPivot.Key)
			i2--;
		// перестановка элементов, на которых произошла остановка разделения
		if (i1 < i2) {
			pTemp = pData[i1];
			pData[i1] = pData[i2];
			pData[i2] = pTemp;
		}
	}
	// установка ведущего элемента между блоками
	pData[0] = pData[i2];
	pData[i2] = pPivot;
	Pivot = i2; // i2 - индекс позиции ведущего элемента
	Efficiency += Size;
} */