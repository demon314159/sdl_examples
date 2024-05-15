//
// execute.cpp
//

#include "execute.h"

Execute::Execute(Queue* queue, Score* score, Lamp* lamp)
    : m_queue(queue)
    , m_score(score)
    , m_lamp(lamp)
    , m_timer(0.0)
{
}

Execute::~Execute()
{
}

int Execute::advance(float seconds)
{
    int solenoid_id = SOLENOID_ID_NONE;
    if (m_timer > 0.0) {
        m_timer -= seconds;
    } else {
        if (!m_queue->empty()) {
            QueueRec t = m_queue->get();
            switch(t.command) {
                case QCOMMAND_NOP:
                    break;
                case QCOMMAND_DELAY:
                    m_timer = 1.0e-3 * (float) t.value;
                    break;
                case QCOMMAND_ADD_CREDIT:
                    m_score->add_credit(t.value);
                    break;
                case QCOMMAND_SOLENOID:
                    solenoid_id = t.value;
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
                case QCOMMAND_SET_BALL:
                    m_score->set_ball_in_play(t.value);
                    break;
                case QCOMMAND_SET_PLAYER:
                    m_score->set_player(t.value);
                    break;
                case QCOMMAND_SET_LAMP:
                    m_lamp->set(t.which_one, t.value ? true : false);
                    break;
                default:;
                    break;
            }
        }
    }
    return solenoid_id;
}

