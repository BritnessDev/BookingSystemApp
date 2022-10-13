/*
 * FlightTicket.h
 *
 *      Author: dongmo
 */

#ifndef FLIGHTTICKET_H_
#define FLIGHTTICKET_H_

class FlightTicket: public Ticket {
private:
    int flightType; // 0 for departure, 1 for return
public:
    FlightTicket(int ft, int d) :
            Ticket(d, 2000) {
        flightType = ft;
        discount = (1.0 - flightType) * day * 0.05
                + flightType * (NUMBEROFDAYS - 1.0 - day) * 0.05;
    }

    void printTicket() {
        string type = flightType == 0 ? "Sydney to Paris" : "Paris to Sydney";

        cout << "Flight ticket from " << type << " on day " << day
                << " at price $" << getTicketPrice() << endl;
    }
};

#endif /* FLIGHTTICKET_H_ */
