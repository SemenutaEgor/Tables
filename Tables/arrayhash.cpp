//arrayhash.cpp

#include "arrayhash.h"

TArrayHashTable::TArrayHashTable(int Size, int Step) : TabSize(Size), HashStep(Step) {
	pRecs = new TTabRecord[TabSize];
	Empty = TTabRecord(-1);
	Mark = TTabRecord(-2);
	for (int i = 0; i < TabSize; i++) {
		pRecs[i] = Empty;
	}
}

TArrayHashTable::~TArrayHashTable() {
	delete[] pRecs;
}

bool TArrayHashTable::FindRecord(TKey k) {
	bool result = false;
	FreePos = -1;
	CurrPos = HashFunc(k) % TabSize;
	for (int i = 0; i < TabSize; i++) {
		Efficiency++;
		if (pRecs[CurrPos] == Empty) {
		}
		else if (pRecs[CurrPos] == Mark) {
			if (FreePos == -1) {
				FreePos = CurrPos;
			}
		}
		else if (pRecs[CurrPos].Key == k) {
			result = true;
			break;
		}
		CurrPos = GetNextPos(CurrPos);
	}
	return result;
}

void TArrayHashTable::InsRecord(TKey k, TValue pVal) {
	if (IsFull()) {
		cerr << " TabFull " << endl;
		//return TabFull;
	}
	else if (FindRecord(k) == true) {
		cerr << " TabRecDbl " << endl;
		//return TabRecDbl;
	}
	else {
		Efficiency++;
		if (FreePos != -1) {
			CurrPos = FreePos;
		}
		pRecs[DataCount].Key = k;
		pRecs[DataCount].pValue = pVal;
		//pRecs[CurrPos] = TTabRecord(k, pVal);
		DataCount++;
		//return TabOK;
	}
}

int TArrayHashTable::DelRecord(TKey k) {
	bool temp = FindRecord(k);
	if (temp == false) {
		cerr << " TabNoRec " << endl;
		return TabNoRec;
	}
	else {
		pRecs[CurrPos] = Mark;
		DataCount--;
	}
}

int TArrayHashTable::Reset(void) {
	CurrPos = 0;
	while (CurrPos < TabSize) {
		if ((pRecs[CurrPos] != Empty) && (pRecs[CurrPos] != Mark))
			break;
		else
			CurrPos++;
	}
	return IsTabEnded();
}

int TArrayHashTable::IsTabEnded(void) const {
	return CurrPos >= TabSize;
}

int TArrayHashTable::GoNext(void) {
	if (!IsTabEnded())
	{
		while (++CurrPos < TabSize)
			if ((pRecs[CurrPos] != Empty) && (pRecs[CurrPos] != Mark))
				break;
	}
	return IsTabEnded();
}

TKey TArrayHashTable::GetKey(void) const {
	return pRecs[CurrPos].GetKey();
}

TValue TArrayHashTable::GetValue(void) const {
	return  pRecs[CurrPos].GetValue();
}
