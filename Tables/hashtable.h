//hashtable.h

#ifndef _hashtable_h
#define _hashtable_h

#include "table.h"

#define TabMaxSize 25

class THashTable : public TTable {
protected:
	virtual unsigned int HashFunc(const TKey key);
public:
	THashTable() : TTable() { }
};

#endif