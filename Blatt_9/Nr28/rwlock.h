#include <pthread.h>

struct rwlock {
	pthread_mutex_t lockLock;
	pthread_cond_t signalRead;
	pthread_cond_t signalWrite;
	int count;
	int writeWaiting;
};

// Initialisiert die Read-Write-Lock-Datenstruktur 'lock'.
int rwlock_init(struct rwlock* lock);
// Fordert einen read-lock für 'lock' an.
int rwlock_lock_read(struct rwlock* lock);
// Fordert einen write-lock für 'lock' an.
int rwlock_lock_write(struct rwlock* lock);
// Gibt einen read-lock auf 'lock' frei.
int rwlock_unlock_read(struct rwlock* lock);
// Gibt einen write-lock auf 'lock' frei.
int rwlock_unlock_write(struct rwlock* lock);
