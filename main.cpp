#include "MyThreadsLib.h"
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <iostream>
#include <fstream>

using namespace std;
#define THREAD_COUNT 10
#define OUTPUT_FILENAME "output.txt"

void *ServerFunction(void *arg);

void *ClientFunction(void *arg);

bool AllThreadsDone();

void SetFlags(bool);

string buffer = "EMPTY";
bool FlagArray[THREAD_COUNT];
ofstream file;
RwLock BufferLock;
RwLock FileLock; //запись в файл
RwLock FlagArrayLock; //флаг работы клиента

int main() {
    Thread server(ServerFunction);
    Thread *clients;
    file.open(OUTPUT_FILENAME);
    SetFlags(true);
    clients = new Thread[THREAD_COUNT];
    for (int i = 0; i < THREAD_COUNT; i++) {
        clients[i] = Thread(ClientFunction, (void *) new int(i));
    }
    for (int i = 0; i < THREAD_COUNT; i++) {
        clients[i].Join();
    }
    server.Join();
    file.close();
    return 0;
}

void *ServerFunction(void *arg) {
    string s;
    while (true) {
        getline(cin, s);
        while (!AllThreadsDone())
            sched_yield();
        BufferLock.WriteLock();
        buffer = s;
        BufferLock.UnLock();
        SetFlags(false);
        if (s.compare("quit") == 0) {
            pthread_exit(NULL);
        }
        sched_yield();
    }
}

void *ClientFunction(void *arg) {
    string s;
    int ThreadIndex = *(int *) arg;
    while (true) {
        s = buffer;
        FlagArrayLock.ReadLock();
        bool IsCurrentThreadWorked = FlagArray[ThreadIndex];
        FlagArrayLock.UnLock();
        if (!IsCurrentThreadWorked) {
            BufferLock.ReadLock();
            s = buffer;
            BufferLock.UnLock();
            if (s == "quit") {
                pthread_exit(NULL);
            }
            FileLock.WriteLock();
            file << "[" << ThreadIndex << "]: " << s << endl;
            FileLock.UnLock();
            FlagArrayLock.WriteLock();
            FlagArray[ThreadIndex] = true;
        }
        sched_yield();
    }
}

bool AllThreadsDone() {
    bool result = true;
    FlagArrayLock.ReadLock();
    for (int i = 0; i < THREAD_COUNT; i++)
        result = result && FlagArray[i];
    FlagArrayLock.UnLock();
    return result;
}

void SetFlags(bool b) {
    FlagArrayLock.WriteLock();
    for (int i = 0; i < THREAD_COUNT; ++i) {
        FlagArray[i] = b;
    }
    FlagArrayLock.UnLock();
}