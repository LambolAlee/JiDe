#ifndef PATIENTINFODOCK_H
#define PATIENTINFODOCK_H

#include <QWidget>

namespace Ui {
class PatientInfoDock;
}

class PatientInfoDock : public QWidget
{
    Q_OBJECT

public:
    explicit PatientInfoDock(QWidget *parent = nullptr);
    ~PatientInfoDock();

private slots:
    void on_returnBtn_clicked();

    void on_editButton_clicked();

private:
    Ui::PatientInfoDock *ui;
};

#endif // PATIENTINFODOCK_H
