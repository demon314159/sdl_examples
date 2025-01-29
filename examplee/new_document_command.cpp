//
// new_document_command.cpp
//

#include "new_document_command.h"
#include "toy.h"

NewDocumentCommand::NewDocumentCommand(Toy* toy)
    : m_toy(toy)
    , m_new_doc(new Document())
    , m_replaced_doc(NULL)
{
}

NewDocumentCommand::~NewDocumentCommand()
{
    if (m_new_doc != NULL)
        delete m_new_doc;
    if (m_replaced_doc != NULL)
        delete m_replaced_doc;
}

void NewDocumentCommand::execute()
{
    m_new_doc->note_many_changes();
    m_replaced_doc = m_toy->replace_doc(m_new_doc);
    m_new_doc = NULL;
}

void NewDocumentCommand::unexecute()
{
    m_replaced_doc->note_many_changes();
    m_new_doc = m_toy->replace_doc(m_replaced_doc);
    m_replaced_doc = NULL;
}


