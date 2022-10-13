/*
 * Constants.h
 *
 *      Author: dongmo
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_


const string nameMap[] = { "Opening", "Round of 16-Group A", "Round of 16-Group B", "Round of 16-Group C",
		"Round of 16-Group D", "Round of 16-Group E", "Round of 16-Group F",
		"Round of 16-Group G", "Round of 16-Group H", "Quarter-finals-1", "Quarter-finals-2",
		"Semi-final", "Third place play-off", "Final", "Closing" };
const int gamePriceMap[] = { 2000, 170, 80, 80, 150, 480, 110, 130, 90, 80, 100,
		300, 100, 100, 800 };

const int gameDayMap[] = { 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 7, 8, 9 };

const int gameQuota[] = {60, 45, 40, 45, 50, 45, 55, 45, 35, 20, 25, 35, 435, 30, 40};

const int hotelPriceMap[] = {150, 220, 310};

map<string, int> hotelTypeIndexMap { { "Regular", 0}, { "Bronze", 1 }, { "Gold", 2 } };

const string hotelIndexToTypeMap[] ={"Regular", "Bronze", "Gold"};

const int hotelQuota[] ={25, 20, 40};// per day

const int MAXGAMES = 10;

const int MAXREQUIREMENTS = 150;

const int NUMBEROFGAMES = 15;

const int NUMBEROFDAYS = 10;

#endif /* CONSTANTS_H_ */
