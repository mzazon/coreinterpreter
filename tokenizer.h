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

class Tokenizer
{
private:
    std::vector<std::string> tokens;
    unsigned int current;
public:
    Tokenizer();
    ~Tokenizer();
    void Tokenize(const std::string &filename);
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



#endif /* defined(__CSE3341__tokenizer__) */
