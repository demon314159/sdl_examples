//
// new_document_command.h
//

#ifndef _NEW_DOCUMENT_COMMAND_H_
#define _NEW_DOCUMENT_COMMAND_H

#include "command.h"
#include "document.h"

class Toy;

class NewDocumentCommand: public Command
{
public:
    NewDocumentCommand(Toy* toy);
    ~NewDocumentCommand();
    void execute() override;
    void unexecute() override;
private:
    Toy* m_toy;
    Document* m_new_doc;
    Document* m_replaced_doc;
};

#endif // _NEW_DOCUMENT_COMMAND_H_
