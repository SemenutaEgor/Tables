#include "treetable.h"

int TTreeTable::IsFull() const // заполнена?
{
	TTreeNode* pNode = new TTreeNode();
	int temp = pNode == NULL;
	delete pNode;
	return temp;
}

bool TTreeTable::FindRecord(TKey k) // найти запись
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
	ppRef = pRoot; // адрес указателя на вершину-результата
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

int TTreeTable::InsRecord(TKey k, TValue pVal) { // вставить запись
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

int TTreeTable::DelRecord(TKey k) // удалить запись
{
	if (FindRecord(k) == NULL) {
		return TabNoRec;
	}
	else
	{
		TTreeNode* pNode = ppRef;
		if (pNode->pRight == NULL)
			ppRef = pNode->pLeft; // один потомок слева
		else if (pNode->pLeft == NULL)
			ppRef = pNode->pRight; // один потомок справа
		else // два потомка - поиск крайнего справа у левого поддерева
		{
			TTreeNode* pN = pNode->pLeft, *ppR = pNode->pLeft;
			while (pN->pRight != NULL)
			{
				ppR = pN->pRight;
				pN = ppR;
			} // вместо удаления pNode удается pN
			pNode->pValue = pN->pValue;   // значение в pNode
			pNode->Key = pN->Key;
			pNode = pN;
			ppR = pN->pLeft; // обход удаляемого pN
		}
		delete pNode;
	}                                                             
}

// навигация
TKey TTreeTable::GetKey(void) const // значение ключа текущей записи
{
	return (pCurrent == NULL) ? 0 : pCurrent->Key;
} 

TValue TTreeTable::GetValue(void) const // указатель на значение
{
	return (pCurrent == NULL) ? NULL : pCurrent->pValue;
} 

int TTreeTable::Reset(void) // установить на первую запись
{
	TTreeNode* pNode = pCurrent = pRoot;
	while (!St.empty())
		St.pop(); // очистка стека
	CurrPos = 0;
	while (pNode != NULL) // переход к крайней левой вершине
	{
		St.push(pNode);
		pCurrent = pNode;
		pNode = pNode->GetLeft();
	}
	return IsTabEnded();
} 

int TTreeTable::IsTabEnded(void) const // таблица завершена?
{
	return CurrPos >= DataCount;
} 

int TTreeTable::GoNext(void) // переход к следующей записи
{
	if (!IsTabEnded() && (pCurrent != NULL))                          
	{
		TTreeNode* pNode = pCurrent = pCurrent->GetRight(); // переход вправо
		St.pop();
		while (pNode != NULL) // переход к крайней левой вершине
		{
			St.push(pNode);
			pCurrent = pNode;
			pNode = pNode->GetLeft();
		}
		// если правого потомка нет, то извлечение из стека
		if ((pCurrent == NULL) && !St.empty())
			pCurrent = St.top();
		CurrPos++;
	}
	return IsTabEnded();                                          
} 

// методы печати
ostream& operator<<(ostream &os, TTreeTable &tab)
{
	cout << "Table printing" << endl;
	tab.PrintTreeTable(os, tab.pRoot);
	return os;
} 

void TTreeTable::Draw(void) // печать дерева (рисунок слева направо)
{
	cout << "Table printing" << endl;
	DrawTreeTable(pRoot, 0);
}

// запись ключей в массив в порядке возрастания с запоминаем номеров ярусов
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
void TTreeTable::Show(void) // печать дерева (рисунок сверху вниз)
{
	int maxl = 0, i, j, k, pn;
	pos = 0;
	PutValues(pRoot, 0);
	for (i = 0; i < pos; i++)
		if (maxl < tl[i])
			maxl = tl[i];
	//  cout << "Печать таблицы" << endl;
	cout << "Table visualization" << endl;
	for (i = 0; i < maxl + 1; i++) // номер яруса
	{
		pn = 0;
		for (j = 0; j < pos; j++) // печать ключей яруса i
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

// служебные методы
void TTreeTable::PrintTreeTable(ostream &os, TTreeNode* pNode)
{
	if (pNode != NULL) // печать дерева с вершиной pNode
	{
		PrintTreeTable(os, pNode->pLeft);
		pNode->Print(os);
		os << endl;
		PrintTreeTable(os, pNode->pRight);
	}
}

void TTreeTable::DrawTreeTable(TTreeNode* pNode, int Level)
{
	if (pNode != NULL) // печать таблицы с соблюдением ярусов
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
	if (pNode != NULL) // удаление дерева с вершиной pNode
	{
		DeleteTreeTable(pNode->pLeft);
		DeleteTreeTable(pNode->pRight);
		delete pNode;
	}
} 
