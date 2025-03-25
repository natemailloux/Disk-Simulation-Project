//
//

#ifndef FCFS_QUEUE_FCFSQUEUE_HPP
#define FCFS_QUEUE_FCFSQUEUE_HPP

#include<iostream>
#include "../CommonFiles/Queue.hpp"
#include "FCFSQueueNode.hpp"

class Request;

class FCFSQueue: public Queue {

public:
    FCFSQueue(): head{nullptr}, tail{nullptr} {}

    virtual void addRequest(int orderValue, Request *request, int cRWHeadTrack, int cRWHeadSector);

    virtual Request *getRequest();
    virtual bool empty();
    virtual void print();
    virtual ~FCFSQueue();

    virtual int size();
    virtual int headTrack();
    virtual int headSector();
    virtual Request *headReq();
    virtual int headNum();

private:
    FCFSQueueNode *head, *tail;
};


#endif //FCFS_QUEUE_FCFSQUEUE_HPP
