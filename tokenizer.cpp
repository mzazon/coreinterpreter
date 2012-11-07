//
//  tokenizer.cpp
//  CSE3341
//
//  Created by Mike Zazon on 10/4/12.
//  Copyright (c) 2012 Mike Zazon. All rights reserved.
//

#include "tokenizer.h"

Tokenizer::Tokenizer()
{
    current = 0;
}

Tokenizer::~Tokenizer()
{

}

void  Tokenizer::Tokenize(const std::string &filename)
{
    std::ifstream inputFile(filename.c_str());
    std::vector<std::string> lines;
    std::string source;
    std::string s,s2;

    //check if input file exists
    if(!inputFile)
	{
        std::cout << "ERROR: Could not open specified input file." << std::endl;
	}
    
    //right now this only tokenizes one line
    //need to loop through a vector of lines...
    
    //outer loop goes over each line in input file
    while(getline(inputFile, source))
	{
        std::stringstream ss(source);
        
        //inner loop uses the stringstream to split the tokens out
        while (getline(ss, s, ' '))
        {
            while(ContainsNonAlpha(s) && s != "") //handle if there are non-alpha
            {
                std::string tmp = SplitNonAlpha(s);
                AddToken(tmp);
            }
            if(s.size() > 0)
            {
                RemoveWhitespace(s);
                if(!ContainsWhitespace(s))
                    AddToken(s);
            }
        }
	}
    
	inputFile.close();
    AddToken("eof");
    //uncomment line below for debug output
    PrintTokens();
}

void Tokenizer::PrintTokens()
{
    for(int i=0; i < tokens.size(); i++)
    {
        std::cout << tokens[i] << std::endl;
    }
}

bool Tokenizer::AddToken(std::string s)
{
    if(s == "\t")
        return false;
    if(s == "\n")
        return false;
    if(s == " ")
        return false;
    if(s == "")
        return false;
    tokens.push_back(s);

    return true;
}

bool Tokenizer::NoWhitespace(std::string s)
{
    if(s.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,:;[]!=-+<>*()") != std::string::npos)
    {
        return false;
    }
    
    return true;
}

//returns true if
bool Tokenizer::ContainsNonAlpha(std::string s)
{
    int i=0;
    while(i< s.size())
    {
        if(s[i] == ',' || s[i] == ';' || s[i] == '[' || s[i] == ']' || s[i] == '!' || s[i] == '=' || s[i] == '-' || s[i] == '+' || s[i] == ':' || s[i] == '<' || s[i] == '>' || s[i] == '*' || s[i] == '(' || s[i] == ')')
            return true;
        i++;
    }
    return false;
}

bool Tokenizer::ContainsWhitespace(std::string s)
{
    for(int i=0; i < s.size(); i++)
    {
        if(s[i] == '\t' || s[i] == ' ')
            return true;
    }
    return false;
}

void Tokenizer::RemoveWhitespace(std::string &s)
{
    s.erase( remove( s.begin(), s.end(), ' ' ), s.end() );
    s.erase( remove( s.begin(), s.end(), '\t' ), s.end() );
}

std::string Tokenizer::SplitNonAlpha(std::string &s)
{
    std::string tmp,tmp2;
    size_t pos;
    pos = s.find_first_of(",;:[]!=-+<>*()");
    tmp=s.substr(0,pos);
    tmp2=s.substr(pos,std::string::npos);
    
    if(pos == 0)
    {
        tmp = s[0];
        tmp2=s.substr(1,std::string::npos);
    }
    
    if(s[0] == '\t')
    {
        tmp = "";
        tmp2=s.substr(1,std::string::npos);
    }
    
    if(s[0] == ':' && s[1] == '=')
    {
        tmp = ":=";
        tmp2=s.substr(2,std::string::npos);
    }
    
    if(s[0] == '!' && s[1] == '=')
    {
        tmp ="!=";
        tmp2=s.substr(2,std::string::npos);
    }
    if(s[0] == '>' && s[1] == '=')
    {
        tmp = ">=";
        tmp2=s.substr(2,std::string::npos);
    }
    if(s[0] == '<' && s[1] == '=')
    {
        tmp = "<=";
        tmp2=s.substr(2,std::string::npos);
    }
    
    s=tmp2;
    s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
    tmp.erase(std::remove(tmp.begin(), tmp.end(), ' '), tmp.end());
            
    return tmp;
}

std::string Tokenizer::Get()
{
    std::string t = tokens[current];
    current+=1;
    return t;
}

std::string Tokenizer::PeekAhead()
{
    //this will overflow array and crash if called unexpectedly
    return tokens[current];
}