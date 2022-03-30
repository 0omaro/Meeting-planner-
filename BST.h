#include<string>

class BST{
public:
	BST();
	void insert(const std::string &word,const int & day,const int & time);
	void Find(std::string & word, const int & date,const int & time);
	void MOD(const std::string &word,const int & day,const int & time);
	void changeTree(BST * oldTree ,BST * newTree,int & date, int & time ,bool &hit);
	void DeleteTree(BST * bt);
	void Print(BST * myTree, int &first);
	bool isEmpty();
	bool getData(std::string &word, int & date, int & time);
	BST * left();
	BST * right();
	void makeLeft(BST * LP);
	void makeRight(BST * RP);
private:
	bool emptyTree;
	std::string title;
	int day;
	int hour;
	BST * lTree;
	BST * rTree;
};

