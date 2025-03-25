#ifndef DISKSIM_X_CLookQUEUE_HPP
#define DISKSIM_X_CLookQUEUE_HPP

#include<iostream>
#include "../CommonFiles/Queue.hpp"
#include "../FCFS_Queue/FCFSQueue.hpp"

class Request;

class CLookQueue: public Queue {

public:
    CLookQueue(): head{nullptr}, tail{nullptr}, nextHead{nullptr}, nextTail{nullptr}{ }

    virtual void addRequest(int orderValue, Request *request, int cRWHeadTrack, int cRWHeadSector);

    virtual Request *getRequest();
    virtual bool empty();
    virtual void print();
    virtual ~CLookQueue();

    void switchLists();
    void insertInc(FCFSQueueNode* _head, FCFSQueueNode* rNode);
    void findLastDuplicate(FCFSQueueNode * node, FCFSQueueNode* rNode);
    int countNodesInList(FCFSQueueNode* iter);
    virtual int size();

    virtual int headTrack();
    virtual int headSector();
    virtual Request* headReq();
    virtual int headNum();

private:

    FCFSQueueNode *head, *tail, *nextHead, *nextTail;

};

#endif //DISKSIM_X_CLookQUEUE_HPP
