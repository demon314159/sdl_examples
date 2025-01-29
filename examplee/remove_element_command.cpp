//
// remove_element_command.cpp
//

#include "remove_element_command.h"

RemoveElementCommand::RemoveElementCommand(int ix, Document* doc)
    : m_ix(ix)
    , m_doc(doc)
{
}

RemoveElementCommand::~RemoveElementCommand()
{
}

void RemoveElementCommand::execute()
{
    m_doc->remove_element(m_ix);
}

void RemoveElementCommand::unexecute()
{
    m_doc->unremove_element(m_ix);
}

