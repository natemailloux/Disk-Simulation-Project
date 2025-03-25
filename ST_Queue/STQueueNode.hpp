#ifndef DISKSIM_X_STQUEUENODE_HPP
#define DISKSIM_X_STQUEUENODE_HPP
#include "../FCFS_Queue/FCFSQueue.hpp"

class Request;

class STQueueNode {
public:
    STQueueNode(int _track, FCFSQueue * _q);
    STQueueNode *next();
    void next(STQueueNode *node);
    void track(int v );
    int track();
    FCFSQueue* getQ();

private:
    STQueueNode *_next;
    FCFSQueue * q;
    int trackNum;

};


#endif //DISKSIM_X_STQUEUENODE_HPP
