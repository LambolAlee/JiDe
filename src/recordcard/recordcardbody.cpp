#include "recordcardbody.h"

RecordCardBody::RecordCardBody(QWidget *parent)
    : QWidget{parent}
{
    _stack = new QUndoStack(this);
}
