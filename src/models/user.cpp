#include "user.h"

User::User(const QString& username, const QString& fullName, const QString& email)
    : m_username(username)
    , m_fullName(fullName)
    , m_email(email)
{
}