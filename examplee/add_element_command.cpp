//
// add_element_command.cpp
//

#include "add_element_command.h"

AddElementCommand::AddElementCommand(Element* e, Document* doc)
    : m_ix(0)
    , m_element_to_add(e)
    , m_doc(doc)
{
}

AddElementCommand::~AddElementCommand()
{
    if (m_element_to_add != NULL)
        delete m_element_to_add;
}

void AddElementCommand::execute()
{
    if (m_element_to_add == NULL) {
        m_doc->unremove_element(m_ix);
    } else {
        m_ix = m_doc->elements();
        m_doc->add_element(m_element_to_add);
        m_element_to_add = NULL;
    }
}

void AddElementCommand::unexecute()
{
    if (m_ix == (m_doc->elements() - 1)) {
        m_element_to_add = m_doc->remove_last_element();
    } else {
        m_doc->remove_element(m_ix);
    }
}


