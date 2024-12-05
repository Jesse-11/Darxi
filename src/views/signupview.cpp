#include "signupview.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFrame>
#include <QMessageBox>

SignupView::SignupView(QWidget *parent) : QWidget(parent) {
    setupUi();
}

void SignupView::setupUi() {
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

    auto *titleLabel = new QLabel("Create Account");
    titleLabel->setObjectName("formTitle");

    m_fullNameInput = new QLineEdit;
    m_fullNameInput->setPlaceholderText("Full Name");
    m_fullNameInput->setObjectName("loginInput");
    m_fullNameInput->setFixedHeight(40);

    m_emailInput = new QLineEdit;
    m_emailInput->setPlaceholderText("Email Address");
    m_emailInput->setObjectName("loginInput");
    m_emailInput->setFixedHeight(40);

    m_usernameInput = new QLineEdit;
    m_usernameInput->setPlaceholderText("Choose Username");
    m_usernameInput->setObjectName("loginInput");
    m_usernameInput->setFixedHeight(40);

    m_passwordInput = new QLineEdit;
    m_passwordInput->setPlaceholderText("Choose Password");
    m_passwordInput->setEchoMode(QLineEdit::Password);
    m_passwordInput->setObjectName("loginInput");
    m_passwordInput->setFixedHeight(40);

    m_confirmPasswordInput = new QLineEdit;
    m_confirmPasswordInput->setPlaceholderText("Confirm Password");
    m_confirmPasswordInput->setEchoMode(QLineEdit::Password);
    m_confirmPasswordInput->setObjectName("loginInput");
    m_confirmPasswordInput->setFixedHeight(40);

    auto *signupButton = new QPushButton("Create Account");
    signupButton->setObjectName("primaryButton");
    signupButton->setFixedHeight(40);

    auto *backToLoginButton = new QPushButton("Already have an account? Login");
    backToLoginButton->setObjectName("secondaryButton");
    backToLoginButton->setFixedHeight(40);

    // Add widgets to form layout
    formLayout->addWidget(titleLabel);
    formLayout->addSpacing(20);
    formLayout->addWidget(m_fullNameInput);
    formLayout->addWidget(m_emailInput);
    formLayout->addWidget(m_usernameInput);
    formLayout->addWidget(m_passwordInput);
    formLayout->addWidget(m_confirmPasswordInput);
    formLayout->addSpacing(10);
    formLayout->addWidget(signupButton);
    formLayout->addWidget(backToLoginButton);
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
    connect(signupButton, &QPushButton::clicked, this, &SignupView::handleSignupAttempt);
    connect(backToLoginButton, &QPushButton::clicked, this, &SignupView::switchToLoginRequested);
}

void SignupView::handleSignupAttempt() {
    if (m_passwordInput->text() != m_confirmPasswordInput->text()) {
        QMessageBox::warning(this, "Error", "Passwords do not match");
        return;
    }

    emit signupRequested(
        m_fullNameInput->text(),
        m_emailInput->text(),
        m_usernameInput->text(),
        m_passwordInput->text()
    );
}