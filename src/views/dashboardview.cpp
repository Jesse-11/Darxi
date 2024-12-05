#include "dashboardview.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFrame>
#include <QDebug>

DashboardView::DashboardView(QWidget *parent) : QWidget(parent) {
    setupUi();
}

void DashboardView::setupUi() {
    auto *layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    // Create header
    auto *header = new QFrame;
    header->setObjectName("header");
    auto *headerLayout = new QHBoxLayout(header);
    
    auto *logoLabel = new QLabel("Network Dashboard");
    logoLabel->setObjectName("headerLogo");
    
    m_userInfoLabel = new QLabel("Welcome");
    m_userInfoLabel->setObjectName("userInfo");
    
    auto *logoutButton = new QPushButton("Logout");
    logoutButton->setObjectName("headerButton");
    
    headerLayout->addWidget(logoLabel);
    headerLayout->addStretch();
    headerLayout->addWidget(m_userInfoLabel);
    headerLayout->addWidget(logoutButton);

    // Create tab widget
    m_tabWidget = new QTabWidget;
    m_tabWidget->setObjectName("mainTabs");

    createOverviewTab();
    createNetworkStatusTab();
    createSettingsTab();

    layout->addWidget(header);
    layout->addWidget(m_tabWidget);

    // Connect signals
    connect(logoutButton, &QPushButton::clicked, this, &DashboardView::logoutRequested);
}

void DashboardView::setUserInfo(const QString& username) {
    m_userInfoLabel->setText("Welcome, " + username);
}

void DashboardView::createOverviewTab() {
    auto *overviewWidget = new QWidget;
    auto *layout = new QVBoxLayout(overviewWidget);
    
    // Add overview widgets here
    layout->addWidget(new QLabel("Overview Dashboard"));
    
    m_tabWidget->addTab(overviewWidget, "Overview");
}

void DashboardView::createNetworkStatusTab() {
    auto *networkWidget = new QWidget;
    auto *layout = new QVBoxLayout(networkWidget);
    
    // Add network status widgets here
    layout->addWidget(new QLabel("Network Status"));
    
    m_tabWidget->addTab(networkWidget, "Network Status");
}

void DashboardView::createSettingsTab() {
    auto *settingsWidget = new QWidget;
    auto *layout = new QVBoxLayout(settingsWidget);
    
    // Add settings widgets here
    layout->addWidget(new QLabel("Settings"));
    
    m_tabWidget->addTab(settingsWidget, "Settings");
}

void DashboardView::updateDashboardData(const QVariantMap& data) {
    // Implement logic to update the dashboard with the new data
}

void DashboardView::updateNetworkStatus(const QString& status) {
    // Implement how you want to display the network status
}