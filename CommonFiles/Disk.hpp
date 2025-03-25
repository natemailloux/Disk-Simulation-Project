 #include "../CommonFiles/Queue.hpp"
#include"../FCFS_Queue/FCFSQueueNode.hpp"
#include <string>
#include "EventNode.hpp"

class EventQueue;

class Disk {
public:
    Disk(Queue *waitQueue, std::string _diskName): queue(waitQueue), diskName(_diskName),
    headTrack(0), headSector(0), isBusy(false), startTime(0){}
    void processRequest(int orderValue, EventQueue *eventQueue, Request *req);
    // if the disk is busy, adds the req to the wait queue
    // otherwise, starts serving this request and adds
    // a disk done event to eventQueue

    void processDiskDone(EventQueue *eventQueue);
    // collects stats regarding the request that was just finished
    // if wait-queue is not empty, get a request from it
    //     and start serving it. This will create a diskdone event.
    // if the wait queue is emtpy, set the status of the disk to
    // idle

    int processTimer() { return queue->size(); }
    // keeps track of the number of elements in its wait queue
    // and returns that number.

    void addRequest(Request* req, int orderValue);
    string getFileName();

    std::string name() { return diskName; }

    double rotationTime(int sector);
    double seekTime(int track);
    double accessTime(Request * req);
    void setTrackAndSect(int track, int sector);

    void createDDoneEvent(Request * req, EventQueue* eventQueue);
    Queue* q() { return queue; }
    int track() { return headTrack; }
    int sector() { return headSector ; }


private:
    Queue * queue;
    bool isBusy;
    string diskName;
    int headTrack, headSector;
    double startTime;

};

class EventQueue {
public:

    EventQueue(): head(nullptr), tail(nullptr), currentTime(0) {}
    void insert(EventNode * node);
    EventNode* getEvent();
    bool empty() { return head == nullptr; }

    void addRequest( Request * req);
    void addTimer(double time);

    void curTime(double time) { currentTime = time; }
    double curTime() { return currentTime; }

    void print();

private:
    EventNode * head, *tail;
    double currentTime;

};