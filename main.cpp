//
//  main.cpp
//  CSE3341
//
//  Created by Mike Zazon on 10/4/12.
//  Copyright (c) 2012 Mike Zazon. All rights reserved.
//

#include <iostream>
#include "parser.h"
#include "printer.h"
#include "executor.h"
#include "parsetree.h"

int main(int argc, char** argv)
{
    Parser parser;
    Executor e;
    Printer pr;
    
    //call parser and build parse tree
	ParseTree* pt = parser.start(argv[1]);
    
    //call printer
	pr.start(pt);
    
    //call executor
	e.start(pt,argv[2]);

}

