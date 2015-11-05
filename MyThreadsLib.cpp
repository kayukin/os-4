#include "MyThreadsLib.h"

RwLock::RwLock() {
    pthread_rwlock_init(&lock, NULL);
}

Thread::Thread(void *(*ThreadFunction)(void *), void *arg) {
    pthread_create(&thread, NULL, ThreadFunction, arg);
}

Thread::Thread() {

}

void Thread::Join() {
    pthread_join(thread, NULL);
}

RwLock::~RwLock() {
    pthread_rwlock_destroy(&lock);
}

void RwLock::WriteLock() {
    pthread_rwlock_wrlock(&lock);
}

void RwLock::ReadLock() {
    pthread_rwlock_rdlock(&lock);
}

void RwLock::UnLock() {
    pthread_rwlock_unlock(&lock);
}
