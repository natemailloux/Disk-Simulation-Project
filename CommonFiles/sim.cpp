#include <iostream>
#include<fstream>
#include"Disk.hpp"
#include<vector>
#include"../FCFS_Queue/FCFSQueue.hpp"
#include"../ST_Queue/STQueue.hpp"
#include"../PickUp_Queue/PickUpQueue.hpp"
#include"../Look_Queue/LookQueue.hpp"
#include"../CLook_Queue/CLookQueue.hpp"
#include <iomanip>
using namespace std;


vector<Request* > createReqList(const string& fileName) {

    std::ifstream inputStream;
    inputStream.open(fileName, std::ios::in);
    if( ! inputStream.is_open()) {
        std::cout << "Unable to open " << fileName << ". Terminating..";
        perror("Error when attempting to open the input file.");
        exit(1);
    }

    vector<Request* > requestsList;
    int time, track, sector;
    while(inputStream >> time && inputStream >> track && inputStream >> sector) {
        double adjustedTime = time / 10.0;
        auto *request = new Request(adjustedTime, track, sector);
        requestsList.push_back(request);
    }

    inputStream.close();
    return requestsList;

}


void addToAllDisks(vector<Disk * >& disks, Request * req, int orderValue, EventQueue* eventQueue ) {

    for ( auto * curDisk : disks ) {
        curDisk->processRequest(orderValue, eventQueue, req);
    }

}


void addToTimerFile(const vector<Disk*>& disks, double time) {

    ofstream outFS;
    outFS.open("output/TIMER_output", ios::app);

    if (!outFS.is_open()) {
        cout << "Error opening output/TIMER_output file\n";
        exit(10);
    }

    int init_width = 10;
    outFS << setw(init_width) << fixed << setprecision(2) << time;

    for (auto * curDisk : disks ) {
        outFS << setw(init_width) << curDisk->q()->size();
    }
    outFS << endl;
    outFS.close();


}


string title(string name) {

    if ( name == "FCFS" || name == "LOOK" || name == "CLOOK" )
        return name;
    else if ( name == "ST" )
        return "STRACK";
    return "PICKUP";

}


void setUpOutputFiles(const vector<Disk*>& disks) {

    ofstream outFS;
    outFS.open("output/TIMER_output");

    if (!outFS.is_open()) {
        cout << "ERROR OPENING output/TIMER_output\n";
        exit(10);
    }

    outFS << "                            TIMER REPORT\n      Time      FCFS    STRACK    PICKUP     CLOOK      LOOK\n";
    outFS.close();

    for (auto * disk : disks) {

        string file = disk->getFileName();
        outFS.open(file);
        if (!outFS.is_open()) {
            cout << "ERROR OPENING " << file << endl;
            exit(10);
        }
        string _title = title(disk->name()) + " REPORT\n";
        outFS << setw(44) << _title;
        outFS << "    # Trac  Sec      Entr      Init      Comp      Wait      Serv   TmInSys\n";
        outFS.close();

    }


}


void get_stats(const string& file, vector<double>& waitList, vector<double>& servList, vector<double>& timeInSysList ) {

    ifstream inFS;
    inFS.open(file);

    if (!inFS.is_open()) {
        cout << "ERROR OPENING " << file << endl;
        exit(14);
    }

    // this gets "rid" of the title and labels at the beginning of the file
    string placeholder;
    getline(inFS, placeholder);
    inFS >> placeholder;
    getline(inFS, placeholder);

    int order, track, sector;
    double entry, init, comp, wait, serv, timeInSys;
    while (inFS >> order && inFS >> track && inFS >> sector && inFS >> entry && inFS >> init && inFS >> comp && inFS >> wait &&
            inFS >> serv && inFS >> timeInSys) {
        waitList.push_back(wait);
        servList.push_back(serv);
        timeInSysList.push_back(timeInSys);

    }
    inFS.close();

}


void queueStats(vector<double>& FCFS, vector<double>& STrack, vector<double>& PickUp,
                vector<double>& CLook, vector<double>& Look) {

    ifstream inFS;
    inFS.open("output/TIMER_output");

    if (!inFS.is_open()){
        cout << "ERROR OPENING output/TIMER_output in queueStats\n";
        exit(14);
    }

    // this gets "rid" of the title and labels at the beginning of the file
    string placeholder;
    getline(inFS, placeholder);
    inFS >> placeholder;
    getline(inFS, placeholder);

    double time;
    int FC_size, ST_size, PU_size, CL_size, LU_size;
    while (inFS >> time && inFS >> FC_size && inFS >> ST_size && inFS >> PU_size && inFS >> CL_size && inFS >> LU_size) {

        FCFS.push_back(FC_size);
        STrack.push_back(ST_size);
        PickUp.push_back(PU_size);
        CLook.push_back(CL_size);
        Look.push_back(LU_size);

    }

    inFS.close();

}


double min(const vector<double>& list) {

    if (list.empty())
        return 0.0;
    double min = list.at(0);
    for (const double& num : list) {
        if (min > num)
            min = num;
    }
    return min;


}


double max(const vector<double>& list) {

    if (list.empty())
        return 0.0;
    double max = list.at(0);
    for (const double& num : list) {
        if (max < num)
            max = num;
    }
    return max;


}


double avg(const vector<double>& list) {

    double size = 0.0;
    if (list.empty())
        return 0.0;
    double sum = 0, avg;
    for (const double& num : list) {
        sum += num;
        size++;
    }
    avg  = sum / size;
    return avg;


}


void outputStats(ofstream& outFS, const vector<double>& list, int wid) {
    outFS << fixed << setprecision(2) << setw(wid) << min(list) << setw(wid)
    << max(list) << setw(wid) << avg(list) << setw(wid);
}


void initSetup() {
    ofstream outFS;
    outFS.open("output/SUMMARY_output");

    if (!outFS.is_open()) {
        cout << "ERROR OPENING output/TIMER_output\n";
        exit(14);
    }

    // multiple outFS calls are used for readability
    outFS << setw(106) << "SUMMARY REPORT\n      Name             TimeInSystem";
    outFS << "                      WaitTime                   ServiceTime            NumInQue\n";
    outFS << "                 Min       Max       Avg       Min       Max";
    outFS << "       Avg       Min       Max       Avg       Max       Avg\n";
    outFS.close();
}


void summaryFile(const vector<Disk * >& disks) {

    ofstream outFS;
    initSetup();
    outFS.open("output/SUMMARY_output", ios::app);


    vector<double> FC_stats, ST_stats, PU_stats, CL_stats, LU_stats;
    queueStats(FC_stats, ST_stats, PU_stats, CL_stats, LU_stats);
    vector<vector<double>> statVec = {FC_stats, ST_stats, PU_stats, CL_stats, LU_stats};
    int idx = 0;

    for (auto * disk : disks) {

        vector<double> wait, serv, timeInSys;
        get_stats(disk->getFileName(), wait, serv, timeInSys);
        int wid = 10;
        outFS << setw(wid) << title(disk->name());
        outputStats(outFS, timeInSys, wid);
        outputStats(outFS, wait, wid);
        outputStats(outFS, serv, wid);
        outFS << max(statVec.at(idx)) << setw(wid) << avg(statVec.at(idx));
        outFS << endl;
        idx++;

    }
    outFS.close();

}


Disk* whichDisk(const vector<Disk *>& disks, const string& name) {

    for (auto * disk : disks) {
        if (disk->name() == name)
            return disk;
    }
    // this should never be called as the given name will be from a DDone event from the event queue
    return nullptr;

}


int main(int argc, char *argv[]) {

    if( argc != 2) {
        std::cout << "usage: " << argv[0] << " nameOfAnInputFile\n";
        exit(1);
    }

    auto *fcfsQueue = new FCFSQueue();
    auto *stQueue = new STQueue();
    auto *pickUpQueue = new PickUpQueue();
    auto *lookQueue = new LookQueue();
    auto *clookQueue = new CLookQueue();

    Disk *fcfsDisk = new Disk(fcfsQueue, "FCFS");
    Disk *stDisk = new Disk(stQueue, "ST");
    Disk *pickupDisk = new Disk(pickUpQueue, "PICKUP");
    Disk *lookDisk = new Disk(lookQueue, "LOOK");
    Disk *clookDisk = new Disk(clookQueue, "CLOOK");

    vector<Disk *> disks = {fcfsDisk, stDisk, pickupDisk, clookDisk, lookDisk};
    auto *eQueue = new EventQueue();

    vector<Request*> requestsList = createReqList(argv[1]);

    if (requestsList.empty()) {
        cout << "NO REQUESTS\n";
        exit(20);
    }

    eQueue->addTimer(50.0);
    eQueue->addRequest(requestsList.at(0));
    setUpOutputFiles(disks);

    int req_idx = 1;
    EventNode * event;

    while (!eQueue->empty()) {

        // debug
        cout << "\t TIME IS " << eQueue->curTime() << endl;
        cout << "----------------------\n";
        eQueue->print();
        cout << endl;

        event = eQueue->getEvent();
        eQueue->curTime(event->time());
        if ( event->isRequestEvent() ) {

            addToAllDisks(disks, event->getRequest()->request(), req_idx, eQueue);
            if ( req_idx <= requestsList.size() - 1) {
                eQueue->addRequest(requestsList.at(req_idx));
                req_idx++;
            }

        }
        else if ( event->isDiskDoneEvent() ) {
            Disk* curDisk = whichDisk(disks, event->getDiskDone()->name());
            curDisk->processDiskDone(eQueue);
        }
        else {

            if (!eQueue->empty()) {
                eQueue->addTimer(event->time() + 50.0);
            }

            addToTimerFile(disks, event->time());

        }
        delete event;

    }
    summaryFile(disks);


    return 0;
}