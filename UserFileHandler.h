#pragma once
#include <fstream>
#include <sstream>
#include <format>



class UserFileHandler
{
private:
	string filePath = "DB\\users\\users.csv";
public:
	void loadUsersFormFile( unordered_map<string, User>& usersMap, int& n);
	void saveUsersToFile( unordered_map<string, User>& usersMap);

};



void UserFileHandler::loadUsersFormFile( unordered_map<string, User>& usersMap, int& n) {


	std::ifstream usersFile(filePath);

	std::string user;

	while (std::getline(usersFile, user)) {

		std::stringstream stream(user);

		std::string id;
		std::string username, password;
		std::string admin;

		std::getline(stream, id, ',');
		std::getline(stream, username, ',');
		std::getline(stream, password, ',');
		std::getline(stream, admin, ',');


		usersMap.insert({ username, User(stoi(id), username, password, stoi(admin)) });
		n++;

	}

}


void UserFileHandler::saveUsersToFile(unordered_map<string, User>& usersMap) {

	std::ofstream usersFile(filePath);
	std::string user;

	

	for (auto it = usersMap.begin(); it != usersMap.end(); it++) {

		string x = ((std::next(it) != usersMap.end()) ? "\n" : "");

		user = std::format("{},{},{},{}{}"
			, it->second.getId()
			, it->second.getUsername()
			, it->second.getPassword()
			, it->second.isAdmin()
			, ((std::next(it) != usersMap.end()) ? "\n" : ""));
		usersFile << user;
	}

	cout << "done\n";

}