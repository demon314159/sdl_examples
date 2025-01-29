//
// add_element_command.h
//

#ifndef _ADD_ELEMENT_COMMAND_H_
#define _ADD_ELEMENT_COMMAND_H

#include "command.h"
#include "document.h"

class AddElementCommand: public Command
{
public:
    AddElementCommand(Element* e, Document* doc);
    ~AddElementCommand();
    void execute() override;
    void unexecute() override;
private:
    int m_ix;
    Element* m_element_to_add;
    Document* m_doc;
};

#endif // _ADD_ELEMENT_COMMAND_H_
