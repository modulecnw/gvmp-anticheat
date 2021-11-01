#pragma once
#include <string>
class UserData
{
public:
    UserData(int id) : m_id(id) {}

    int m_id;
    std::string m_username;
};