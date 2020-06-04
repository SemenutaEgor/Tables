//hashtable.cpp

#include "hashtable.h"

unsigned int THashTable::HashFunc(const TKey key) {
	unsigned long hashval = key;
	return hashval;
}