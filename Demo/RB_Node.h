#ifndef RB_NODE_H
#define RB_NODE_H
#include<fstream>
#include <iostream>
#include<vector>
#include <cmath>
#include<string>

#define RED 0
#define BLACK 1
#define BLANK 0

using namespace std;

class RB_Node
  {
    friend class RedBlackTree;
    public:
       RB_Node( int _color, RB_Node* _right, RB_Node* _left, RB_Node* _parent, long _ID, int _count ):RB_COLOR(_color ), right( _right ), left(_left ), parent( _parent ), ID(_ID), count(_count) {};
       RB_Node():RB_Node( BLACK, nullptr, nullptr, nullptr, 0, 0){}
       ~RB_Node();
    private:
       int RB_COLOR;
       RB_Node* right;
       RB_Node* left;
       RB_Node* parent;
       long ID;
       int count;
};

#endif // RB_NODE_H
