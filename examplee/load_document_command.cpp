//
// load_document_command.cpp
//

#include "load_document_command.h"
#include "toy.h"

LoadDocumentCommand::LoadDocumentCommand(const char* file_name, Toy* toy)
    : m_toy(toy)
    , m_new_doc(new Document(file_name))
    , m_replaced_doc(NULL)
{
}

LoadDocumentCommand::~LoadDocumentCommand()
{
    if (m_new_doc != NULL)
        delete m_new_doc;
    if (m_replaced_doc != NULL)
        delete m_replaced_doc;
}

void LoadDocumentCommand::execute()
{
    m_new_doc->note_many_changes();
    m_replaced_doc = m_toy->replace_doc(m_new_doc);
    m_new_doc = NULL;
}

void LoadDocumentCommand::unexecute()
{
    m_replaced_doc->note_many_changes();
    m_new_doc = m_toy->replace_doc(m_replaced_doc);
    m_replaced_doc = NULL;
}

