//table.h

#ifndef _table_h
#define _table_h

#include <iostream>
#include "record.h"

#define TabOK        0 // ошибок нет
#define TabEmpty  -101 // таблица пуста
#define TabFull   -102 // таблица полна
#define TabNoRec  -103 // нет записи
#define TabRecDbl -104 // дублирование записи
#define TabNoMem  -105 // нет памяти

#define TabMaxSize 25

using namespace std;

class TTable {

protected:
	int DataCount;  //the number of entries in the table
	int Efficiency; //effectiveness indicator

public:
	TTable() { DataCount = 0; Efficiency = 0; }
	virtual ~TTable() { };

	//information methods
	int GetDataCount() const { return DataCount; }
	int GetEfficiency() const { return   Efficiency; }
	void SetEfficiency(int e) { Efficiency = e; }
	void ClearEfficiency() { Efficiency = 0; }
	int IsEmpty() const { return DataCount == 0; }
	virtual int IsFull() const = 0;

	//basic methods
	virtual bool FindRecord(TKey k) = 0;
	virtual void InsRecord(TKey k, TValue pVal) = 0;
	virtual int DelRecord(TKey k) = 0;

	//navigation
	virtual int Reset(void) = 0;
	virtual int IsTabEnded(void) const = 0;
	virtual int GoNext(void) = 0;

	//access
	virtual TKey GetKey(void) const = 0;
	virtual TValue GetValue(void) const = 0;

	//table printing
	friend ostream& operator<<(ostream &os, TTable &tab) {
		cout << "Table printing" << endl;
		int i = 0;
		for (tab.Reset(); !tab.IsTabEnded(); tab.GoNext()) {
			os << " Key: " << tab.GetKey() << " Val: " << tab.GetValue() << endl;
			i++;
			tab.SetEfficiency(i);
		}
		return os;
	}
};
#endif
