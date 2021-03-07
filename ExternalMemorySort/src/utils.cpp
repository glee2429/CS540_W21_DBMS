/*******************************************************************************
 * utils.cpp
 *
 * Jeffrey M. Young, Claire Lee
 * Copyright (c) 2021
 *
 * Utilities for the project
 *
 *******************************************************************************/

#include <iostream>
#include <fstream>

#include "settings.h"
#include "utils.h"


// some simple logging
void logWith(std::string prefix, std::string msg){
  if (DEBUG) {
    std::cout << prefix << "  " << msg << '\n';
  };
}

// wrappers around logWith
void log(std::string msg){ logWith("[DEBUG]", msg); }
void log0(std::string msg){ logWith("[Phase 0]", msg); }
void log1(std::string msg){ logWith("[Phase 1]", msg); }
void logInsert(std::string msg){ logWith("[INSERT]", msg); }
void logLookup(std::string msg){ logWith("[LOOKUP]", msg); }

int stringToInt(std::string s) { return atoi(s.c_str()); }

// get the rightmost N bits of an integer
unsigned int rightMostN (unsigned int original, unsigned int n) {
  return (original & ((1 << n) - 1));
}

unsigned int flipIth (unsigned int n, unsigned int i) {
  return (n ^ (1 << i));
}

unsigned int zeroIthBit(unsigned int n,unsigned int i){
  return (n &= ~(1UL << i));
}

unsigned int zeroAllAfter(unsigned int n, unsigned int i){
  unsigned int ret = n;
  // counting starts at 0, so i = 2 is the third bit
  for (unsigned int j = i; j <= 8; j++){ ret = zeroIthBit(ret,j); }
  return ret;
}

std::string toBitString(unsigned int n) {
  return std::bitset<8>(n).to_string();
}

unsigned int suffix_sub1(unsigned int n, unsigned int i){
  int j = floor(log2(n));
  return (n - (int)(pow(2,j)));
}

// this should probably be a const but I dont care
std::string newline(){ return "\n" ;}
std::string sep(){ return "=======================================" ;}
std::string comma(){return ",";}

bool file_exists( std::string fname ) { return bool(std::ifstream(fname)) ;}

unsigned int hash(unsigned int to_hash, unsigned int i){
  return (to_hash % (int)(pow(2,i)));
}
