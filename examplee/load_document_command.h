//
// load_document_command.h
//

#ifndef _LOAD_DOCUMENT_COMMAND_H_
#define _LOAD_DOCUMENT_COMMAND_H

#include "command.h"
#include "document.h"

class Toy;

class LoadDocumentCommand: public Command
{
public:
    LoadDocumentCommand(const char* file_name, Toy* toy);
    ~LoadDocumentCommand();
    void execute() override;
    void unexecute() override;
private:
    Toy* m_toy;
    Document* m_new_doc;
    Document* m_replaced_doc;
};

#endif // _LOAD_DOCUMENT_COMMAND_H_
