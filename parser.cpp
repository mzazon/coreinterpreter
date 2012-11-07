//
//  parser.cpp
//  CSE3341
//
//  Created by Mike Zazon on 10/4/12.
//  Copyright (c) 2012 Mike Zazon. All rights reserved.
//

#include "parser.h"
#include "scanner.h"
#include "tokenizer.h"
#include <iostream>


Parser::Parser()
{

}

ParseTree* Parser::PROG()
{
	ParseTree* retTree = new ParseTree();
    
	(*retTree).setToken((*parser).get());

	if(!(*parser).Advance()) ThrowParserError();
    
	if((*parser).get().token == INT)
    {
		(*retTree).SetLeaf1(DECL_SEQ()->getLeaf());
        
		if((*parser).get().token == BEGIN)
        {
			if(!(*parser).Advance()) ThrowParserError();
            
			(*retTree).SetLeaf2(STMT_SEQ()->getLeaf());
            
			if(((*parser).get().token == END) && !(*parser).Advance())
            {
				(*retTree).setAlt(1);
				return retTree;
			}
            else
            {
				ThrowParserError();
			}
		}
        else
        {
			ThrowParserError();
		}
	}
    else
    {
        ThrowParserError();
	}
    return retTree;
}

ParseTree* Parser::DECL_SEQ()
{
	ParseTree* retTree = new ParseTree();
    
	(*retTree).setToken((*parser).get());

	(*retTree).SetLeaf1(DECL()->getLeaf());
	
    if((*parser).get().token == INT)
    {
		(*retTree).SetLeaf2(DECL_SEQ()->getLeaf());
		(*retTree).setAlt(2);
		return retTree;
	}
    
	(*retTree).setAlt(1);
	return retTree;
}

ParseTree* Parser::STMT_SEQ()
{
	ParseTree* retTree = new ParseTree();
	(*retTree).SetLeaf1(STMT()->getLeaf());
    
	if(!((*parser).get().token == IF) && !((*parser).get().token == DO) && !((*parser).get().token == ID) && !((*parser).get().token == CASE) && !((*parser).get().token == INPUT) && !((*parser).get().token == OUTPUT))
    {
		(*retTree).setAlt(1);
	}
    else
    {
		(*retTree).setAlt(2);
		(*retTree).SetLeaf2(STMT_SEQ()->getLeaf());
	}
	return retTree;
}

ParseTree* Parser::DECL()
{
	ParseTree* retTree = new ParseTree();
    
	if(!(*parser).Advance()) ThrowParserError();
    
	(*retTree).SetLeaf1(ID_LIST(false)->getLeaf());
    
	if(!((*parser).get().token == SEMI_COLON)) ThrowParserError();

	if(!(*parser).Advance()) ThrowParserError();
    
	return retTree;
}

ParseTree* Parser::ID_LIST(bool in)
{
	ParseTree* retTree = new ParseTree();
    
	if(!((*parser).get().token == ID))
    {
		ThrowParserError();
	}
	if(in)
    {
		if(!isin((*parser).get().string))
        {
			ThrowParserError();
		}
	}
    else
    {
		if(isin((*parser).get().string))
        {
			ThrowParserError();
		}
	}

	(*retTree).SetLeaf1(ID_TERMINAL()->getLeaf());
    
	if((*parser).get().token == COMMA)
    {
		if(!(*parser).Advance()) ThrowParserError();
		(*retTree).SetLeaf2(ID_LIST(in)->getLeaf());
		(*retTree).setAlt(2);
	}
    else
    {
		(*retTree).setAlt(1);
	}
	return retTree;

}
ParseTree* Parser::STMT()
{
	ParseTree* retTree = new ParseTree();
    
	if((*parser).get().token == ID)
    {
		(*retTree).SetLeaf1(ASSIGN()->getLeaf());
		(*retTree).setAlt(1);
	}
    else if((*parser).get().token == IF)
    {
		(*retTree).SetLeaf1(IFF()->getLeaf());
		(*retTree).setAlt(2);
	}
    else if((*parser).get().token == DO)
    {
		(*retTree).SetLeaf1(DOWHILE()->getLeaf());
		(*retTree).setAlt(3);
	}
    else if((*parser).get().token == INPUT)
    {
		(*retTree).SetLeaf1(IN()->getLeaf());
		(*retTree).setAlt(4);
	}
    else if((*parser).get().token == OUTPUT)
    {
		(*retTree).SetLeaf1(OUT()->getLeaf());
		(*retTree).setAlt(5);
	}
    else if((*parser).get().token == CASE)
    {
		(*retTree).SetLeaf1(CASE_STMT()->getLeaf());
		(*retTree).setAlt(6);
	}
    else
    {
		ThrowParserError();
	}
	return retTree;
}
ParseTree* Parser::ASSIGN()
{
	ParseTree* retTree = new ParseTree();
    
	if((isin((*parser).get().string)))
    {
		(*retTree).SetLeaf1(ID_TERMINAL()->getLeaf());
		if(!((*parser).get().token == ASSIGNMENT))
        {
			ThrowParserError();
		}
        
		if(!(*parser).Advance()) ThrowParserError();
		(*retTree).SetLeaf2(EXPR()->getLeaf());
        
		if(!((*parser).get().token == SEMI_COLON))
        {
			ThrowParserError();
		}

		if(!(*parser).Advance()) ThrowParserError();

	}
    else
    {
		ThrowParserError();
	}
	return retTree;

}
ParseTree* Parser::IN()
{
	ParseTree* retTree = new ParseTree();

	if(!(*parser).Advance()) ThrowParserError();
    
	(*retTree).SetLeaf1(ID_LIST(true)->getLeaf());
    
	if(!((*parser).get().token == SEMI_COLON))
    {
		ThrowParserError();
	}

	if(!(*parser).Advance()) ThrowParserError();
	
    return retTree;

}

ParseTree* Parser::IFF()
{
	ParseTree* retTree = new ParseTree();

	if(!(*parser).Advance()) ThrowParserError();
    
	(*retTree).SetLeaf1(COND()->getLeaf());
    
	if(!((*parser).get().token == THEN))
    {
		ThrowParserError();
	}
	if(!(*parser).Advance()) ThrowParserError();
    
	(*retTree).setAlt(1);
	(*retTree).SetLeaf2(STMT_SEQ()->getLeaf());
	if((*parser).get().token == ELSE)
    {
		if(!(*parser).Advance()) ThrowParserError();
		(*retTree).setAlt(2);
		(*retTree).SetLeaf3(STMT_SEQ()->getLeaf());
	}
	if(!((*parser).get().token == ENDIF))
    {
		ThrowParserError();
	}

	if(!(*parser).Advance()) ThrowParserError();
	if(!((*parser).get().token == SEMI_COLON))
    {
		ThrowParserError();
	}

	if(!(*parser).Advance()) ThrowParserError();
    
	return retTree;

}


ParseTree* Parser::DOWHILE()
{
	ParseTree* retTree = new ParseTree();

	if(!(*parser).Advance()) ThrowParserError();
    
	(*retTree).SetLeaf1(STMT_SEQ()->getLeaf());

	if(!((*parser).get().token == WHILE))
    {
		ThrowParserError();
	}
    
	if(!(*parser).Advance()) ThrowParserError();
	(*retTree).SetLeaf2(COND()->getLeaf());
    
	if(!((*parser).get().token == ENDDO))
    {
		ThrowParserError();
	}

	if(!(*parser).Advance()) ThrowParserError();
    
	if(!((*parser).get().token == SEMI_COLON))
    {
		ThrowParserError();
	}

	if(!(*parser).Advance()) ThrowParserError();
    
	return retTree;

}
ParseTree* Parser::COND()
{
	ParseTree* retTree = new ParseTree();
    
	if((*parser).get().token == NOT)
    {
		(*retTree).setAlt(2);

		if(!(*parser).Advance()) ThrowParserError();
        
		(*retTree).SetLeaf1(COND()->getLeaf());
        
	}
    else if((*parser).get().token == LEFT_PAREN)
    {

		if(!(*parser).Advance()) ThrowParserError();
        
		(*retTree).SetLeaf1(COND()->getLeaf());
        
		if((*parser).get().token == AND)
        {
			(*retTree).setAlt(3);
		}
        else if((*parser).get().token == OR)
        {
			(*retTree).setAlt(4);
		}
        else
        {
			ThrowParserError();

		}

		if(!(*parser).Advance()) ThrowParserError();
        
		(*retTree).SetLeaf2(COND()->getLeaf());
        
		if(!((*parser).get().token == RIGHT_PAREN))
        {
			ThrowParserError();
		}

		if(!(*parser).Advance()) ThrowParserError();

	}
    else
    {
		(*retTree).setAlt(1);
		(*retTree).SetLeaf1(COMP()->getLeaf());
	}
	return retTree;
}
ParseTree* Parser::COMP()
{
	ParseTree* retTree = new ParseTree();
    
	if(!((*parser).get().token == LEFT_BRACKET))
    {
		ThrowParserError();
	}

	if(!(*parser).Advance()) ThrowParserError();
    
	(*retTree).SetLeaf1(FACTOR()->getLeaf());
	(*retTree).SetLeaf2(COMP_OP()->getLeaf());
	(*retTree).SetLeaf3(FACTOR()->getLeaf());
    
	if(!((*parser).get().token == RIGHT_BRACKET))
    {
		ThrowParserError();
	}

	if(!(*parser).Advance()) ThrowParserError();
    
	return retTree;

}
ParseTree* Parser::COMP_OP()
{
	ParseTree* retTree = new ParseTree();
	if((*parser).get().token == LESS_THAN)
    {
		(*retTree).setAlt(1);
		if(!(*parser).Advance()) ThrowParserError();
	}
    else if((*parser).get().token == EQUAL)
    {
		(*retTree).setAlt(2);
		if(!(*parser).Advance()) ThrowParserError();
	}
    else if((*parser).get().token == NOT_EQUAL)
    {
		(*retTree).setAlt(3);
		if(!(*parser).Advance()) ThrowParserError();
	}
    else if((*parser).get().token == GREATER_THAN)
    {
		(*retTree).setAlt(4);
		if(!(*parser).Advance()) ThrowParserError();
        
	}
    else if((*parser).get().token == GREATER_THAN_OR_EQUAL)
    {
		(*retTree).setAlt(5);
		if(!(*parser).Advance()) ThrowParserError();
        
	}
    else if((*parser).get().token == LESS_THAN_OR_EQUAL)
    {
		(*retTree).setAlt(6);

		if(!(*parser).Advance()) ThrowParserError();
	}
    else
    {
		ThrowParserError();
	}
	return retTree;
}
ParseTree* Parser::EXPR()
{
	ParseTree* retTree = new ParseTree();
	(*retTree).SetLeaf1(TERM()->getLeaf());
    
	if((*parser).get().token == PLUS)
    {
		(*retTree).setAlt(2);

		if(!(*parser).Advance()) ThrowParserError();
		(*retTree).SetLeaf2(EXPR()->getLeaf());
	}
    else if((*parser).get().token == MINUS)
    {
		(*retTree).setAlt(3);
		if(!(*parser).Advance()) ThrowParserError();
		(*retTree).SetLeaf2(EXPR()->getLeaf());

	}
    else
    {
		(*retTree).setAlt(1);
	}
	return retTree;
}
ParseTree* Parser::TERM()
{
	ParseTree* retTree = new ParseTree();
	(*retTree).SetLeaf1(FACTOR()->getLeaf());
    
	if((*parser).get().token == MULTIPLY)
    {
		(*retTree).setAlt(2);
		if(!(*parser).Advance()) ThrowParserError();
		(*retTree).SetLeaf2(TERM()->getLeaf());
	}
    else
    {
		(*retTree).setAlt(1);
	}
	return retTree;
}

ParseTree* Parser::FACTOR()
{
	ParseTree* retTree = new ParseTree();
	if((*parser).get().token == CONST)
    {
		(*retTree).setAlt(1);
		(*retTree).SetLeaf1(CONST_TERMINAL()->getLeaf());
	}
    else if((*parser).get().token == ID)
    {
		(*retTree).setAlt(2);
		if(!isin((*parser).get().string))
        {
			ThrowParserError();
		}
		(*retTree).SetLeaf1(ID_TERMINAL()->getLeaf());
	}
    else if((*parser).get().token == MINUS)
    {
		(*retTree).setAlt(3);

		if(!(*parser).Advance()) ThrowParserError();
		(*retTree).SetLeaf1(FACTOR()->getLeaf());

	}
    else if(!(*parser).get().token == LEFT_PAREN)
    {
		(*retTree).setAlt(4);
        
		if(!(*parser).Advance()) ThrowParserError();
		(*retTree).SetLeaf1(EXPR()->getLeaf());
		if(!((*parser).get().token == RIGHT_PAREN))
        {
			ThrowParserError();
		}
        
		if(!(*parser).Advance()) ThrowParserError();
	}
    else
    {
        ThrowParserError();
    }
	return retTree;

}

ParseTree* Parser::CASE_STMT() {
	ParseTree* retTree = new ParseTree();

	if(!(*parser).Advance()) ThrowParserError();
    
	(*retTree).SetLeaf1(ID_TERMINAL()->getLeaf());

    if(!(*parser).Advance()) ThrowParserError();
        
	(*retTree).SetLeaf2(CASE_SEQ()->getLeaf());

	if(!((*parser).get().token == SEMI_COLON))
    {
		ThrowParserError();
	}
	if(!(*parser).Advance()) ThrowParserError();
    
	return retTree;
}

ParseTree* Parser::CASE_SEQ()
{
	ParseTree* retTree = new ParseTree();
	(*retTree).SetLeaf1((*CONST_LIST()).getLeaf());

    if(!(*parser).Advance()) ThrowParserError();
    (*retTree).SetLeaf2((*EXPR()).getLeaf());
    
	if((*parser).get().token == ELSE)
    {
		(*retTree).setAlt(2);
        if(!(*parser).Advance()) ThrowParserError();
		(*retTree).SetLeaf3((*EXPR()).getLeaf());
	}
    else if((*parser).get().token == BAR)
    {
		(*retTree).setAlt(1);
		(*retTree).SetLeaf2(CASE_SEQ()->getLeaf());
	}
	return retTree;
}

ParseTree* Parser::CONST_LIST()
{
    ParseTree* retTree = new ParseTree();
    
    (*retTree).SetLeaf1((*CONST_TERMINAL()).getLeaf());
    
    if((*parser).get().token == COMMA)
    {
        (*retTree).setAlt(2);
        
        if(!(*parser).Advance()) ThrowParserError();
        
        (*retTree).SetLeaf2((*CONST_TERMINAL()).getLeaf());
    }
    else
    {
        (*retTree).setAlt(1);
    }
    return retTree;
}

ParseTree* Parser::OUT()
{
	ParseTree* retTree = new ParseTree();

    if(!(*parser).Advance()) ThrowParserError();
		(*retTree).SetLeaf1(ID_LIST(true)->getLeaf());
    
		if(!((*parser).get().token == SEMI_COLON))
        {
			ThrowParserError();
		}

		if(!(*parser).Advance()) ThrowParserError();
		return retTree;
}

ParseTree* Parser::ID_TERMINAL()
{
	ParseTree* retTree = new ParseTree();
	(*retTree).setToken((*parser).get());
    
	if(!(isin((*parser).get().string)))
    {
		symbolList[symbolIndex].ID = (*parser).get().string;
		symbolList[symbolIndex].SYMBOL_INIT_FLAG = false;
		symbolIndex++;
	}

	if(!(*parser).Advance()) ThrowParserError();
	return retTree;

}
ParseTree* Parser::CONST_TERMINAL()
{
	ParseTree* retTree = new ParseTree();
    
	if(!((*parser).get().token == CONST))
    {
		ThrowParserError();
	}
    
	(*retTree).setToken((*parser).get());

	if(!(*parser).Advance()) ThrowParserError();
	return retTree;

}
void Parser::ThrowParserError()
{
	std::cout << "*** FATAL PARSER ERROR: unexpected token or end of file.  Exiting to OS. ***" << std::endl;
    exit(1);
}

ParseTree* Parser::start(std::string filename)
{
    parser = new Scanner(filename.c_str());
	numSymbols = 0;
	symbolIndex = 0;
	symbolList = new Symbol[5000];
	tree = new ParseTree();
    
	(*parser).Advance();
	Token tmp = (*parser).get();
    
	if(tmp.token == PROGRAM)
    {
		tree = PROG();
	}
    else
    {
        ThrowParserError();
	}
    
	(*tree).setSymbolList(symbolList);
	(*tree).setNumSymbols(symbolIndex);
	return tree;
}

bool Parser::isin(std::string s) {
	for (int i = 0; i < symbolIndex; i++) {
		if(s == symbolList[i].ID) {
			return true;
		}
	}
	return false;
}

