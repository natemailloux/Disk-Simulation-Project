#ifndef DISKSIM_X_LOOKQUEUE_HPP
#define DISKSIM_X_LOOKQUEUE_HPP

#include<iostream>
#include "../CommonFiles/Queue.hpp"
#include "../FCFS_Queue/FCFSQueue.hpp"

class Request;

class LookQueue: public Queue {

public:
    LookQueue(): head{nullptr}, tail{nullptr}, nextHead{nullptr}, nextTail{nullptr}{ }

    virtual void addRequest(int orderValue, Request *request, int cRWHeadTrack, int cRWHeadSector);

    virtual Request *getRequest();
    virtual bool empty();
    virtual void print();
    virtual ~LookQueue();

    void switchLists();
    void findLastDuplicate(FCFSQueueNode * node, FCFSQueueNode* rNode);
    void insertInc(FCFSQueueNode* head, FCFSQueueNode* rNode);
    void insertDec(FCFSQueueNode* head, FCFSQueueNode* rNode);
    virtual int size();
    int countNodesInList(FCFSQueueNode* iter);
    virtual int headTrack();
    virtual int headSector();
    virtual Request *headReq();
    virtual int headNum();

private:

    FCFSQueueNode *head, *tail, *nextHead, *nextTail;
    bool goingIn = true;
};

#endif //DISKSIM_X_LOOKQUEUE_HPP
