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

class TTable
{
protected:
	int DataCount;  // количество записей в таблице
	int Efficiency; // показатель эффективности выполнения операции
public:
	TTable() { DataCount = 0; Efficiency = 0; }
	virtual ~TTable() { };
	// информационные методы
	int GetDataCount()   const { return DataCount; } // количество записей
	int GetEfficiency()  const { return   Efficiency; } // эффективность
	void ClearEfficiency() { Efficiency = 0; } //обнулить счётчик операций
	int IsEmpty()        const { return DataCount == 0; } // пуста?
	virtual int IsFull() const = 0;                       // заполнена?
	// основные методы
	virtual bool FindRecord(TKey k) = 0;         // найти запись
	virtual int InsRecord(TKey k, TValue pVal) = 0; // вставить
	virtual int DelRecord(TKey k) = 0;         // удалить запись
	// навигация
	virtual int Reset(void) = 0; // установить на первую запись
	virtual int IsTabEnded(void) const = 0; // таблица завершена?
	virtual int GoNext(void) = 0; // переход к следующей записи

	// доступ
	virtual TKey GetKey(void) const = 0;
	virtual TValue GetValue(void) const = 0;
	// Печать таблицы
	friend ostream& operator<<(ostream &os, TTable &tab)
	{
		cout << "Table printing" << endl;
		for (tab.Reset(); !tab.IsTabEnded(); tab.GoNext())
		{
			os << " Key: " << tab.GetKey() << " Val: " << tab.GetValue() << endl;
		}
		return os;
	}
};
#endif
