#ifndef CARD_H_
#define CARD_H_

#include <iostream>
#include <string>

struct Card{
    int id;
    enum class Suit { Hearts, Diamonds, Clubs, Spades };
    enum class Rank { Two = 2, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace };

    Suit suit;
    Rank rank;
    bool faceUp;

    Card(int CardID, Suit s, Rank r, bool f = false);
    std::string toString() const;
};

#endif