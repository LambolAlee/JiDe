#include "formulartablecard.h"
#include <QUndoStack>

#include "formulartablebody.h"


FormularTableCard::FormularTableCard(QWidget *parent)
    : RecordCardFrame(parent)
{
    setText(QStringLiteral("Formular"));
    setTitle(QStringLiteral("Formular"));
    setBody(new FormularTableBody(this));
    initUndoSystem();
}

void FormularTableCard::submit()
{
    // do something here...
    return RecordCardFrame::submit();
}

void FormularTableCard::cancel()
{
    // do something here...
    return RecordCardFrame::cancel();
}
