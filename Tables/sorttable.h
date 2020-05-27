//sorttable.h
#ifndef _sorttable_h
#define _sorttable_h
#include "scantable.h"

enum TSortMethod { INSERT_SORT=1, MERGE_SORT, QUICK_SORT };

class TSortTable : public TScanTable {
protected:

	TTabRecord *pBuff; //merge sort buffer

	TSortMethod SortMethod; //sorting method index

	void SortData(void);   //data sorting
	void InsertSort(TTabRecord *pMem, int DataCount); //insertion method
	void MergeSort(TTabRecord *pMem, int DataCount); //merge method
	void MergeSorter(TTabRecord *&pData, TTabRecord *&pBuff, int Size);
	void MergeData(TTabRecord *&pData, TTabRecord *&pBuff, int n1, int n2);
	void QuickSort(TTabRecord *pMem, int DataCount); //quick sort
	void QuickSplit(TTabRecord *pData, int Size, int &Pivot);
public:
	TSortTable(int Size = TabMaxSize) : TScanTable(Size) { };

	//creating an ordered table by the table being viewed
	TSortTable(const TScanTable &tab) { *this = tab; }
	TSortTable& operator=(const TScanTable &tab);
	/*TSortMethod GetSortMethod(void) { return SortMethod; }
	void SetSortMethod(TSortMethod sm) { SortMethod = sm; }*/

	//basic methods
	virtual bool FindRecord(TKey k);                
	virtual int InsRecord(TKey k, TValue pVal); 
	virtual int DelRecord(TKey k);                  
};

#endif 