#include "RedBlackTree.h"
RedBlackTree ::  RedBlackTree()
    {
      m_nullNode = new RB_Node();
      m_root = m_nullNode;
      m_nullNode->right = m_root;
      m_nullNode->left = m_root;
      m_nullNode->parent = m_root;
      m_nullNode->RB_COLOR = BLACK;          // default  = BLACK
    }

RedBlackTree :: ~RedBlackTree()
    {
        clear (m_root);
        delete m_nullNode;
    }

long RedBlackTree::num = 0;

bool RedBlackTree::isRightSon( RB_Node* node )
{
    return node -> parent -> right == node ? true: false;
}

bool RedBlackTree::isLeftSon( RB_Node* node )
{
  return node -> parent -> left == node ? true : false;
}


 void RedBlackTree :: clear( RB_Node* node)
 {
   if ( node != m_nullNode)
   {
    clear( node -> left );
    clear ( node -> right );
    delete node;
   }
 }

 void RedBlackTree :: CounterBinding ( RB_Node* node1, RB_Node* node2 )
 {
     node1 -> ID = node2 -> ID;
     node1 -> count = node2 -> count;
 }

void RedBlackTree :: reset()
{
    m_nullNode->left = m_root;
    m_nullNode->right = m_root;
    m_root -> RB_COLOR = BLACK;
}

RB_Node* RedBlackTree :: Search( const long _ID)
    {
      RB_Node* index = m_root;
      if ( index== m_nullNode)
        return index;
      while( index != m_nullNode && index-> ID != _ID)
    {
     if ( _ID < index->ID) index = index -> left;
    else if ( _ID > index->ID ) index = index -> right;
    }
      return index;
    }

bool RedBlackTree :: LeftRotate(RB_Node* node)
{
  if ( node == m_nullNode && node -> right == m_nullNode) return false;
  RB_Node * z = node -> right;
  z ->parent = node ->parent;
  node -> right = z -> left;
  if ( z-> left != m_nullNode)
    z-> left->parent = node;

  if ( node -> parent == m_nullNode )                                      // node = m_root
  {
      m_root = z;
      reset();                                                                                          //m_nullNode->parent = m_root
  }
  else if ( isLeftSon( node ))
    node -> parent-> left = z;
  else if( isRightSon( node ) )
    node -> parent ->right = z;
  node -> parent = z;
  z -> left = node;
  return true;
}

bool RedBlackTree :: RightRotate(RB_Node* node)
{
  if ( node == m_nullNode || node -> left == m_nullNode ) return false;
   RB_Node * z = node -> left;
   node -> left = z -> right;
   z -> parent = node -> parent;
   if ( z -> right != m_nullNode ) z-> right -> parent = node;
   if ( node -> parent == m_nullNode )
   {
       m_root =  z;
       reset();
   }
   else if ( isRightSon( node )  )
    node -> parent -> right = z;
   else if ( isLeftSon( node ) )
    node ->parent -> left = z;
   node -> parent = z;
   z -> right = node;
   return true;
}

void RedBlackTree :: initialize(const char * file)
    {
        ifstream fin(file);
        if ( !fin )
        {
            cout<<"The file does not exist."<<endl;
            return ;
        }
        long idata;
        int idata1;
        fin >> idata;

     while (!fin.eof())
    {
        fin >> idata;
        if(fin.eof()) break;
        fin >> idata1;
        RB_Node* node= new RB_Node();
        node->ID = idata;
        node->count = idata1;
        pair_vector.push_back(node);
    }
     fin.close();

    int h = 0;
    num = pair_vector.size();
    m_root = InitializingRBTree(pair_vector.begin(), pair_vector.end()-1,m_nullNode, h);
    vector<RB_Node*>().swap(pair_vector);
    }

  RB_Node* RedBlackTree :: InitializingRBTree( vector<RB_Node*>::iterator Start, vector<RB_Node*>::iterator End,RB_Node *m_ParentNode, int h)
{
   if(Start>End) return m_nullNode;
    ++h;
   auto mid = Start+ (End-Start)/2;
   (*mid)->parent = m_ParentNode;
   (*mid)->left =  InitializingRBTree(Start, mid - 1,*mid, h);
   (*mid)->right = InitializingRBTree(mid+1,End, *mid,h);
    if ( pow( 2, h) - 1 > num )
         (*mid)->RB_COLOR = RED;
    return *mid;
}

void RedBlackTree::PrintTree()
{
    preOrder(m_root, 1);
}

void RedBlackTree :: preOrder(RB_Node* node, int index)
{
    if(node != m_nullNode)
    {
    cout<<node->ID<<"         ";
    cout<<node->count<<"             "<<node->RB_COLOR<<"        "<<index<<endl;
    index++;
    preOrder(node->left, index);
    preOrder(node->right, index);
    }
}

bool RedBlackTree :: Insert(  long _ID,  int _count)
{
    RB_Node* insert_location;
    RB_Node* index;
    index = m_root;
    while( index != m_nullNode)
    {
        insert_location = index;
        if( _ID < index-> ID) index = index -> left;
        else if( _ID > index -> ID)  index =  index -> right;
    }
     RB_Node* insert_node = new RB_Node( RED, m_nullNode, m_nullNode, m_nullNode, _ID, _count);
     ++num;
     if (insert_location != m_nullNode )
     {
         if ( _ID < insert_location -> ID)
            insert_location->left = insert_node;
         else if ( _ID > insert_location -> ID)
            insert_location->right = insert_node;
            insert_node -> parent = insert_location;
     }
     else if ( insert_location == m_nullNode )
     {
        m_root = insert_node;
        m_nullNode -> left = insert_node;
        m_nullNode -> right =  insert_node;
        m_nullNode -> parent = insert_node;
     }
     pair_vector.push_back( insert_node );
      InsertFixUp( insert_node);
      return true;
}

void RedBlackTree :: InsertFixUp ( RB_Node* node)
{
    while ( node -> parent -> RB_COLOR == RED )
    {
       if( isLeftSon( node -> parent ) )
       {
           RB_Node* uncle = node -> parent -> parent -> right;
            if ( uncle -> RB_COLOR == RED)
            {
                node->parent-> RB_COLOR = BLACK;
                uncle -> RB_COLOR = BLACK ;
                uncle -> parent -> RB_COLOR = RED;
                node = node-> parent -> parent;
            }
            else if ( uncle -> RB_COLOR == BLACK )
                {
                if ( isRightSon( node ))
                {
                    node = node -> parent;
                    LeftRotate( node );
                }
                else
                {
                    node -> parent -> RB_COLOR = BLACK;
                    node -> parent -> parent -> RB_COLOR =RED;
                    RightRotate( node -> parent -> parent );
                }
            }
       }

            else
            {
                RB_Node* uncle = node -> parent -> parent -> left;
                if ( uncle -> RB_COLOR == RED)
                {
                    node -> parent -> RB_COLOR = BLACK;
                    uncle -> RB_COLOR = BLACK;
                    uncle -> parent -> RB_COLOR = RED;
                    node = node -> parent -> parent;
                }
                else if ( uncle -> RB_COLOR == BLACK )
                {
                    if ( isLeftSon( node ))
                    {
                        node = node -> parent;
                        RightRotate( node );
                    }
                    else
                    {
                        node ->parent -> RB_COLOR = BLACK;
                        node -> parent ->parent -> RB_COLOR = RED;
                        LeftRotate( node -> parent -> parent );
                    }
                }
            }
    }
    reset();
}

RB_Node * RedBlackTree :: Successor ( RB_Node * node)       // searching for successor for  BST Tree node
{
    if ( node == m_nullNode) return m_nullNode;
    RB_Node * successor_node = node -> right;
    while ( successor_node != m_nullNode )
    {
        if ( successor_node -> left != m_nullNode ) successor_node = successor_node -> left;
        else break;
    }
    if ( successor_node == m_nullNode )
    {
        RB_Node* index = node -> parent;
        successor_node = node;
        while ( index != m_nullNode && isRightSon( successor_node ))
        {
            successor_node = index;
            index = index -> parent;
        }
        successor_node = index;
    }
   return successor_node;
}

RB_Node * RedBlackTree :: Predecessor ( RB_Node * node)       // searching for predecessor for  BST Tree node
{
    if ( node == m_nullNode) return m_nullNode;
    RB_Node * predecessor_node = node -> left;
    while ( predecessor_node  != m_nullNode )
    {
        if ( predecessor_node  -> right != m_nullNode ) predecessor_node  = predecessor_node  -> right;
        else break;
    }
    if ( predecessor_node  == m_nullNode )
    {
        RB_Node* index = node -> parent;
        predecessor_node  = node;
        while ( index != m_nullNode && isLeftSon( predecessor_node  ))
        {
            predecessor_node  = index;
            index = index -> parent;
        }
        predecessor_node  = index;
    }
   return predecessor_node ;
}

bool RedBlackTree :: Delete (  const long _ID )
{
   if ( _ID <=0 )return false;
   RB_Node* index = new RB_Node();
   index = Search (  _ID );
   if ( index == m_nullNode) return false;
   if ( index -> left != m_nullNode && index ->right != m_nullNode )
   {
       RB_Node* SuccessorNode = Successor( index );
       CounterBinding( index, SuccessorNode);
       index = SuccessorNode;
   }
   RB_Node* index_child = new RB_Node ();
   if ( index -> left != m_nullNode )index_child = index -> left;
   else if ( index -> right != m_nullNode ) index_child = index -> right;
   else index_child = m_nullNode;
   index_child -> parent = index -> parent;
   if( index_child -> parent == m_nullNode )
   {
       m_root = index_child;
       reset();
       m_nullNode -> parent = m_root;
   }
   else if ( isRightSon( index ))
    index->parent -> right = index_child;
   else if ( isLeftSon( index ))
    index -> parent -> left = index_child;
   if ( index ->RB_COLOR == BLACK && index_child != m_nullNode &&index -> parent != m_nullNode )
    DeleteFixUp ( index_child );
    delete index;
    index = m_nullNode;
    return true;
}

void RedBlackTree :: DeleteFixUp ( RB_Node * node)
{
  while ( node != m_root && node -> RB_COLOR == BLACK)
  {
      if( isLeftSon( node ) )
      {
         RB_Node* brother = node -> parent -> right;
         if ( brother -> RB_COLOR == RED )                                                                                                              //case 1
         {
             brother -> RB_COLOR = BLACK;
             brother -> parent ->RB_COLOR =RED;
             LeftRotate( brother -> parent);
         }
         else if ( brother -> RB_COLOR == BLACK )
         {
            if ( brother -> left ->RB_COLOR == BLACK && brother -> right -> RB_COLOR == BLACK )             //case 2
            {
                brother -> RB_COLOR = RED;
                node = brother -> parent;
            }
            else if ( brother -> left -> RB_COLOR == RED && brother -> right -> RB_COLOR == BLACK)  //case 3
            {
                brother -> left -> RB_COLOR = BLACK;
                brother -> RB_COLOR = RED;
                RightRotate( brother );
            }
            else if ( brother -> right -> RB_COLOR == RED)                                                                                   //case 4
            {
                brother -> RB_COLOR = brother -> parent ->RB_COLOR ;
                brother -> parent -> RB_COLOR = BLACK;
                brother -> right -> RB_COLOR = BLACK;
                LeftRotate( brother -> parent );
                node = m_root;
            }
         }
      }

      else if ( isRightSon( node ))
      {
          RB_Node* brother = node -> parent -> left;
          if ( brother -> RB_COLOR == RED)
          {
              brother -> RB_COLOR = BLACK;
              node -> parent -> RB_COLOR = RED;
              RightRotate( node -> parent );
          }
          else if ( brother -> RB_COLOR == BLACK )
          {
              if ( brother->left->RB_COLOR==BLACK && brother->right->RB_COLOR == BLACK)
              {
                  brother -> RB_COLOR = RED;
                  node = node -> parent;
              }
              else if ( brother -> left -> RB_COLOR == RED &&brother -> right -> RB_COLOR ==BLACK )
              {
                  brother -> RB_COLOR = RED;
                  brother -> left -> RB_COLOR = BLACK;
                  LeftRotate( brother );
              }
              else if ( brother -> right -> RB_COLOR == RED )
              {
                  brother -> RB_COLOR = brother -> parent -> RB_COLOR;
                  brother -> parent -> RB_COLOR = BLACK;
                  brother -> right -> RB_COLOR = BLACK;
                  LeftRotate( brother -> parent );
                  node = m_root;
              }
          }
      }
  }
m_root -> RB_COLOR = BLACK;
}

void RedBlackTree :: Increase ( long _ID, unsigned int m )
{
    RB_Node* index = Search( _ID );
    if ( index != m_nullNode )
    {
        index -> count = index -> count + m;
        cout<< index  -> count <<endl;
    }
    else if ( index == m_nullNode)
    {
        Insert( _ID, m );
        cout<<  m <<endl;
    }
}

void RedBlackTree :: Reduce ( long _ID , unsigned int m )
{
    RB_Node* index = Search( _ID );
    if ( index == m_nullNode )
    {
        cout<<BLANK<<endl;
        return;
    }
    index -> count = index -> count - m;
    if ( index -> count > 0 )
        cout<<index -> count<<endl;
    else if ( index -> count <= 0)
    {
        Delete( _ID );
        cout<<BLANK<<endl;
    }
}

void RedBlackTree :: Count ( long _ID )
{
  RB_Node* index = Search( _ID );
  if ( index == m_nullNode )cout<<BLANK;
  else cout<<index -> count<<endl;
}

void RedBlackTree :: Next ( long _ID )
{
   RB_Node* index = Search( _ID );
   if ( index == m_nullNode)
   {
      Insert(  _ID, BLANK);
      Next ( _ID );
      Delete ( _ID );
      return ;
   }
   index = Successor ( index );
   if ( index == m_nullNode )cout<<BLANK<<' '<<BLANK<<endl;
   else cout<<index-> ID<< ' '<<index -> count<<endl;
}

void RedBlackTree :: Previous ( long _ID )
{
   RB_Node* index = Search( _ID );
   if ( index == m_nullNode)
   {
      Insert(  _ID, BLANK);
      Previous ( _ID );
      Delete ( _ID );
      return ;
   }
   index = Predecessor (index);
   if ( index == m_nullNode )cout<<BLANK<<' '<<BLANK<<endl;
   else cout<<index-> ID<< ' '<<index -> count<<endl;
}

RB_Node* RedBlackTree :: FindSplitNode ( RB_Node* node, long _ID1, long _ID2 )
{
    if ( node == m_nullNode )return m_nullNode;
    if ( _ID1 >= _ID2 ) return m_nullNode;
    if ( node -> ID >= _ID1 && node -> ID <= _ID2 ) return node;
    RB_Node* index = node;
    while (index != m_nullNode)
    {
        if ( index -> ID < _ID1) index = index -> right;
        else if ( index -> ID > _ID2) index = index -> left;
        else break;
    }
    return index;
}

long RedBlackTree :: num_Node ( RB_Node* node)
{
    if ( node == m_nullNode )return BLANK;
    else return  node->count + num_Node ( node -> left) + num_Node ( node ->right );
}

void RedBlackTree :: InRange ( long _ID1, long _ID2 )
{
   if ( _ID1 == _ID2)
   {
       RB_Node* node = Search(_ID1);
       if ( node == m_nullNode )
           cout <<BLANK << endl;
       else cout << node -> count << endl;
       return ;
   }
   RB_Node * node = FindSplitNode( m_root, _ID1, _ID2 );
   if ( node == m_nullNode )
   {
       cout<<BLANK<<endl;
       return;
   }

   else if ( node -> left == m_nullNode || node -> right == m_nullNode )
   {
    cout<< node -> count <<endl;
    return;
   }

   long num = node -> count ;
   RB_Node * node1 = node -> left;
     while ( node1 != m_nullNode )
   {
       if ( _ID1 <= node1-> ID )
       {
           num= num + num_Node( node1-> right) + node1 -> count;
           node1= node1 ->left;
       }
       else
       {
           node1 = node1 ->right;
       }
   }

 RB_Node * node2 = node -> right;
  while ( node2 != m_nullNode )
   {
       if ( _ID2 >= node2 -> ID )
       {
           num = num + num_Node( node2 -> left ) + node2 -> count;
           node2 = node2 -> right;
       }
       else
       {
           node2 = node2 -> left;
       }
   }

   cout<< num  << endl;
   return;
}


