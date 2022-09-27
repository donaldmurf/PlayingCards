#include<iostream>
#include<string>
#include<stdint.h>
#include<stack>
#include<chrono>
#include<random>
#include<vector>
#include<algorithm>

using namespace std;

//A class which represents a deck of cards with utility functions.
class CardDeck {
	struct Card;//Forward declaration of card structure.
private:
	//Deck container.
	vector<Card> Deck;
public:
	const uint8_t  FULL_DECK = 52;
	//The suit of the card.
	enum SUIT { SPADE, CLUB, HEART, DIAMOND };

	//The value of the cards. Non-face cards are represented by their inherent value.
	enum CARDVALUE { ACE = 1, JACK = 11, QUEEN = 12, KING = 13 };

	//Card representation.
	struct Card {
		SUIT Suit;
		CARDVALUE value;
	};

	//Shuffles deck using the mersenne twister algorithm.
	void shuffleDeck() {
		auto seed = chrono::system_clock::now().time_since_epoch().count();
		mt19937_64 generator(seed);

		shuffle(Deck.begin(), Deck.end(), generator);
	};

	//Constructor generates deck and shuffles it.
	CardDeck() {
		for (uint8_t i = CARDVALUE::ACE; i <= CARDVALUE::KING; i++) {
			for (uint8_t j = SUIT::SPADE; j <= SUIT::DIAMOND; j++) {
				Card card;
				card.Suit = (SUIT)j;
				card.value = (CARDVALUE)i;

				Deck.push_back(card);
			}
		}
		shuffleDeck();
	};

	//Overloads the stream operator and prints the deck.
	friend ostream& operator<<(ostream& os, const CardDeck& deck) {
		for (auto i : deck.Deck) {
			switch (i.Suit)
			{
			case SUIT::SPADE:
				os << "Spade";
				break;
			case SUIT::CLUB:
				os << "Club";
				break;
			case SUIT::HEART:
				os << "Heart";
				break;
			case SUIT::DIAMOND:
				os << "Diamond";
				break;
			}

			os << "\t";

			switch (i.value) {
			case CARDVALUE::ACE:
				os << "Ace";
				break;
			case CARDVALUE::JACK:
				os << "Jack";
				break;
			case CARDVALUE::QUEEN:
				os << "Queen";
				break;
			case CARDVALUE::KING:
				os << "King";
				break;
			default:
				os << i.value;
				break;
			}

			os << endl;
		}
		return os;
	};

	//Adds 2 decks and copies them into return deck.
	CardDeck operator+(const CardDeck& addDeck) {
		CardDeck doubleDeck;
		doubleDeck.Deck.clear();
		doubleDeck.Deck.insert(doubleDeck.Deck.end(), addDeck.Deck.begin(), addDeck.Deck.end());
		doubleDeck.Deck.insert(doubleDeck.Deck.end(), Deck.begin(), Deck.end());
		return doubleDeck;
	}

	//Returns size of deck container.
	int getDeckSize() {
		return Deck.size();
	}

	void addDeck(CardDeck x) {
		Deck.insert(Deck.end(), x.Deck.begin(), x.Deck.end());
	}

	CardDeck(uint64_t numDecks) {
		for (int i = 0; i < numDecks; i++) {
			CardDeck x;
			addDeck(x);
		}
		shuffleDeck();
	}
};

class BlackJack {

	CardDeck Deck;
	int players;

public:
	BlackJack(int players) {
		this->players = players;
	}
	BlackJack() : BlackJack(1) {

	}
};

int main() {

	BlackJack onePlayer;
	BlackJack twoplayer(2);



	/*
	CardDeck testDeck;
	CardDeck SecDeck;
	CardDeck BiggyDeck = testDeck + SecDeck;

	cout << BiggyDeck << "\n";
	cout << "Total cards in deck: " << BiggyDeck.getDeckSize() << endl;*/

	system("pause");
	return 0;
}