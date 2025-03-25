#include"Request.hpp"
#include<string>
using namespace std;


class TimerEvent {
public:

    TimerEvent(double _time): time(_time) {}
    double getTime() { return time; }

private:
    double time;

};

class RequestEvent {
public:

    RequestEvent(Request * _req): req(_req) {}
    Request * request() { return req; }

private:
    Request * req;


};

class DiskDoneEvent {
public:
    DiskDoneEvent(double _time, string _diskName): time(_time), diskName(_diskName) {}
    string name() { return diskName; }

private:
    double time;
    string diskName;


};

class EventNode {
public:

    EventNode(): timerEvent(nullptr), requestEvent(nullptr), ddoneEvent(nullptr),
                 isTimer(false), isRequest(false), isDDone(false), _next(nullptr), _time(0) {}
    void addTimer(TimerEvent *timer) {
        timerEvent = timer;
        isTimer = true;
    }
    void addRequest(RequestEvent *request) {
        requestEvent = request;
        isRequest = true;
    }
    void addDiskDone(DiskDoneEvent *dDone) {
        ddoneEvent = dDone;
        isDDone = true;
    }

    EventNode * next() { return _next; }
    void next(EventNode * node ) { _next = node; }
    void time(double value) { _time = value; }
    double time() { return _time;  }

    TimerEvent *getTimer() { return timerEvent; }
    RequestEvent *getRequest() { return requestEvent; }
    DiskDoneEvent *getDiskDone() { return ddoneEvent; }
    bool isTimerEvent() { return isTimer; }
    bool isRequestEvent() { return isRequest; }
    bool isDiskDoneEvent() { return isDDone; }

private:
    TimerEvent *timerEvent;
    RequestEvent *requestEvent;
    DiskDoneEvent *ddoneEvent;
    bool isTimer, isRequest, isDDone;

    double _time;
    EventNode * _next;
};