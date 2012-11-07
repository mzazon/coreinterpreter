//
//  main.cpp
//  CSE3341
//
//  Created by Mike Zazon on 10/4/12.
//  Copyright (c) 2012 Mike Zazon. All rights reserved.
//

#include <iostream>
#include "tokenizer.h"
#include "scanner.h"
#include "parsetree.h"
#include "parser.h"
#include "printer.h"
#include "executor.h"

int main(int argc, const char * argv[])
{
    //check command line parameters and throw usage tip if incorrect
    if ( argc != 2 ) std::cout<<"usage: "<< argv[0] <<" <filename>" << std::endl;
    else
    {
        Parser parser(argv[1]);
        Printer printer(parser.GetTree());
        ParseTree* tree = parser.GetTree();
        Executor* exe = new Executor(tree, argv[2]);
        exe->Start();
    }
    
    return 0;
}

