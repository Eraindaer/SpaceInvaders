#include "FileManager.h"
FileManager::FileManager() {

}
FileManager::~FileManager() {

}


void FileManager::Write(const char* path) {
	fs.open(path, std::fstream::out);
	for (auto const& entry : classment) {
		fs << entry.second << std::endl << entry.first << std::endl;
	}
	fs.close();
}

void FileManager::SetClassment(const char* path, std::string input, int score) {
	std::ifstream in(path);
	std::string str, name;
	int line = 0;
	while (std::getline(in, str)) {
		if (line % 2 == 0)
			name = str;
		else
			classment.insert(std::make_pair(std::stoi(str), name));
		line++;
	}
	classment.insert(std::make_pair(score, input));
}
