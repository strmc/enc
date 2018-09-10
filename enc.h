#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <fstream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

int main(int, char**);

void encrypt(fs::path, const std::string);

void help(const std::string);
