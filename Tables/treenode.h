//treenode.h
#ifndef _treenode_h
#define _treenode_h
#include "record.h"

class   TTreeNode;
typedef TTreeNode *PTTreeNode;

class TTreeNode : public TTabRecord
{
protected:
	PTTreeNode pLeft, pRight; // указатели на поддеревья
public:
	TTreeNode(TKey k = 0, TValue pVal = NULL, PTTreeNode pL = NULL, PTTreeNode pR = NULL) : TTabRecord(k, pVal), pLeft(pL), pRight(pR) {
	}
	PTTreeNode GetLeft(void) const { return pLeft; }
	PTTreeNode GetRight(void) const { return pRight; }
	//virtual TValue* GetCopy(); // изготовить копию

	friend class TTreeTable;
};

#endif 

