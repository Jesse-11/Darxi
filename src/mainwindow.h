#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QTabWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QFrame>
#include <QResizeEvent>


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    

protected:
void resizeEvent(QResizeEvent *event) override
{
    // Ensure the window never becomes smaller than our minimum size
    QSize newSize = event->size();
    if (newSize.width() < 800 || newSize.height() < 1000) {
        newSize.setWidth(std::max(800, newSize.width()));
        newSize.setHeight(std::max(1000, newSize.height()));
        resize(newSize.width(), newSize.height());
    }
    QMainWindow::resizeEvent(event);
}
private slots:
    void handleLogin();
    void switchToSignup();
    void switchToLogin();
    void handleSignup();

private:
    void setupUi();
    void createLoginPage();
    void createSignupPage();
    void createDashboardPage();
    void setupStyles();

    
    
    //Main containers
    QStackedWidget *m_stackedWidget;
    QWidget *m_loginPage;
    QWidget *m_signupPage;
    QWidget *m_dashboardPage;

    //Login widgets
    QLineEdit *m_usernameInput;
    QLineEdit *m_passwordInput;

    //Signup widgets
    QLineEdit *m_fullNameInput;
    QLineEdit *m_emailInput;
    QLineEdit *m_newUsernameInput;
    QLineEdit *m_newPasswordInput;
    QLineEdit *m_confirmPasswordInput;


    //Dashboard widgets
    QTabWidget *m_tabWidget;
    QLabel *m_statusLabel;

    //Style 
    QString loadStyleSheet(const QString &filename);
    void applyTheme();
};

#endif // MAINWINDOW_H