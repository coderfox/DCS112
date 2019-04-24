#include <iostream>
#include <string>
#include "SimpleList.hpp"
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

int main1()
{
  freopen("in2", "r", stdin);
  freopen("out2_my", "w", stdout);
  list li;

  int n;
  cin >> n;

  for (int i = 0, data, pos; i < n; i++)
  {
    cin >> pos >> data;
    li.insert(pos, data);
  }

  cout << li.toString() << " size: " << li.size() << endl;

  list li2(li);
  list li3;

  li = li3 = li2 = li;

  cout << li.toString() << " size: " << li.size() << endl;
  cout << li2.toString() << " size: " << li2.size() << endl;
  cout << li3.toString() << " size: " << li3.size() << endl;

  int m;
  cin >> m;

  for (int i = 0, pos; i < m; i++)
  {
    cin >> pos;
    li.erase(pos);
  }

  cout << li.toString() << endl;

  cout << li.sort().toString() << endl;
  cout << li2.sort().toString() << endl;
  cout << li3.sort().toString() << endl;

  return 0;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &v)
{
  if (!v.empty())
  {
    // out << '[';
    std::copy(v.begin(), v.end(), std::ostream_iterator<T>(out, "->"));
    out << "NULL";
  }
  return out;
}

int main2()
{
  freopen("in2", "r", stdin);
  freopen("out2", "w", stdout);
  vector<int> li;

  int n;
  cin >> n;

  for (int i = 0, data, pos; i < n; i++)
  {
    cin >> pos >> data;
    if (pos > li.size())
      continue;
    li.insert(li.begin() + pos, data);
  }

  cout << li << " size: " << li.size() << endl;

  vector<int> li2(li);
  vector<int> li3;

  li = li3 = li2 = li;

  cout << li << " size: " << li.size() << endl;
  cout << li2 << " size: " << li2.size() << endl;
  cout << li3 << " size: " << li3.size() << endl;

  int m;
  cin >> m;

  for (int i = 0, pos; i < m; i++)
  {
    cin >> pos;
    li.erase(li.begin() + pos);
  }

  cout << li << endl;

  sort(li.begin(), li.end());
  sort(li2.begin(), li2.end());
  sort(li3.begin(), li3.end());
  cout << li << endl;
  cout << li2 << endl;
  cout << li3 << endl;

  return 0;
}

int main()
{
  main1();
  main2();
  return 0;
}