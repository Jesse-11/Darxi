#include "mainwindow.h"
#include "../controllers/authcontroller.h"
#include "../controllers/dashboardcontroller.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDebug>
#include <QEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setMinimumSize(800, 800);
    installEventFilter(this);
    setupUi();
    setupStyles();
    connectSignals();
}

MainWindow::~MainWindow()
{
    delete m_stackedWidget;
    delete m_loginView;
    delete m_signupView;
    delete m_dashboardView;
}

void MainWindow::setupUi() {
    setWindowTitle("Darxi Networking");
    
    m_stackedWidget = new QStackedWidget(this);
    setCentralWidget(m_stackedWidget);

    // Create views
    m_loginView = new LoginView(this);
    m_signupView = new SignupView(this);
    m_dashboardView = new DashboardView(this);

    // Add to stacked widget
    m_stackedWidget->addWidget(m_loginView);
    m_stackedWidget->addWidget(m_signupView);
    m_stackedWidget->addWidget(m_dashboardView);

    // Start with login view
    m_stackedWidget->setCurrentWidget(m_loginView);
}

void MainWindow::connectSignals() {
    // Connect LoginView signals
    connect(m_loginView, &LoginView::loginRequested,
            &AuthController::instance(), &AuthController::login);
    connect(m_loginView, &LoginView::switchToSignupRequested,
            this, &MainWindow::switchToSignup);

    // Connect SignupView signals
    connect(m_signupView, &SignupView::signupRequested,
            &AuthController::instance(), &AuthController::signup);
    connect(m_signupView, &SignupView::switchToLoginRequested,
            this, &MainWindow::switchToLogin);

    // Connect DashboardView signals
    connect(m_dashboardView, &DashboardView::logoutRequested,
            this, &MainWindow::handleLogout);

    // Connect AuthController signals
    connect(&AuthController::instance(), &AuthController::loginSuccessful,
            this, &MainWindow::handleLoginSuccess);
    connect(&AuthController::instance(), &AuthController::loginFailed,
            this, &MainWindow::handleLoginError);
    connect(&AuthController::instance(), &AuthController::signupSuccessful,
            this, &MainWindow::switchToLogin);
    connect(&AuthController::instance(), &AuthController::signupFailed,
            this, &MainWindow::handleSignupError);

    // Connect DashboardController signals
    connect(&DashboardController::instance(), &DashboardController::networkStatusUpdated,
            m_dashboardView, &DashboardView::updateNetworkStatus);
    connect(&DashboardController::instance(), &DashboardController::dashboardDataLoaded,
            m_dashboardView, &DashboardView::updateDashboardData);
}

void MainWindow::switchToLogin() {
    m_stackedWidget->setCurrentWidget(m_loginView);
}

void MainWindow::switchToSignup() {
    m_stackedWidget->setCurrentWidget(m_signupView);
}

void MainWindow::switchToDashboard() {
    m_stackedWidget->setCurrentWidget(m_dashboardView);
}

void MainWindow::handleLoginSuccess(const User& user) {
    m_dashboardView->setUserInfo(user.getUsername());
    DashboardController::instance().loadUserDashboard(user);
    switchToDashboard();
}

void MainWindow::handleLoginError(const QString& error) {
    QMessageBox::warning(this, "Login Error", error);
}

void MainWindow::handleSignupError(const QString& error) {
    QMessageBox::warning(this, "Signup Error", error);
}

void MainWindow::handleLogout() {
    AuthController::instance().logout();
    switchToLogin();
}

void MainWindow::setupStyles() {
    // Set the application style
    setStyleSheet(R"(
        QMainWindow {
            background-color: #f0f0f0;
        }

        #header {
            background-color: #2c3e50;
            min-height: 60px;
            padding: 0 20px;
        }

        #headerLogo {
            color: white;
            font-size: 18px;
            font-weight: bold;
        }

        #userInfo {
            color: white;
            font-size: 14px;
        }

        #headerButton {
            background-color: transparent;
            color: white;
            border: 1px solid white;
            border-radius: 4px;
            padding: 5px 15px;
        }

        #headerButton:hover {
            background-color: rgba(255, 255, 255, 0.1);
        }

        #mainTabs {
            background-color: white;
        }

        QTabBar::tab {
            padding: 8px 20px;
        }

        QTabBar::tab:selected {
            background-color: #3498db;
            color: white;
        }

        #logoContainer {
            background-color: #3498db;
            padding: 20px;
        }

        #logoText {
            color: white;
            font-size: 24px;
            font-weight: bold;
            text-align: center;
        }

        QLineEdit {
            padding: 8px;
            border: 1px solid #bdc3c7;
            border-radius: 4px;
        }

        QPushButton#primaryButton {
            background-color: #3498db;
            color: white;
            border: none;
            border-radius: 4px;
            padding: 10px;
        }

        QPushButton#secondaryButton {
            background-color: transparent;
            color: #3498db;
            border: 1px solid #3498db;
            border-radius: 4px;
            padding: 10px;
        }
    )");
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::Resize) {
        QSize newSize = this->size();
        if (newSize.width() < 800 || newSize.height() < 800) {
            this->resize(qMax(newSize.width(), 800), qMax(newSize.height(), 800));
        }
    }
    return QMainWindow::eventFilter(obj, event);
}