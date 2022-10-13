/*
 * ClientRequest.h
 *
 *      Author: dongmo
 */

#ifndef CLIENTREQUEST_H_
#define CLIENTREQUEST_H_

class CustomerRequirement {
public:
	int cId;
	string hotelType;
	bool games[NUMBEROFGAMES];
	int budget;

	CustomerRequirement() {
		cId = -1;
		hotelType = "";
		budget = -1;
		for (int i = 0; i < NUMBEROFGAMES; i++)
			games[i] = false;
	}
	// get the day of earliest game that user playing
	int earliestGameDay() {
		int flyin = 9;
		for (int i = 0; i < NUMBEROFGAMES; i++) {
			if (games[i] && gameDayMap[i] < flyin)
				flyin = gameDayMap[i];
		}
		return flyin;
	}
	// get the day of last game that user playing
	int latestGameDay() {
		int flyout = 0;
		for (int i = 0; i < NUMBEROFGAMES; i++) {
			if (games[i] && gameDayMap[i] > flyout)
				flyout = gameDayMap[i];
		}
		return flyout;
	}

	void print() {
		cout << "Customer " << cId << ":" << setw(8) << budget << setw(8) << hotelType;

		for (int i = 0; i < NUMBEROFGAMES; i++) {
			if (games[i])
				cout << setw(8) << i;
		}
		cout << endl;
	}
};

#endif /* CLIENTREQUEST_H_ */
