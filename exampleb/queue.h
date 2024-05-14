//
// queue.h
//

#ifndef _QUEUE_H_
#define _QUEUE_H_

struct QueueRec {
    int command;
    int which_one;
    int value;
};

#define MAX_ENTRIES 200

#define QCOMMAND_NOP             0
#define QCOMMAND_DELAY           1
#define QCOMMAND_ADD_CREDIT      2
#define QCOMMAND_SOLENOID        3
#define QCOMMAND_SET_SCORE       4
#define QCOMMAND_ADD_SCORE       5
#define QCOMMAND_SET_BLANK       6
#define QCOMMAND_SET_FLASH       7
#define QCOMMAND_SET_BALL        8
#define QCOMMAND_SET_PLAYER      9

#define SOLENOID_ID_NONE               0
#define SOLENOID_ID_OUT_HOLE           1
#define SOLENOID_ID_KNOCKER            2
#define SOLENOID_ID_TENS_CHIME         3
#define SOLENOID_ID_HUNDREDS_CHIME     4
#define SOLENOID_ID_THOUSANDS_CHIME    5
#define SOLENOID_ID_DROP_TARGET_JACKS  6
#define SOLENOID_ID_DROP_TARGET_QUEENS 7
#define SOLENOID_ID_DROP_TARGET_KINGS  8
#define SOLENOID_ID_DROP_TARGET_ACES   9
#define SOLENOID_ID_DROP_TARGET_ALL    10

class Queue
{
public:
    Queue();
    ~Queue();

    bool empty() const;
    bool full() const;
    void put(const QueueRec& rec);
    void put(int command, int which_one, int value);
    QueueRec get();

private:
    int m_put_ix;
    int m_get_ix;
    QueueRec m_rec[MAX_ENTRIES];
    int next_put_ix() const;
    int next_get_ix() const;
};

#endif // _QUEUE_H_
