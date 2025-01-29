//
// remove_element_command.h
//

#ifndef _REMOVE_ELEMENT_COMMAND_H_
#define _REMOVE_ELEMENT_COMMAND_H

#include "command.h"
#include "document.h"

class RemoveElementCommand: public Command
{
public:
    RemoveElementCommand(int ix, Document* doc);
    ~RemoveElementCommand();
    void execute() override;
    void unexecute() override;
private:
    int m_ix;
    Document* m_doc;
};

#endif // _REMOVE_ELEMENT_COMMAND_H_
