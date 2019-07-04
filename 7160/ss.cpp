#include<iostream>
#include "source.h"
using namespace std;
void nature_complete(map<string, int> &nature);
void card_complete(vector<pair<string, int>>& card, map<string, int> &nature);
bool compare(pair<string,int> a, pair<string, int> b);
void print(vector<pair<string, int>> ::iterator begin, vector<pair<string, int>> ::iterator end);
int main()
{
	map<string, int> Nature;
	nature_complete(Nature);
	auto be = Nature.cbegin();
	vector<pair<string, int>> Card;
	card_complete(Card,Nature);
	sort(Card.begin(), Card.end(), compare);
	auto bbe = Card.begin();
	auto eend = Card.end();
	print(bbe, eend);
	getchar();
	getchar();
}
