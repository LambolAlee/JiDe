#ifndef LAUNCHWINDOW_H
#define LAUNCHWINDOW_H

#include <QMainWindow>

#include "framelesswindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LaunchWindow; }
QT_END_NAMESPACE

class LaunchWindow : public QMainWindow
{
    Q_OBJECT

public:
    LaunchWindow(QWidget *parent = nullptr);
    ~LaunchWindow();

    QMenuBar *menuBar();

private:
    Ui::LaunchWindow *ui;
};
#endif // LAUNCHWINDOW_H
