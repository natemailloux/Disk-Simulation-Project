#include "Disk.hpp"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>


string Disk::getFileName() {

    // this function gets a correct output file based on the disk's name
    // this was done as the file path was not set for a majority of the proj
    if ( diskName == "FCFS")
        return "output/FCFS_output";
    else if ( diskName == "ST" )
        return "output/STRACK_output";
    else if ( diskName == "LOOK" )
        return "output/LOOK_output";
    else if ( diskName == "CLOOK" )
        return "output/CLOOK_output";
    return "output/PICKUP_output";

}


void Disk::setTrackAndSect(int track, int sector) {

    // updates the disk's track and head to emulate the R/W head
    headTrack = track;
    if ( sector == 29 )
        headSector = 0;
    else
        headSector = sector + 1;

}


void Disk::processRequest(int orderValue, EventQueue *eventQueue, Request *req) {

    if (!isBusy) {
        createDDoneEvent(req, eventQueue);
        isBusy = true;
    }
    queue->addRequest(orderValue, req, headTrack, headTrack);

}


void Disk::processDiskDone(EventQueue *eQueue) {

    if (isBusy) {
        isBusy = false;

        string fileName = getFileName();
        ofstream outFS;
        outFS.open(fileName, ios::app);

        int width = 5, laterWidth = 10;
        double curTime = eQueue->curTime(), entry = queue->headReq()->time(), init = startTime,
        serv = curTime - startTime, wait = init - entry, timeInSys = serv + wait;

        if (startTime == entry) {
            wait = 0;
        }

        outFS << fixed << setprecision(2) << setw(width) << queue->headNum() << setw(width) << queue->headTrack() <<
        setw(width) << queue->headSector();
        outFS << setw(laterWidth) << entry << setw(laterWidth) << init << setw(laterWidth) << curTime << setw(laterWidth) <<
        wait << setw(laterWidth) << serv << setw(laterWidth) << timeInSys << endl;

        outFS.close();
        queue->getRequest();


    }
    if (!queue->empty()) {
        createDDoneEvent(queue->headReq(), eQueue);
        isBusy = true;
    }


}



void Disk::createDDoneEvent(Request * req, EventQueue* eventQueue) {

    startTime = eventQueue->curTime();
    double accTime = accessTime(req) + eventQueue->curTime();
    setTrackAndSect(req->track(), req->sector());

    if (eventQueue->curTime() == 0)
        accTime += req->time();

    auto * diskDoneEvent = new DiskDoneEvent(accTime, diskName);
    auto * eventNode = new EventNode;

    eventNode->addDiskDone(diskDoneEvent);
    eventNode->time(accTime);
    eventQueue->insert(eventNode);

}


void EventQueue::insert(EventNode *node) {

    // inserting a node to a list that is time ordered
    if (!head)
        head = tail = node;
    else if ((head->time() > node->time()) || (node->time() == head->time() && node->isTimerEvent())){
        node->next(head);
        head = node;
    }
    else if (tail->time() <= node->time() ) {
        tail->next(node);
        tail = node;
    }
    else {
        EventNode * iter = head, *prev = head;
        while (iter->next() && iter->time() <= node->time()) {
            prev = iter;
            iter = iter->next();
        }
        node->next(prev->next());
        prev->next(node);

    }


}


EventNode* EventQueue::getEvent() {

    // getEvent should not be called on an empty list, this is a protocol to avoid that
    if (!head) {
        std::cout << "ATTEMPTED TO GET AN EVENT WHEN EVENT QUEUE IS EMPTY\n";
        exit(3);
    }
    EventNode * event = head;
    head = head->next();
    if ( head == nullptr )
        tail = nullptr;
    return event;

}


double Disk::accessTime(Request *req) {

    return seekTime(req->track()) + rotationTime(req->sector()) + 0.1;

}


double Disk::rotationTime(int sector) {

    if ( headSector == sector )
        return 0.0;
    else if (headSector < sector)
        return (sector - headSector) * 0.1;
    return ( 30 - headSector + sector ) * 0.1;

}


double Disk::seekTime(int track) {

    return fabs(headTrack - track) * 3;

}


void EventQueue::addRequest( Request * req) {

    auto * eventNode = new EventNode;
    auto * requestEvent = new RequestEvent(req);
    eventNode->addRequest(requestEvent);
    eventNode->time(req->time());
    insert(eventNode);

}


void EventQueue::addTimer(double time) {

    auto * eventNode = new EventNode;
    auto * timerEvent = new TimerEvent(time);
    eventNode->addTimer(timerEvent);
    eventNode->time(time);
    insert(eventNode);

}


// used for debugging the event queue
void EventQueue::print() {

    if (!head)
        cout << "EMPTY\n";
    else {

        EventNode * iter = head;
        while (iter) {
            if (iter->isTimerEvent())
                cout << "TIMER FOR TIME: ";
            else if ( iter->isDiskDoneEvent() )
                cout << "DDONE for " << iter->getDiskDone()->name() << " and TIME: ";
            else {
                cout << "REQ W/ TRACK " << iter->getRequest()->request()->track() << " and sector " <<
                iter->getRequest()->request()->sector() << " and TIME: ";

            }
            cout << iter->time() << endl;
            iter = iter->next();
        }
        cout << endl;

    }

}

