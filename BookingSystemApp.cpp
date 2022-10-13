/*
 * BookingSystem.cpp
 *
 *      Author: dongmo
 */

#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<vector>
#include<map>

using namespace std;

#include "Constants.h"
#include "Ticket.h"
#include "GameTicket.h"
#include "FlightTicket.h"
#include "HotelVoucher.h"
#include "CustomerRequirement.h"
#include "Package.h"
#include "BookingSystem.h"
#include "RequirementCreator.h"
#include "BookingSystem.h"
#include "SmartBookingSystem.h"

#ifndef BookingSystem_CPP_
#define BookingSystem_CPP_

void classTest1() {
	cout << "Test CustomerRequirement class ... " << endl;

	CustomerRequirement requirementList[2];
	requirementList[0].cId = 0;
	requirementList[0].budget = 9020;
	requirementList[0].hotelType = "Gold";
	requirementList[0].games[14] = true;
	requirementList[0].games[2] = true;
	requirementList[0].games[7] = true;

	requirementList[1].cId = 1;
	requirementList[1].budget = 7805;
	requirementList[1].hotelType = "Regular";
	requirementList[1].games[0] = true;
	requirementList[1].games[4] = true;
	requirementList[1].games[10] = true;
	requirementList[1].games[9] = true;
	requirementList[1].games[3] = true;

	cout << "* Test data ..." << endl;
	cout << setw(8) << "Customer No" << setw(8) << "budget" << setw(8) << "hotel"
			<< setw(8) << "games" << endl;

	for (int i = 0; i < 2; i++)
		requirementList[i].print();

	cout << "\n* Test functions (an example)..." << endl;
	cout << "  - Earliest game day: " << requirementList[0].earliestGameDay()
			<< endl;
	cout << "  - Latest game day: " << requirementList[0].latestGameDay() << endl;
}

void classTest2() {
	cout << "Test FlightTicket class ... " << endl;

	FlightTicket *tickets[2];
	tickets[0] = new FlightTicket(0, 0);
	tickets[1] = new FlightTicket(1, 1);

	for (int i = 0; i < 2; i++)
		tickets[i]->printTicket();
}

void classTest3() {
	cout << "Test HotelVoucher class ... " << endl;

	HotelVoucher *vouchers[3];
	vouchers[0] = new HotelVoucher("Gold", 0, 0.0);
	vouchers[1] = new HotelVoucher("Bronze", 5,0.2);
	vouchers[2] = new HotelVoucher("Regular", 7, 0.4);

	for (int i = 0; i < 3; i++)
		vouchers[i]->printTicket();

}

void classTest4() {
	cout << "Test GameTicket class ... " << endl;

	GameTicket *tickets[3];
	tickets[0] = new GameTicket(2);
	tickets[1] = new GameTicket(5);
	tickets[2] = new GameTicket(14);

	for (int i = 0; i < 3; i++)
		tickets[i]->printTicket();

}

void classTest5() {
	cout << "\nTest RequirementCreator Class ... " << endl;
	RequirementCreator rg;
	rg.createCutomerBundle();
	rg.writeBundle();
}

void classTest6() {
	cout << "\nTest Package class: \nExample package 1 ... " << endl;
	Package p;
	p.addFlightTicket(0, 3);
	p.addFlightTicket(1, 8);
	p.addGameTicket(2);
	p.addGameTicket(5);
	p.addGameTicket(14);

	p.addHotelVoucher("Regular", 4, 0.0);
	p.addHotelVoucher("Bronze", 8, 0.0);
	p.addHotelVoucher("Gold", 0, 0.0);

	p.printPackage();

	cout << "\nTest Package class: \nExmaple package 2... " << endl;
	Package p2;
	p2.addFlightTicket(0, 3);
	p2.addFlightTicket(1, 6);
	p2.addGameTicket(1);
	p2.addGameTicket(7);
	p2.addGameTicket(8);

	p2.addHotelVoucher("Gold", 3, 0.0);
	p2.addHotelVoucher("Regular", 4, 0.2);
	p2.addHotelVoucher("Gold", 5, 0.4);

	p2.printPackage();
}

void classTest7() {
	BookingSystem agent;
	agent.readCustomerRequirements();
	agent.generatePackages();

	cout<<"\nGenerated valid packages: " << endl;
	agent.printSuccessfulPackages();
}

int main() {
	srand(time(0)); // seed random number generator

	SmartBookingSystem smartagent;

	cout << "Choose a class to test: " << endl;
	cout << "1. Test CustomerRequirement class" << endl;
	cout << "2. Test FlightTicket class" << endl;
	cout << "3. Test HotelVoucher class" << endl;
	cout << "4. Test gameTicket class" << endl;
	cout << "5. Test RequirementCreator class" << endl;
	cout << "6. Test Package class" << endl;
	cout << "7. Test BookingSystem class" << endl;
	cout << "8. Run Smart Travel agent" << endl;
	cout << "9. Quit" << endl;

	int choice;
	cin >> choice;

	switch (choice) {
	case 1:
		classTest1();
		break;
	case 2:
		classTest2();
		break;
	case 3:
		classTest3();
		break;
	case 4:
		classTest4();
		break;
	case 5:
		classTest5();
		break;
	case 6:
		classTest6();
		break;
	case 7:
		classTest7();
		break;
	case 8:
		smartagent.readCustomerRequirements();
		smartagent.generatePackages();
		smartagent.printSuccessfulPackages();
	//	agent.printUnsuccessfulPackages();
		smartagent.vacancy();
		break;
	case 9:
		cout << "Bye!" << endl;
		break;
	default:
		cout << "Invalid input!" << endl;
	}

	return 0;
}

#endif /* BookingSystem_CPP */
