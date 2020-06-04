//treenode.h
#ifndef _treenode_h
#define _treenode_h
#include "record.h"

#define BalOk 0
#define BalLeft -1
#define BalRight 1

//class   TTreeNode;
//typedef TTreeNode *PTTreeNode;

class TTreeNode : public TTabRecord {
protected:
	TTreeNode *pLeft, *pRight; // ��������� �� ����������
	int Balance; //������ ������������ �������
public:

	TTreeNode() { pLeft = pRight = NULL; Balance = BalOk; } //default constructor
	TTreeNode(TKey k, TValue pVal, TTreeNode *pL = NULL, TTreeNode *pR = NULL, int bal = BalOk):
	TTabRecord(k, pVal), pLeft(pL), pRight(pR), Balance(bal) {} //����������� �������������
	TTreeNode* GetLeft(void) const { return pLeft; }
	TTreeNode* GetRight(void) const { return pRight; }
	//virtual TValue* GetCopy(); // ���������� �����

	int GetBalance(void) const { return Balance; }
	void SetBalance(int bal) { Balance = bal; }

	friend class TTreeTable;
	friend class TBalanceTree;
};

#endif 

