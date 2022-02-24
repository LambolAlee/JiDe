#ifndef FORMULARTABLECARD_H
#define FORMULARTABLECARD_H

#include "recordcard/recordcardframe.h"
#include "formulartablebody.h"

class FormularTableCard : public RecordCardFrame
{
    Q_OBJECT

public:
    FormularTableCard(QWidget *parent = nullptr);

protected slots:
    void submit() override;
    void cancel() override;
};

#endif // FORMULARTABLECARD_H
