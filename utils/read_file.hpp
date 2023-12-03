#pragma once

#include <string>
#include <fstream>
#include <vector>

std::string read(const char *filename) {
	std::fstream fs(filename);
	std::string line;
	std::getline(fs, line, (char)EOF);
	fs.close();
	return line;
}

std::vector<std::string> read_lines(const char *filename) {
	std::fstream fs(filename);
	std::vector<std::string> v;
	for (std::string line; std::getline(fs, line);) {
		v.push_back(line);
	}
	fs.close();
	return v;
}

