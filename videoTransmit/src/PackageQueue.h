/*
 * PackageQueue.h
 *
 *  Created on: Jan 24, 2018
 *      Author: root
 */

#ifndef PACKAGEQUEUE_H_
#define PACKAGEQUEUE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <mutex>
#include <condition_variable>
#include <queue>

#define SUCCESS 0
#define FAIL -1


class PackageQueue {
public:
	PackageQueue();
	virtual ~PackageQueue();

	int pop(unsigned char *Package, int Size);
	int push(unsigned char *Package, int Size);
	int isEmpty();


	private:

		std::mutex gMtx;

		const int QUEUE_LIMIT = 8192;
		const int FIRST_PACKAGE = 1;

		int gAvailablePackage = 0;
		int gSize;

		int *gStackPackageSize = new int[QUEUE_LIMIT];

		unsigned char **gStackPackage = new unsigned char *[QUEUE_LIMIT];
};

#endif /* PACKAGEQUEUE_H_ */
