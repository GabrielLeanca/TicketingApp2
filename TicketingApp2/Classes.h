#pragma once

#include <iostream>
#include <string>
#include <random>
using namespace std;

enum ticketType {
	VIP, CATEGORY1, CATEGORY2, CATEGORY3, OTHER
};

ostream& operator<<(ostream& console, ticketType type) {
	switch (type)
	{
	case VIP:
		console << "VIP";
		break;
	case CATEGORY1:
		console << "CATEGORY1";
		break;
	case CATEGORY2:
		console << "CATEGORY2";
		break;
	case CATEGORY3:
		console << "CATEGORY3";
		break;
	default:
		console << "OTHER";
	}
	return console;
}

class Event;
class Ticket;

