/*
 * ContextSwitchMeasurement.h
 *
 *  Created on: Jun 14, 2014
 *      Author: developer
 */
#include <stdint.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

#ifndef CONTEXTSWITCHMEASUREMENT_H_
#define CONTEXTSWITCHMEASUREMENT_H_

uint32_t getCtxSwitchMeasurement();

#endif /* CONTEXTSWITCHMEASUREMENT_H_ */
