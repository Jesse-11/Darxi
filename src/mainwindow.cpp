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
#include "database/databasemanager.h"

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

    // Logo container setup
    auto *logoContainer = new QFrame;
    logoContainer->setObjectName("logoContainer");
    logoContainer->setFixedHeight(150);
    auto *logoLayout = new QVBoxLayout(logoContainer);
    
    auto *logoLabel = new QLabel("NETWORK\nDASHBOARD");
    logoLabel->setObjectName("logoText");
    logoLabel->setAlignment(Qt::AlignCenter);
    logoLayout->addWidget(logoLabel);

    // Form container setup
    auto *formContainer = new QFrame;
    formContainer->setObjectName("formContainer");
    formContainer->setFixedWidth(400);
    auto *formLayout = new QVBoxLayout(formContainer);
    formLayout->setSpacing(15);
    formLayout->setContentsMargins(40, 40, 40, 40);

    auto *titleLabel = new QLabel("Create Account");
    titleLabel->setObjectName("formTitle");

    // Initialize member variables with the input fields
    m_fullNameInput = new QLineEdit(this);
    m_fullNameInput->setPlaceholderText("Full Name");
    m_fullNameInput->setObjectName("loginInput");
    m_fullNameInput->setFixedHeight(40);

    m_emailInput = new QLineEdit(this);
    m_emailInput->setPlaceholderText("Email Address");
    m_emailInput->setObjectName("loginInput");
    m_emailInput->setFixedHeight(40);

    m_newUsernameInput = new QLineEdit(this);
    m_newUsernameInput->setPlaceholderText("Choose Username");
    m_newUsernameInput->setObjectName("loginInput");
    m_newUsernameInput->setFixedHeight(40);

    m_newPasswordInput = new QLineEdit(this);
    m_newPasswordInput->setPlaceholderText("Choose Password");
    m_newPasswordInput->setEchoMode(QLineEdit::Password);
    m_newPasswordInput->setObjectName("loginInput");
    m_newPasswordInput->setFixedHeight(40);

    m_confirmPasswordInput = new QLineEdit(this);
    m_confirmPasswordInput->setPlaceholderText("Confirm Password");
    m_confirmPasswordInput->setEchoMode(QLineEdit::Password);
    m_confirmPasswordInput->setObjectName("loginInput");
    m_confirmPasswordInput->setFixedHeight(40);

    // Add widgets to form layout with controlled spacing
    formLayout->addWidget(titleLabel);
    formLayout->addSpacing(20);
    formLayout->addWidget(m_fullNameInput);
    formLayout->addWidget(m_emailInput);
    formLayout->addWidget(m_newUsernameInput);
    formLayout->addWidget(m_newPasswordInput);
    formLayout->addWidget(m_confirmPasswordInput);

    // Add the standard buttons
    auto *signupButton = new QPushButton("Create Account");
    signupButton->setObjectName("primaryButton");
    signupButton->setFixedHeight(40);

    auto *backToLoginButton = new QPushButton("Already have an account? Login");
    backToLoginButton->setObjectName("secondaryButton");
    backToLoginButton->setFixedHeight(40);

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
    QString username = m_usernameInput->text();
    QString password = m_passwordInput->text();
    
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Login Error", "Please enter both username and password.");
        return;
    }
    
    if (DatabaseManager::instance().validateCredentials(username, password)) {
        m_stackedWidget->setCurrentWidget(m_dashboardPage);
    } else {
        QMessageBox::warning(this, "Login Error", "Invalid username or password.");
    }
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
    qDebug() << "=== Starting Signup Process ===";

    // Check if input fields exist
    if (!m_fullNameInput || !m_emailInput || !m_newUsernameInput || 
        !m_newPasswordInput || !m_confirmPasswordInput) {
        qDebug() << "Error: One or more input fields are null";
        QMessageBox::critical(this, "Error", "Application initialization error");
        return;
    }

    // Get input values with validation
    QString fullName = m_fullNameInput->text().trimmed();
    QString email = m_emailInput->text().trimmed();
    QString username = m_newUsernameInput->text().trimmed();
    QString password = m_newPasswordInput->text().trimmed();
    QString confirmPassword = m_confirmPasswordInput->text().trimmed();

    qDebug() << "Input validation starting...";
    qDebug() << "Full Name length:" << fullName.length();
    qDebug() << "Email length:" << email.length();
    qDebug() << "Username length:" << username.length();
    qDebug() << "Password length:" << password.length();

    // Validation checks
    if (fullName.isEmpty() || email.isEmpty() || username.isEmpty() || 
        password.isEmpty() || confirmPassword.isEmpty()) {
        qDebug() << "Empty field detected";
        QMessageBox::warning(this, "Signup Error", "Please fill in all fields.");
        return;
    }

    if (password != confirmPassword) {
        qDebug() << "Password mismatch";
        QMessageBox::warning(this, "Signup Error", "Passwords do not match.");
        return;
    }

    qDebug() << "Attempting database creation...";
    
    try {
        // Check database connection
        if (!DatabaseManager::instance().isInitialized()) {
            qDebug() << "Database not initialized";
            QMessageBox::critical(this, "Error", "Database connection error");
            return;
        }

        // Attempt user creation
        qDebug() << "Calling createUser...";
        bool success = DatabaseManager::instance().createUser(
            fullName, email, username, password);

        if (success) {
            qDebug() << "User created successfully";
            QMessageBox::information(this, "Success", "Account created successfully!");
            switchToLogin();
        } else {
            qDebug() << "User creation failed";
            QMessageBox::warning(this, "Signup Error", "Username or email already exists.");
        }
    } catch (const std::exception& e) {
        qDebug() << "Exception caught during signup:" << e.what();
        QMessageBox::critical(this, "Error", "An unexpected error occurred during signup.");
    }

    qDebug() << "=== Signup Process Complete ===";
}