//Functions to serialize activity and date data
#pragma once

#include <algorithm>
#include <cstdint>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "activity.h"
#include "acdate.h"
#include "idgen.h"

const int32_t ACSERIALIZE_MAGIC_NUMBER=0xEE;

bool write_to_file(std::string,std::vector<date>,std::vector<std::string>);
bool read_from_file(std::string,std::vector<date>&,std::vector<std::string>&);
