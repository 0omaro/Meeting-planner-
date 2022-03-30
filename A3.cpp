#include<iostream>
#include<string.h>
#include <stdio.h>
#include<fstream>
#include<bits/stdc++.h>
#include"BST.h"
using namespace std;

void checkLine(string txt,string * arg0);
bool checkTitle(string txt, string & word);
bool checkDay(string day,int &date);
bool checkHour(string hour,int &time);
int main(int argc,char** argv){
	if (argc != 2)
		cout<<"Invalid arguments"<<endl;
	else{
		BST * newTree = NULL;
		BST * swapTree = NULL;
		bool flag0 = false;
		bool flag1 = false;
		bool flag2 = false;
		bool flag3 = false;
		int date=-1;
		int time=-1;
		int printstate= 0;
		BST * myTree = new BST;
		string word="";
		string commandfile;
		string commandarg[100] = {""};
		string cwd ="./";
		commandfile = argv[1];
		commandfile = cwd +commandfile;
		string line;
		ifstream file1 (commandfile);
		if(file1.is_open())
		{
		while (getline(file1,line)){
			line.erase(remove(line.begin(), line.end(), '\r'), line.end());
			for(int z = 0 ;z <99;z++)
				commandarg[z] = "";
			checkLine(line,commandarg);
			if (commandarg[0] != ""){
				if (commandarg[0].compare("ADD") == 0){
					if(commandarg[4] == "" && commandarg[3] != ""){
						flag1 = checkTitle(commandarg[1],word);
						flag2 = checkDay(commandarg[2],date);
						flag3 = checkHour(commandarg[3],time);
						if(flag1 && flag2 && flag3){
							myTree->insert(word,date,time);
						}
					}
					else
						cout<<"Invalid arguments"<<endl;
				}
				else if (commandarg[0].compare("Find") == 0){
					if(commandarg[3] == ""&& commandarg[2] != ""){
						flag1 = checkDay(commandarg[1],date);
						flag2 = checkHour(commandarg[2],time);
						if(flag1 && flag2){
							myTree->Find(word,date,time);
							if (word != "")
								cout<<word<<endl;
						}
					}
					else
						cout<<"Invalid arguments"<<endl;
				}
				else if (commandarg[0].compare("MOD") == 0){
					if(commandarg[4] == ""&& commandarg[3] != ""){
						flag1 = checkTitle(commandarg[1],word);
						flag2 = checkDay(commandarg[2],date);
						flag3 = checkHour(commandarg[3],time);
						if(flag1 && flag2 && flag3){
							myTree->MOD(word,date,time);
						}
					}
					else
						cout<<"Invalid arguments"<<endl;
				}
				else if (commandarg[0].compare("DEL") == 0){
					if(commandarg[3] == ""&& commandarg[2] != ""){
						flag1 = checkDay(commandarg[1],date);
						flag2 = checkHour(commandarg[2],time);
						if(flag1 && flag2){
							newTree = new BST;
							myTree->changeTree(myTree,newTree,date,time,flag0);
							if (flag0){
								swapTree = myTree;
								myTree = newTree;
								newTree = swapTree;
								newTree->DeleteTree(newTree);
								delete newTree;
								swapTree = NULL;
								flag0= false;
							}
							else{
								newTree->DeleteTree(newTree);
								delete newTree;
								cout<<"Empty "<<date<<" "<<time<<endl;
							}
							date = time = -1;
						}
					}
					else
						cout<<"Invalid arguments"<<endl;
				}
				else if (commandarg[0].compare("Print") == 0){
					if(commandarg[1] == "" && commandarg[4] == ""){
						myTree->Print(myTree,printstate);
						printstate =0;
					}
					else
						cout<<"Invalid arguments"<<endl;
				}
				else{
					cout<<"Invalid command"<<endl;
				}
			}
			word = "";
			date = -1;
			time = -1;
		}
		}
		else
		{cout<<"File not Found"<<endl;}

		myTree->DeleteTree(myTree);
		delete myTree;
	}
}

void checkLine(string txt,string * arg){
	int i=0;
	int z=0;
	int coma = 0;
	int titleplace = 0;
	int dayplace = 0;
	int timeplace = 0;
	int moreargplace = 0;
	int comaplace[2] = {0};
	string word = "";
	for (auto x : txt){
		if(coma == 0 && x == '\"'){
			comaplace[0]=i;
			coma++;
		}
		else if (coma >= 1 && x == '\"'){
			comaplace[1]=i;
			coma++;
		}
		i++;
	}
	for(int j = comaplace[1]+1;j<txt.length();j++)
		if(txt[j] == '\t')
			txt.insert(j+1, " ");
	i = 0;
	coma = 0;
	comaplace[0]=comaplace[1]=0;
	for (auto x : txt){
		if (x == ' '){
			arg[i]=word;
			i++;
			word = "";
		}
		else {
		word = word + x;
		}
	}
	arg[i]=word;
	word ="";
	i++;
	for(int j = 1;j<=i;j++){
		if(arg[j].find('\"') != string::npos){
			if(coma == 0){
				comaplace[0]=j;
				coma++;
			}
			else if (coma >= 1){
				comaplace[1]=j;
				coma++;
			}
		}
	}
	if(coma >=2 && comaplace [0] == 1){
		for(int j = 2;j <= comaplace[1];j++){
			arg[1] = arg[1] +" "+ arg[j];
		}
	}
	if(coma == 1 && comaplace[0] > 1){
		for(int j = 1 ;j <i; j++)
			if(arg[j] != ""){
				arg[z+1] = arg[j];
				z++;
			}
	}
	if(coma == 0){
		for (int j = coma+1; j <= i;j++){
			if(titleplace ==0 && arg [j] != "" && arg[j] != "\t")
				titleplace = j;
			else if(dayplace ==0 && arg [j] != "" && arg[j] != "\t")
				dayplace = j;
			else if (timeplace == 0 && arg[j] != "" && arg[j] != "\t")
				timeplace = j;
			else if (moreargplace == 0 && arg[j] != "" && arg[j] != "\t")
				moreargplace = j;
		}
		if (titleplace != 0 )
			arg[1] = arg[titleplace];
		else
			arg[1] = "";
		if (dayplace != 0 )
			arg[2] = arg[dayplace];
		else
			arg[2] = "";
		if (timeplace != 0)
			arg[3] = arg[timeplace];
		else
			arg[3] = "";
		if (moreargplace != 0)
			arg[4] = arg[moreargplace];
		else
			arg[4] = "";
	}
	if(coma == 1 ){
		for (int j = coma+1; j <= i;j++){
			if(dayplace ==0 && arg [j] != "" && arg[j] != "\t")
				dayplace = j;
			else if (timeplace == 0 && arg[j] != "" && arg[j] != "\t")
				timeplace = j;
			else if (moreargplace == 0 && arg[j] != "" && arg[j] != "\t")
				moreargplace = j;
		}
		if (dayplace != 0 )
			arg[2] = arg[dayplace];
		else
			arg[2] = "";
		if (timeplace != 0)
			arg[3] = arg[timeplace];
		else
			arg[3] = "";
		if (moreargplace != 0)
			arg[4] = arg[moreargplace];
		else
			arg[4] = "";
	}
	if (coma > 1){
		for (int j = comaplace[1]+1; j <= i;j++){
			if(dayplace ==0 && arg [j] != "" && arg[j] != "\t")
				dayplace = j;
			else if (timeplace == 0 && arg[j] != "" && arg[j] != "\t")
				timeplace = j;
			else if (moreargplace == 0 && arg[j] != "" && arg[j] != "\t")
				moreargplace = j;
		}

		if (dayplace != 0 )
			arg[2] = arg[dayplace];
		else
			arg[2] = "";
		if (timeplace != 0)
			arg[3] = arg[timeplace];
		else
			arg[3] = "";
		if (moreargplace != 0)
			arg[4] = arg[moreargplace];
		else
			arg[4] = "";
	}
	if(arg[0] == "Print"){
		for(int j = 1; j <=i;j++){
			if (moreargplace == 0 && arg[j] != "" && arg[j] != "\t")
				moreargplace = j;
		}
		if (moreargplace != 0)
			arg[4] = arg[moreargplace];
		else
			arg[4] = "";
	}
}


bool checkTitle(string txt, string &word){
	if(txt[txt.length()-1] == '\t')
		txt.erase (txt.end()-1);
	if(txt[0] == '\"' && txt[txt.length()-1] == '\"' && txt.length() != 1){
		word = txt;
		return true;
	}
	else{
		cout<<"Invalid title"<<endl;
		return false;
	}
}

bool checkDay(string day,int &date){
	day.erase(remove(day.begin(), day.end(), '\t'), day.end());
	for(unsigned int i =0 ; i < day.length() ; i++){
		if(isdigit(day[i]));
		else{
			cout<<"Invalid day"<<endl;
			return false;
		}
	}
	date = stoi(day);
	if (date <=0 || date >365){
		cout<<"Invalid day"<<endl;
		return false;
	}
	else
		return true;
}

bool checkHour(string hour,int &time){
	hour.erase(remove(hour.begin(), hour.end(), '\t'), hour.end());
	hour.erase(remove(hour.begin(), hour.end(), '\r'), hour.end());
	for(unsigned int i =0 ; i < hour.length() ; i++){
		if(isdigit(hour[i]));
		else{
			cout<<"Invalid hour"<<endl;
			return false;
		}
	}
	time = stoi(hour);
	if (time <0 || time >23){
		cout<<"Invalid hour"<<endl;
		return false;
	}
	else
		return true;

}
