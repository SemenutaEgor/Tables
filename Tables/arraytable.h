//arraytable.h
#ifndef _arraytable_h
#define _arraytable_h

#include "table.h"

#define TabMaxSize 25

enum TDataPos { FIRST_POS, CURRENT_POS, LAST_POS };

class TArrayTable : public TTable {

protected:
	TTabRecord *pRecs; // memory for table entries
	int TabSize; //table size
	int CurrPos; //current record number (numbering from 0)

public:
	TArrayTable() {};
	TArrayTable(int Size = TabMaxSize) {
		pRecs = new TTabRecord[Size];
		TabSize = Size;
		DataCount = CurrPos = 0;
	}
	virtual ~TArrayTable() {
		delete[] pRecs;
	}

	//information methods
	virtual int IsFull() const {
		return DataCount >= TabSize;
	}

	int GetTabSize() const {
		return TabSize;
	}

	//access
	virtual TKey GetKey(void) const {
		return GetKey(CURRENT_POS);
	}
	virtual TValue GetValue(void) const {
		return GetValue(CURRENT_POS);
	}
	virtual TKey GetKey(TDataPos mode) const; 
	virtual TValue GetValue(TDataPos mode) const; 

	//navigation
	virtual int Reset(void);       
	virtual int IsTabEnded(void) const; 
	virtual int GoNext(void);     
	virtual int SetCurrentPos(int pos); 
	int GetCurrentPos(void) const {      
		return CurrPos;
	}

	//friend TSortTable;
};
#endif
