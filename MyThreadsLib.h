#ifndef OS_4_MYTHREADSLIB_H
#define OS_4_MYTHREADSLIB_H

#include <pthread.h>

namespace MyThreadsLib {
    class RwLock {
        pthread_rwlock_t lock;
    public:
        RwLock();

        ~RwLock();

        void WriteLock();

        void ReadLock();

        void Unlock();
    };

    class Thread {
        pthread_t thread;
    public:
        Thread();

        Thread(void *(*ThreadFunction)(void *), void *arg = NULL);

        void Join();

        bool operator==(const Thread &) const;

        bool operator!=(const Thread &) const;
    };
}
#endif //OS_4_MYTHREADSLIB_H
