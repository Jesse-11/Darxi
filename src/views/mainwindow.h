#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "loginview.h"
#include "signupview.h"
#include "dashboardview.h"
#include "../models/user.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    void setupUi();
    void setupStyles();
    void connectSignals();
    void handleLogout();
    void handleLoginSuccess(const User& user);
    void handleLoginError(const QString& error);
    void handleSignupError(const QString& error);
    void switchToSignup();
    void switchToLogin();
    void switchToDashboard();

private:
    QStackedWidget* m_stackedWidget;
    LoginView* m_loginView;
    SignupView* m_signupView;
    DashboardView* m_dashboardView;
};

#endif // MAINWINDOW_H