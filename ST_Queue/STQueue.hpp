#ifndef DISKSIM_X_STQueue_HPP
#define DISKSIM_X_STQueue_HPP

#include<iostream>
#include "../CommonFiles/Queue.hpp"
#include "../FCFS_Queue/FCFSQueue.hpp"
#include "STQueueNode.hpp"

class Request;

class STQueue: public Queue {

public:
    STQueue(): head{nullptr}, tail{nullptr}{ }

    Request* getRequest();
    virtual void addRequest(int orderValue, Request *request, int cRWHeadTrack, int cRWHeadSector);

    STQueueNode * createNewQ(int orderValue, Request* request, int cRWHeadTrack, int cRWHeadSector);
    virtual bool empty();
    virtual void print();
    virtual ~STQueue();
    virtual int size();
    virtual int headTrack();
    virtual int headSector();
    virtual Request *headReq();
    virtual int headNum();


private:

    STQueueNode * head, * tail;

};

#endif //DISKSIM_X_STQueue_HPP
