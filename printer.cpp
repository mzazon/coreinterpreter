//
//  printer.cpp
//  CSE3341
//
//  Created by Mike Zazon on 10/4/12.
//  Copyright (c) 2012 Mike Zazon. All rights reserved.
//

#include "printer.h"
#include <iostream>

Printer::Printer()
{

}

void Printer::start(ParseTree* t)
{
    MyTree = t;
    numSpaces=0;
	PROG();
}


void Printer::IDD()
{
	std::cout << (*MyTree).getID();
}
void Printer::CONST()
{
	std::cout << (*MyTree).getConst();
}

void Printer::PRINT_WHITE_SPACE()
{
	for (int i = 1; i <= numSpaces; i++)
    {
		std::cout << " ";
	}
}

void Printer::PROG()
{
	std::cout << "program" << std::endl;
	INCREASE_INDENT();
    
	(*MyTree).first();
	DECL_SEQ();
	(*MyTree).root();
	DECREASE_INDENT();
    
	std::cout << "begin" << std::endl;
	INCREASE_INDENT();
	(*MyTree).second();
	STMT_SEQ();
    
	(*MyTree).root();
	DECREASE_INDENT();
    
	std::cout << "end" << std::endl;

}
void Printer::DECL_SEQ()
{
	(*MyTree).first();
	DECL();
	(*MyTree).root();
	if((*MyTree).getAlt() == 2)
	{
		(*MyTree).second();
		DECL_SEQ();
		(*MyTree).root();
	}
}
void Printer::STMT_SEQ()
{
	(*MyTree).first();
	STMT();
	(*MyTree).root();
	if((*MyTree).getAlt() == 2){
		(*MyTree).second();
		STMT_SEQ();
		(*MyTree).root();
	}
}

void Printer::DECL()
{
	PRINT_WHITE_SPACE();
	std::cout << "int ";
	(*MyTree).first();
	ID_LIST();
	(*MyTree).root();
	std::cout << ";" << std::endl;
}

void Printer::ID_LIST()
{
	(*MyTree).first();
	IDD();
	(*MyTree).root();
	if((*MyTree).getAlt() == 2)
    {
		std::cout << ",";
		(*MyTree).second();
		ID_LIST();
		(*MyTree).root();
	}

}

void Printer::STMT()
{
	switch ((*MyTree).getAlt())
    {
	case 1:
		(*MyTree).first();
		ASSIGN();
		(*MyTree).root();
		break;
	case 2:
		(*MyTree).first();
		IFF();
		(*MyTree).root();
		break;
	case 3:
		(*MyTree).first();
		DOLOOP();
		(*MyTree).root();
		break;
	case 4:
		(*MyTree).first();
		INN();
		(*MyTree).root();
		break;
	case 5:
		(*MyTree).first();
		OUT();
		(*MyTree).root();
		break;
	case 6:
		(*MyTree).first();
		CASE_STMT();
		(*MyTree).root();
		break;
	}
}

void Printer::ASSIGN()
{
	PRINT_WHITE_SPACE();
	(*MyTree).first();
	IDD();
	(*MyTree).root();
	std::cout << ":=";
	(*MyTree).second();
	EXPR();
	(*MyTree).root();
	std::cout << ";" << std::endl;
}

void Printer::INN()
{
	PRINT_WHITE_SPACE();
	std::cout << "input ";
	(*MyTree).first();
	ID_LIST();
	(*MyTree).root();
	std::cout << ";" << std::endl;
}

void Printer::IFF()
{
	PRINT_WHITE_SPACE();
	std::cout << "if";
	(*MyTree).first();
	COND();
	(*MyTree).root();
	std::cout << "then" << std::endl;
	INCREASE_INDENT();
	(*MyTree).second();
	STMT_SEQ();
	(*MyTree).root();
	DECREASE_INDENT();
	if((*MyTree).getAlt() == 2)
    {
		PRINT_WHITE_SPACE();
		std::cout << "else" << std::endl;
		INCREASE_INDENT();
		(*MyTree).third();
		STMT_SEQ();
		(*MyTree).root();
		DECREASE_INDENT();
	}
	PRINT_WHITE_SPACE();
	std::cout << "endif;" << std::endl;
}

void Printer::INCREASE_INDENT()
{
    numSpaces++;
    numSpaces++;
}
void Printer::DECREASE_INDENT()
{
    numSpaces--;
    numSpaces--;
}

void Printer::DOLOOP()
{
	PRINT_WHITE_SPACE();
	std::cout << "do" << std::endl;
	INCREASE_INDENT();
	(*MyTree).first();
	STMT_SEQ();
	(*MyTree).root();
	DECREASE_INDENT();
	PRINT_WHITE_SPACE();
	std::cout << "while";
	(*MyTree).second();
	COND();
	(*MyTree).root();
	std::cout << "enddo;" << std::endl;
}

void Printer::COND()
{
	switch ((*MyTree).getAlt())
    {
	case 1:
		(*MyTree).first();
		COMP();
		(*MyTree).root();
		break;
	case 2:
		std::cout << "!";
		(*MyTree).first();
		COND();
		(*MyTree).root();
		break;
	case 3:
		std::cout << "(";
		(*MyTree).first();
		COND();
		(*MyTree).root();
		std::cout << "AND";
		(*MyTree).second();
		COND();
		(*MyTree).root();
		std::cout << ")";
		break;
	case 4:
		std::cout << "(";
		(*MyTree).first();
		COND();
		(*MyTree).root();
		std::cout << "OR";
		(*MyTree).second();
		COND();
		(*MyTree).root();
		std::cout << ")";
		break;
	}
}

void Printer::COMP()
{
	std::cout << "[";
	(*MyTree).first();
	FACTOR();
	(*MyTree).root();
	(*MyTree).second();
	COMP_OP();
	(*MyTree).root();
	(*MyTree).third();
	FACTOR();
	(*MyTree).root();
	std::cout << "]";
}

void Printer::COMP_OP()
{
	switch ((*MyTree).getAlt())
    {
	case 1:
		std::cout << "<";
		break;
	case 2:
		std::cout << "=";
		break;
	case 3:
		std::cout << "!=";
		break;
	case 4:
		std::cout << ">";
		break;
	case 5:
		std::cout << ">=";
		break;
	case 6:
		std::cout << "<=";
		break;
	}
}

void Printer::EXPR()
{
	(*MyTree).first();
	TERM();
	(*MyTree).root();
	if((*MyTree).getAlt() == 2)
    {
		std::cout << "+";
		(*MyTree).second();
		EXPR();
		(*MyTree).root();
	}
	else if((*MyTree).getAlt() == 3)
    {
		std::cout << "-";
		(*MyTree).second();
		EXPR();
		(*MyTree).root();
	}
}
void Printer::TERM()
{
	(*MyTree).first();
	FACTOR();
	(*MyTree).root();
	if((*MyTree).getAlt() == 2){
		std::cout << "*";
		(*MyTree).second();
		TERM();
		(*MyTree).root();
	}
}

void Printer::FACTOR()
{
	switch((*MyTree).getAlt()){
	case 1:
		(*MyTree).first();
		CONST();
		(*MyTree).root();
		break;
	case 2:
		(*MyTree).first();
		IDD();
		(*MyTree).root();
		break;
	case 3:
        std::cout << "-";
        (*MyTree).first();
        FACTOR();
        (*MyTree).root();
        break;
    case 4:
        std::cout << "(";
        (*MyTree).first();
        EXPR();
        (*MyTree).root();
        std::cout << ")";
        break;
	}
}

void Printer::CASE_STMT()
{
	PRINT_WHITE_SPACE();
	std::cout << "case ";
	(*MyTree).first();
	IDD();
	(*MyTree).root();
    std::cout << " of ";
	std::cout << std::endl;
	INCREASE_INDENT();
	(*MyTree).second();
	CASE_SEQ();
	(*MyTree).root();
	DECREASE_INDENT();
}

void Printer::CONST_LIST()
{
    (*MyTree).first();
    CONST();
    (*MyTree).root();
    if((*MyTree).getAlt() == 2)
    {
        std::cout << ",";
        (*MyTree).second();
        CONST_LIST();
        (*MyTree).root();
    }
}

void Printer::CASE_SEQ()
{
	(*MyTree).first();
	(*MyTree).root();
    
	if((*MyTree).getAlt() == 2)
    {
		(*MyTree).second();
		CASE_SEQ();
		(*MyTree).root();
	}
	else
    {
		(*MyTree).second();
		(*MyTree).root();
	}
}

void Printer::OUT()
{
	PRINT_WHITE_SPACE();
	std::cout << "output ";
	(*MyTree).first();
	ID_LIST();
	(*MyTree).root();
	std::cout << ";" << std::endl;
}

