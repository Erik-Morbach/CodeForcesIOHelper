#pragma once

#include <fstream>
#include <string>
#include <iostream>

void downloadFile(std::string &url);
std::ifstream getFile(std::string &url);
std::string getStringHTMLfromFile(std::ifstream &file);
void writeFile(std::ofstream &file, std::string w);
