#include "recordcardbody.h"

#include <QUndoStack>

RecordCardBody::RecordCardBody(QWidget *parent)
    : QWidget{parent}
{
    _stack = new QUndoStack(this);
}
