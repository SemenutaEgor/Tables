//scantable.h
#ifndef _scantable_h
#define _scantable_h

#include "arraytable.h"

class TScanTable : public TArrayTable
{
public:
	TScanTable(int Size = TabMaxSize) : TArrayTable(Size) { };
	// основные методы
	virtual bool FindRecord(TKey k);                  // найти запись
	virtual int InsRecord(TKey k, TValue pVal); // вставить запись
	virtual int DelRecord(TKey k); // удалить запись
};

#endif