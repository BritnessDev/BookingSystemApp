/*
 * FlightTicket.h
 *
 *      Author: dongmo
 */
#ifndef PACKAGE_H_
#define PACKAGE_H_

#define max_htTickets 10
#define max_gmTickets 15
class Package
{
private:
public:
	int clientID;
	FlightTicket *ftTickets[2];
	HotelVoucher *htTickets[max_htTickets];
	GameTicket *gmTickets[max_gmTickets];
    Package() {
    	int i;
    	clientID = -1;
    	ftTickets[0] = NULL; ftTickets[1] = NULL;
    	for(i = 0; i < max_htTickets; i++)
    		htTickets[i] = NULL;
    	for(i = 0; i < max_gmTickets; i++)
    		gmTickets[i] = NULL;
	}
	void addFlightTicket(int type, int day)
	{
		// fly_in ticket
		ftTickets[type] = new FlightTicket(type, day);
	}
	void addGameTicket(int gameType)
	{
		gmTickets[gameType] = new GameTicket(gameType);
	}
	
	void addHotelVoucher(string htName, int day, double discount)
	{
		htTickets[day] = new HotelVoucher(htName, day, discount);
	}
	
	~Package()
	{
		int i;
		free(ftTickets[0]); free(ftTickets[1]);
		for(i = 0; i < max_htTickets; i++)
			if(htTickets[i])
				free(htTickets[i]);
		for(i = 0; i < max_gmTickets; i++)
			if(gmTickets[i])
				free(gmTickets[i]);
	}
	
	void printPackage()
	{
		int i;
		cout << "Ticket Info" << endl;
		cout << "Departure date: " << ftTickets[0]->getDay() << endl;
		cout << "Arrival date: " << ftTickets[1]->getDay() << endl;
		cout << "Hotel Voucher Info" << endl;
		for(i = 0; i < max_htTickets; i++)
			if(htTickets[i])
				cout << "Day: " << htTickets[i]->getDay() << " Discount: " << htTickets[i]->getDiscount() << " Price: " << htTickets[i]->getTicketPrice() << endl;
		cout << "Game Ticket Info" << endl;
		for(i = 0; i < max_gmTickets; i++)
			if(gmTickets[i])
				cout << "Day: " << gmTickets[i]->getDay() << " Name: " << gmTickets[i]->getGameName(i) << " Price: " << gmTickets[i]->getTicketPrice() << endl;
	}
};

#endif /* FLIGHTTICKET_H_ */
