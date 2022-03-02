#ifndef PATIENTINFODOCK_H
#define PATIENTINFODOCK_H

#include "bean/patient/patient.h"
#include "dao/patientdao.h"

#include <QWidget>
#include <QToolButton>
#include <QLineEdit>
#include <QPushButton>


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
    void returnButton_clicked();
    void editButton_clicked();

    void triggerUndoButton(QToolButton *toolBtn, const char *propertyName, const QString &changedText);
    void triggerUndoButtonForButtonGroup(int id, bool bl);
    void reset(QLineEdit *lineEdit, const char *propertyName);

    void on_resetSexBtn_clicked();
    void on_resetEthnicBtn_clicked();

private:
    Ui::PatientInfoDock *ui;
    Patient *_patient; // no need to delete because patientdao will do this
    QPushButton *_returnButton;
    QPushButton *_editButton;
    QPushButton *_saveButton;
    QPushButton *_discardButton;

    QSize sizeHint() const override;

    void connectSignalsWithSlots();
    void createNavigateBar();

    void updateEditArea();
    void updateShowArea();
};

#endif // PATIENTINFODOCK_H
