#ifndef SIGNUPVIEW_H
#define SIGNUPVIEW_H

#include <QWidget>
#include <QLineEdit>

class SignupView : public QWidget {
    Q_OBJECT

public:
    explicit SignupView(QWidget *parent = nullptr);

signals:
    void signupRequested(const QString& fullName, const QString& email,
                        const QString& username, const QString& password);
    void switchToLoginRequested();

private:
    void setupUi();
    void handleSignupAttempt();

    QLineEdit *m_fullNameInput;
    QLineEdit *m_emailInput;
    QLineEdit *m_usernameInput;
    QLineEdit *m_passwordInput;
    QLineEdit *m_confirmPasswordInput;
};

#endif // SIGNUPVIEW_H