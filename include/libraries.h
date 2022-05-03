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

#define ABSINT(a) ((a < 0)? -a : a)
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

static int number_of_vehicles = 0;
