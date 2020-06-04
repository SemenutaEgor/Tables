#include "treetable.h"

int TTreeTable::IsFull() const // ���������?
{
	TTreeNode* pNode = new TTreeNode();
	int temp = pNode == NULL;
	delete pNode;
	return temp;
}

bool TTreeTable::FindRecord(TKey k) // ����� ������
{
	pPrev = NULL;
	pCurrent = pRoot;
	while (pCurrent != NULL) {
		Efficiency++;
		if (pCurrent->Key == k) break;
		pPrev = pCurrent;
		if (pCurrent->Key < k) pCurrent = pCurrent->pRight;
		else pCurrent = pCurrent->pLeft;
	}
	if (pCurrent != NULL) {
		return true;
	}
	else {
		pCurrent = pPrev;
		return false;
	}
	/*TTreeNode* pNode = pRoot;
	ppRef = pRoot; // ����� ��������� �� �������-����������
	Efficiency = 0;
	while (pNode != NULL)
	{
		Efficiency++;
		if (pNode->Key == k)
			break;
		if (pNode->Key < k)
			ppRef = pNode->pRight;
		else
			ppRef = pNode->pLeft;
		pNode = ppRef;
	}
	if (pNode == NULL) {
		return TabNoRec;
	}
	else {
		//return TabOK;
	}
	return (pNode == NULL) ? false : true;*/
} 

int TTreeTable::InsRecord(TKey k, TValue pVal) { // �������� ������
	if (IsFull()) {
		return TabFull;
	}
	else if (FindRecord(k) == true) {
		return TabRecDbl;
	}
	else {
		TTreeNode *tmp = new TTreeNode(k, pVal);
		if (pRoot == NULL) {
			pRoot = tmp;
		}
		else {
			if (k < pCurrent->Key) {
				pCurrent->pLeft = tmp;
			}
			else {
				pCurrent->pRight = tmp;
			}
		}
		Efficiency++;
		DataCount++;
	}
} 

int TTreeTable::DelRecord(TKey k) // ������� ������
{
	if (FindRecord(k) == NULL) {
		return TabNoRec;
	}
	else
	{
		TTreeNode* pNode = ppRef;
		if (pNode->pRight == NULL)
			ppRef = pNode->pLeft; // ���� ������� �����
		else if (pNode->pLeft == NULL)
			ppRef = pNode->pRight; // ���� ������� ������
		else // ��� ������� - ����� �������� ������ � ������ ���������
		{
			TTreeNode* pN = pNode->pLeft, *ppR = pNode->pLeft;
			while (pN->pRight != NULL)
			{
				ppR = pN->pRight;
				pN = ppR;
			} // ������ �������� pNode ������� pN
			pNode->pValue = pN->pValue;   // �������� � pNode
			pNode->Key = pN->Key;
			pNode = pN;
			ppR = pN->pLeft; // ����� ���������� pN
		}
		delete pNode;
	}                                                             
}

// ���������
TKey TTreeTable::GetKey(void) const // �������� ����� ������� ������
{
	return (pCurrent == NULL) ? 0 : pCurrent->Key;
} 

TValue TTreeTable::GetValue(void) const // ��������� �� ��������
{
	return (pCurrent == NULL) ? NULL : pCurrent->pValue;
} 

int TTreeTable::Reset(void) // ���������� �� ������ ������
{
	TTreeNode* pNode = pCurrent = pRoot;
	while (!St.empty())
		St.pop(); // ������� �����
	CurrPos = 0;
	while (pNode != NULL) // ������� � ������� ����� �������
	{
		St.push(pNode);
		pCurrent = pNode;
		pNode = pNode->GetLeft();
	}
	return IsTabEnded();
} 

int TTreeTable::IsTabEnded(void) const // ������� ���������?
{
	return CurrPos >= DataCount;
} 

int TTreeTable::GoNext(void) // ������� � ��������� ������
{
	if (!IsTabEnded() && (pCurrent != NULL))                          
	{
		TTreeNode* pNode = pCurrent = pCurrent->GetRight(); // ������� ������
		St.pop();
		while (pNode != NULL) // ������� � ������� ����� �������
		{
			St.push(pNode);
			pCurrent = pNode;
			pNode = pNode->GetLeft();
		}
		// ���� ������� ������� ���, �� ���������� �� �����
		if ((pCurrent == NULL) && !St.empty())
			pCurrent = St.top();
		CurrPos++;
	}
	return IsTabEnded();                                          
} 

// ������ ������
ostream& operator<<(ostream &os, TTreeTable &tab)
{
	cout << "Table printing" << endl;
	tab.PrintTreeTable(os, tab.pRoot);
	return os;
} 

void TTreeTable::Draw(void) // ������ ������ (������� ����� �������)
{
	cout << "Table printing" << endl;
	DrawTreeTable(pRoot, 0);
}

// ������ ������ � ������ � ������� ����������� � ���������� ������� ������
void TTreeTable::PutValues(TTreeNode* pNode, int Level)
{
	if ((pNode != NULL) && (pos < 20))
	{
		PutValues(pNode->pLeft, Level + 1);
		tk[pos] = pNode->Key;
		tl[pos] = Level;
		pos++;
		PutValues(pNode->pRight, Level + 1);
	}
} 
void TTreeTable::Show(void) // ������ ������ (������� ������ ����)
{
	int maxl = 0, i, j, k, pn;
	pos = 0;
	PutValues(pRoot, 0);
	for (i = 0; i < pos; i++)
		if (maxl < tl[i])
			maxl = tl[i];
	//  cout << "������ �������" << endl;
	cout << "Table visualization" << endl;
	for (i = 0; i < maxl + 1; i++) // ����� �����
	{
		pn = 0;
		for (j = 0; j < pos; j++) // ������ ������ ����� i
		{
			if (tl[j] == i)
			{
				for (k = 0; k < 2 * (j - pn); k++)
					cout << " ";
				cout << tk[j];
				pn = j + 1;
			}
		}
		cout << endl;
	}
}

// ��������� ������
void TTreeTable::PrintTreeTable(ostream &os, TTreeNode* pNode)
{
	if (pNode != NULL) // ������ ������ � �������� pNode
	{
		PrintTreeTable(os, pNode->pLeft);
		pNode->Print(os);
		os << endl;
		PrintTreeTable(os, pNode->pRight);
	}
}

void TTreeTable::DrawTreeTable(TTreeNode* pNode, int Level)
{
	if (pNode != NULL) // ������ ������� � ����������� ������
	{
		DrawTreeTable(pNode->pRight, Level + 1);
		for (int i = 0; i < 2 * Level; i++)
			cout << " ";
		pNode->Print(cout);
		cout << endl;
		DrawTreeTable(pNode->pLeft, Level + 1);
	}
} 

void TTreeTable::DeleteTreeTable(TTreeNode* pNode)
{
	if (pNode != NULL) // �������� ������ � �������� pNode
	{
		DeleteTreeTable(pNode->pLeft);
		DeleteTreeTable(pNode->pRight);
		delete pNode;
	}
} 
