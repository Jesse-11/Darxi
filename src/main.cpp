#include "mainwindow.h"
#include "database/databasemanager.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Enable debug output
    qDebug() << "Application starting...";
    qDebug() << "Application directory:" << QCoreApplication::applicationDirPath();

    if (!DatabaseManager::instance().initialize()) {
        qDebug() << "Database initialization failed";
        QMessageBox::critical(nullptr, "Error", "Failed to initialize database.");
        return 1;
    }
    
    qDebug() << "Database initialized successfully";

    
    MainWindow window;
    window.show();
    return app.exec();
}