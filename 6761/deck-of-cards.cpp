#include "deck-of-cards.hpp"

using std::vector;

DeckOfCards::DeckOfCards()
{
    deck = vector<Card>();
    currentCard = 0;
    for (int suit = 0; suit < Card::totalSuits; suit++)
    {
        for (int face = 0; face < Card::totalFaces; face++)
        {
            deck.push_back(Card(face, suit));
            currentCard++;
        }
    }
}
Card DeckOfCards::dealCard()
{
    return deck[Card::totalFaces * Card::totalSuits - (currentCard--)];
}
bool DeckOfCards::moreCards() const
{
    return currentCard != 0;
}