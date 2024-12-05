#ifndef DASHBOARDVIEW_H
#define DASHBOARDVIEW_H

#include <QWidget>
#include <QTabWidget>
#include <QLabel>

class DashboardView : public QWidget {
    Q_OBJECT

public:
    explicit DashboardView(QWidget *parent = nullptr);
    void setUserInfo(const QString& username);

signals:
    void logoutRequested();

public slots:
    void updateDashboardData(const QMap<QString, QVariant>& data);
    void updateNetworkStatus(const QString& status);

private:
    void setupUi();
    void createOverviewTab();
    void createNetworkStatusTab();
    void createSettingsTab();

    QTabWidget *m_tabWidget;
    QLabel *m_userInfoLabel;
};

#endif // DASHBOARDVIEW_H