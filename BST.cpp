#include<iostream>
#include<string>
#include <assert.h>
#include"BST.h"
BST::BST(){
	emptyTree = true;
		lTree = NULL;
		rTree = NULL;
		title = "";
		day = -1;
		hour = -1;
}


void BST::insert(const std::string &word,const int & date,const int & time){
	if(emptyTree){
		emptyTree = false;
		title = word;
		day = date;
		hour = time;
		lTree = new BST;
		rTree = new BST;
	}
	else if(date < day)
		lTree->insert(word,date,time);
	else if(date > day)
		rTree->insert(word,date,time);
	else
		if(time < hour)
			lTree->insert(word,date,time);
		else if(time > hour)
			rTree->insert(word,date,time);
		else
			std::cout<<"Conflict "<<date<<" "<<time<<std::endl;
}

void BST::Find(std::string & word, const int & date,const int & time){
	if(emptyTree){
		std::cout<<"Empty "<<date<<" "<<time<<std::endl;
		word = "";
	}
	else if(date < day)
		lTree->Find(word,date,time);
	else if(date > day)
		rTree->Find(word,date,time);
	else
		if(time < hour)
			lTree->Find(word,date,time);
		else if(time > hour)
			rTree->Find(word,date,time);
		else{
			word = title;
		}
}

void BST::MOD(const std::string & word, const int & date,const int & time){
	if(emptyTree){
		std::cout<<"Empty "<<date<<" "<<time<<std::endl;
	}
	else if(date < day)
		lTree->MOD(word,date,time);
	else if(date > day)
		rTree->MOD(word,date,time);
	else
		if(time < hour)
			lTree->MOD(word,date,time);
		else if(time > hour)
			rTree->MOD(word,date,time);
		else{
			title = word;
		}
}

void BST::changeTree(BST * oldTree ,BST * newTree,int & date, int & time ,bool &hit){
	if(!oldTree->emptyTree){
		if(date == oldTree->day && time == oldTree->hour){
			hit = true;
		}
		else{
			newTree->insert(oldTree->title,oldTree->day,oldTree->hour);
		}
		changeTree(oldTree->left(),newTree,date,time,hit);
		changeTree(oldTree->right(),newTree,date,time,hit);
	}

}
void BST::DeleteTree(BST * bt){
	if(!bt->emptyTree){
		DeleteTree(bt->left());
		delete bt->left();
		DeleteTree(bt->right());
		delete bt->right();
	}
}

void BST::Print(BST * t1,int &first){
	if(!t1->isEmpty()){
		first =1;
		Print(t1->left(),first);
		std::cout<<t1->title<<" "<<t1->day<<" "<<t1->hour<<std::endl;
		Print(t1->right(),first);

	}
	else{
		if(first == 0){
			std::cout<< "Empty Planner"<<std::endl;
			first = 1;
		}
	}
}
bool BST::isEmpty(){
	return emptyTree;
}
bool BST::getData(std::string &word, int & date, int & time){
	if(!emptyTree){
		word = title;
		date = day;
		time = hour;
		return true;
	}
	else
		return false;
}

BST * BST::left(){
	assert(!emptyTree);
	return lTree;
}

BST * BST::right(){
	assert(!emptyTree);
	return rTree;
}

void BST::makeRight(BST * rP){
	assert(!emptyTree);
	assert(right()->emptyTree);
	delete right();
	rTree = rP;
}

void BST::makeLeft(BST * lP){
	assert(!emptyTree);
	assert(left()->emptyTree);
	delete left();
	rTree = lP;
}


