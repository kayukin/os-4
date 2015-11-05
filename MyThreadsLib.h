#ifndef OS_4_MYTHREADSLIB_H
#define OS_4_MYTHREADSLIB_H

#include <pthread.h>

class RwLock {
    pthread_rwlock_t lock;
public:
    RwLock();
    ~RwLock();
    void WriteLock();
    void ReadLock();
    void UnLock();
};

class Thread {
    pthread_t thread;
public:
    Thread();

    Thread(void *(*ThreadFunction)(void *), void *arg = NULL);

    void Join();
};

#endif //OS_4_MYTHREADSLIB_H