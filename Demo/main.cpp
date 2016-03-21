#include "RedBlackTree.h"

using namespace std;

  int main(int argc, const char *argv[])
{
  const char* file1 = argv[1];
  RedBlackTree myTree ;
  myTree.initialize(file1);

  const char * file2= argv[2];
  ifstream fin (file2);
  const char * file3 = argv[3];
  ofstream fout(argv[3]); 
  streambuf *cinbackup; 
  streambuf *coutbackup;
  cinbackup= cin.rdbuf(fin.rdbuf()); 
  coutbackup = cout.rdbuf(cout.rdbuf());

  if ( !fin )
 {
   cout<<"The command file does not exist."<<endl;
   return 0;
 }
  string str;
  long a,c = 0;
  int b =0;

  while ( !fin.eof() )
  {
    fin >> str;
    if ( str == "increase"  )
    {
        fin >> a ;
        fin >> b;
        myTree.Increase ( a, b);
    }
    else if ( str == "reduce" )
    {
        fin >> a;
        fin >> b;
        myTree.Reduce ( a, b );
    }
    else if ( str == "count")
    {
        fin >> a;
        myTree.Count ( a );
    }

    else if ( str == "inrange")
    {
        fin >> a;
        fin >> c;
        myTree.InRange ( a, c );
    }

    else if ( str == "next")
    {
        fin >> a;
        myTree.Next( a );
    }

    else if ( str == "previous")
    {
        fin >> a;
        myTree.Previous( a );
    }

    else if ( str == "quit" )
    {
        cin.rdbuf(cinbackup);
	cout.rdbuf(coutbackup); 
    }
  }

  //myTree.InRange(27,88);
  return 0;
}
