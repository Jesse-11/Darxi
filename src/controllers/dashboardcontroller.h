#ifndef DASHBOARDCONTROLLER_H
#define DASHBOARDCONTROLLER_H

#include <QObject>
#include "../models/user.h"

class DashboardController : public QObject {
    Q_OBJECT

public:
    static DashboardController& instance();
    ~DashboardController();
    void loadUserDashboard(const User& user);
    void refreshNetworkStatus();

signals:
    void networkStatusUpdated(const QString& status);
    void dashboardDataLoaded(const QVariantMap& data);

private:
    static DashboardController* m_instance;
    explicit DashboardController(QObject *parent = nullptr);

    DashboardController(const DashboardController&) = delete;
    DashboardController& operator=(const DashboardController&) = delete;

    void fetchNetworkStatus();
    void fetchDashboardData();
};

#endif // DASHBOARDCONTROLLER_H