#include "LookQueue.hpp"
#include "../CommonFiles/Request.hpp"

// if both q's are empty
bool LookQueue::empty() {
    return head == nullptr && nextHead == nullptr;
}


LookQueue::~LookQueue() {

    while( head != nullptr ) {
        FCFSQueueNode *node = head;
        head = node->next();
        delete node;
    }

}

void LookQueue::findLastDuplicate(FCFSQueueNode * node, FCFSQueueNode* rNode) {

    // this func finds the last node of a set track, this ensures that duplicate track nodes are ordered by FCFS
    while (node->next() && node->next()->request()->track() == rNode->request()->track() )
        node = node->next();
    // checks to see if you will be inserting a new node as the tail
    if (node == tail) {
        tail->next(rNode);
        tail = rNode;
    }
    else {
        rNode->next(node->next());
        node->next(rNode);
    }

}



void LookQueue::switchLists() {

    goingIn = !goingIn;
    head = nextHead;
    tail = nextTail;
    nextTail = nextHead = nullptr;

}


void LookQueue::insertInc(FCFSQueueNode* _head, FCFSQueueNode* rNode) {

    // this func inserts a node based on the list currently being ordered increasingly
    FCFSQueueNode * iter = _head, *prev = _head;
    while (iter->next() && iter->request()->track() < rNode->request()->track()) {
        prev = iter;
        iter = iter->next();
    }
    if (rNode->request()->track() == prev->next()->request()->track())
        findLastDuplicate(prev, rNode);
    else {
        rNode->next(prev->next());
        prev->next(rNode);
    }

}


void LookQueue::insertDec(FCFSQueueNode* _head, FCFSQueueNode* rNode) {

    // this func inserts a node based on the list currently being ordered decreasingly
    FCFSQueueNode * iter = _head, *prev = _head;
    while (iter->next() && iter->request()->track() > rNode->request()->track()) {
        prev = iter;
        iter = iter->next();
    }
    if (rNode->request()->track() == prev->next()->request()->track())
        findLastDuplicate(prev, rNode);
    else {
        rNode->next(prev->next());
        prev->next(rNode);
    }
}


void LookQueue::addRequest(int orderValue, Request *request, int cRWHeadTrack, int cRWHeadSector) {


    auto * rNode = new FCFSQueueNode(orderValue, request);
    if (empty()) {
        head = tail = rNode;
        return;
    }
    // increasing
    if (goingIn) {

        if (rNode->request()->track() < cRWHeadTrack) {
            if (!nextHead)
                nextHead = nextTail = rNode;
            else {
                if (nextHead->request()->track() < request->track()) {
                    rNode->next(nextHead);
                    nextHead = rNode;
                }
                else if (nextTail->request()->track() >= request->track()) {
                    nextTail->next(rNode);
                    nextTail = rNode;
                }
                else {
                    insertDec(nextHead, rNode);
                }
            }
        }
        else {
            if (!head)
                head = tail = rNode;
            else if (head->request()->track() > request->track()) {
                rNode->next(head);
                head = rNode;
            } else if (tail->request()->track() <= request->track()) {
                tail->next(rNode);
                tail = rNode;
            } else {
                insertInc(head, rNode);

            }
        }
    }
    else {

        if (!head)
            head = tail = rNode;
        else if (rNode->request()->track() > cRWHeadTrack) {
            if (!nextHead)
                nextHead = nextTail = rNode;
            else
            if (nextHead->request()->track() > request->track()) {
                rNode->next(nextHead);
                nextHead = rNode;
            }
            else if (nextTail->request()->track() <= request->track()) {
                nextTail->next(rNode);
                nextTail = rNode;
            }
            else {
                insertInc(nextHead, rNode);

            }
        }
        else {
            if (head->request()->track() < request->track()) {
                rNode->next(head);
                head = rNode;
            } else if (tail->request()->track() >= request->track()) {
                tail->next(rNode);
                tail = rNode;
            } else {
                insertDec(head, rNode);

            }
        }
    }


}



Request *LookQueue::getRequest() {
    if( empty() ) {
        std::cout << "Calling PickUpQueue::getRequest() on an empty queue. Terminating...\n";
        exit(1);
    }
    if ( head == nullptr) {
        tail = nullptr;
        switchLists();
    }
    FCFSQueueNode *pickNode = head;
    Request *request = pickNode->request();
    head = head->next();
    if ( head == nullptr)
        tail = nullptr;
    delete pickNode;
    return request;

}

void LookQueue::print() {
    for(auto cur = head; cur; cur = cur->next() )
        cur->request()->print();
}


int LookQueue::countNodesInList(FCFSQueueNode* iter) {

    if (!iter)
        return 0;

    int count = 0;
    while ( iter ) {
        count++;
        iter = iter->next();
    }
    return count;

}


int LookQueue::size() {

    return countNodesInList(head) + countNodesInList(nextHead);

}

int LookQueue::headTrack() {

    if (empty()) {
        std::cout << "ERROR WITH HEAD TRACK\n";
        exit(10);
    }
    if (!head)
        switchLists();
    return head->request()->track();

}


int LookQueue::headSector() {

    if (empty()) {
        std::cout << "ERROR WITH HEAD SECTOR\n";
        exit(10);
    }
    if (!head)
        switchLists();
    return head->request()->sector();

}

Request *LookQueue::headReq() {

    if (empty()) {
        std::cout << "ERROR WITH HEAD REQ\n";
        exit(10);
    }
    if (!head)
        switchLists();
    return head->request();

}


int LookQueue::headNum() {

    if (empty()) {
        std::cout << "ERROR WITH HEAD REQ\n";
        exit(10);
    }
    return head->num();

}

