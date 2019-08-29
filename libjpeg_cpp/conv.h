#pragma once
#include "jpeg.h"
#include <vector>
using namespace std;

vector<vector<vector<int>>> filterImage(marengo::jpeg::Image &img, vector<vector<vector<float>>> &filter, int divison_factor);