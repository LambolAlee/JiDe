#include "Config.h"
#include "Json.h"

#include <QString>
#include <QStringList>
#include <QApplication>

extern const QLatin1String CONF_ROOT("%1/.recmed/%2");

Config::Config() {
    json = new Json(resolve(QLatin1String("config.json")), true); // 配置文件路径
}

Config::~Config() {
    delete json;
}

QString Config::getDatabaseType() const {
    return json->getString("database.type");
}

QString Config::getDatabaseHost() const {
    return json->getString("database.host");
}

QString Config::getDatabaseName() const {
    QString name = json->getString("database.db_files.selected_db");
    return resolve(name);
}

QString Config::getDatabaseUsername() const {
    return json->getString("database.username");
}

QString Config::getDatabasePassword() const {
    return json->getString("database.password");
}

bool Config::getDatabaseTestOnBorrow() const {
    return json->getBool("database.test_on_borrow", false);
}

QString Config::getDatabaseTestOnBorrowSql() const {
    return json->getString("database.test_on_borrow_sql", "SELECT 1");
}

int Config::getDatabaseMaxWaitTime() const {
    return json->getInt("database.max_wait_time", 5000);
}

int Config::getDatabaseMaxConnectionCount() const {
    return json->getInt("database.max_connection_count", 5);
}

int Config::getDatabasePort() const {
    return json->getInt("database.port", 0);
}

bool Config::isDatabaseDebug() const {
    return json->getBool("database.debug", false);
}

QStringList Config::getDatabaseSqlFiles() const {
    return json->getStringList("database.sql_files");
}

QStringList Config::getQssFiles() const {
    return json->getStringList("qss_files");
}

QString Config::resolve(QLatin1String relativePath)
{
    static QString rootPath = QApplication::applicationDirPath();
    return CONF_ROOT.arg(rootPath, relativePath);
}

QString Config::resolve(const QString &relativePath)
{
    static QString rootPath = QApplication::applicationDirPath();
    return CONF_ROOT.arg(rootPath, relativePath);
}
