#include "loginview.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFrame>

LoginView::LoginView(QWidget *parent) : QWidget(parent) {
    setupUi();
}

void LoginView::setupUi() {
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // Logo section
    auto *logoContainer = new QFrame;
    logoContainer->setObjectName("logoContainer");
    logoContainer->setFixedHeight(150);
    auto *logoLayout = new QVBoxLayout(logoContainer);
    
    auto *logoLabel = new QLabel("NETWORK\nDASHBOARD");
    logoLabel->setObjectName("logoText");
    logoLabel->setAlignment(Qt::AlignCenter);
    logoLayout->addWidget(logoLabel);

    // Form section
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

    auto *createAccountButton = new QPushButton("Create New Account");
    createAccountButton->setObjectName("secondaryButton");
    createAccountButton->setFixedHeight(40);

    // Add widgets to form layout
    formLayout->addWidget(titleLabel);
    formLayout->addSpacing(20);
    formLayout->addWidget(m_usernameInput);
    formLayout->addWidget(m_passwordInput);
    formLayout->addSpacing(10);
    formLayout->addWidget(loginButton);
    formLayout->addSpacing(10);
    formLayout->addWidget(createAccountButton);
    formLayout->addStretch();

    // Center the form
    auto *centeringLayout = new QHBoxLayout;
    centeringLayout->addStretch();
    centeringLayout->addWidget(formContainer);
    centeringLayout->addStretch();

    mainLayout->addWidget(logoContainer);
    mainLayout->addLayout(centeringLayout);
    mainLayout->addStretch();

    // Connect signals
    connect(loginButton, &QPushButton::clicked, this, &LoginView::handleLoginAttempt);
    connect(createAccountButton, &QPushButton::clicked, this, &LoginView::switchToSignupRequested);
    connect(m_passwordInput, &QLineEdit::returnPressed, this, &LoginView::handleLoginAttempt);
}

void LoginView::handleLoginAttempt() {
    emit loginRequested(m_usernameInput->text(), m_passwordInput->text());
}