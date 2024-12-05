#ifndef USER_H
#define USER_H

#include <QString>

class User {
public:
    User() = default;
    User(const QString& username, const QString& fullName, const QString& email);

    QString getUsername() const { return m_username; }
    QString getFullName() const { return m_fullName; }
    QString getEmail() const { return m_email; }

private:
    QString m_username;
    QString m_fullName;
    QString m_email;
};

#endif // USER_H
