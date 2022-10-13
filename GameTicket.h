/*
 * FlightTicket.h
 *
 *      Author: dongmo
 */

#ifndef GAMETTICKET_H_
#define GAMEHTTICKET_H_

class GameTicket: public Ticket {
private:
    int gameId; // gameId
public:
	// d is valid day for game
    GameTicket(int id) :
            Ticket(gameDayMap[id], gamePriceMap[id]) { // set valid day and full price as game price
        gameId = id;
        // set the discount
        discount = 0;
    }
	char* getGameName(int id)
	{
		return (char *)nameMap[id].c_str();
	}
	
    void printTicket() {
    	
        cout << "Game Name" << nameMap[gameId] << " on day " << day
                << " at price $" << getTicketPrice() << endl;
    }
};

#endif /* FLIGHTTICKET_H_ */
