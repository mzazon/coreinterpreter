//
//  executor.cpp
//  CSE3341
//
//  Created by Mike Zazon on 10/4/12.
//  Copyright (c) 2012 Mike Zazon. All rights reserved.
//

#include "executor.h"
#include <iostream>
#include <vector>


Executor::Executor()
{
    
}

void Executor::PROG()
{
	(*MyTree).second();
	STMT_SEQ();
	(*MyTree).root();
}

void Executor::STMT_SEQ()
{
	(*MyTree).first();
	STMT();
	(*MyTree).root();
    
	if((*MyTree).getAlt() == 2)
    {
		(*MyTree).second();
		STMT_SEQ();
		(*MyTree).root();
	}
}

void Executor::ID_LIST(bool isUsedFor)
{
	(*MyTree).first();
	std::string x = IDD();
    
	if(isUsedFor)
    {
		if((*inputTokens).Next())
        {
			setID(x, (*inputTokens).getv());
		}
        else
        {
			ThrowExecutorError("input error");
		}
	}
    else
    {
		if(!SYMBOL_INIT_FLAG(x))
		{
			ThrowExecutorError("symbol not init");
		}
		else
		{
			std::cout << get(x) << std::endl;
		}
	}
	(*MyTree).root();
	if((*MyTree).getAlt() == 2)
    {
		(*MyTree).second();
		ID_LIST(isUsedFor);
		(*MyTree).root();
	}

}
void Executor::STMT()
{
	int x = (*MyTree).getAlt();
	(*MyTree).first();
	switch (x)
    {
	case 1:
		ASSIGN();
		break;
	case 2:
		IFF();
		break;
	case 3:
		DOLOOP();
		break;
	case 4:
		INN();
		break;
	case 5:
		OUT();
		break;
	case 6:
		CASE_STMT();
		break;
	}
	(*MyTree).root();
}
void Executor::ASSIGN()
{
	(*MyTree).first();
	std::string ID = IDD();
	(*MyTree).root();
	(*MyTree).second();
	setID(ID, EXPR());
	(*MyTree).root();
}
void Executor::INN()
{
	(*MyTree).first();
	ID_LIST(true);
	(*MyTree).root();
}
void Executor::IFF()
{
	(*MyTree).first();
	if(COND())
    {
		(*MyTree).root();
		(*MyTree).second();
		STMT_SEQ();
		(*MyTree).root();
	}
    else
    {
		(*MyTree).root();
		if((*MyTree).getAlt() == 2)
        {
			(*MyTree).third();
			STMT_SEQ();
			(*MyTree).root();
		}
	}
}
void Executor::DOLOOP()
{

	(*MyTree).second();
    
	if(COND())
    {
		(*MyTree).root();
		(*MyTree).first();
		STMT_SEQ();
		(*MyTree).root();
		DOLOOP();
	}
	else
	{
		(*MyTree).root();
	}
}
bool Executor::COND()
{
	bool ret;
	bool temp;
	switch ((*MyTree).getAlt())
    {
	case 1:
		(*MyTree).first();
		ret = COMP();
		(*MyTree).root();
		break;
	case 2:
		(*MyTree).first();
		ret = !COND();
		(*MyTree).root();
		break;
	case 3:
		(*MyTree).first();
		temp = COND();
		(*MyTree).root();
		(*MyTree).second();
		ret = temp && COND();
		(*MyTree).root();
		break;
	case 4:
		(*MyTree).first();
		temp = COND();
		(*MyTree).root();
		(*MyTree).second();
		ret = temp || COND();
		(*MyTree).root();
		break;
	}
	return ret;
}
bool Executor::COMP()
{
	int x, y;
	bool ret;
	(*MyTree).first();
	x = FACTOR();
	(*MyTree).root();
	(*MyTree).third();
	y = FACTOR();
	(*MyTree).root();
	(*MyTree).second();
	switch ((*MyTree).getAlt()) {
	case 1:
		ret = x < y;
		break;
	case 2:
		ret = x == y;
		break;
	case 3:
		ret = x != y;
		break;
	case 4:
		ret = x > y;
		break;
	case 5:
		ret = x >= y;
		break;
	case 6:
		ret = x <= y;
		break;
	}
	(*MyTree).root();
	return ret;

}
TokenEnum Executor::COMP_OP()
{
	return (*MyTree).getType();
}
int Executor::EXPR()
{
	int x, y;
	(*MyTree).first();
	x = TERM();
	(*MyTree).root();
	if((*MyTree).getAlt() == 2) {
		(*MyTree).second();
		y = EXPR();
		(*MyTree).root();
		return x + y;
	} else if((*MyTree).getAlt() == 3) {
		(*MyTree).second();
		y = EXPR();
		(*MyTree).root();
		return x - y;
	}
	return x;
}

int Executor::TERM()
{
	int x, y;
	(*MyTree).first();
	x = FACTOR();
	(*MyTree).root();
	if((*MyTree).getAlt() == 2) {
		(*MyTree).second();
		y = TERM();
		(*MyTree).root();
		return x * y;
	}
	return x;
}
int Executor::FACTOR()
{
	int Alt = (*MyTree).getAlt();
	int ret;
	std::string x;
	(*MyTree).first();
	switch (Alt) {
	case 1:
		ret = CONST();
		break;
	case 2:
		x = IDD();
		if(SYMBOL_INIT_FLAG(x))
				{
		ret = get(x);
				}
		else
		{
			ThrowExecutorError("not initialized error");
		}
		break;
	case 3:
		ret = (-1)*FACTOR();
		break;
    case 4:
        ret = EXPR();
        break;
            
	}
	(*MyTree).root();
	return ret;
}
void Executor::CASE_STMT()
{
	(*MyTree).first();
	std::string ID = IDD();
	(*MyTree).root();
	(*MyTree).second();
	setID(ID, CASE_SEQ(ID));
	(*MyTree).root();
}
int Executor::CASE_SEQ(std::string ID)
{
	int ret=0;
    (*MyTree).first();
    if(get(ID) == CONST())
        ret = EXPR();
    
	return ret;
}

void Executor::CONST_LIST()
{
	(*MyTree).first();
	int x = CONST();
	(*MyTree).root();
	if((*MyTree).getAlt() == 2)
    {
		(*MyTree).second();
		CONST_LIST();
		(*MyTree).root();
	}
    //remove when done
    x=0;
}

void Executor::OUT()
{
	(*MyTree).first();
	ID_LIST(false);
	(*MyTree).root();
}
std::string Executor::IDD()
{
	return (*MyTree).getID();
}
int Executor::CONST()
{
	return (*MyTree).getConst();
}
void Executor::setID(std::string x, int value)
{
	for (int i = 0; i < (*MyTree).getNumSymbols(); i++)
    {
		if(x == (*MyTree).getSymbolList()[i].ID) {
			(*MyTree).getSymbolList()[i].value = value;
			(*MyTree).getSymbolList()[i].SYMBOL_INIT_FLAG = true;
		}
	}
}

int Executor::get(std::string x)
{
	for (int i = 0; i < (*MyTree).getNumSymbols(); i++)
    {
		if(x == (*MyTree).getSymbolList()[i].ID) {
			return (*MyTree).getSymbolList()[i].value;
		}
	}
    return 0;
}

bool Executor::SYMBOL_INIT_FLAG(std::string x)
{
	for (int i = 0; i < (*MyTree).getNumSymbols(); i++)
    {
		if(x == (*MyTree).getSymbolList()[i].ID)
        {
			if((*MyTree).getSymbolList()[i].SYMBOL_INIT_FLAG) return true;
			else return false;
		}
	}
	return false;
}

void Executor::start(ParseTree* tree, std::string inputFile)
{
    MyTree = tree;
	inputTokens = new Scanner(inputFile.c_str());
	PROG();
}

void Executor::ThrowExecutorError(std::string s)
{

    std::cout << "*** FATAL EXECUTOR ERROR: unexpected token or end of file.  Exiting to OS. ***" << std::endl;
    if(s != "")
    {
        std::cout << "*** More Information: " << s << std::endl;
    }
    exit(1);
}
