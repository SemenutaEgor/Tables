//treetable.h

#ifndef _treetable_h
#define _treetable_h
#include <stack>
#include "table.h"
#include "treenode.h"

class TTreeTable : public TTable {
protected:
	TTreeNode  *pRoot; //pointer to the root of the tree
	TTreeNode *ppRef; //address of the pointer to the top - result in FindRecord
	TTreeNode  *pCurrent; //pointer to current vertex
	TTreeNode *pPrev; //pointer to previous
	int CurrPos; //current vertex number
	stack<TTreeNode*> St; //stack for iterator

	void PrintTreeTable(ostream &os, TTreeNode *pNode);
	void DrawTreeTable(TTreeNode *pNode, int Level);
	void DeleteTreeTable(TTreeNode *pNode);
public:

	TTreeTable() : TTable() {
		CurrPos = 0; pRoot = pCurrent = NULL; ppRef = NULL;
	}
	~TTreeTable() { DeleteTreeTable(pRoot); }

	virtual int IsFull() const;

	//basic methods
	virtual bool FindRecord(TKey k);
	virtual int InsRecord(TKey k, TValue pVal);
	virtual int DelRecord(TKey k);

	//navigation
	virtual int Reset(void);
	virtual int IsTabEnded(void) const;
	virtual int GoNext(void);

	//access
	virtual TKey GetKey(void) const;
	virtual TValue GetValue(void) const;

	//Table printing
	friend ostream& operator<<(ostream &os, TTreeTable &tab);
	void Draw(void); //tree print(picture from left to right)
	//void Show(void); //tree print (top to bottom drawing)

/*protected:
	string tk[20];
	int tl[20], pos;
	void PutValues(TTreeNode *pNode, int Level); // служебный метод для Show*/
};

#endif 

