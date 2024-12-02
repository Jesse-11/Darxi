#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFile>
#include <QLabel>
#include <QPushButton>
#include <QTabWidget>
#include <QMessageBox>
#include <QFrame>
#include <QFont>
#include <QScrollArea>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    setMinimumSize(800, 800);
    resize(800, 800);

    connect(this, &QWidget::windowTitleChanged, this, [this]() {
        if (this->size().width() < 800 || this->size().height() < 1000) {
            this->resize(
                std::max(800, this->size().width()),
                std::max(1000, this->size().height())
            );
        }
    });
    setupUi();
    setupStyles();
}


MainWindow::~MainWindow() = default;
void MainWindow::setupUi()
{
    // Set window properties
    setWindowTitle("Darxi Networking");
    setMinimumSize(800, 1000);
    
    // Create main stacked widget
    m_stackedWidget = new QStackedWidget(this);
    setCentralWidget(m_stackedWidget);

    //Create pages
    createLoginPage();
    createSignupPage();
    createDashboardPage();

    //Add pages to stacked widget
    m_stackedWidget->addWidget(m_loginPage);
    m_stackedWidget->addWidget(m_signupPage);
    m_stackedWidget->addWidget(m_dashboardPage);

    //Start with login Page
    m_stackedWidget->setCurrentWidget(m_loginPage);
}

void MainWindow::createLoginPage()
{
    m_loginPage = new QWidget;
    
    auto *mainLayout = new QVBoxLayout(m_loginPage);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // Create logo container with fixed height
    auto *logoContainer = new QFrame;
    logoContainer->setObjectName("logoContainer");
    logoContainer->setFixedHeight(150);
    auto *logoLayout = new QVBoxLayout(logoContainer);
    
    auto *logoLabel = new QLabel("NETWORK\nDASHBOARD");
    logoLabel->setObjectName("logoText");
    logoLabel->setAlignment(Qt::AlignCenter);
    logoLayout->addWidget(logoLabel);

    // Create form container with fixed width and vertical size policy
    auto *formContainer = new QFrame;
    formContainer->setObjectName("formContainer");
    formContainer->setFixedWidth(400);
    auto *formLayout = new QVBoxLayout(formContainer);
    formLayout->setSpacing(15);
    formLayout->setContentsMargins(40, 40, 40, 40);

    auto *titleLabel = new QLabel("Login");
    titleLabel->setObjectName("formTitle");

    m_usernameInput = new QLineEdit;
    m_usernameInput->setPlaceholderText("Username");
    m_usernameInput->setObjectName("loginInput");
    m_usernameInput->setFixedHeight(40);

    m_passwordInput = new QLineEdit;
    m_passwordInput->setPlaceholderText("Password");
    m_passwordInput->setEchoMode(QLineEdit::Password);
    m_passwordInput->setObjectName("loginInput");
    m_passwordInput->setFixedHeight(40);

    auto *loginButton = new QPushButton("Login");
    loginButton->setObjectName("primaryButton");
    loginButton->setFixedHeight(40);

    auto *forgotPasswordLink = new QPushButton("Forgot Password?");
    forgotPasswordLink->setObjectName("linkButton");
    forgotPasswordLink->setCursor(Qt::PointingHandCursor);
    forgotPasswordLink->setFixedHeight(30);

    auto *createAccountButton = new QPushButton("Create New Account");
    createAccountButton->setObjectName("secondaryButton");
    createAccountButton->setFixedHeight(40);

    // Add widgets to form layout with controlled spacing
    formLayout->addWidget(titleLabel);
    formLayout->addSpacing(20);
    formLayout->addWidget(m_usernameInput);
    formLayout->addWidget(m_passwordInput);
    formLayout->addSpacing(10);
    formLayout->addWidget(loginButton);
    formLayout->addWidget(forgotPasswordLink);
    formLayout->addSpacing(10);
    formLayout->addWidget(createAccountButton);
    formLayout->addStretch();

    // Center the form in a horizontal layout
    auto *centeringLayout = new QHBoxLayout;
    centeringLayout->addStretch();
    centeringLayout->addWidget(formContainer);
    centeringLayout->addStretch();

    // Add all elements to main layout
    mainLayout->addWidget(logoContainer);
    mainLayout->addLayout(centeringLayout);
    mainLayout->addStretch();

    // Connect signals
    connect(loginButton, &QPushButton::clicked, this, &MainWindow::handleLogin);
    connect(createAccountButton, &QPushButton::clicked, this, &MainWindow::switchToSignup);
    connect(m_usernameInput, &QLineEdit::returnPressed, m_passwordInput, QOverload<>::of(&QWidget::setFocus));
    connect(m_passwordInput, &QLineEdit::returnPressed, this, &MainWindow::handleLogin);
}

void MainWindow::createSignupPage()
{
    m_signupPage = new QWidget;
    
    auto *mainLayout = new QVBoxLayout(m_signupPage);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // Logo container with fixed height
    auto *logoContainer = new QFrame;
    logoContainer->setObjectName("logoContainer");
    logoContainer->setFixedHeight(150);
    auto *logoLayout = new QVBoxLayout(logoContainer);
    
    auto *logoLabel = new QLabel("NETWORK\nDASHBOARD");
    logoLabel->setObjectName("logoText");
    logoLabel->setAlignment(Qt::AlignCenter);
    logoLayout->addWidget(logoLabel);

    // Form container with fixed width
    auto *formContainer = new QFrame;
    formContainer->setObjectName("formContainer");
    formContainer->setFixedWidth(400);
    auto *formLayout = new QVBoxLayout(formContainer);
    formLayout->setSpacing(15);
    formLayout->setContentsMargins(40, 40, 40, 40);

    auto *titleLabel = new QLabel("Create Account");
    titleLabel->setObjectName("formTitle");

    auto *fullNameInput = new QLineEdit;
    fullNameInput->setPlaceholderText("Full Name");
    fullNameInput->setObjectName("loginInput");
    fullNameInput->setFixedHeight(40);

    auto *emailInput = new QLineEdit;
    emailInput->setPlaceholderText("Email Address");
    emailInput->setObjectName("loginInput");
    emailInput->setFixedHeight(40);

    auto *newUsernameInput = new QLineEdit;
    newUsernameInput->setPlaceholderText("Choose Username");
    newUsernameInput->setObjectName("loginInput");
    newUsernameInput->setFixedHeight(40);

    auto *newPasswordInput = new QLineEdit;
    newPasswordInput->setPlaceholderText("Choose Password");
    newPasswordInput->setEchoMode(QLineEdit::Password);
    newPasswordInput->setObjectName("loginInput");
    newPasswordInput->setFixedHeight(40);

    auto *confirmPasswordInput = new QLineEdit;
    confirmPasswordInput->setPlaceholderText("Confirm Password");
    confirmPasswordInput->setEchoMode(QLineEdit::Password);
    confirmPasswordInput->setObjectName("loginInput");
    confirmPasswordInput->setFixedHeight(40);

    auto *infoText = new QLabel("Password must contain at least 8 characters, including uppercase, lowercase, numbers, and special characters.");
    infoText->setObjectName("infoText");
    infoText->setWordWrap(true);
    infoText->setAlignment(Qt::AlignLeft);
    infoText->setStyleSheet("font-size: 11px; color: #666;");

    auto *signupButton = new QPushButton("Create Account");
    signupButton->setObjectName("primaryButton");
    signupButton->setFixedHeight(40);

    auto *backToLoginButton = new QPushButton("Already have an account? Login");
    backToLoginButton->setObjectName("secondaryButton");
    backToLoginButton->setFixedHeight(40);

    // Add widgets to form layout with controlled spacing
    formLayout->addWidget(titleLabel);
    formLayout->addSpacing(20);
    formLayout->addWidget(fullNameInput);
    formLayout->addWidget(emailInput);
    formLayout->addWidget(newUsernameInput);
    formLayout->addWidget(newPasswordInput);
    formLayout->addWidget(confirmPasswordInput);
    formLayout->addWidget(infoText);
    formLayout->addSpacing(10);
    formLayout->addWidget(signupButton);
    formLayout->addSpacing(5);
    formLayout->addWidget(backToLoginButton);
    formLayout->addStretch();

    // Center the form in a horizontal layout
    auto *centeringLayout = new QHBoxLayout;
    centeringLayout->addStretch();
    centeringLayout->addWidget(formContainer);
    centeringLayout->addStretch();

    // Add all elements to main layout
    mainLayout->addWidget(logoContainer);
    mainLayout->addLayout(centeringLayout);
    mainLayout->addStretch();

    // Connect signals
    connect(signupButton, &QPushButton::clicked, this, &MainWindow::handleSignup);
    connect(backToLoginButton, &QPushButton::clicked, this, &MainWindow::switchToLogin);

    // Add enter key navigation
    connect(fullNameInput, &QLineEdit::returnPressed, emailInput, QOverload<>::of(&QWidget::setFocus));
    connect(emailInput, &QLineEdit::returnPressed, newUsernameInput, QOverload<>::of(&QWidget::setFocus));
    connect(newUsernameInput, &QLineEdit::returnPressed, newPasswordInput, QOverload<>::of(&QWidget::setFocus));
    connect(newPasswordInput, &QLineEdit::returnPressed, confirmPasswordInput, QOverload<>::of(&QWidget::setFocus));
    connect(confirmPasswordInput, &QLineEdit::returnPressed, this, &MainWindow::handleSignup);
}

void MainWindow::createDashboardPage()
{
    m_dashboardPage = new QWidget;
    auto *layout = new QVBoxLayout(m_dashboardPage);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    // Create header
    auto *header = new QFrame;
    header->setObjectName("header");
    auto *headerLayout = new QHBoxLayout(header);
    
    auto *logoLabel = new QLabel("Network Dashboard");
    logoLabel->setObjectName("headerLogo");
    
    auto *userInfo = new QLabel("Welcome, User");
    userInfo->setObjectName("userInfo");
    
    headerLayout->addWidget(logoLabel);
    headerLayout->addStretch();
    headerLayout->addWidget(userInfo);

    // Create tab widget
    m_tabWidget = new QTabWidget;
    m_tabWidget->setObjectName("mainTabs");

    // Add tabs
    m_tabWidget->addTab(new QWidget(), "Overview");
    m_tabWidget->addTab(new QWidget(), "Network Status");
    m_tabWidget->addTab(new QWidget(), "Performance");
    m_tabWidget->addTab(new QWidget(), "Settings");

    // Add widgets to main layout
    layout->addWidget(header);
    layout->addWidget(m_tabWidget);
}

void MainWindow::setupStyles()
{
    // Base color palette remains the same
    QPalette palette;
    palette.setColor(QPalette::Window, QColor("#f0f0f0"));
    palette.setColor(QPalette::WindowText, QColor("#2c3e50"));
    palette.setColor(QPalette::Base, QColor("#ffffff"));
    palette.setColor(QPalette::AlternateBase, QColor("#f5f5f5"));
    palette.setColor(QPalette::Text, QColor("#2c3e50"));
    palette.setColor(QPalette::Button, QColor("#3498db"));
    palette.setColor(QPalette::ButtonText, QColor("#ffffff"));
    setPalette(palette);

    // Updated stylesheet without box-sizing property
    setStyleSheet(R"(
        QMainWindow {
            min-width: 400px;
            min-height: 600px;
        }

        #logoContainer {
            background-color: #3498db;
            min-height: 100px;
            max-height: 200px;
        }

        #logoText {
            color: white;
            font-size: 24px;
            font-weight: bold;
            padding: 20px;
        }

        #formContainer {
            background-color: white;
            margin: 20px;
            padding: 20px;
            border-radius: 8px;
            min-width: 300px;
            max-width: 500px;
        }

        #formTitle {
            font-size: 24px;
            color: #2c3e50;
            font-weight: bold;
            margin-bottom: 20px;
            qproperty-alignment: AlignCenter;
        }

        QLineEdit {
            padding: 8px;
            border: 1px solid #bdc3c7;
            border-radius: 4px;
            font-size: 14px;
            margin: 5px 0;
            min-height: 35px;
            min-width: 200px;
        }

        QPushButton {
            padding: 10px;
            border-radius: 4px;
            font-size: 14px;
            min-height: 40px;
            margin: 5px 0;
            min-width: 200px;
        }

        #primaryButton {
            background-color: #3498db;
            color: white;
            border: none;
        }

        #secondaryButton {
            background-color: transparent;
            color: #3498db;
            border: 1px solid #3498db;
        }

        #infoText {
            font-size: 12px;
            color: #7f8c8d;
            margin: 10px 0;
            line-height: 1.4;
        }

        QScrollArea {
            border: none;
            background: transparent;
        }
    )");
}


void MainWindow::handleLogin()
{
    // Add authentication logic here
    m_stackedWidget->setCurrentWidget(m_dashboardPage);
}

void MainWindow::switchToSignup()
{
    m_stackedWidget->setCurrentWidget(m_signupPage);
}

void MainWindow::switchToLogin()
{
    m_stackedWidget->setCurrentWidget(m_loginPage);
}

void MainWindow::handleSignup()
{
    // Add signup logic here
    m_stackedWidget->setCurrentWidget(m_loginPage);
}