#ifndef PATIENTINFODOCK_H
#define PATIENTINFODOCK_H

#include "patient/patientinfo.h"

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

    void setById(int id);

private slots:
    void on_returnBtn_clicked();
    void on_editButton_clicked();
    void on_nameLE_textEdited(const QString &arg1);

private:
    Ui::PatientInfoDock *ui;
    PatientInfo _info;

    void updateEditArea();
    void updateShowArea();
};

#endif // PATIENTINFODOCK_H
