#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

//constructor
//Thetea(1) in toate cazurile
SortedMultiMap::SortedMultiMap(Relation r) {
	//TODO - Implementation
	root = NULL;
	relatie = r;
	count = 0;
}

//initializez un nod cu o pereche de tip (cheie, valoare), iar copii null 
//Theta(1) in toate cazurile
BSTNode* SortedMultiMap::initNode(TKey c, TValue v)
{
	TElem elem = pair<TKey, TValue>(c, v);
	BSTNode* node = new BSTNode;
	node->info = elem;
	node->left = NULL;
	node->right = NULL;
	return node;
}

//inserarea raportata la un nod
BSTNode* SortedMultiMap::insert(BSTNode* node, TKey c, TValue v)
{
	if (node == NULL) //cand arborele e gol, deci setez radacina
		node = initNode(c, v);
	//caut pozitia pentru inserat dupa valoare
	else if (node->info.first > c) 
		node->left = insert(node->left, c, v);
	//in cazul in care am noduri duplicate, le pun in copilul stang
	else if (node->info.first == c)
	{
		if (node->info.second)
		node->left = initNode(c, v);
		return node;
	}
	else if (node->info.first < c)
		node->right = insert(node->right, c, v);

	return node;
}

//ma folosesc de implementarea recursiva -> complexitatea lui add depinde de insert
//Best case: Theta(1)-cand arborele e gol, Worst, Average: O(n)
void SortedMultiMap::add(TKey c, TValue v) {
	//TODO - Implementation
	if (root == NULL)
		root = insert(root, c, v);
	else
		BSTNode* n = insert(root, c, v);
	count++;
}

//avand in vedere ca o cheie poate sa existe de mai multe ori, trebuie sa parcurg tot arborele -> complexitate O(n) in toate cazurile
vector<TValue> SortedMultiMap::search(TKey c) const {
	//TODO - Implementation
	vector <TValue> found; //vector de tip TValue pentru valorile cu aceeasi cheie
	BSTNode* current = root;
	while (current != NULL )
	{
		if (current->info.first == c)
		{
			found.push_back(current->info.second);
		}
		if (current->info.first < c)
			current = current->right;
		else
			current = current->left;
	}
	return found;
}

//returnez nodul minim dintr-un subarbore
//O(n) pe toate cazurile 
BSTNode* SortedMultiMap::minimum(BSTNode* node)
{
	BSTNode* current = node;
	if (current == NULL) //daca arborele e gol
		return NULL;
	else
		while (current->left != NULL)
			current = current->left;
	return current;
}

//stergerea recursiva a unui nod intr-un subarbore
//la remove am o problema cred ca din cauza ca inserez noduri cu aceeasi cheie si nu am putut sa o rezolv
BSTNode* SortedMultiMap::removeRec(BSTNode*& node, TKey c, TValue v)
{
	bool ok = false;
	vector<TValue> s = search(c);
	for (int i = 0; i < s.size(); i++)
		if (s[i] == v)
			ok = true;
	if (node == NULL || ok==false)
		return NULL;
	//prima data caut nodul pe care trebuie sa il sterg
	else if (node->info.first > c)
	{
		node->left = removeRec(node->left, c, v);
	}
	else if (node->info.first < c)
	{
		node->right = removeRec(node->right, c, v);
	}
	else if (node->info.first == c && node->info.second == v)//cand node->info.first = c, deci elimin nodul
	{
		BSTNode* temp = node;
		if (node->left == NULL && node->right == NULL) //nu are niciun copil
		{
			delete node;
			node = NULL;
			return temp;
		}
		else if (node->left == NULL) //daca are doar un copil in dreapta
		{
			node = node->right;
			delete temp;
//			temp = NULL;
		}
		else if (node->right == NULL) //daca are doar un copil in stanga
		{
			node = node->left;
			delete temp;
//			temp = NULL;
		}
		else //daca are 2 copii
		{
			BSTNode* min = minimum(node->right);
			node->info = min->info;
			node->right = removeRec(node->right, min->info.first, min->info.second);
		}
	}
	return node;
	
	//daca nodul cautat nu exista in arbore
//	return NULL;
}

//complexitatea depinde de functia recursiva removeRec, iar removeRec depinde de functia care gaseste minimul din subarborele drept
//Best:O(n), Average+Worst : O(n^2) in cazul in care trebuie sa inlocuiesc elementul pe care il sterg cu minimul, deci am 2 parcurgeri ale arborelui
bool SortedMultiMap::remove(TKey c, TValue v) {
	//TODO - Implementation
	if (removeRec(root, c, v) == NULL)
	{
		return false;
	}
	count--;
	return true;
}

//Returnez numarul de noduri din arbore (cand inserez sau sterg, modific count-ul)
//Theta(1) in toate cazurile
int SortedMultiMap::size() const {
	//TODO - Implementation
	return count;
}

//verific daca arborele e gol (ar mai fi fost si varianta in care sa verific daca radacina e nula)
//Theta(1) in toate cazurile
bool SortedMultiMap::isEmpty() const {
	//TODO - Implementation
	if (count == 0)
		return true;
	return false;
}

//creeaza o instanta pentru iterator
//Theta(1)
SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

//destructorul : Theta(1) in toate cazurile
//prin faptul ca setez radacina pe NULL, inseamna ca nu mai am legaturi catre celelalte noduri
SortedMultiMap::~SortedMultiMap() {
	//TODO - Implementation
	root = NULL;
}


/*
//functia suplimentara
//O(n) in toate cazurile fiindca parcurg tot arborele
pair<TKey, int>* SortedMultiMap::bag_Schlussel()
{
	//array de perechi de tipul <cheie, valoare> pe care il initializez cu valori nule
	pair<TKey,int>* bag = new pair<TKey, int>;
	for (int i = 0; i < 3; i++)
	{
		bag[i].first = 0;
		bag[i].second = 0;
	}

	BSTNode* node = root;
	int i = 0;

	while (node != NULL)
	{
		if (bag[i].first == 0) //adaug in bag un element care nu mai apare si setez frecventa 1
		{
			i++;
			bag[i].first = node->info.first;
			bag[i].second = 1;
		}
		else //inseamna ca cheia exista asa ca actualizez doar frecventa
			bag[i].second++;

		if (node != NULL)
			node = node->left;
		else
			node = node->right;
	}
	return bag;
}*/