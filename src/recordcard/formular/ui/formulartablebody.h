#ifndef FORMULARTABLEBODY_H
#define FORMULARTABLEBODY_H

#include <QWidget>
#include "../formularmodel.h"
#include "recordcard/recordcardbody.h"
#include <QUndoStack>

namespace Ui {
class FormularTableBody;
}

class FormularTableBody : public RecordCardBody
{
    Q_OBJECT

public:
    explicit FormularTableBody(QWidget *parent = nullptr);
    ~FormularTableBody();

private:
    Ui::FormularTableBody *ui;

    FormularModel *_model;

    void initActions();
    void initModel();
};

#endif // FORMULARTABLEBODY_H
