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

#define MAX_ENTRIES 100

#define QCOMMAND_NOP             0
#define QCOMMAND_DELAY           1
#define QCOMMAND_ADD_CREDIT      2
#define QCOMMAND_EJECT_BALL      3
#define QCOMMAND_SET_SCORE       4
#define QCOMMAND_ADD_SCORE       5
#define QCOMMAND_SET_BLANK       6
#define QCOMMAND_SET_FLASH       7
#define QCOMMAND_DROP_TARGET     8
#define QCOMMAND_PLAY_CHIME      9

class Queue
{
public:
    Queue();
    ~Queue();

    bool empty() const;
    bool full() const;
    void put(const QueueRec& rec);
    QueueRec get();

private:
    int m_put_ix;
    int m_get_ix;
    QueueRec m_rec[MAX_ENTRIES];
    int next_put_ix() const;
    int next_get_ix() const;
};

#endif // _QUEUE_H_
