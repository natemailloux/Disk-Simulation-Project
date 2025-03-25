#include "STQueueNode.hpp"

class Request;

STQueueNode::STQueueNode(int _track, FCFSQueue* _q) :  trackNum{_track}, q{_q},_next(nullptr) {}

STQueueNode *STQueueNode::next() {
    return _next;
}

void STQueueNode::next(STQueueNode *node) {
    _next = node;
}

int STQueueNode::track() {
    return trackNum;
}

void STQueueNode::track(int v) {
    trackNum = v;
}

FCFSQueue* STQueueNode::getQ() {
    return q;
}
