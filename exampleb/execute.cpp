//
// execute.cpp
//

#include "execute.h"

#define BONUS_DELAY 250 // milliseconds

Execute::Execute(Queue* queue, Queue* fast_queue, Score* score, Lamp* lamp, ReplayScore* replay_score)
    : m_queue(queue)
    , m_fast_queue(fast_queue)
    , m_score(score)
    , m_lamp(lamp)
    , m_replay_score(replay_score)
    , m_initial_high_game(0)
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
        if (!m_fast_queue->empty()) {
            solenoid_id = interpret(m_fast_queue->get());
        } else if (!m_queue->empty()) {
            solenoid_id = interpret(m_queue->get());
        }
    }
    return solenoid_id;
}

int Execute::interpret(const QueueRec& qrec)
{
    int solenoid_id = SOLENOID_ID_NONE;
    switch(qrec.command) {
        case QCOMMAND_NOP:
            break;
        case QCOMMAND_DELAY:
            m_timer = 1.0e-3 * (float) qrec.value;
            break;
        case QCOMMAND_ADD_CREDIT:
            m_score->add_credit(qrec.value);
            break;
        case QCOMMAND_SOLENOID:
            solenoid_id = qrec.value;
            break;
        case QCOMMAND_RESET_SCORE:
            m_score->reset_score();
            m_replay_score->reset();
            m_initial_high_game = m_score->get_high_game();
            break;
        case QCOMMAND_ADD_SCORE:
            m_score->add_player_score(qrec.which_one, qrec.value);
            if (m_replay_score->check(m_score)) {
                m_fast_queue->put(QCOMMAND_SOLENOID, 0, SOLENOID_ID_KNOCKER);
                m_fast_queue->put(QCOMMAND_ADD_CREDIT, 0, 1);
                m_fast_queue->put(QCOMMAND_DELAY, 0, BONUS_DELAY);
            }
            break;
        case QCOMMAND_SET_BLANK:
            m_score->set_player_blank(qrec.which_one, qrec.value ? true : false);
            break;
        case QCOMMAND_SET_FLASH:
            m_score->set_player_flash(qrec.which_one, qrec.value ? true : false);
            break;
        case QCOMMAND_SET_BALL:
            m_score->set_ball_in_play(qrec.value);
            break;
        case QCOMMAND_SET_PLAYER:
            m_score->set_player(qrec.value);
            break;
        case QCOMMAND_SET_LAMP:
            m_lamp->set(qrec.which_one, qrec.value ? true : false);
            break;
        case QCOMMAND_SET_MATCH:
            m_score->set_match(qrec.value);
            for (int i = 0; i < qrec.which_one; i++) {
                int score = m_score->get_player_score(i + 1);
                score = score / 10;
                score = score % 10;
                score = score * 10;
                if (score == qrec.value) {
                    m_queue->put(QCOMMAND_SOLENOID, 0, SOLENOID_ID_KNOCKER);
                    m_queue->put(QCOMMAND_ADD_CREDIT, 0, 1);
                    m_queue->put(QCOMMAND_DELAY, 0, BONUS_DELAY);
                }
            }
            if (m_score->get_high_game() > m_initial_high_game) {
                for (int i = 0; i < 3; i++) {
                    m_queue->put(QCOMMAND_SOLENOID, 0, SOLENOID_ID_KNOCKER);
                    m_queue->put(QCOMMAND_ADD_CREDIT, 0, 1);
                    m_queue->put(QCOMMAND_DELAY, 0, BONUS_DELAY);
                }
            }
            break;
        default:;
            break;
    }
    return solenoid_id;
}
