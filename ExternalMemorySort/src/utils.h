/*******************************************************************************
 * utils.h
 *
 * Jeffrey M. Young, Claire Lee
 * Copyright (c) 2021
 *
 * Utilities for the project
 *
 *******************************************************************************/
#pragma once

#include <ios>
#include <bitset>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <iomanip>
#include <iostream>

void logWith(std::string, std::string);
void log(std::string);
void log0(std::string);
void log1(std::string);
void logInsert(std::string);
void logLookup(std::string);

int stringToInt(std::string);

// get the rightmost N bits of an integer
unsigned int rightMostN (unsigned int,unsigned int);

// flip the most significant digit assuming a byte
unsigned int flipIth (unsigned int,unsigned int);
unsigned int zeroIthBit(unsigned int,unsigned int);
unsigned int zeroAllAfter(unsigned int,unsigned int);

std::string toBitString(unsigned int);

std::string newline();
std::string sep();
std::string comma();

bool file_exists(std::string fname);

unsigned int suffix_sub1(unsigned int, unsigned int);

unsigned int hash(unsigned int,unsigned int);

std::string make_run_fname(unsigned int, std::string);
