
#pragma once
#include <iostream>
#include "filereadstream.h"
#include "document.h"

using namespace std;
using namespace rapidjson;

Document parseJSONFile(const char * fileLocation);
