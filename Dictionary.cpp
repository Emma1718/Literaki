#include "Dictionary.h"

using namespace std;

Dictionary::Dictionary(string filename_dict)
{
  ifstream read_file(filename_dict.c_str(), ifstream::in );
  string s;
  
  while (read_file>>s)
    {
      this->words.insert(s); 
    }
  read_file.close();
}

bool Dictionary::checkWord(string word )
{

  set<string>::iterator iter;
  
  iter = this->words.find(word);

  if (iter==this->words.end ())
    return false;
  else
    return true;
}

void Dictionary::ShowD()
{
  set <string>::iterator it;
  for(it=this->words.begin();it!=this->words.end();it++)
    cout<<(*it)<<endl;
}
