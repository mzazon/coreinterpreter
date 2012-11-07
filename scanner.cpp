//
//  scanner.cpp
//  CSE3341
//
//  Created by Mike Zazon on 10/4/12.
//  Copyright (c) 2012 Mike Zazon. All rights reserved.
//

#include "scanner.h"

Scanner::Scanner()
{

    
}

Scanner::Scanner(const std::string filename)
{
    tokens.Tokenize(filename);
    current = tokens.Get();
}

std::string Scanner::GetCurrent()
{
    return current;
}

int Scanner::GetCurrentNum()
{
    return atoi(current.c_str());
}

bool Scanner::Advance()
{
    current = tokens.Get();
    return true;
}

std::string Scanner::PeekAhead()
{
    return tokens.PeekAhead();
}

bool Scanner::CurrentIsID()
{
    if(current == "program") return false;
    if(current == "begin") return false;
    if(current == "end") return false;
    if(current == "int") return false;
    if(current == ";") return false;
    if(current == ",") return false;
    if(current == ":=") return false;
    if(current == "input") return false;
    if(current == "output") return false;
    if(current == "if") return false;
    if(current == "then") return false;
    if(current == "endif") return false;
    if(current == "else") return false;
    if(current == "while") return false;
    if(current == "begin") return false;
    if(current == "endwhile") return false;
    if(current == "!") return false;
    if(current == "AND") return false;
    if(current == "(") return false;
    if(current == ")") return false;
    if(current == "OR") return false;
    if(current == "[") return false;
    if(current == "]") return false;
    if(current == "<") return false;
    if(current == "=") return false;
    if(current == "!=") return false;
    if(current == ">") return false;
    if(current == ">=") return false;
    if(current == "<=") return false;
    if(current == "+") return false;
    if(current == "|") return false;
    if(current == "-") return false;
    if(current == "*") return false;
    if(current == "eof") return false;
    if((current.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") != std::string::npos))
    {

        return false;
    }
    return true;
}

bool Scanner::CurrentIsCONST()
{
    if(current.find_first_not_of("0123456789") != std::string::npos)
    {
        return false;
    }
    
    return true;
}