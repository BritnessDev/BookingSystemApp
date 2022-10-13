/*
 * FlightTicket.h
 *
 *      Author: dongmo
 */

#ifndef HOTELVOUCHER_H_
#define HOTELVOUCHER_H_

class HotelVoucher: public Ticket {
private:
    char *hotel_type; // 0: Regular, 1: Bronze, 2: Gold
public:
    HotelVoucher(string hotelType, int d, double ht_discount) :
            Ticket(d, getFullPrice((char *)hotelType.c_str())) {
        hotel_type = (char *)hotelType.c_str();
        discount = ht_discount;
    }
	int getFullPrice(char *hotelType)
	{
		int i;
		for(i = 0; i < 3; i++)
		{
			if(!strcmp((char *)hotelIndexToTypeMap[i].c_str(), hotelType))
				return hotelPriceMap[i] * (1.0 - discount);
		}
		return 0;
	}
	static int getHotelId(char* hotelType)
	{
		if(!strcmp(hotelType, "Regular"))
			return 0;
		if(!strcmp(hotelType, "Bronze"))
			return 1;
		if(!strcmp(hotelType, "Gold"))
			return 2;
		return -1;
	}
    void printTicket() {
        cout << "Hotel Type " << hotel_type << " on day " << day
                << " at price $" << getTicketPrice() << endl;
    }
};

#endif /* FLIGHTTICKET_H_ */
