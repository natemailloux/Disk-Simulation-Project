//
// Created by natem on 10/24/2024.
//

#ifndef DISKSIM_X_PICKUPQUEUE_HPP
#define DISKSIM_X_PICKUPQUEUE_HPP

#include "../CommonFiles/Queue.hpp"
#include "../FCFS_Queue/FCFSQueue.hpp"

class Request;

class PickUpQueue: public Queue {

public:
    PickUpQueue(): head{nullptr}, tail{nullptr}{ }

    virtual void addRequest(int orderValue, Request *request, int cRWHeadTrack, int cRWHeadSector);

    virtual Request *getRequest();
    virtual bool empty();
    virtual void print();
    virtual ~PickUpQueue();

    void findLastDuplicate(FCFSQueueNode * node, FCFSQueueNode* rNode);
    static bool betweenNodes(FCFSQueueNode* iter, FCFSQueueNode* rNode);
    bool beforeHead(FCFSQueueNode * rNode, int headTrack);
    virtual int size();
    virtual int headTrack();
    virtual int headSector();
    virtual Request *headReq();
    virtual int headNum();

private:

    FCFSQueueNode *head, *tail;

};

#endif //DISKSIM_X_PICKUPQUEUE_HPP
