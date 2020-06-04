#include "arraytable.h"

TKey TArrayTable::GetKey(TDataPos mode) const {
	int pos = -1;
	if (!IsEmpty()) {
		switch (mode) {
		case FIRST_POS:
			pos = 0;
			break;
		case LAST_POS:
			pos = DataCount - 1;
			break;
		default:
			pos = CurrPos;
			break;
		}
	}
	if (pos == -1) {
		return 0;
	}
	else {
		return pRecs[pos].Key;
	}
}

TValue TArrayTable::GetValue(TDataPos mode) const {
	int pos = -1;
	if (!IsEmpty()) {
		switch (mode) {
		case FIRST_POS:
			pos = 0;
			break;
		case LAST_POS:
			pos = DataCount - 1;
			break;
		default:
			pos = CurrPos;
			break;
		}
	}
	if (pos == -1) {
		return "";
	}
	else {
		return pRecs[pos].pValue;
	}
}

int TArrayTable::Reset(void) {
	CurrPos = 0;
	return IsTabEnded();
}

int TArrayTable::IsTabEnded(void) const {
	return CurrPos >= DataCount;
}

int TArrayTable::GoNext(void) {
	if (!IsTabEnded())
		CurrPos++;
	return IsTabEnded();
}

int TArrayTable::SetCurrentPos(int pos) {
	CurrPos = ((pos > -1) && (pos < DataCount)) ? pos : 0;
	return IsTabEnded();
}
