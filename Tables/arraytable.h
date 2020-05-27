//arraytable.h
#ifndef _arraytable_h
#define _arraytable_h

#include "table.h"

#define TabMaxSize 25

enum TDataPos { FIRST_POS, CURRENT_POS, LAST_POS };

class TArrayTable : public TTable {
protected:
	TTabRecord *pRecs; // память для записей таблицы
	int TabSize;        // макс. возм. к-во записей
	int CurrPos;        // номер текущего записи (нумерация от 0)
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
	// информационные методы
	virtual int IsFull() const {
		return DataCount >= TabSize;
	}
	int GetTabSize() const {
		return TabSize;
	}
	// доступ
	virtual TKey GetKey(void) const {
		return GetKey(CURRENT_POS);
	}
	virtual TValue GetValue(void) const {
		return GetValue(CURRENT_POS);
	}
	virtual TKey GetKey(TDataPos mode) const; // ключ
	virtual TValue GetValue(TDataPos mode) const; // указ-ль на значение
	// навигация
	virtual int Reset(void);       // установить на первую запись
	virtual int IsTabEnded(void) const; // таблица завершена?
	virtual int GoNext(void);       // переход к следующей записи
	// (=1 после применения GoNext для последней записи таблицы)
	virtual int SetCurrentPos(int pos); // установить текущую запись
	int GetCurrentPos(void) const {      // получить номер текущей записи
		return CurrPos;
	}

	//friend TSortTable;
};
#endif
