/*******************************************************************************
 * csv.cpp
 *
 * Jeffrey M. Young, Claire Lee
 * Copyright (c) 2021
 *
 * A simple csv reader, based on code from: https://www.geeksforgeeks.org/csv-file-management-using-c/
 *
 *******************************************************************************/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <sstream>   // for get line in read
#include <iterator>  // for iterator writing to an output file

#include "utils.h"
#include "settings.h"

// a csv is a type synonym for a matrix of strings
using csv = std::vector<std::vector<std::string> >;

/********************************************************************************
 * printCsv
 *
 * Print the csv matrix to stdout
 *******************************************************************************/
void printCsv(csv c) {
  for (auto row : c) {
    for (auto field : row) {
      std::cout << " " << field;
    }
    std::cout << '\n';
  }
}


/********************************************************************************
 * readCsv We isolate the side effect of reading the csv here making no
 * assumptions about the type of columns. Post processing of these columns
 * should be done with the convert function below. This function will attempt to
 * read the whole csv into memory. See `readNCsv` for a function that only reads
 * a chunk
 *******************************************************************************/
csv readCsv(std::string file) {
  // File pointer
  std::fstream fin;

  // Open an existing file
  fin.open(file, std::fstream::in);

  // Read the Data from the file
  // as String Vector
  std::vector<std::string> row;
  csv csvdata;
  std::string line;


  if (fin) {
    std::string line;

    while (getline(fin, line)) {
      std::stringstream sep(line);
      std::string field;
      row.clear();

      while (getline(sep, field, ',')) {
        row.push_back(field);
      }
      csvdata.push_back(row);
    }
  }
  return csvdata;
}

/********************************************************************************
 * readCsvChunk
 *
 * readCsv but read the csv in chunks returning a vector of information and a
 * streampos. We assume the file is already open and thus input a file stream.
 * It is the callers (the function that called this one) responsibility to close
 * the stream!
 *
 *******************************************************************************/
std::tuple<csv, std::streampos> readCsvChunk(std::istream& fin, std::streampos pos, unsigned int chunk_size) {
  std::vector<std::string> row;  // a row is a vec of strings
  csv chunk;                     // a chunk is a vec of vec of strings
  std::string line;              // a line is a string
  unsigned int i = 0;            // counter


  // log the current file pointer location
  std::streampos current_loc = fin.tellg();

  // if the position we want to read from is not the current position move the
  // file pointer. We incur an extra seek here for usability, this should
  // never fire for this assignment.
  if (pos != current_loc){fin.seekg(pos);} // seekg defaults to beginning of
                                           // file std::ios::beg

  // now read as we are in right position
  while (getline(fin, line) && (i <= chunk_size)) {
    std::stringstream sep(line);
    std::string field;
    row.clear();

    while (getline(sep, field, ',')) {
      row.push_back(field);
    }

    // recur
    chunk.push_back(row);
    i++;
  }

  // last file pointer read
  current_loc = fin.tellg();
  return std::make_tuple(chunk, current_loc);
}


/********************************************************************************
 * loadLine
 *
 * Load a single line into a buffer, assuming a csv file
 * We use copy semantics here, could also load directly using a pointer
 *******************************************************************************/
void loadLine(std::istream& fin, std::vector<std::string> *buffer) {
  std::string line; // a line is a string

  // get a line and seperate it into fields
  getline(fin, line);

  std::stringstream sep(line);
  std::string field;

  // empty the buffer
  buffer->clear();

  // now add new data to the buffer as long as a line was read
  if (!line.empty()){
    while (getline(sep, field, ',')) { buffer->push_back(field); }
  }
}


/********************************************************************************
 * Convert
 * the string data in the csv matrix to numeric data based on the
 * columns that hold numeric data
 *******************************************************************************/
csv convert(csv data, std::vector<int> numerics) {
  for (auto row : data) {
    for (auto i : numerics) {
      int num = atoi(row.at(i).c_str());
      row[i] = num;
    }
  }
  return data;
}

/********************************************************************************
 * Write
 * Write the csv to disk
 *******************************************************************************/
void writeCsv(std::string out, csv& data){
  std::ofstream of;
  std::string line ;
  long unsigned int row_size;

  of.open(out, std::ios::out ); // using only std::ios::out overwrites the file
                                // everytime
    // write
    for (auto row : data) {
      row_size = row.size();

      for (long unsigned int i = 0; i < row_size; i++) {
        // construct line and avoid last comma
        if (i == row_size - 1) { // then last element so don't writ comma
          line += row.at(i);
        } else{
          line += row.at(i) + comma();
        }
      };
      // write line
      of << line << std::endl;
      // reset the accumulator
      line.clear();
    }

  of.close();
}

std::string make_run_fname(unsigned int run_num, std::string relation){
  return (SORTED_DIR + relation + std::to_string(run_num) + CSV_SUFFIX);
}


/********************************************************************************
 * Convert a row in a csv to a string
 *
 *******************************************************************************/
std::string showLine(std::vector<std::string> buffer) {
  std::string line;              // a line is a string
  long unsigned int buf_size = buffer.size();

  for (long unsigned int i = 0; i < buf_size; i++) {
    // construct line and avoid last comma
    if (i == buf_size - 1) { // then last element so don't writ comma
      line += buffer.at(i);
    } else{
      line += buffer.at(i) + comma();
    }
  };
  return line;
}
