//arraytable.h
#ifndef _arraytable_h
#define _arraytable_h

#include "table.h"

#define TabMaxSize 25

enum TDataPos { FIRST_POS, CURRENT_POS, LAST_POS };

class TArrayTable : public TTable {
protected:
	TTabRecord *pRecs; // ������ ��� ������� �������
	int TabSize;        // ����. ����. �-�� �������
	int CurrPos;        // ����� �������� ������ (��������� �� 0)
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
	// �������������� ������
	virtual int IsFull() const {
		return DataCount >= TabSize;
	}
	int GetTabSize() const {
		return TabSize;
	}
	// ������
	virtual TKey GetKey(void) const {
		return GetKey(CURRENT_POS);
	}
	virtual TValue GetValue(void) const {
		return GetValue(CURRENT_POS);
	}
	virtual TKey GetKey(TDataPos mode) const; // ����
	virtual TValue GetValue(TDataPos mode) const; // ����-�� �� ��������
	// ���������
	virtual int Reset(void);       // ���������� �� ������ ������
	virtual int IsTabEnded(void) const; // ������� ���������?
	virtual int GoNext(void);       // ������� � ��������� ������
	// (=1 ����� ���������� GoNext ��� ��������� ������ �������)
	virtual int SetCurrentPos(int pos); // ���������� ������� ������
	int GetCurrentPos(void) const {      // �������� ����� ������� ������
		return CurrPos;
	}

	//friend TSortTable;
};
#endif