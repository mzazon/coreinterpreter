//
//  scanner.h
//  CSE3341
//
//  Created by Mike Zazon on 10/4/12.
//  Copyright (c) 2012 Mike Zazon. All rights reserved.
//

#ifndef __CSE3341__scanner__
#define __CSE3341__scanner__

#include <iostream>
#include <string>
#include <set>
#include "tokenizer.h"

class Scanner {
private:
    std::string previous;
    std::string current;
    Tokenizer tokens;
    std::set<std::string> setOfKeywords;
public:
    Scanner();
    Scanner(const std::string filename);
    std::string GetCurrent();
    bool Advance();
    std::string PeekAhead();
    bool CurrentIsID();
    bool CurrentIsCONST();
    int GetCurrentNum();
    
};

#endif /* defined(__CSE3341__scanner__) */
