//
// Created by natem on 10/28/2024.
//
#include "CLookQueue.hpp"
#include "../CommonFiles/Request.hpp"


/***
 * This checks if the queue is empty
 * @return
 */
bool CLookQueue::empty() {
    return head == nullptr && nextHead == nullptr;
}


/***
 * De-constructor
 */
CLookQueue::~CLookQueue() {

    while( head != nullptr ) {
        FCFSQueueNode *node = head;
        head = node->next();
        delete node;
    }

}


/***
 * This func finds the last node of a set track, this ensures that
 * duplicate track nodes are ordered by First Come First Serve
 * @param node the node to be added
 * @param rNode current place in the list
 */
void CLookQueue::findLastDuplicate(FCFSQueueNode * node, FCFSQueueNode* rNode) {

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


void CLookQueue::insertInc(FCFSQueueNode* _head, FCFSQueueNode* rNode) {

    // this func inserts a node based on the list currently increasing
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


void CLookQueue::addRequest(int orderValue, Request *request, int cRWHeadTrack, int cRWHeadSector) {


    auto * rNode = new FCFSQueueNode(orderValue, request);
    if (empty() ) {
        head = tail = rNode;
        return;
    }
    if (rNode->request()->track() < cRWHeadTrack) {
        if (nextHead == nullptr)
            nextHead = nextTail = rNode;
        else {
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
    }
    else {
        if (!head)
            head = tail = rNode;
        else if (head->request()->track() > request->track()) {
            rNode->next(head);
            head = rNode;
        }
        else if (tail->request()->track() <= request->track()) {
            tail->next(rNode);
            tail = rNode;
        }
        else {
            insertInc(head, rNode);

        }
    }



}


/***
 * This swaps the current list to the next list
 */
void CLookQueue::switchLists() {

    head = nextHead;
    tail = nextTail;
    nextTail = nextHead = nullptr;

}


/***
 * This retrieves the head request of the queue
 * @return the head request
 */
Request *CLookQueue::getRequest() {
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


/***
 * This prints the contents of the queue
 */
void CLookQueue::print() {
    for(auto cur = head; cur; cur = cur->next() )
        cur->request()->print();
}


/***
 * This iterates through a LL and returns the amount of nodes
 * visited
 * @param iter ptr to the beginning of the list
 * @return the amount of nodes in the list
 */
int CLookQueue::countNodesInList(FCFSQueueNode* iter) {

    if (!iter)
        return 0;

    int count = 0;
    while ( iter ) {
        count++;
        iter = iter->next();
    }
    return count;

}


/***
 * This function finds the amount of nodes in the queue
 * @return the amount of nodes
 */
int CLookQueue::size() {

    return countNodesInList(head) + countNodesInList(nextHead);

}


int CLookQueue::headTrack() {

    if (empty()) {
        std::cout << "ERROR WITH HEAD TRACK\n";
        exit(10);
    }
    if (!head)
        switchLists();
    return head->request()->track();

}


int CLookQueue::headSector() {

    if (empty()) {
        std::cout << "ERROR WITH HEAD SECTOR\n";
        exit(10);
    }
    if (!head)
        switchLists();
    return head->request()->sector();

}


Request *CLookQueue::headReq() {

    if (empty()) {
        std::cout << "ERROR WITH HEAD REQ\n";
        exit(10);
    }
    if (!head)
        switchLists();
    return head->request();

}


int CLookQueue::headNum() {

    if (empty()) {
        std::cout << "ERROR WITH HEAD REQ\n";
        exit(10);
    }
    if (!head)
        switchLists();
    return head->num();

}
