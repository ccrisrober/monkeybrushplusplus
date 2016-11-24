/* 
 * File:   iniReader.h
 * Author: benmaynard
 *
 * Created on August 26, 2010, 2:49 PM
 */

#ifndef INIREADER_H
#define	INIREADER_H

#include <string>
#include <fstream>
#include <algorithm>

/*
parseIniFile("sample.ini");
cout << "MYSQL Host: " << getOptionToString("mysql_host") << "\n"; //Return string
cout << "MYSQL User: " << getOptionToString("mysql_user") << "\n"; //Return string
cout << "MYSQL Pass: " << getOptionToString("mysql_pass") << "\n"; //Return string
cout << "MYSQL DB: " << getOptionToChar("mysql_db") << "\n"; //Return char
cout << "MYSQL Socket: " << getOptionToChar("mysql_socket") << "\n"; //Return char
cout << "MYSQL Port: " << getOptionToInt("mysql_port") << "\n"; //Return int
cout << "Bad Config Item: " << getOptionToString("bad_config_item") << "\n"; //Should return nothing

cleanupIniReader();
*/

/**
 * Parse a configuration file
 * 
 * @param	fileName The name of the file to parse
 * @return	none
 */
void parseIniFile(std::string fileName);

/**
 * If you are finished with the config item, use this function to cleanup the results
 * 
 * @return none
 */
void cleanupIniReader();

/**
 * Return the value of the requested key in with the string type
 *
 * @param	key The option key
 * @return	string The value of the requested key
 */
std::string getOptionToString(std::string key);

/**
 * Return the value of the requested key in with the int type
 *
 * @param	key The option key
 * @return	int The value of the requested key
 * @note	If item is not an integer (or does not exist) then 0 will be returned.
 */
int getOptionToInt(std::string key);

/**
 * Return the value of the requested key in with the char type
 *
 * @param    key The option key
 * @return   char The value of the requested key
 */
const char *getOptionToChar(std::string key);

std::string parseOptionName(std::string value);
std::string parseOptionValue(std::string value);
std::string trim(std::string s);
std::string rtrim(std::string s);
std::string ltrim(std::string s);

#endif	/* INIREADER_H */