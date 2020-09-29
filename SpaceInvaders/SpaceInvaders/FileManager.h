#pragma once
#include <fstream>
#include <utility>
#include <string>
#include <map>
class FileManager
{
public:
	FileManager();
	~FileManager();
	
	void SetClassment(const char* path, std::string input, int score);
	void Write(const char* path);

	inline std::multimap<int, std::string, std::greater<int>> GetClassment(){ return classment; }

private:
	std::multimap<int, std::string, std::greater<int>> classment;
	std::fstream fs;
};

