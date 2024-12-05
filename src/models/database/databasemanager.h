// databasemanager.h
#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QString>

class DatabaseManager : public QObject
{
    Q_OBJECT

public:
    static DatabaseManager& instance();
    bool isInitialized() const { return m_database.isOpen(); }
    
    bool initialize();
    bool userExists(const QString& username);
    bool validateCredentials(const QString& username, const QString& password);
    bool createUser(const QString& fullName, const QString& email, 
                   const QString& username, const QString& password);
    
    // Prevent copying
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

private:
    explicit DatabaseManager(QObject *parent = nullptr);
    ~DatabaseManager();

    bool createTables();
    QString hashPassword(const QString& password);
    
    QSqlDatabase m_database;
    static const QString DATABASE_FILENAME;
};

#endif // DATABASEMANAGER_H