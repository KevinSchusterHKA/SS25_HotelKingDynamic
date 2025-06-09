#include <string>


class Logger {
public:
	Logger();
	

private:
	std::string path;
	void writeToFile(std::string text);
	
};