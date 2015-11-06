#include "MyThreadsLib.h"

using namespace MyThreadsLib;

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

void RwLock::Unlock() {
    pthread_rwlock_unlock(&lock);
}

bool Thread::operator==(const Thread &thread2) const {
    return (bool) pthread_equal(thread, thread2.thread);
}

bool Thread::operator!=(const Thread &thread2) const {
    return !(*this == thread2);
}
