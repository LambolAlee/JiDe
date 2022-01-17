#ifndef LAUNCHWINDOW_H
#define LAUNCHWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class LaunchWindow; }
QT_END_NAMESPACE

class LaunchWindow : public QMainWindow
{
    Q_OBJECT

public:
    LaunchWindow(QWidget *parent = nullptr);
    ~LaunchWindow();

private:
    Ui::LaunchWindow *ui;
};
#endif // LAUNCHWINDOW_H
