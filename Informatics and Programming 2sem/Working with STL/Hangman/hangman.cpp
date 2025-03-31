#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>

using namespace std;

void pr(string *res, char *arr, int n) {
  setlocale(LC_ALL, "RUS");
  for (int i = 0; i < n; i++)
    cout << res[i] << " ";
  cout << endl;
  for (char ch = 'a'; ch <= 'z'; ch++) {
    cout << arr[ch] << " ";
  }
  cout << endl;
}

int main() {
  // setlocale(LC_ALL, "RUS");
  vector<string> words = {
      "abscissa",    "television",   "disorder",      "psychology",
      "informatics", "experiment",   "entertainment", "mathematics",
      "computer",    "organization", "ability",       "directory",
      "company",     "volleyball",   "collaboration", "instrument",
      "education",   "behavior",     "conference"};
  int n = words.size();
  srand(time(NULL));
  int num = rand() % (n + 1);
  string w = words[num];
  int k = w.length();
  string *res = new string[k];
  for (int i = 0; i < k; i++)
    res[i] = "_";
  char *arr = new char[126];
  for (char ch = 'a'; ch <= 'z'; ch++) {
    arr[ch] = ch;
  }
  pr(res, arr, k);
  int xod = 7;
  cout << "Number of moves: " << xod << endl;
  while (xod != 0) {
    cout << "Will you enter the whole word? (y or n) ";
    char yn;
    cin >> yn;
    if (yn == 'y') {
      cout << "Word:";
      string sl;
      cin >> sl;
      if (sl == w)
        cout << "Victory:)";
      else
        cout << "Loss:(, the right word is " << w;
      break;
    }
    cout << "There " << xod << " moves left" << endl;
    cout << "Letter: ";
    char b;
    cin >> b;
    if (w.find(b) == -1) {
      arr[b] = '-';
      xod--;
      cout << "Mistake" << endl;
      pr(res, arr, k);
    } else if (yn == 'n') {
      for (int i = 0; i < k; i++)
        if (w[i] == b) {
          arr[b] = '-';
          res[i] = b;
        }
      pr(res, arr, k);
    }
    int j = 0;
    for (int i = 0; i < k; i++)
      if (res[i] == "_")
        j++;
    if (j == 0) {
      cout << "Victory:)";
      break;
    }
    if (j != 0 && xod == 0)
      cout << "Loss:(, the right word is " << w;
  }
}
