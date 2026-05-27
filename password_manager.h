/**
 * @file password_manager.h
 * @author Moin Ahmed
 * @brief Contains functionality for basic random password generators and means of storing them in a csv file.
 * @date 2026
 *
 */

#ifndef PASSWORD_MANAGER_H
#define PASSWORD_MANAGER_H

#include <string>
#include <random>
#include <iostream>
#include <fstream>
// #include <QDebug>

std::string DATA_FILE_PATH = "data.csv";

/**
 * @brief generate_random_password (credits: https://generate-random.org/passwords/cpp)
 * @param length: length of the password
 * @param includeSpecial: whether to include special characters which are "!@#$%^&*()-_=+[]{}|;:,.<>?"
 * @return std::string with the random password
 */
std::string generate_random_password(int length, bool includeSpecial) {
    const std::string lowercase = "abcdefghijklmnopqrstuvwxyz";
    const std::string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string numbers = "0123456789";
    const std::string special = "!@#$%^&*()-_=+[]{}|;:,.<>?";

    std::string chars = lowercase + uppercase + numbers;
    if (includeSpecial) {
        chars += special;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, chars.length() - 1);

    std::string password;
    password.reserve(length);

    for (int i = 0; i < length; ++i) {
        password += chars[distrib(gen)];
    }

    return password;
}

/**
 * @brief store_user_info_to_csv
 * @param service: std
 * @param username
 * @param password
 */
void store_user_info_to_csv(std::string service, std::string username, std::string password)
{
    std::fstream password_file(DATA_FILE_PATH, std::ios::app);
    if (password_file.is_open()) {
        password_file << service << "," << username << "," << password << std::endl;
        password_file.close();
    } else {
        std::cerr << "File not found" << std::endl;
    }
}

#endif // PASSWORD_MANAGER_H
