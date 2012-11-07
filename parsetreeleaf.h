//
//  parsetreenode.h
//  CSE3341
//
//  Created by Mike Zazon on 10/5/12.
//  Copyright (c) 2012 Mike Zazon. All rights reserved.
//

#ifndef __CSE3341__parsetreenode__
#define __CSE3341__parsetreenode__



class ParseTreeLeaf
{
private:
    ParseTreeLeaf* parent;
    ParseTreeLeaf* child1;
    ParseTreeLeaf* child2;
    ParseTreeLeaf* child3;
    ParseTreeLeaf* child4;
    ParseTreeLeaf* child5;
    unsigned int alt;
    std::string value;
public:
    ParseTreeLeaf();
    bool setValue(std::string v);
    std::string getValue();
    bool setAlt(int alt);
    unsigned int getAlt();
    ParseTreeLeaf* GetParent();
    ParseTreeLeaf* GetChild1();
    ParseTreeLeaf* GetChild2();
    ParseTreeLeaf* GetChild3();
    ParseTreeLeaf* GetChild4();
    ParseTreeLeaf* GetChild5();
    bool SetParent(ParseTreeLeaf* p);
    bool SetChild1(ParseTreeLeaf* c);
    bool SetChild2(ParseTreeLeaf* c);
    bool SetChild3(ParseTreeLeaf* c);
    bool SetChild4(ParseTreeLeaf* c);
    bool SetChild5(ParseTreeLeaf* c);
};

#endif /* defined(__CSE3341__parsetreenode__) */
