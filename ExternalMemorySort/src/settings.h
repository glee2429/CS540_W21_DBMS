/*******************************************************************************
 * settings.h
 *
 * Jeffrey M. Young, Claire Lee
 * Copyright (c) 2021
 *
 * Dirty globals used to tune the system
 *
 *******************************************************************************/
#pragma once

// Size Constants
#define INT_SIZE    4
#define DOUBLE_SIZE 8
#define STRING_SIZE 40
#define NUM_BLOCKS  22

// debug
#define DEBUG       1 // 0 for off, 1 for on

// file constants
#define EMP_FILE     "Emp"
#define KEY_LOC_EMP   0
#define SORTED_DIR   ".sorted_data/"
#define DATA_DIR     "data/"
#define CSV_SUFFIX   ".csv"
