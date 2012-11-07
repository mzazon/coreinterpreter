//
//  executor.cpp
//  CSE3341
//
//  Created by Mike Zazon on 10/17/12.
//  Copyright (c) 2012 Mike Zazon. All rights reserved.
//

#include "executor.h"

Executor::Executor(ParseTree* tree, std::string inputfile)
{
    input = new Scanner(inputfile.c_str());
    this->tree = tree;
}

void Executor::Start()
{
    PROG();
}

void Executor::PROG()
{
    tree->CursorTo2();
    STMT_SEQ();
    tree->CursorToParent();
}

void Executor::STMT_SEQ()
{
    tree->CursorTo1();
    STMT();
    tree->CursorToParent();
    if(tree->getAlt() == 2)
    {
        tree->CursorTo2();
        STMT_SEQ();
        tree->CursorToParent();
    }
}

void Executor::ID_LIST(bool flag)
{
    tree->CursorTo1();
    std::string x = ID();
	if (flag) {
		if (input->Advance()) {
			setIDvalue(x, input->GetCurrentNum());
		} else {
			std::cout << "Error: unable to find input value in file."
            << std::endl;
			exit(0);
		}
	} else {
		if (!isInit(x))
		{
			std::cout << "Error: use of ID " << x
            << " before it is initialized" << std::endl;
		}
		else
		{
			std::cout << getIDvalue(x) << std::endl;
		}
	}
	tree->CursorToParent();
	if (tree->getAlt() == 2) {
		tree->CursorTo2();
		ID_LIST(flag);
		tree->CursorToParent();
	}
    
}
    
void Executor::STMT() {
	int x = tree->getAlt();
	tree->CursorTo1();
	switch (x) {
        case 1:
            ASSIGN();
            break;
        case 2:
            IF();
            break;
        case 3:
            LOOP();
            break;
        case 4:
            IN();
            break;
        case 5:
            OUT();
            break;
        //TODO: case 6:
           // CASE();
           // break;
	}
	tree->CursorToParent();
}

void Executor::ASSIGN() {
	tree->CursorTo1();
	std::string id = ID();
	tree->CursorToParent();
	tree->CursorTo2();
	setIDvalue(id, EXPR());
	tree->CursorToParent();
}

void Executor::IN() {
	tree->CursorTo1();
	ID_LIST(true);
	tree->CursorToParent();
}
void Executor::IF() {
	tree->CursorTo1();
	if (COND()) {
		tree->CursorToParent();
		tree->CursorToParent();
		STMT_SEQ();
		tree->CursorToParent();
	} else {
		tree->CursorToParent();
		if (tree->getAlt() == 2) {
			tree->CursorTo3();
			STMT_SEQ();
			tree->CursorToParent();
		}
	}
}
void Executor::LOOP() {
    
	tree->CursorTo2();
	if (COND()) {
		tree->CursorToParent();
		tree->CursorTo1();
		STMT_SEQ();
		tree->CursorToParent();
		LOOP();
	}
	else
	{
		tree->CursorToParent();
	}
}

bool Executor::COND() {
	bool flag;
	bool temp;
	switch (tree->getAlt()) {
        case 1:
            tree->CursorTo1();
            flag = COMP();
            tree->CursorToParent();
            break;
        case 2:
            tree->CursorTo1();
            flag = !COND();
            tree->CursorTo1();
            break;
        case 3:
            tree->CursorTo1();
            temp = COND();
            tree->CursorToParent();
            tree->CursorTo2();
            flag = temp && COND();
            tree->CursorToParent();
            break;
        case 4:
            tree->CursorTo1();
            temp = COND();
            tree->CursorToParent();
            tree->CursorTo2();
            flag = temp || COND();
            tree->CursorToParent();
            break;
	}
	return flag;
}

bool Executor::COMP() {
	int x, y;
	bool flag;
	tree->CursorTo1();
	x = FACTOR();
	tree->CursorToParent();
	tree->CursorTo3();
	y = FACTOR();
	tree->CursorToParent();
	tree->CursorTo2();
	switch (tree->getAlt()) {
        case 1:
            flag = x < y;
            break;
        case 2:
            flag = x == y;
            break;
        case 3:
            flag = x != y;
            break;
        case 4:
            flag = x > y;
            break;
        case 5:
            flag = x >= y;
            break;
        case 6:
            flag = x <= y;
            break;
	}
	tree->CursorToParent();
	return flag;
    
}

//TODO: need comparison operator execution
std::string Executor::COMP_OP()
{
    return tree->getValue();
}

int Executor::EXPR() {
	int x, y;
	tree->CursorTo1();
	x = TERM();
	tree->CursorToParent();
	if (tree->getAlt() == 2) {
		tree->CursorTo2();
		y = EXPR();
		tree->CursorToParent();
		return x + y;
	} else if (tree->getAlt() == 3) {
		tree->CursorTo2();
		y = EXPR();
		tree->CursorToParent();
		return x - y;
	}
	return x;
}

int Executor::TERM() {
	int x, y;
	tree->CursorTo1();
	x = FACTOR();
	tree->CursorToParent();
	if (tree->getAlt() == 2) {
		tree->CursorTo2();
		y = TERM();
		tree->CursorToParent();
		return x * y;
	}
	return x;
}

int Executor::FACTOR() {
	int a = tree->getAlt();
	int ret;
	std::string s;
	tree->CursorTo1();
	switch (a) {
        case 1:
            ret = CONST();
            break;
        case 2:
            s = ID();
            if(isInit(s))
            {
                ret = getIDvalue(s);
            }
            else
            {
                std::cout << "ERROR: attempt to use ID "<< s << " before it is initialized.";
                exit(0);
            }
            break;
        case 3:
            ret = EXPR();
            break;
	}
	tree->CursorToParent();
	return ret;
}
/*
void Executor::CASE() {
	tree->CursorTo1();
    //TODO: this might not work properly (dereferencing)
	std::string ID = this->ID();
	tree->CursorToParent();
	tree->CursorTo2();
	setIDvalue(ID, CASE_SEQ(ID));
	tree->CursorToParent();
} */
/*
int Executor::CASE_SEQ(std::string ID) {
	int ret;
	tree->CursorTo1();
	tree->CursorTo1();
	if (execLTGT(getIDvalue(ID))) {
		tree->MoveToParent();
		solution = execCase();
		tree->MoveToParent();
	} else {
		tree->MoveToParent();
		tree->MoveToParent();
		if (tree->getAlt() == 1) {
			tree->MoveToSecond();
			solution = execDefault();
		} else {
			tree->MoveToSecond();
			solution = execCase_Seq(ID);
		}
		tree->MoveToParent();
	}
	return solution;
}

int Executor::CASE_STMT() {
	tree->MoveToSecond();
	int x = execEXP();
	tree->MoveToParent();
	return x;
}
*/

void Executor::OUT() {
	tree->CursorTo1();
	ID_LIST(false);
	tree->CursorToParent();
}

std::string Executor::ID() {
	return tree->getValue();
}

int Executor::CONST() {
	return atoi(tree->getValue().c_str());
}

void Executor::setIDvalue(std::string s, int value) {
	for (int i = 0; i < tree->SymbolTableSize(); i++) {
		if (s == tree->GetSymbol(i)) {
			//TODO: need to fill the ID values in asap
		}
	}
}

int Executor::getIDvalue(std::string s) {
	for (int i = 0; i < tree->SymbolTableSize(); i++) {
		if (s == tree->GetSymbol(i)) {
			return atoi(tree->GetSymbol(i).c_str());
		}
	}
    return 99;
}

bool Executor::isInit(std::string s) {
	for (int i = 0; i < tree->SymbolTableSize(); i++) {
		if (s == tree->GetSymbol(i)) {
			if (true)
				return true;
			else
				return false;
		}
	}
	return false;
}