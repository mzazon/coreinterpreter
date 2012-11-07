//
//  tokenizer.h
//  CSE3341
//
//  Created by Mike Zazon on 10/4/12.
//  Copyright (c) 2012 Mike Zazon. All rights reserved.
//

#ifndef __CSE3341__tokenizer__
#define __CSE3341__tokenizer__

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

//enumeration class for all possible tokens in the Core language
enum TokenEnum
{
    PROGRAM,BAR,BEGIN,END,INT,ID,COMMA,ASSIGNMENT,INPUT,IF,OF,THEN,ENDIF,ELSE,DO,WHILE,ENDDO,NOT,AND,OR,LEFT_PAREN,
    RIGHT_PAREN,LEFT_BRACKET,RIGHT_BRACKET,LESS_THAN,GREATER_THAN,EQUAL,NOT_EQUAL,LESS_THAN_OR_EQUAL,GREATER_THAN_OR_EQUAL,PLUS,MINUS,MULTIPLY,CONST,SEMI_COLON,COLON,OUTPUT,CASE,ERROR
};

//Token Class Definition
class Token
{
private:
    int id;
    void ResetToken();
    void InitToken();
public:
    bool SetToken(std::string);
    TokenEnum token;
    int value;
    std::string string;
};

//Tokenizer Class for extracting tokens from a file
class Tokenizer
{
private:
    std::vector<std::string> tokens;
    int current;
public:
    Tokenizer();
    void Tokenize(const std::string &filename);
    bool Advance();
    void PrintTokens();
    bool NoWhitespace(std::string s);
    bool ContainsNonAlpha(std::string s);
    std::string SplitNonAlpha(std::string &s);
    bool ContainsWhitespace(std::string s);
    void RemoveWhitespace(std::string &s);
    bool AddToken(std::string s);
    std::string Get();
    std::string PeekAhead();
};

class CSE3341errorHandler
{
private:
    int id;
    int errorCode;
public:
    CSE3341errorHandler();
    void ThrowError(std::string what, std::string who);
};

#endif /* defined(__CSE3341__tokenizer__) */
