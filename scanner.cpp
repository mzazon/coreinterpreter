//
//  scanner.cpp
//  CSE3341
//
//  Created by Mike Zazon on 10/4/12.
//  Copyright (c) 2012 Mike Zazon. All rights reserved.
//

#include "scanner.h"
#include "tokenizer.h"
#include <iostream>

Scanner::Scanner(std::string filename) {
    tokens.Tokenize(filename.c_str());
}

bool Scanner::Advance() {
    if(tokens.Advance())
    {
        current = tokens.Get();
        MyToken.string = current;
        MyToken.token = Match(current);
        
        if(MyToken.token == CONST)
        {
            MyToken.value = atoi(current.c_str());
        }
        
        return true;
    }
    else
    {
        return false;
    }
}

//This function performs lookups and matches from plain text to the Token Enumeration
TokenEnum Scanner::Match(std::string s)
{
	if(s == "program") return PROGRAM;
	else if(s == "begin") return BEGIN;
    else if(s == "|") return BAR;
	else if(s == "end") return END;
	else if(s == "int") return INT;
	else if(s == ";") return SEMI_COLON;
	else if(s == ",") return COMMA;
	else if(s == ":=") return ASSIGNMENT;
	else if(s == "input") return INPUT;
	else if(s == "if") return IF;
    else if(s == "do") return DO;
	else if(s == "then") return THEN;
	else if(s == "else") return ELSE;
	else if(s == "endif") return ENDIF;
	else if(s == "do") return DO;
	else if(s == "while") return WHILE;
    else if(s == "enddo") return ENDDO;
	else if(s == "AND") return AND;
	else if(s == "OR") return OR;
	else if(s == "!") return NOT;
	else if(s == "<") return LESS_THAN;
	else if(s == ">") return GREATER_THAN;
	else if(s == "=") return EQUAL;
	else if(s == "<=") return LESS_THAN_OR_EQUAL;
	else if(s == ">=") return GREATER_THAN_OR_EQUAL;
	else if(s == "!=") return NOT_EQUAL;
	else if(s == "(") return LEFT_PAREN;
	else if(s == "[") return LEFT_BRACKET;
	else if(s == ")") return RIGHT_PAREN;
	else if(s == "]") return RIGHT_BRACKET;
	else if(s == "+") return PLUS;
	else if(s == "-") return MINUS;
	else if(s == "*") return MULTIPLY;
	else if(s == "output") return OUTPUT;
	else if(s == "case") return CASE;
	else if(s == ":") return COLON;
	else
    {
        //the first character determines what this token is
		if(isNum(s[0]))
        {
			return CONST;
		}
        else
        {
			return ID;
		}
	}
}

Token Scanner::get()
{
    return MyToken;
}

bool Scanner::isNum(char c)
{
	if(c >= '0' && c <= '9')
    {
		return true;
	}
	return false;
}
int Scanner::getLine()
{
    return line;
}
int Scanner::getv()
{
    return CurrentValue;
}
bool Scanner::Next()
{
	if(!Advance())
		return false;
    
	if(MyToken.token == CONST)
    {
		CurrentValue = MyToken.value;
	}
    else if(MyToken.token == MINUS)
    {
		if(!Advance())
			return false;
        
		if(MyToken.token == CONST)
        {
			CurrentValue = -1 * MyToken.value;
		}
        else
        {
            std::cout << "*** INPUT FILE ERROR ***\n"; exit(0);
		}
	}
    else
    {
		std::cout << "*** INPUT FILE ERROR ***\n"; exit(0);
	}
	return true;
}

