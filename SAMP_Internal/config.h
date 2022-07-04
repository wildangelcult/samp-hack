#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include "global.h"
#include "json.hpp"
#include "freecam.h"
using json = nlohmann::json;

namespace CONFIG {
	void init();
	void save(std::string filename);
	void load(std::string filename);
	void remove(std::string filename);
	std::vector<std::string> list();
};