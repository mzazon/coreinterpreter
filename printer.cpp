//
//  printer.cpp
//  CSE3341
//
//  Created by Mike Zazon on 10/7/12.
//  Copyright (c) 2012 Mike Zazon. All rights reserved.
//

#include "printer.h"

Printer::Printer()
{
    
}
Printer::Printer(ParseTree * tree)
{
    t = tree;
    PROG();
}
void Printer::PROG()
{
    Print("program"); NewLine();
    (*t).CursorTo1();
    INCREASE_INDENT();
    DECL_SEQ();
    (*t).CursorToParent();
    DECREASE_INDENT();
    Print("begin"); NewLine();
    INCREASE_INDENT();
    (*t).CursorTo2();
    STMT_SEQ();
    DECREASE_INDENT();
    (*t).CursorToParent();
    Print("end");
    
    
}
void Printer::DECL_SEQ()
{
    (*t).CursorTo1();
    
    DECL();

    (*t).CursorToParent();

    if((*t).getAlt() == 2)
    {
        (*t).CursorTo2();
        DECL_SEQ();
        (*t).CursorToParent();
    }
}
void Printer::STMT_SEQ()
{
    (*t).CursorTo1();
    STMT();
    (*t).CursorToParent();
    if((*t).getAlt() == 2)
    {
        (*t).CursorTo2();
        STMT_SEQ();
        (*t).CursorToParent();
    }
}
void Printer::DECL()
{
    Space();
    std::cout << "int ";
    (*t).CursorTo1();
    ID_LIST();
    (*t).CursorToParent();
    Print(";"); NewLine();
    
    
}
void Printer::STMT()
{
    Space();
    int a = (*t).getAlt();
    (*t).CursorTo1();
    
    if(a == 1) ASSIGN();
    else if(a == 2) IF();
    else if(a == 3) LOOP();
    else if(a == 4) IN();
    else if(a == 5) OUT();
    
    (*t).CursorToParent();
}
void Printer::ID_LIST()
{
    std::cout<<"HEY WE HERE!"<<std::endl;
    (*t).CursorTo1();
    ID();
    (*t).CursorToParent();
    std::cout << "*** " << (*t).getAlt() << std::endl;
    if((*t).getAlt() == 2)
    {
        std::cout << ",";
        std::cout << "! about to call CursorTo2 from within alt2 if\n";
        (*t).CursorTo2();
        std::cout << "! about to call ID_LIST from within alt2 if\n";
        ID_LIST();
        (*t).CursorToParent();
    }
}
void Printer::ASSIGN()
{
    (*t).CursorTo1();
    ID();
    (*t).CursorToParent();
    Print(":=");
    (*t).CursorTo2();
    EXPR();
    (*t).CursorToParent();
    Print(";"); NewLine();
}
void Printer::IF()
{
    Print("if");
    (*t).CursorTo1();
    COND();
    (*t).CursorToParent();
    Print("then"); NewLine(); INCREASE_INDENT();
    (*t).CursorTo2();
    STMT_SEQ();
    DECREASE_INDENT();
    (*t).CursorToParent();
    if((*t).getAlt() == 2)
    {
        Print("else"); NewLine();
        INCREASE_INDENT();
        (*t).CursorTo3();
        STMT_SEQ();
        (*t).CursorToParent();
        DECREASE_INDENT();
    }
    Print("endif;"); NewLine();
}
void Printer::LOOP()
{
    Space();
    Print("do"); NewLine();
    INCREASE_INDENT();
    (*t).CursorTo1();
    STMT_SEQ();
    (*t).CursorToParent();
    DECREASE_INDENT();
    Space();
    Print("while");
    (*t).CursorTo2();
    COND();
    (*t).CursorToParent();
    Print("endwhile;");
}
void Printer::IN()
{
    Space();
    Print("input ");
    (*t).CursorTo1();
    ID_LIST();
    (*t).CursorToParent();
    Print(";"); NewLine();
}
void Printer::OUT()
{
    Space();
    Print("output ");
    (*t).CursorTo1();
    ID_LIST();
    (*t).CursorToParent();
    Print(";"); NewLine();
}
void Printer::EXPR()
{
    (*t).CursorTo1();
    TERM();
    (*t).CursorToParent();
    
    if((*t).getAlt() == 2)
    {
        Print("+");
        (*t).CursorTo2();
        EXPR();
        (*t).CursorToParent();
    }
    else if((*t).getAlt() == 3)
    {
        Print("-");
        (*t).CursorTo2();
        EXPR();
        (*t).CursorToParent();
    }
}
void Printer::COND()
{
    int a = (*t).getAlt();
    (*t).CursorTo1();
    
    if(a == 1)
    {
        CMPR();
        (*t).CursorToParent();
    }
    else if(a==2)
    {
        Print("!");
        COND();
        (*t).CursorToParent();
    }
    else if(a==3)
    {
        Print("(");
        (*t).CursorTo1();
        COND();
        (*t).CursorToParent();
        Print("AND");
        (*t).CursorTo2();
        COND();
        (*t).CursorToParent();
        Print(")");
    }
    else if(a==4)
    {
        Print("(");
        (*t).CursorTo1();
        COND();
        (*t).CursorToParent();
        Print("OR");
        (*t).CursorTo2();
        COND();
        (*t).CursorToParent();
        Print(")");
    }
}
void Printer::CMPR()
{
    Print("[");
    (*t).CursorTo1();
    EXPR();
    (*t).CursorToParent();
    (*t).CursorTo2();
    CMPR_OP();
    (*t).CursorToParent();
    (*t).CursorTo3();
    EXPR();
    (*t).CursorToParent();
    Print("]");
}
void Printer::CMPR_OP()
{
    int a = (*t).getAlt();
    if(a == 1) Print("<");
    else if(a == 2) Print("=");
    else if(a == 3) Print("!=");
    else if(a == 4) Print(">");
    else if(a == 5) Print(">=");
    else if(a == 6) Print(">=");
    
}
void Printer::TERM()
{
    (*t).CursorTo1();
    FACTOR();
    (*t).CursorToParent();
    if((*t).getAlt() == 2)
    {
        Print("*");
        (*t).CursorTo2();
        TERM();
        (*t).CursorToParent();
    }
}
void Printer::FACTOR()
{
    
    if((*t).getAlt() == 1)
    {
        (*t).CursorTo1();
        CONST();
        (*t).CursorToParent();
    }
    else if((*t).getAlt() == 2)
    {
        (*t).CursorTo1();
        ID();
        (*t).CursorToParent();
    }
    else if((*t).getAlt() == 3)
    {
        Print("-");
        (*t).CursorTo1();
        FACTOR();
        (*t).CursorToParent();
    }
    else if((*t).getAlt() == 4)
    {
        Print("(");
        (*t).CursorTo1();
        EXPR();
        (*t).CursorToParent();
        Print(")"); NewLine();
    }
}
void Printer::CASE()
{
    //TODO:
}
void Printer::CASE_LIST()
{
    //TODO:
}
void Printer::ID()
{
    Print((*t).getValue());
}
void Printer::CONST()
{
    Print((*t).getValue());
}
void Printer::INCREASE_INDENT()
{
    i+=2;
}
void Printer::DECREASE_INDENT()
{
    i-=2;
}
void Printer::Print(std::string s)
{
    std::cout << s;
}
void Printer::NewLine()
{
    std::cout << std::endl;
}
void Printer::Space()
{
    for(int j=i; j>0; j--)
        std::cout << " ";
}