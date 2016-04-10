#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

void readFreq(vector<int> &frequencies)
{
  ifstream inf("frequencies");
  int temp;

  for (int f = 0; f < 26; f++)
  {
    inf >> temp;
    frequencies.push_back(temp);
  } // for every letter's frequency value

  inf.close();
} // readFreq() reads frequency values from english alphabet

int countFreq(vector<int>& cvec, const string &str)
{
  char letteru = 'A';
  char letterl = 'a';
  int countl = 0;
  int countu = 0;

  while (letteru <= 'Z' && letterl <= 'z')
  {
    countl = count(str.begin(), str.end(), letterl);
    countu = count(str.begin(), str.end(), letteru);
    cvec.push_back(countu + countl);
    letteru++;
    letterl++;

    //cout << "count " << countu + countl << endl;
  } // go through the alphabet

  return (countu + countl);
} // countFreq()

class Attempt
{
  int shift;
  int lh;
public:

  Attempt(int shif, int l) : shift(shif), lh(l)
  {
  }; // constructor

  bool operator<(const Attempt &rhs) const
  {
    //cout << "LHS: " << lh << " RHS: " << rhs.lh << endl;
    return (lh < rhs.lh);
  } // operator<()

  int getLH() const
  {
    return lh;
  } // getLH()

  int getShift() const
  {
    return shift;
  } // int getShift()

  void print()
  {
    cout << "The shift is " << shift << " and the likelyhood is " << lh << endl;
  } // print()
}; // class Atempt

void readInput(stringstream& s, ifstream& f)
{
  if (f)
  {
    s << f.rdbuf();
    f.close();
  } // if file is valid
} // readInput()

void shift(string &str, int n)
{
  for (string::iterator sit = str.begin(); sit != str.end(); sit++)
  {

    if (isalpha(*sit))
    {
      if (*sit == 'z')
        *sit = 'a';
      else if (*sit == 'Z') //this is else if
        *sit = 'A';
      else // if not a or z
      {
        *sit = *sit + n;
      } // if not a or z
    } // if letter  

  } // iterate thru string
}

void shift1(string str, int n)
{
  for (int s = 0; s <= n; s++)
  {
    for (string::iterator sit = str.begin(); sit != str.end(); sit++)
    {

      if (isalpha(*sit))
      {
        if (*sit == 'z')
          *sit = 'a';
        else if (*sit == 'Z')
          *sit = 'A';
        else
        {
          *sit = *sit + 1;
        }

      }

    }
  }
  cout << str << endl;
} // Shift

int main(int argc, char** argv)
{
  vector<Attempt> attemptList;
  vector<int> frequencies;
  stringstream s;
  ifstream f(argv[1]);

  readFreq(frequencies);
  readInput(s, f);


  string str = s.str();
  //cout << str << endl;
  for (int s = 0; s < 26; s++)
  {
    shift(str, 1);

    //cout << str;

    int count_lower, count_upper, count_total;

    char letter_lower = 'a';
    char letter_upper = 'A';
    vector<int> countvec;
    int likelyhood = 0;

    for (int i = 0; i <= 26; i++)
    {
      count_lower = count(str.begin(), str.end(), letter_lower + i);
      count_upper = count(str.begin(), str.end(), letter_upper + i);
      count_total = count_lower + count_upper;
      countvec.push_back(count_total);
    }

    for (int k = 0; k < (int) countvec.size() - 1; k++)
    {
      //cout<< "coutvec[" << k << "] -> " << countvec[k] << endl;
      // cout << "frequencies[" << k << "] -> " << frequencies[k] << endl;
      likelyhood += countvec.at(k) * frequencies.at(k);
    } // for every shift -> likelyhood


    attemptList.push_back(Attempt(s, likelyhood));

  }
  sort(attemptList.begin(), attemptList.end());
  //selectSort(attemptList);

  //vector<Attempt>::iterator vit;
  //for(vit = attemptList.begin();vit != attemptList.end(); vit++)
  // {
  //  cout << vit->getLH() << endl ;
  //}
  int count = 1;
  for (vector<Attempt>::reverse_iterator lit = attemptList.rbegin(); lit != attemptList.rbegin() + 6; lit++)
  {
    cout << "Deciphered message version #" << count << endl;
    {
      shift1(str, lit->getShift());
      count++;
      //cout << str << endl;
    }
  }
  return 0;
} // main()


