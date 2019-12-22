#include <boost/filesystem.hpp>
#include <iostream>
#include <map>
#include<string>


std::map<std::string, std::string> Account_Broker;
std::multimap<std::string, int> Account_Date;

int proverka1( std::string str) {
	int proverka = 0;
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '_') proverka++;
	}
	if (proverka == 2) return 1;
	else return 0;
}

int proverkabalance(int& pos, std::string str) {
	std::string buffer = "";
	while (str[pos] != '_') {

		buffer += str[pos];
		pos++;

	}
	if (buffer == "balance") return 1;
	else return 0;
}

int proverkanumber(int& pos, std::string str) {

	
	std::string buffer = "";
	while (str[pos] != '_') {

		if (str[pos] != '0' && str[pos] != '1' && str[pos] != '2' && str[pos] != '3' && str[pos] != '4' &&
			str[pos] != '5' && str[pos] != '6' && str[pos] != '7' && str[pos] != '8' && str[pos] != '9') return 0;

		buffer += str[pos];
		pos++;
		
	}
	
	if (buffer.length() == 8) return 1;
	else return 0;
}

int proverkakonec(int& pos, std::string str) {
	std::string buffer = "";
	while (pos != str.length()) {

		if (str[pos] != '0' && str[pos] != '1' && str[pos] != '2' && str[pos] != '3' && str[pos] != '4' &&
			str[pos] != '5' && str[pos] != '6' && str[pos] != '7' && str[pos] != '8' && str[pos] != '9') {
			return 0;
		}
		buffer += str[pos];
		pos++;
	}
	return 1;
}


void Bypass(boost::filesystem::path s) {
	const boost::filesystem::path p{ s };
	
	for (boost::filesystem::directory_entry& x : boost::filesystem::directory_iterator(p))
	{
		if (boost::filesystem::is_directory(x))  Bypass(x.path());
		else {

			
			int flag = 1;
			std::string str = "";
			str = x.path().filename().string().substr(0, x.path().stem().string().length());
			
			std::string buffer = "";
			int pos = 0;

			if (proverka1(str) != 1) continue;

			
			while (str[pos] != '_') {
				
				buffer += str[pos];
				pos++;

			}
			if (buffer != "balance")
				flag = proverkabalance(pos, str);


			buffer = "";
			pos++;
			while (str[pos] != '_') {
				
				if (str[pos] != '0' && str[pos] != '1' && str[pos] != '2' && str[pos] != '3' && str[pos] != '4' &&
					str[pos] != '5' && str[pos] != '6' && str[pos] != '7' && str[pos] != '8' && str[pos] != '9') {
					flag = 0;
					break;
				}

				buffer += str[pos];
				pos++;
			}
			if (buffer.length() != 8) {
				flag = 0;
			}
			
			flag = proverkanumber(pos, str);
			buffer = "";
			pos++;


			flag = proverkakonec(pos, str);

			if (str.length() != 25) flag == 0;
			pos = 0;

			if (boost::filesystem::is_regular_file(x) && flag == 1) {
				
				std::cout << x.path().parent_path().filename() << " " << x.path().filename() << '\n';
				Account_Broker.insert(std::pair<std::string, std::string>(x.path().filename().string().substr(8, 8), x.path().parent_path().filename().string()));
				Account_Date.insert(std::pair<std::string, int>(x.path().filename().string().substr(8, 8), atoi(x.path().filename().string().substr(17, 25).c_str())));
			}

			else continue;
		}
	}

	
	return;
}
int main() {
	const boost::filesystem::path p{ "C:/Users/alkop/Downloads/ftp" };
	Bypass(p);
	std::vector<int>MAX;
	std::cout << std::endl;
	for (auto it = Account_Broker.begin(); it != Account_Broker.end(); ++it) {
		int max = -1;
		for (auto at = Account_Date.begin(); at != Account_Date.end(); ++at) {
			if (it->first == at->first) {
				if (at->second > max)  max = at->second;
			}
		}
		std::cout << "broker: " << it->second << " account: " << it->first << " files: " << Account_Date.count(it->first) << " last update: " << max << std::endl;
	}
	return 0;
}



