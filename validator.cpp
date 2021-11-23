#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include "validator.h"


//can switch to encrypt lib
std::string encryptDecrypt(std::string toEncrypt) {
    char key = 'J'; //Any char will work
    std::string output = toEncrypt;
    for (int i = 0; i < toEncrypt.size(); i++)
        output[i] = toEncrypt[i] ^ key;
    return output;
}

void create(){
  if(std::ifstream("expiry")) {
    return;
  } else {
    std::string expiry_date = "2021-12-12";
    std::string encrypted_date = encryptDecrypt(expiry_date);
    std::ofstream expiry_file;
    expiry_file.open("expiry");
    expiry_file << encrypted_date;
    expiry_file.close();
    return;
  }
}

bool validate() {
  if(!std::ifstream("expiry")) return false;
  std::string line;
  std::ifstream expiry_file("expiry");
  if(expiry_file.is_open()) {
     getline(expiry_file, line);
     std::string decrypt_date = encryptDecrypt(line);
     std::time_t current_time = std::time(0);   // get time now
     std::tm tmholder;
     tmholder.tm_year = std::stoi(decrypt_date.substr(0,4)) - 1900;
     tmholder.tm_mon = std::stoi(decrypt_date.substr(5,2));
     tmholder.tm_mday = std::stoi(decrypt_date.substr(8,2));
     tmholder.tm_hour = 0;
     tmholder.tm_min = 0;
     tmholder.tm_sec = 0;
     tmholder.tm_isdst = -1;

     std::time_t expiry_time = std::mktime(&tmholder);
     bool validation = std::difftime(expiry_time,current_time) > 0 ;

// DUBUG_LOGGING
//     std::cout << "line:";
//     std::cout << decrypt_date.c_str();
//     std::cout << '\n';
//     std::cout << "current:";
//     std::cout << current_time;
//     std::cout << '\n';
//     std::cout << "exp:";
//     std::cout << expiry_time;
//     std::cout << '\n';
//     std::cout << "diff:";
//     std::cout << std::difftime(expiry_time,current_time);
//     std::cout << '\n';

     expiry_file.close();
     return validation;
  }
  return false;
}
