/*
 * PackageQueue.cpp
 *
 *  Created on: Jan 24, 2018
 *      Author: root
 */

#include "PackageQueue.h"

PackageQueue::PackageQueue()
{
	// TODO Auto-generated constructor stub


}


PackageQueue::~PackageQueue()
{
	// TODO Auto-generated destructor stub
}


int PackageQueue::push(unsigned char* Package, int Size)
{

	while(gAvailablePackage >= QUEUE_LIMIT)
	{
		printf("\n!!!Qeueu is dump!!!\n");
	}

	gMtx.lock();
	gAvailablePackage++;
	if(gAvailablePackage > QUEUE_LIMIT)
		gAvailablePackage = QUEUE_LIMIT;

	gStackPackage[gAvailablePackage] = new unsigned char[Size];
	gStackPackageSize[gAvailablePackage] = Size;

	for(int i = 0; i<Size; i++)
		gStackPackage[gAvailablePackage][i] = Package[i];

//	memcpy(gStackPackage[gAvailablePackage], Package, Size);

	gMtx.unlock();

	return SUCCESS;
}



int PackageQueue::pop(unsigned char* Package, int Size)
{
	gMtx.lock();


//	memcpy(Package,gStackPackage[FIRST_PACKAGE], Size);

	for(int i = 0; i<Size; i++)
		Package[i] = gStackPackage[FIRST_PACKAGE][i];

	delete []gStackPackage[FIRST_PACKAGE];

	gAvailablePackage--;
	if(gAvailablePackage < 0)
		gAvailablePackage = 0;

	if(gAvailablePackage >= FIRST_PACKAGE)
	{

		for(int i=FIRST_PACKAGE; i<=gAvailablePackage; i++)
		{
			gStackPackage[i] = gStackPackage[i + 1];
			gStackPackageSize[i] = gStackPackageSize[i + 1];
		}

		gMtx.unlock();

		return SUCCESS;
	}
	else
	{

		gMtx.unlock();
		return FAIL;

	}
}



int PackageQueue::isEmpty()
{
	gMtx.lock();
	if(gAvailablePackage < FIRST_PACKAGE)
	{
		gMtx.unlock();
		return FAIL;
	}
	else
	{
		gMtx.unlock();
		return gStackPackageSize[FIRST_PACKAGE];
	}
}