#include "List_dynamic_array.h"

#include <iostream>
#include <cassert>

using namespace std;

List_dynamic_array::List_dynamic_array()
{
        cards = new Card[INITIAL_CAPACITY];
        hand_capacity = INITIAL_CAPACITY;
        cards_held = 0;
}

List_dynamic_array::~List_dynamic_array()
{
        delete [] cards;
}

/*
 * explicit copy constructor necessary because of pointer to cards
 * array 
 */
List_dynamic_array::List_dynamic_array(const List_dynamic_array &source)
{

	cards_held    = source.cards_held;
	hand_capacity = source.hand_capacity;

	cards = new Card[hand_capacity];
	for (int i = 0; i < cards_held; i++) {
		cards[i] = source.cards[i];
	}
}

/*
 * explicit operator= overload necessary because of pointer to cards
 * array
 */
List_dynamic_array
List_dynamic_array::operator=(const List_dynamic_array &source)
{
	Card *new_cards;

	// check for self-assignment -- return without doing anything
	if (this == &source) {
		return *this;
	}

	hand_capacity = source.hand_capacity;
	cards_held    = source.cards_held;
	new_cards     = new Card[hand_capacity];

	for (int i = 0; i < hand_capacity; i++) {
		new_cards[i] = source.cards[i];
	}
	delete [ ] cards;
	cards = new_cards;
	return *this;
}

bool List_dynamic_array::is_empty()
{
        return cards_held == 0;
}

void List_dynamic_array::make_empty()
{
        cards_held = 0;
}


int List_dynamic_array::cards_in_hand()
{
        return cards_held;
}

void List_dynamic_array::print_list()
{
	for (int i = 0; i < cards_held; i++) {
		cards[i].print_card();
		if (i != cards_held - 1) {
			cout << ", ";
		} else {
			cout << "\n";
		}
	}
}

void List_dynamic_array::print_list_int()
{
	for (int i = 0; i < cards_held; i++) {
		cards[i].print_card_int();
		if (i != cards_held - 1) {
			cout << ", ";
		} else {
			cout << "\n";
		}
	}
}

void List_dynamic_array::insert_at_front(Card c)
{
	if(cards_held >= hand_capacity) {
		//index = 0 indicates inserting the card at front
		insert_in_hand(0);
		cards[0] = c;
	}
}

void List_dynamic_array::insert_at_back(Card c)
{
	if(cards_held >= hand_capacity) {
		//index = -1 indicates inserting the card at back
		insert_in_hand(-1);
		cards[cards_held - 1] = c;

	}
}

void List_dynamic_array::insert_at_index(Card c,int index)
{
	// if index is greater than cards_held, then fail
	assert(index <= cards_held);

	if(cards_held >= hand_capacity) {
		//index indicates where to insert the card
		insert_in_hand(index);
		cards[index] = c;
	}
}

void List_dynamic_array::replace_at_index(Card c, int index)
{
	// if index is greater than cards_held-1, then fail
	assert(index < cards_held);
	cards[index] = c;
}

Card List_dynamic_array::card_at(int index)
{
	// if index is out of bounds, fail
	assert (index >= 0 && index < cards_held);
	return cards[index];
}

bool List_dynamic_array::has_card(Card c)
{
	for(int i = 0; i < cards_held; i++) {
		if(cards[i].same_card(c) == true) {
			return true;
		}
	}
	return false;
}

bool List_dynamic_array::remove(Card c)
{
	for(int i = 0; i < cards_held; i++) {
		if(cards[i].same_card(c) == true) {
			--cards_held;
			for(int j = i; j < cards_held; j++) {
				cards[i] = cards[i+1];
			}
			return true;
		}
	}
	return false;
}

Card List_dynamic_array::remove_from_front()
{
	// if the list is empty, fail
	assert(cards_held > 0);

	--cards_held;
	Card first_card = cards[0];

	for(int i = 0; i < cards_held; i++) {
		cards[i] = cards[i+1];
	}
	return first_card;
}

Card List_dynamic_array::remove_from_back()
{
	// if the list is empty, fail
	assert(cards_held > 0);

	--cards_held;
	return cards[cards_held];

}

Card List_dynamic_array::remove_from_index(int index)
{
	--cards_held;
	Card index_card = cards[index];

	for(int i = index; i < cards_held; i++) {
		cards[i] = cards[i+1];
	}
	return index_card;
	
}

void List_dynamic_array::insert_in_hand(int index)
{
	++cards_held;
	int new_capacity = (hand_capacity * 2);
	Card * temp_hand = new Card[new_capacity];

	int index_mod = 0;
	for(int i = 0; i < cards_held; i++) {

		//where the card is copied to depends on the shift
		//front: index is 0. Index_mod shifts everything 1
		//end: index is -1. i will never be -1. No shift
		//index: shift will occur at index

		if(i == index) {
			index_mod = 1;
		}
		temp_hand[i + index_mod] = cards[i];
	}

	delete [] cards;
	cards = temp_hand;
}
