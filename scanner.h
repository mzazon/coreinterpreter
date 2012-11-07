//
//  scanner.h
//  CSE3341
//
//  Created by Mike Zazon on 10/4/12.
//  Copyright (c) 2012 Mike Zazon. All rights reserved.
//

#ifndef __CSE3341__scanner__
#define __CSE3341__scanner__

#include <fstream>
#include <string>
#include "tokenizer.h"


class Scanner {
public:
	Scanner(std::string filename);
	Token get();
    bool Next();
	bool Advance();
	int getLine();
	int getv();
private:
    Tokenizer tokens;
    std::string current;
	Token MyToken;
    bool isNum(char c);
	TokenEnum Match(std::string s);
	int line;
	int CurrentValue;
};
#endif /* defined(__CSE3341__scanner__) */