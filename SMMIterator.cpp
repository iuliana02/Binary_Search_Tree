#include "SMMIterator.h"
#include "SortedMultiMap.h"

//constructor
//ma pozitionez pe nodul cel mai din stanga si tot adaug nodurile in stack
//cand nu mai am noduri in stanga, scot din stack ultimul nod adaugat si acesta este primul element, pe care il atribui iteratorului
SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
	//TODO - Implementation
	BSTNode* node = map.root;
	while (node != NULL)
	{
		stack.push_back(node);
		node = node->left;
	}
	if (!map.isEmpty())
		iterator = stack.back(); //adica top (ia ultimul element de pe stack), cel mai mic
	else
		iterator = NULL;
}

//returnez primul element
//imi iau un vector auxiliar ca si stack si adaug copii din stanga ai arborelui, iar la sfarsit returnez ultimul nod adaugat (acela fiind primul nod)
//Best: Theta(1), cand am un singur copil in stanga ; Worst+Average: O(n), cand arborele e balansat si trebuie sa parcurg toata lungimea arborelui
void SMMIterator::first(){
	//TODO - Implementation
	if (map.root == NULL)
	{
		std::exception e;
//		throw e;
		return;
	}
	BSTNode* node = map.root;
	vector <BSTNode*> v;
	while (node != NULL)
	{
		v.push_back(node);
		node = node->left;
	}
	iterator = v.back();
	stack.clear();
	stack = v;
}

//Theta(1) pt toate cazurile fiindca scot doar un ultimul element din stack
void SMMIterator::next(){
	//TODO - Implementation
	if (valid())
	{
		//scot ultimul nod inserat in stack
		BSTNode* node = stack.back();
		stack.pop_back();
		if (node->right != NULL) //verific daca am copil in dreapta, acela fiind mai mare ca nodul curent
		{
			node = node->right;
			while (node != NULL)
			{
				stack.push_back(node);
				node = node->left;
			}
		}

		if (stack.size() > 0)
		{
			iterator = stack.back();
		}
		else
			iterator = NULL;
	}
	else
	{
		std::exception e;
		throw e;
	}
}

//Theta(1) in toate cazurile
//returneaza true daca e pe o pozitie valida deci am un nod, altfel false
bool SMMIterator::valid() const{
	//TODO - Implementation
	if (iterator == NULL)
		return false;
	return true;
}

//returneaza perechea (cheie, valoare) de unde se afla iteratorul
//Theta(1) in toate cazurile 
TElem SMMIterator::getCurrent() const{
	//TODO - Implementation
	if (valid()==true)
		return iterator->info;
	else
	{
		std::exception e;
		throw e;
	}
}


//calculez maximul din subarborele drept, deci merg tot in nodul din dreapta
// O(1) in best case, O(n) in worst si average fiindca trebuie sa parcurg arborele
void SMMIterator::end()
{
	if (map.root == NULL)
	{
		std::exception e;
		//		throw e;
		return;
	}
	BSTNode* node = map.root;
	vector <BSTNode*> v;
	while (node != NULL)
	{
		v.push_back(node);
		node = node->right;
	}
	iterator = v.back();
	stack.clear();
	stack = v;
}

//Theta(1) pt toate cazurile fiindca scot doar un ultimul element din stack
//asemanator cu next doar ca aici merg pe copilu din stanga
void SMMIterator::previous()
{
	if (valid())
	{
		//scot ultimul nod inserat in stack
		BSTNode* node = stack.back();
		stack.pop_back();
		if (node->right != NULL) //verific daca am copil in stanga
		{
			node = node->left;
			while (node != NULL)
			{
				stack.push_back(node);
				node = node->left;
			}
		}

		if (stack.size() > 0)
		{
			iterator = stack.back();
		}
		else
			iterator = NULL;
	}
}

//Nu am inteles cum as putea include relatia avand in vedere ca inserarea e fixa, iar la iterator ar fi trebuit sa fac cate o parcurgere separata pentru fiecare relatie.