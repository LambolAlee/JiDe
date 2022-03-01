#ifndef RECORDMANAGER_H
#define RECORDMANAGER_H

#include <QMainWindow>

#include "framelesswindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class RecordManager; }
QT_END_NAMESPACE

#ifdef Q_OS_MAC
class RecordManager : public CFramelessWindow
#endif// Q_OS_MAC

#ifdef Q_OS_WIN
class RecordManager : public QMainWindow
#endif// Q_OS_WIN
{
    Q_OBJECT

public:
    RecordManager(QWidget *parent = nullptr);
    ~RecordManager();

    QMenuBar *menuBar();

private:
    Ui::RecordManager *ui;
};
#endif // RECORDMANAGER_H
