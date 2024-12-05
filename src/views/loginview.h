#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include <QWidget>
#include <QLineEdit>

class LoginView : public QWidget {
    Q_OBJECT

public:
    explicit LoginView(QWidget *parent = nullptr);

signals:
    void loginRequested(const QString& username, const QString& password);
    void switchToSignupRequested();

private:
    void setupUi();
    void handleLoginAttempt();

    QLineEdit *m_usernameInput;
    QLineEdit *m_passwordInput;
};

#endif // LOGINVIEW_H