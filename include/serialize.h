//Functions to serialize activity and date data
#pragma once

#define ACSERIALIZE_MAGIC_NUMBER (int32_t)0xEE;

#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

#include "activity.h"
#include "acdate.h"

bool write_to_file(std::string,std::vector<date>,std::vector<std::string>);
bool read_from_file(std::string,std::vector<date>&,std::vector<std::string>&);
