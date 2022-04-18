/* date = March 25th 2022 11:23 am */
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <atomic>
#include <stdint.h>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <thread>
#include <iomanip>

#define global_variable static
#define Clocker(a, b) ((double)(b-a)/CLOCKS_PER_SEC)

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef struct internal_pair {
    std::string result = "";
    int cost = 0;
}Pair;

typedef struct internal_Pair_solutions {
    int cost = 0;
    double time = 0;
}Pairsolve;

typedef struct internal_edges{
    std::string city1;
    std::string city2;
    int cost;
    
}Edge;

typedef struct internal_triplepair {
    Pairsolve brute_force;
    Pairsolve greedy;
    Pairsolve dynamic;
}Triple;