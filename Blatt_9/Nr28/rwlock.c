#include "rwlock.h"
#include <stdlib.h>

// Initialisiert die Read-Write-Lock-Datenstruktur 'lock'.
int rwlock_init(struct rwlock* lock) {
	int err;
	if ((err = pthread_cond_init(&lock->signalRead, NULL)) < 0) return err;
	if ((err = pthread_cond_init(&lock->signalWrite, NULL)) < 0) return err;
	if ((err = pthread_mutex_init(&lock->lockLock, NULL)) < 0) return err;
	lock->count = 0;
	lock->writeWaiting = 0;
	return 0;
}

// Fordert einen read-lock für 'lock' an.
int rwlock_lock_read(struct rwlock* lock) {
	pthread_mutex_lock(&lock->lockLock);
	while (lock->count < 0) {
		// wait for change to try again
		pthread_cond_wait(&lock->signalRead, &lock->lockLock);
	}
	lock->count++;
	pthread_mutex_unlock(&lock->lockLock);
	return 0;
}
// Fordert einen write-lock für 'lock' an.
int rwlock_lock_write(struct rwlock* lock) {
	pthread_mutex_lock(&lock->lockLock);
	lock->writeWaiting++;
	while (lock->count != 0) {
		// wait for change to try again
		pthread_cond_wait(&lock->signalWrite, &lock->lockLock);
	}
	lock->writeWaiting--;
	lock->count--;
	pthread_mutex_unlock(&lock->lockLock);
	return 0;
}
// Gibt einen read-lock auf 'lock' frei.
int rwlock_unlock_read(struct rwlock* lock) {
	pthread_mutex_lock(&lock->lockLock);
	lock->count--;
	if (lock->writeWaiting) {
		pthread_cond_signal(&lock->signalWrite);
	} else {
		pthread_cond_broadcast(&lock->signalRead);
	}
	pthread_mutex_unlock(&lock->lockLock);
	return 0;
}
// Gibt einen write-lock auf 'lock' frei.
int rwlock_unlock_write(struct rwlock* lock) {
	pthread_mutex_lock(&lock->lockLock);
	lock->count++;
	if (lock->writeWaiting) {
		pthread_cond_signal(&lock->signalWrite);
	} else {
		pthread_cond_broadcast(&lock->signalRead);
	}
	pthread_mutex_unlock(&lock->lockLock);
	return 0;
}