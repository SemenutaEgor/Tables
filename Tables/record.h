//record.h
#ifndef _reccord_h
#define _record_h

#include <iostream>
#include <string>

using namespace std;

typedef string TKey;
typedef string TValue;

class TTabRecord
{
protected:
	TKey Key;    // ключ
	TValue pValue; // значение

	virtual void Print(ostream &os) { os << Key << " " << pValue; }
public:
	TTabRecord() {}
	TTabRecord(TKey k) { Key = k; }
	TTabRecord(TKey k = "", TValue pVal = NULL) { Key = k; pValue = pVal; }
	void SetKey(TKey k) { Key = k; }
	TKey GetKey(void) { return Key; }
	void SetValuePtr(TValue p) { pValue = p; }
	TValue GetValuePtr(void) { return pValue; }
	virtual TValue* GetCopy(); // изготовить копию
	TTabRecord& operator=(TTabRecord &tr)
	{
		Key = tr.Key;
		pValue = tr.pValue;
		return *this;
	}
	virtual int operator==(const TTabRecord &tr) { return Key == tr.Key; }
	virtual int operator< (const TTabRecord &tr) { return Key > tr.Key; }
	virtual int operator> (const TTabRecord &tr) { return Key < tr.Key; }

	friend class TArrayTable;
	friend class TScanTable;

};

typedef TTabRecord* PTTabRecord;
#endif
