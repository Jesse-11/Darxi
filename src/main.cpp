#include "views/mainwindow.h"
#include "models/database/databasemanager.h"
#include "controllers/authcontroller.h"
#include "controllers/dashboardcontroller.h"
#include <QApplication>
#include <QMessageBox>
#include <QDebug>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    qDebug() << "Application starting...";
    qDebug() << "Application directory:" << QCoreApplication::applicationDirPath();

    // Initialize database
    if (!DatabaseManager::instance().initialize()) {
        qDebug() << "Database initialization failed";
        QMessageBox::critical(nullptr, "Error", "Failed to initialize database.");
        return 1;
    }
    
    qDebug() << "Database initialized successfully";

    // Create and show main window
    MainWindow window;
    window.show();

    return app.exec();
}