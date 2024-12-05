#include "authcontroller.h"
#include "../models/database/databasemanager.h"
#include <QDebug>

AuthController::AuthController(QObject *parent) : QObject(parent) {}

AuthController& AuthController::instance() {
    static AuthController instance;
    return instance;
}

bool AuthController::login(const QString& username, const QString& password) {
    if (DatabaseManager::instance().validateCredentials(username, password)) {
        User user(username, "", ""); // In real app, fetch full user data
        emit loginSuccessful(user);
        return true;
    }
    
    emit loginFailed("Invalid username or password");
    return false;
}

bool AuthController::signup(const QString& fullName, const QString& email,
                          const QString& username, const QString& password) {
    if (DatabaseManager::instance().createUser(fullName, email, username, password)) {
        emit signupSuccessful();
        return true;
    }
    
    emit signupFailed("Username or email already exists");
    return false;
}

void AuthController::logout() {
    // Implement logout logic
}