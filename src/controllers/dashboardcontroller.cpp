#include "dashboardcontroller.h"
#include <QDebug>
#include <QVariant>

DashboardController* DashboardController::m_instance = nullptr;

DashboardController::~DashboardController()
{
    m_instance = nullptr;
}

DashboardController& DashboardController::instance() {
    if (!m_instance) {
        m_instance = new DashboardController(nullptr);
    }
    return *m_instance;
}

DashboardController::DashboardController(QObject *parent)
    : QObject(parent)
{
}

void DashboardController::loadUserDashboard(const User& user) {
    // Implement dashboard loading logic
}

void DashboardController::refreshNetworkStatus() {
    fetchNetworkStatus();
}

void DashboardController::fetchNetworkStatus() {
    // TODO: Implement actual network status checking
    // This is a placeholder implementation
    emit networkStatusUpdated("Network Status: Connected");
}

void DashboardController::fetchDashboardData() {
    QVariantMap dashboardData;
    dashboardData.insert("activeConnections", QVariant(5));
    dashboardData.insert("networkSpeed", QVariant(QString("1 Gbps")));
    dashboardData.insert("systemStatus", QVariant(QString("Normal")));
    
    emit dashboardDataLoaded(dashboardData);
}