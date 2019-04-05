#include <sstream>
#include "card.hpp"

using namespace std;

const char *Card::faceNames[13] = {
    "Ace",
    "Deuce",
    "Three",
    "Four",
    "Five",
    "Six",
    "Seven",
    "Eight",
    "Nine",
    "Ten",
    "Jack",
    "Queen",
    "King",
};
const char *Card::suitNames[4] = {
    "Hearts",
    "Diamonds",
    "Clubs",
    "Spades",
};

// a) Data members face and suit of type int.The range of face is [0,12],and the range of suit is [0,3].
//
// b) A constructor that receives two ints representing the face and suit and uses them to initialize the data members.
//
// c) Two static arrays of strings representing the faces and suits (which will be given below).
//
// d) A toString function that returns the Card as a string in the form "face of suit".

Card::Card(int cardFace, int cardSuit) : face(cardFace),
                                         suit(cardSuit)
{
}
std::string Card::toString() const
{
    stringstream ss;
    ss << '[' << face << ':' << suit << ']' << faceNames[face] << " of " << suitNames[suit];
    return ss.str();
}
int Card::getFace() const
{
    return face;
}
int Card::getSuit() const
{
    return suit;
}