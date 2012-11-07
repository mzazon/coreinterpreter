//
//  parser.cpp
//  CSE3341
//
//  Created by Mike Zazon on 10/15/12.
//  Copyright (c) 2012 Mike Zazon. All rights reserved.
//

#include "parser.h"

Parser::Parser(std::string filename)
{
    //init all members
    scanner = new Scanner(filename);
    st = new SymbolTable();
    t = new ParseTree();
    token = "init";
    
    //start the parser
    t = PROG();
}
void Parser::Error(std::string s)
{
    std::cout << "*** FATAL SCANNER ERROR: " << s << "***" << std::endl;
    exit(1);
}
ParseTree * Parser::PROG()
{
    ParseTree * retTree = new ParseTree();
    
    if((*scanner).GetCurrent() == "program")
    {
        (*retTree).setValue((*scanner).GetCurrent());
        (*scanner).Advance();
        if((*scanner).GetCurrent() == "int")
        {
            (*retTree).SetChild1((*DECL_SEQ()).Cursor());
            if((*scanner).GetCurrent() == "begin")
            {
                (*scanner).Advance(); //advance begin
                (*retTree).SetChild2((*STMT_SEQ()).Cursor());
                if((*scanner).GetCurrent() == "end")
                {
                    (*retTree).setAlt(1);
                    return retTree;
                }
                else
                {
                    Error("Expected end token, got " + (*scanner).GetCurrent() + " instead.");
                }
            }
            else
            {
                Error("Expected begin token, got " + (*scanner).GetCurrent() + " instead.");
            }
        }
        else
        {
            Error("Expected int (DECL_STMT) token, got " + (*scanner).GetCurrent() + " instead.");
        }
    }
    else
    {
        Error("Expected program token, got " + (*scanner).GetCurrent() + " instead.");
    }
    //return retTree;
}
ParseTree * Parser::DECL_SEQ()
{
    ParseTree * retTree = new ParseTree();
    
    (*retTree).setValue((*scanner).GetCurrent());
    (*retTree).SetChild1((*DECL()).Cursor());
    
    
    if((*scanner).GetCurrent() == "int")
    {
        (*retTree).SetChild2((*DECL_SEQ()).Cursor());
        (*retTree).setAlt(2);
        return retTree;
    }
    (*retTree).setAlt(1);
    return retTree;
}
ParseTree * Parser::STMT_SEQ()
{
    ParseTree * retTree = new ParseTree();

    (*retTree).setValue((*scanner).GetCurrent());
    (*retTree).SetChild1((*STMT()).Cursor());
    (*retTree).setAlt(1);
    
    if(!(*scanner).CurrentIsID() && !((*scanner).GetCurrent() == "do") && !((*scanner).GetCurrent() == "input") && !((*scanner).GetCurrent() == "output") && !((*scanner).GetCurrent() == "if") && !((*scanner).GetCurrent() == "while") && !((*scanner).GetCurrent() == "enddo"))
    {
        (*retTree).setAlt(1);
    }
    else
    {
        (*retTree).setAlt(2);
        (*retTree).SetChild2((*STMT_SEQ()).Cursor());
    }

    return retTree;
}
ParseTree * Parser::DECL()
{
    ParseTree * retTree = new ParseTree();
    
    //this line below may not be needed to set value properly
    (*retTree).setValue((*scanner).GetCurrent());
    
    (*scanner).Advance();

    (*retTree).SetChild1((*ID_LIST()).Cursor());
    
    if(!((*scanner).GetCurrent() == ";"))
    {
        Error("Expected ; token, got " + (*scanner).GetCurrent() + " instead.");
    }
    
    (*scanner).Advance(); //advance the ;
    
    
    return retTree;
}
ParseTree * Parser::STMT()
{
    ParseTree * retTree = new ParseTree();
    
    /*
    switch(token)
    {
        case "if":
            //do
            break;
        case "do":
            //do
            break;
        case "input";
            //do
            break;
        case "output":
            //do
            break;
            
        default:
            //default statement
    }
    */
    if((*scanner).CurrentIsID())
    {
        //parse assign alt 1
        (*retTree).SetChild1((*ASSIGN()).Cursor());
        (*retTree).setAlt(1);
    }
    else if((*scanner).GetCurrent() == "if")
    {
        //parse assign alt 2
        (*retTree).SetChild1((*IF()).Cursor());
        (*retTree).setAlt(2);
    }
    else if((*scanner).GetCurrent() == "do")
    {
        //parse assign alt 3
        (*retTree).SetChild1((*LOOP()).Cursor());
        (*retTree).setAlt(3);
    }
    else if((*scanner).GetCurrent() == "input")
    {
        //parse assign alt 4
        (*retTree).SetChild1((*IN()).Cursor());
        (*retTree).setAlt(4);
    }
    else if((*scanner).GetCurrent() == "output")
    {
        //parse assign alt 5
        (*retTree).SetChild1((*OUT()).Cursor());
        (*retTree).setAlt(5);
    }
    else if((*scanner).GetCurrent() == "case")
    {
        //parse alt 6
        (*retTree).SetChild1((*CASE()).Cursor());
        (*retTree).setAlt(6);
    }
    else
    {
        //invalid statement
        Error("Expected an if/do/input/output/case/assign token, got " + (*scanner).GetCurrent() + " instead.");
    }

    return retTree;
}
ParseTree * Parser::ID_LIST()
{
    ParseTree * retTree = new ParseTree();
    
    //check here for: declaration, double declaration, and unexpected input here.
    
    (*retTree).SetChild1((*ID()).Cursor());
    
    if((*scanner).GetCurrent() == ",")
    {
        (*scanner).Advance();
        (*retTree).SetChild2((*ID_LIST()).Cursor());
        (*retTree).setAlt(2);
    }
    else
    {
        //we use alt 1 here if list is gone
        (*retTree).setAlt(1);
    }
    return retTree;
}
ParseTree * Parser::ASSIGN()
{
    ParseTree * retTree = new ParseTree();
    
    //TODO: check if its already declared, replace true below
    if((*st).IsInTable((*scanner).GetCurrent()))
    {
        (*retTree).SetChild1((*ID()).Cursor());
        if(!((*scanner).GetCurrent() == ":="))
        {
            Error("Expected an := token, got " + (*scanner).GetCurrent() + " instead.");
        }
        std::cout << " DEBUG ***************** " << (*scanner).GetCurrent() << std::endl;
        (*scanner).Advance();
        std::cout << " DEBUG ***************** " << (*scanner).GetCurrent() << std::endl;
        (*retTree).SetChild2((*EXPR()).Cursor());
        
        if(!((*scanner).GetCurrent() == ";"))
        {
            Error("Expected a ; token, got " + (*scanner).GetCurrent() + " instead.");
        }
        (*scanner).Advance();
        
    }
    else
    {
        Error((*scanner).GetCurrent() + " symbol is not declared in declr statements at beginning of program.");
    }

    return retTree;
}
ParseTree * Parser::IF()
{
    ParseTree * retTree = new ParseTree();
    
    (*scanner).Advance();
    
    (*retTree).SetChild1((*COND()).Cursor());
    
    //next token should be then
    
    if(!((*scanner).GetCurrent() == "then"))
    {
        Error("Expected then token, got " + (*scanner).GetCurrent() + " instead.");
    }
    (*scanner).Advance();
    (*retTree).setAlt(1);
    (*retTree).SetChild2((*STMT_SEQ()).Cursor());
    if((*scanner).GetCurrent() == "else")
    {
        (*scanner).Advance();
        (*retTree).setAlt(2);
        (*retTree).SetChild3((*STMT_SEQ()).Cursor());
    }
    if(!((*scanner).GetCurrent() == "endif"))
    {
        Error("Expected endif token, got " + (*scanner).GetCurrent() + " instead.");
    }
    (*scanner).Advance();
    if(!((*scanner).GetCurrent() == ";"))
    {
        Error("Expected ; token, got " + (*scanner).GetCurrent() + " instead.");
    }
    (*scanner).Advance();
    
    

    return retTree;
}
ParseTree * Parser::LOOP()
{
    ParseTree * retTree = new ParseTree();

    return retTree;
}
ParseTree * Parser::IN()
{
    ParseTree * retTree = new ParseTree();
    //get input token
    (*scanner).Advance();
    (*retTree).SetChild1((*ID_LIST()).Cursor());
    if(!((*scanner).GetCurrent() == ";"))
    {
        Error("Expected ; token, got " + (*scanner).GetCurrent() + " instead.");
        
    }
    
    (*scanner).Advance();
    return retTree;
}
ParseTree * Parser::OUT()
{
    ParseTree * retTree = new ParseTree();
    (*scanner).Advance();
    (*retTree).SetChild1((*ID_LIST()).Cursor());
    if(!((*scanner).GetCurrent() == ";"))
    {
        Error("Expected ; token, got " + (*scanner).GetCurrent() + " instead.");
    }
    
    (*scanner).Advance();
    
    return retTree;
}
ParseTree * Parser::EXPR()
{
    ParseTree * retTree = new ParseTree();
    (*retTree).SetChild1((*TERM()).Cursor());
    
    std::cout << "** EXPR DEBUG: "<<(*scanner).GetCurrent() << std::endl;
    
    if((*scanner).GetCurrent() == "+") // plus
    {
        //set alt 2
        (*retTree).setAlt(2);
        (*scanner).Advance(); //get the +
        (*retTree).SetChild2((*EXPR()).Cursor());
    }
    else if((*scanner).GetCurrent() == "-") // minus
    {
        //set alt 3
        (*retTree).setAlt(3);
        (*scanner).Advance(); // get the -
        (*retTree).SetChild2((*EXPR()).Cursor());
    }
    else
        (*retTree).setAlt(1);
    
    return retTree;
}
ParseTree * Parser::COND()
{
    ParseTree * retTree = new ParseTree();
    
    if((*scanner).GetCurrent() == "!")
    {
        (*retTree).setAlt(2);
        (*scanner).Advance();
        (*retTree).SetChild1((*COND()).Cursor());
    }
    else if((*scanner).GetCurrent() == "(")
    {
        (*scanner).Advance();
        (*retTree).SetChild1((*COND()).Cursor());
        if((*scanner).GetCurrent() == "AND")
        {
            (*retTree).setAlt(3);
        }
        else if((*scanner).GetCurrent() == "OR")
        {
            (*retTree).setAlt(4);
        }
        else
        {
            Error("Expected AND/OR token, got " + (*scanner).GetCurrent() + " instead.");
        }
        
        (*scanner).Advance();
        
        (*retTree).SetChild2((*COND()).Cursor());
        if(!((*scanner).GetCurrent() == ")"))
        {
            Error("Expected ) token, got " + (*scanner).GetCurrent() + " instead.");
        }
    }
    else
    {
        (*retTree).setAlt(1);
        (*retTree).SetChild1((*CMPR()).Cursor());
    }

    return retTree;
}
ParseTree * Parser::CMPR()
{
    ParseTree * retTree = new ParseTree();
    
    if(!((*scanner).GetCurrent() == "["))
    {
        Error("Expected [ token, got " + (*scanner).GetCurrent() + " instead.");
    }
    (*scanner).Advance();
    (*retTree).SetChild1((*EXPR()).Cursor());
    (*retTree).SetChild2((*CMPR_OP()).Cursor());
    (*retTree).SetChild3((*EXPR()).Cursor());
    
    if(!((*scanner).GetCurrent() == "]"))
    {
        Error("Expected ] token, got " + (*scanner).GetCurrent() + " instead.");
    }
    
    (*scanner).Advance();
    
    return retTree;
}
ParseTree * Parser::CMPR_OP()
{
    ParseTree * retTree = new ParseTree();
    
    if((*scanner).GetCurrent() == "<")
    {
        (*retTree).setAlt(1);
    }
    else if((*scanner).GetCurrent() == "=")
    {
        (*retTree).setAlt(2);
    }
    else if((*scanner).GetCurrent() == "!=")
    {
        (*retTree).setAlt(3);
    }
    else if((*scanner).GetCurrent() == ">")
    {
        (*retTree).setAlt(4);
    }
    else if((*scanner).GetCurrent() == ">=")
    {
        (*retTree).setAlt(5);
    }
    else if((*scanner).GetCurrent() == "<=")
    {
        (*retTree).setAlt(6);
    }
    else
    {
        Error("Expected CMPR_OP token, got " + (*scanner).GetCurrent() + " instead.");
    }
    (*scanner).Advance();
    
    return retTree;
}
ParseTree * Parser::TERM()
{
    ParseTree * retTree = new ParseTree();
    
    std::cout << "** TERM DEBUG: "<<(*scanner).GetCurrent() << std::endl;
    
    (*retTree).SetChild1((*FACTOR()).Cursor());
    
    if((*scanner).GetCurrent() == "*")
    {
        (*retTree).setAlt(2);
        (*scanner).Advance();
        (*retTree).SetChild2((*TERM()).Cursor());
    }
    else
    {
        (*retTree).setAlt(1);
    }
    return retTree;
}
ParseTree * Parser::FACTOR()
{
    ParseTree * retTree = new ParseTree();
    
    std::cout << "** TERM DEBUG: "<<(*scanner).GetCurrent() << std::endl;
    
    if((*scanner).CurrentIsCONST())
    {
        std::cout << "** TERM DEBUG (inside CurrentIsCONST: "<<(*scanner).GetCurrent() << std::endl;
        (*retTree).setAlt(1);
        (*retTree).SetChild1((*CONST()).Cursor());
    }
    else if((*scanner).CurrentIsID())
    {
        std::cout << "** TERM DEBUG (inside IsID): "<<(*scanner).GetCurrent() << std::endl;
        (*retTree).setAlt(2);
        (*retTree).SetChild1((*ID()).Cursor());
    }
    else if((*scanner).GetCurrent() == "-")
    {
        (*retTree).setAlt(3);
        (*retTree).SetChild1((*FACTOR()).Cursor());
    }
    else if((*scanner).GetCurrent() == "(")
    {
        //advance scanner
        (*scanner).Advance();
        //call expr
        (*retTree).SetChild1((*EXPR()).Cursor());
        (*retTree).setAlt(4);
        //consume lparen
        (*scanner).Advance();
    }

    return retTree;
}
ParseTree * Parser::CASE()
{
    ParseTree * retTree = new ParseTree();

    return retTree;
}
ParseTree * Parser::CASE_LIST()
{
    ParseTree * retTree = new ParseTree();

    return retTree;
}
ParseTree * Parser::ID()
{
    ParseTree * retTree = new ParseTree();
    
    (*retTree).setValue((*scanner).GetCurrent());
    
    std::cout << "!DEBUG (ParserID): " << (*retTree).getValue() << std::endl;
    
    if(!(*st).IsInTable((*scanner).GetCurrent()))
    {
        (*st).InsertSymbol((*retTree).getValue());
    }
    
    
    std::cout << "!DEBUG (Size): " << (*st).Size() << std::endl;
    
    (*scanner).Advance();
    
    return retTree;
}
ParseTree * Parser::CONST()
{
    ParseTree * retTree = new ParseTree();
    
    (*retTree).setValue((*scanner).GetCurrent());
    (*retTree).setAlt(1);
    
    //TODO: check to make sure this is actually a const int
    
    (*scanner).Advance(); // consume const
    
    return retTree;
}
ParseTree * Parser::GetTree()
{
    return t;
}