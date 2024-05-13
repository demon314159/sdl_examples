//
// execute.cpp
//

#include "execute.h"

Execute::Execute(Queue* queue, Score* score)
    : m_queue(queue)
    , m_score(score)
{
}

Execute::~Execute()
{
}

void Execute::advance(float seconds)
{
    if (!m_queue->empty()) {
        QueueRec t = m_queue->get();
        switch(t.command) {
            case QCOMMAND_NOP:
                break;
            case QCOMMAND_DELAY:
                break;
            case QCOMMAND_ADD_CREDIT:
                m_score->add_credit(t.value);
                break;
            case QCOMMAND_EJECT_BALL:
                break;
            case QCOMMAND_SET_SCORE:
                m_score->set_player_score(t.which_one, t.value);
                break;
            case QCOMMAND_ADD_SCORE:
                m_score->add_player_score(t.which_one, t.value);
                break;
            case QCOMMAND_SET_BLANK:
                m_score->set_player_blank(t.which_one, t.value ? true : false);
                break;
            case QCOMMAND_SET_FLASH:
                m_score->set_player_flash(t.which_one, t.value ? true : false);
                break;
            case QCOMMAND_DROP_TARGET:
                break;
            case QCOMMAND_PLAY_CHIME:
                break;
            default:;
                break;
        }
    }
}

