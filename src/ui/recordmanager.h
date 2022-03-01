#ifndef RECORDMANAGER_H
#define RECORDMANAGER_H

#include <QMainWindow>

#ifdef Q_OS_WIN
#include "framelesswindow.h"
#endif// Q_OS_WIN

QT_BEGIN_NAMESPACE
namespace Ui { class RecordManager; }
QT_END_NAMESPACE

class RecordManager : public QMainWindow
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
