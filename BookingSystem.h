/*
 * FlightTicket.h
 *
 *      Author: dongmo
 */

#ifndef BOOKINGSYSTEM_H_
#define BOOKINGSYSTEM_H_

#define max_packages 150

class BookingSystem {
private:
	CustomerRequirement reqs[150];
	int reqNum, acceptedReqs = 0, declinedReqs = 0;
	int roomStatus[10][3];
	int gameStatus[15];
	FILE *acceptedOutput, *declinedOutput;
public:
	struct stat st;
	FILE* filePointer;
    BookingSystem() {
        int i;
		reqNum = 0;
        for(i = 0; i < 10; i++)
        	{
        		roomStatus[i][0] = 0;
        		roomStatus[i][1] = 0;
        		roomStatus[i][2] = 0;
			}
		for(i = 0; i < 15; i++)
			gameStatus[i] = 0;
		acceptedOutput = fopen("AcceptedRequirements.txt", "w");
		declinedOutput = fopen("DeclinedRequirements.txt", "w");
    }
    bool readCustomerRequirements()
    {
    	filePointer = fopen("requirementList.txt", "r");
    	if(filePointer == NULL)
    	{
    		printf("File is not available");
    		return false;
		}
		else
		{
			char ch, buf[128];
        	int cId = 0, i = 0, j = 0;
        	
        	memset(buf, 0, sizeof(buf));
        	
        	while (fgets(buf, 127, filePointer))
			{	
				j = 0;
				char *token = strtok(buf, ",");
				reqs[cId].budget = atoi(token);
				token = strtok(NULL, ",");
				reqs[cId].hotelType.assign(token, 16);
				token = strtok(NULL, ",") + 1;
				while(token != NULL)
				{
					if(atoi(token) == 0 && token[0] != '0')
						break;
					reqs[cId].games[atoi(token)] = true;
					token = strtok(NULL, ",");
				}
				cId++;
				j++;
			}
			puts("Loaded from file Successfully ");
			reqNum = cId;
			return true;
		}
		
	}
	void generatePackages()
	{
		bool success = true;
		int i, j, fly_in = 0, fly_out = 0, fullPrice = 0;
		double discount = 0.0;
		for(i = 0; i< reqNum; i++)
		{
			Package package;
			int hotel_type = 0;
			package.clientID = i;
			fullPrice = 0;
			fly_in = 0;
			fly_out = 0;
			success = true;
			discount = 0.0;
			fly_in = reqs[i].earliestGameDay();
			fly_out = reqs[i].latestGameDay();
			package.addFlightTicket(0, fly_in);
			fullPrice += package.ftTickets[0]->getTicketPrice();
			package.addFlightTicket(1, fly_out);
			fullPrice += package.ftTickets[1]->getTicketPrice();
			for(j = 0; j < 15; j++)
				if(reqs[i].games[j])
					{
						// if there is no game quota
						if(gameStatus[j] <= gameQuota[j])
						{
							package.addGameTicket(j);
							fullPrice += (package.gmTickets[j]->getTicketPrice());
						}
						else
							success = false;
					}
			// hotel voucher
			if(fly_in > fly_out) success = false;
			for(j = fly_in; j < fly_out; j++)
			{
				discount = 0;
				hotel_type = HotelVoucher::getHotelId((char *)reqs[i].hotelType.c_str());
				
				if(roomStatus[j][hotel_type] > hotelQuota[hotel_type])
					success = false;
				
				// 20% discount
				if((hotel_type == 1) && ((roomStatus[j][hotel_type]) / (hotelQuota[j] + 0.0) < 0.5))
					discount = 0.2;
				if(hotel_type == 2)
				{
					if((roomStatus[j][hotel_type]) / (hotelQuota[j] + 0.0) < 0.2)
						discount = 0.2;
					if((roomStatus[j][hotel_type]) / (hotelQuota[j] + 0.0) < 0.5)
						discount = 0.4;
				}
				package.addHotelVoucher(reqs[i].hotelType, j, discount);
				fullPrice += (package.htTickets[j]->getFullPrice((char *)reqs[i].hotelType.c_str()));
			}
			
			if(fullPrice > reqs[i].budget)
				success = false;
			if(success)
				{
					char hotelInfo[65536], gameInfo[65536], temp[128];
					printSuccessfulPackages();
					package.printPackage();
					memset(hotelInfo, 0, sizeof(hotelInfo));
					memset(gameInfo, 0, sizeof(gameInfo));
					memset(temp, 0, sizeof(temp));
					for(j = 0; j < 15; j++)
						if(reqs[i].games[j])
								gameStatus[j] ++;
					for(j = fly_in; j < fly_out; j++)
						roomStatus[j][hotel_type]++;
					acceptedReqs++;
					
					strcpy(hotelInfo, "Hotel Voucher Info\n");
					for(j = 0; j < max_htTickets; j++)
						if(package.htTickets[j])
							{
								sprintf(temp, "Day: %d Discount: %f Price: %f\n", package.htTickets[j]->getDay(), package.htTickets[j]->getDiscount(), package.htTickets[j]->getTicketPrice());
								strcat(hotelInfo, temp);
							}
					strcpy(gameInfo, "Game Ticket Info\n");
					for(j = 0; j < max_gmTickets; j++)
						if(package.gmTickets[j])
						{
							sprintf(temp, "Day: %d Name: %s Price: %f\n", package.gmTickets[j]->getDay(), package.gmTickets[j]->getGameName(j), package.gmTickets[j]->getTicketPrice());
							strcat(gameInfo, temp);
						}
					
					fprintf(acceptedOutput, "Client ID: %d \n FullPrice: %d\n Ticket Info\nDeparture date: %d\n Arrival date: %d\n %s\n%s",
					package.clientID, fullPrice, package.ftTickets[0]->getDay(), package.ftTickets[1]->getDay(), gameInfo, hotelInfo);
				}
			else
			{
				char hotelInfo[65536], gameInfo[65536], temp[128];
				memset(hotelInfo, 0, sizeof(hotelInfo));
				memset(gameInfo, 0, sizeof(gameInfo));
				memset(temp, 0, sizeof(temp));
				declinedReqs++;
				
				strcpy(hotelInfo, "Hotel Voucher Info\n");
					for(j = 0; j < max_htTickets; j++)
						if(package.htTickets[j])
							{
								sprintf(temp, "Day: %d Discount: %f Price: %f\n", package.htTickets[j]->getDay(), package.htTickets[j]->getDiscount(), package.htTickets[j]->getTicketPrice());
								strcat(hotelInfo, temp);
							}
					strcpy(gameInfo, "Game Ticket Info\n");
					for(j = 0; j < max_gmTickets; j++)
						if(package.gmTickets[j])
						{
							sprintf(temp, "Day: %d Name: %s Price: %f\n", package.gmTickets[j]->getDay(), package.gmTickets[j]->getGameName(j), package.gmTickets[j]->getTicketPrice());
							strcat(gameInfo, temp);
						}
					
					fprintf(declinedOutput, "Client ID: %d \n FullPrice: %d\n Ticket Info\nDeparture date: %d\n Arrival date: %d\n %s\n%s",
					package.clientID, fullPrice, package.ftTickets[0]->getDay(), package.ftTickets[1]->getDay(), gameInfo, hotelInfo);
			}
			// create package
			
		}
	}
	void printSuccessfulPackages()
	{
		puts("Successfully Created");
	}
	void printDeclinedPackages()
	{
		puts("Sorry, Declined");
	}
    void printTicket() {
        
    }
    
};

#endif /* FLIGHTTICKET_H_ */
