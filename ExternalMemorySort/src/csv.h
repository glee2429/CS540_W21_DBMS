#pragma once

#include <ios>
#include <fstream> // if, of, stream
#include <bitset>
#include <string>
#include <tuple>  // for returning tuples from functions
#include "utils.h"

// a csv is a type synonym for a matrix of strings
using csv = std::vector<std::vector<std::string> >;

void printCsv(csv);
csv readCsv(std::string);
csv convert(csv,std::vector<int>);
std::tuple<csv,std::streampos> readCsvChunk(std::istream&,std::streampos,unsigned int);
void writeCsv(std::string,csv&);
std::string showLine(std::vector<std::string>);
void loadLine(std::istream&, std::vector<std::string>*);
