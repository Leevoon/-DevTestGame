#include "GameInformationReader.h"
#include "json.hpp"

#include <fstream>
#include <string>
#include <sstream>
GameInformationReader::GameInformationReader(const std::string & path)
{
	std::ifstream fs(path.c_str());
	std::string str;
	if (fs.is_open()) {
		str=std::string((std::istreambuf_iterator<char>(fs)),std::istreambuf_iterator<char>());
	}
	nlohmann::json json;
	try
	{
		json = nlohmann::json::parse(str);
	}
	catch (const std::exception& exception)
	{
		std::cerr << exception.what() << std::endl;
	}
	if (json.contains("win_height")) {
		m_info.m_windowHeight = json["win_height"].get<int>();
	}
	if (json.contains("win_width")) {
		m_info.m_windowWidth = json["win_width"].get<int>();
	}
	if (json.contains("col")) {
		m_info.m_col = json["col"].get<int>();
	}
	if (json.contains("row")) {
		m_info.m_row = json["row"].get<int>();
	}
	if (json.contains("moves_count")) {
		m_info.m_movesCount = json["moves_count"].get<int>();
	}
	if (json.contains("figures_count")) {
		m_info.m_figureCounts = json["figures_count"].get<int>();
	}
	std::vector<std::string> jsonArray;
	if (json.contains("objectives")) {
		jsonArray = json["objectives"].get<std::vector<std::string>>();
	}
	for (auto i = 0; i < jsonArray.size(); ++i) {
		std::istringstream iss(jsonArray.at(i));
		std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
			std::istream_iterator<std::string>());
		if (results.front() == "Red") {
			m_info.m_objectives[ItemType::eRed] = std::stoi(results.back());
		}else if (results.front() == "Green") {
			m_info.m_objectives[ItemType::eGreen] = std::stoi(results.back());
		}if (results.front() == "Blue") {
			m_info.m_objectives[ItemType::eBlue] = std::stoi(results.back());
		}if (results.front() == "Orange") {
			m_info.m_objectives[ItemType::eOrange] = std::stoi(results.back());
		}if (results.front() == "Violet") {
			m_info.m_objectives[ItemType::eViolet] = std::stoi(results.back());
		}
	}

	if (m_info.m_windowHeight < 500) {
		m_info.m_windowHeight = 1080;
	}
	if (m_info.m_windowWidth < 500) {
		m_info.m_windowWidth = 744;
	}
}

std::string GameInformationReader::getErrorMessage(bool &ok)
{
	std::string err;
	ok = true;
	if (m_info.m_row > 10 || m_info.m_row < 7) {
		err += "Row must be in range [7,10].\n";
		ok = false;
	}
	if (m_info.m_col > 10 || m_info.m_col < 7) {
		err += "Col must be in range [7,10].\n";
		ok = false;
	}
	if (m_info.m_objectives.size() > 3) {
		err += "Objectives count must be max 3.\n";
		ok = false;
	}
	if (m_info.m_figureCounts < 3 || m_info.m_figureCounts > 5) {
		err += "Figures colors count must be in range [3,5].\n";
		ok = false;
	}
	if (m_info.m_movesCount < 0) {
		err += "Moves count must be positive number.\n";
		ok = false;
	}
	return err;
}

GameInfo GameInformationReader::getInfo()
{
	return m_info;
}
