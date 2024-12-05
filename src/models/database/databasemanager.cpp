// databasemanager.cpp
#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QCryptographicHash>
#include <QCoreApplication>
#include <QDebug>

const QString DatabaseManager::DATABASE_FILENAME = "network_dashboard.db";

DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager instance;
    return instance;
}

DatabaseManager::DatabaseManager(QObject *parent)
    : QObject(parent)
{
    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setDatabaseName(DATABASE_FILENAME);
}

DatabaseManager::~DatabaseManager()
{
    if (m_database.isOpen()) {
        m_database.close();
    }
}

bool DatabaseManager::initialize()
{
    // Set the database file path to be in the application directory
    QString dbPath = QCoreApplication::applicationDirPath() + "/" + DATABASE_FILENAME;
    m_database.setDatabaseName(dbPath);

    // Try to open or create the database
    if (!m_database.open()) {
        qDebug() << "Failed to open database at:" << dbPath;
        qDebug() << "Error:" << m_database.lastError().text();
        return false;
    }

    // Create tables if they don't exist
    if (!createTables()) {
        qDebug() << "Failed to create tables";
        qDebug() << "Error:" << m_database.lastError().text();
        m_database.close();
        return false;
    }

    qDebug() << "Database initialized successfully at:" << dbPath;
    return true;
}

bool DatabaseManager::createTables()
{
    QSqlQuery query;
    return query.exec(
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "full_name TEXT NOT NULL,"
        "email TEXT UNIQUE NOT NULL,"
        "username TEXT UNIQUE NOT NULL,"
        "password_hash TEXT NOT NULL,"
        "created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP"
        ")"
    );
}

QString DatabaseManager::hashPassword(const QString& password)
{
    QByteArray passwordBytes = password.toUtf8();
    QByteArray hashedBytes = QCryptographicHash::hash(passwordBytes, QCryptographicHash::Sha256);
    return QString(hashedBytes.toHex());
}

bool DatabaseManager::userExists(const QString& username)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM users WHERE username = ?");
    query.addBindValue(username);
    
    if (!query.exec() || !query.next()) {
        return false;
    }
    
    return query.value(0).toInt() > 0;
}

bool DatabaseManager::validateCredentials(const QString& username, const QString& password)
{
    QSqlQuery query;
    query.prepare("SELECT password_hash FROM users WHERE username = ?");
    query.addBindValue(username);
    
    if (!query.exec() || !query.next()) {
        return false;
    }
    
    QString storedHash = query.value(0).toString();
    QString inputHash = hashPassword(password);
    
    return storedHash == inputHash;
}

bool DatabaseManager::createUser(const QString& fullName, const QString& email,
                               const QString& username, const QString& password)
{
    if (userExists(username)) {
        return false;
    }

    QSqlQuery query;
    query.prepare(
        "INSERT INTO users (full_name, email, username, password_hash) "
        "VALUES (?, ?, ?, ?)"
    );
    
    query.addBindValue(fullName);
    query.addBindValue(email);
    query.addBindValue(username);
    query.addBindValue(hashPassword(password));
    
    return query.exec();
}