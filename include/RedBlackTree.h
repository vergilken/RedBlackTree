#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include "RB_Node.h"

class RedBlackTree
{
    private:
            RB_Node *m_nullNode;
            RB_Node *m_root;
            static long num;
            vector<RB_Node*>pair_vector;

            void reset();
            void preOrder(RB_Node* node, int index);
            bool isNullChildNode ( RB_Node * node );
            bool isNullParentNode ( RB_Node * node );
            void clear( RB_Node* node );

            bool Insert(  long _ID, int _count);
            void InsertFixUp ( RB_Node* node);
            bool LeftRotate(RB_Node * node);
            bool RightRotate(RB_Node* node);
            bool isRightSon( RB_Node * node );
            bool isLeftSon( RB_Node * node);

            bool Delete (  const long _ID );
            void DeleteFixUp ( RB_Node* node);
            RB_Node* Successor( RB_Node * node);
            RB_Node * Predecessor ( RB_Node * node);
            void CounterBinding( RB_Node* node1, RB_Node* node2);

           long num_Node ( RB_Node* node);
           RB_Node* Search( const long _ID);
           RB_Node* FindSplitNode ( RB_Node* node, long _ID1, long _ID2 );

           RB_Node* InitializingRBTree(vector<RB_Node*>::iterator Start, vector<RB_Node*>::iterator End,RB_Node *m_ParentNode, int h);

    public:
           RedBlackTree();
           virtual ~RedBlackTree();

           void initialize ( const char * file );
           void PrintTree();

           void Increase ( long _ID, unsigned  int m);
           void Reduce ( long _ID ,   unsigned int m );
           void Count ( long _ID );
           void InRange ( long _ID1, long _ID2 );
           void Next ( long _ID );
           void Previous ( long _ID );
};

#endif // REDBLACKTREE_H
