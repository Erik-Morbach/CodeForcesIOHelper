#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "HTML.h"
std::vector<std::string> getContestProblemsURLs(std::string url);

bool searchNextProblemName(std::string &partialHTML,std::vector<std::string> &ans,int contestId);

