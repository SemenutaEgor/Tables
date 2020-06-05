//arrayhash.h

#ifndef __ARRHASH_H__
#define __ARRHASH_H__

#include "hashtable.h"

#define TabHashStep  7

class TArrayHashTable : public THashTable {

protected:
	TTabRecord *pRecs; //memory for table entries
	int TabSize; //maximum possible number of records
	int HashStep; //secondary mixing step
	int FreePos; //first free string found during search
	int CurrPos; //current line number at search completion
	TTabRecord Mark; //marker for indicating rows with deleted records
	TTabRecord Empty; //vacant line marker

	//open mixing function (secondary hashing)
	int GetNextPos(int pos) { return (pos + HashStep) % TabSize; }

public:
	TArrayHashTable(int Size = TabMaxSize, int Step = TabHashStep);
	virtual ~TArrayHashTable();

	//information methods
	virtual int IsFull() const { return DataCount >= TabSize; }

	//basic methods
	virtual bool FindRecord(TKey k);
	virtual void InsRecord(TKey k, TValue pVal);
	virtual int DelRecord(TKey k);

	//navigation
	virtual int Reset(void);
	virtual int IsTabEnded(void) const;
	virtual int GoNext(void);

	//access
	virtual TKey GetKey(void) const;
	virtual TValue GetValue(void) const;
};

#endif

