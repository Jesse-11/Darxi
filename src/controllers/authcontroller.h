#ifndef AUTHCONTROLLER_H
#define AUTHCONTROLLER_H

#include <QObject>
#include "../models/user.h"

class AuthController : public QObject {
    Q_OBJECT

public:
    static AuthController& instance();
    bool login(const QString& username, const QString& password);
    bool signup(const QString& fullName, const QString& email, 
                const QString& username, const QString& password);
    void logout();

signals:
    void loginSuccessful(const User& user);
    void loginFailed(const QString& error);
    void signupSuccessful();
    void signupFailed(const QString& error);

private:
    explicit AuthController(QObject *parent = nullptr);
    AuthController(const AuthController&) = delete;
    AuthController& operator=(const AuthController&) = delete;
};

#endif // AUTHCONTROLLER_H
