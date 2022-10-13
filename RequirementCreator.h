/*
 * FlightTicket.h
 *
 *      Author: dongmo
 */

#ifndef REQUIREMENTCREATOR_H_
#define REQUIREMENTCREATOR_H_
#define max_count 150
#define min_count 100

class RequirementCreator{
private:
public:
	int reqLenght;
	CustomerRequirement *reqs[150];
    RequirementCreator() 
    {	
    	int i;
    	reqLenght  = (int)(((double)rand() / (double)RAND_MAX) * 50 + min_count);
    	for(i = 0; i < reqLenght; i++)
    		reqs[i] = new CustomerRequirement();
	}
	void createCutomerBundle()
	{
		// Create Input data
	}
	void writeBundle()
	{
		// write file
	}
	~RequirementCreator()
	{
		int i;
		for(i = 0; i < reqLenght; i++)
			if(reqs[i])
				free(reqs[i]);
	}
};

#endif /* FLIGHTTICKET_H_ */
