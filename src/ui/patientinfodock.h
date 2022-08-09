#ifndef PATIENTINFODOCK_H
#define PATIENTINFODOCK_H

#include <QWidget>


class Patient;
class QPushButton;
class QToolButton;
class QLineEdit;

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
    void editButton_clicked();

    void triggerUndoButton(QToolButton *toolBtn, const char *propertyName, const QVariant &value);
    void triggerUndoButtonForSex(int id, bool bl);
    void triggerUndoButtonForEthnicity(int index);
    void reset(QLineEdit *lineEdit, const char *propertyName);

    void on_resetSexBtn_clicked();
    void on_resetEthnicBtn_clicked();

    void updateEditArea();

private:
    Ui::PatientInfoDock *ui;
    Patient *_patient; // no need to delete because patientdao will do this
    QPushButton *_editButton;
    QPushButton *_saveButton;
    QPushButton *_discardButton;

    QSize sizeHint() const override;

    void connectSignalsWithSlots();
    void createEditButtons();

    void saveChanges();
    void discardChanges();
    void backToShow();
    void updateShowArea();
};

#endif // PATIENTINFODOCK_H
