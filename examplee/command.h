//
// command.h
//

#ifndef _COMMAND_H_
#define _COMMAND_H

#include "document.h"

class Toy;

class Command
{
public:
    virtual ~Command();
    virtual void execute() = 0;
    virtual void unexecute() = 0;
};

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

class NewCommand: public Command
{
public:
    NewCommand(Toy* toy);
    ~NewCommand();
    void execute() override;
    void unexecute() override;
private:
    Toy* m_toy;
    Document* m_new_doc;
    Document* m_replaced_doc;
};

#endif // _COMMAND_H_
