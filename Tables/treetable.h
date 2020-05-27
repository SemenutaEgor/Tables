//treetable.h
#ifndef _treetable_h
#define _treetable_h
#include <stack>
#include "table.h"
#include "treenode.h"

class TTreeTable : public TTable
{
protected:
	PTTreeNode  pRoot;    // указатель на корень дерева
	PTTreeNode *ppRef;    // адрес указателя на вершину-результата в FindRecord
	PTTreeNode  pCurrent; // указатель на текущую вершину
	int CurrPos;          // номер текущей вершины
	stack<PTTreeNode> St; // стек для итератора

	void PrintTreeTable(ostream &os, PTTreeNode pNode); // Печать
	void DrawTreeTable(PTTreeNode pNode, int Level);   // Печать с ярусами
	void DeleteTreeTable(PTTreeNode pNode);              // Удаление
public:
	TTreeTable() : TTable()
	{
		CurrPos = 0; pRoot = pCurrent = NULL; ppRef = NULL;
	}
	~TTreeTable() { DeleteTreeTable(pRoot); }
	// информационные методы
	virtual int IsFull() const;               // заполнена?
	// основные методы
	virtual bool FindRecord(TKey k); // найти запись
	virtual int       InsRecord(TKey k, TValue pVal); // вставить
	virtual int       DelRecord(TKey k); // удалить запись
	// навигация
	virtual int Reset(void);       // установить на первую запись
	virtual int IsTabEnded(void) const; // таблица завершена?
	virtual int GoNext(void);       // переход к следующей записи
	// (=1 после применения GoNext для последней записи таблицы)
	// доступ
	virtual TKey GetKey(void) const;    // ключ текущей записи
	virtual TValue GetValue(void) const; // указатель на значение
	// Печать таблицы
	friend ostream& operator<<(ostream &os, TTreeTable &tab);
	void Draw(void); // печать дерева (рисунок слева направо)
	void Show(void); // печать дерева (рисунок сверху вниз)
protected:
	string tk[20];
	int tl[20], pos;
	void PutValues(PTTreeNode pNode, int Level); // служебный метод для Show
};

#endif 

