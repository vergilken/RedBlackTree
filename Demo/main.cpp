#include "RedBlackTree.h"

using namespace std;

  int main(int argc, const char *argv[])
{
  const char* file1 = argv[1];
  RedBlackTree myTree ;
  myTree.initialize(file1);

  if ( !cin )
 {
   cout<<"The command file does not exist."<<endl;
   return 0;
 }
  string str;
  long a,c = 0;
  int b =0;

  while ( !cin.eof() )
  {
    cin >> str;
    if ( str == "increase"  )
    {
        cin >> a ;
        cin >> b;
        myTree.Increase ( a, b);
    }
    else if ( str == "reduce" )
    {
        cin >> a;
        cin >> b;
        myTree.Reduce ( a, b );
    }
    else if ( str == "count")
    {
        cin >> a;
        myTree.Count ( a );
    }

    else if ( str == "inrange")
    {
        cin >> a;
        cin >> c;
        myTree.InRange ( a, c );
    }

    else if ( str == "next")
    {
        cin >> a;
        myTree.Next( a );
    }

    else if ( str == "previous")
    {
        cin >> a;
        myTree.Previous( a );
    }

    else if ( str == "quit" )
    {
       ;
    }
  }

  //myTree.InRange(27,88);
  return 0;
}
