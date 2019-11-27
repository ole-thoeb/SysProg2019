#include "mystdlib.h"


char memory[1048576];

typedef struct header {
	size_t size;
	struct header *next;
} header;

header* firstHeader = (header*)memory;

//declare helper functions
header* getHeader(void *ptr);
void* getPointer(header *h);
header* nextBlock(header *h);
size_t totalBlockSize(size_t size);
size_t associatedMemory(header *h);header* nearestFreeBlockBefore(header* h);

// return the header associated with the mem starting at ptr
header* getHeader(void *ptr) {
	return (header*)((char*)ptr - sizeof(header));
}

// return the pointer that points to the start of the mem associated to the header
void* getPointer(header *h) {
	return (char*)h + sizeof(header);
}

// return address of next block (has not to be free / not neccesary h->next)
header* nextBlock(header *h) {
	return (header*)((char*)h + associatedMemory(h));
}

// retuns size a block of size size needs
size_t totalBlockSize(size_t size) {
	return size + sizeof(header);
}

// returns the total size the header needs (header size + mem size)
size_t associatedMemory(header *h) {
	return totalBlockSize(h->size);
}

header* nearestFreeBlockBefore(header* h) {
	header *headerBefore = firstHeader;
	// while the next header adress is closer as the current
	while (h - headerBefore > h - headerBefore->next && h - headerBefore->next > 0) {
		// advance to next header
		headerBefore = headerBefore-> next;
	}
	return headerBefore;
}

int first = 1;
void *mymalloc(size_t size) {
	if (!size) return NULL;
	if (first) {
		first = 0;
		firstHeader->size = 1048576 - sizeof(header);
		firstHeader->next = firstHeader;
	}
	header *curHeader = firstHeader;
	if (curHeader->size >= size + sizeof(header)) {
		//address of the header of the new mem block
		header *newHeader = (header*)((char*)curHeader + curHeader->size - size);
		//set size of new block
		newHeader->size = size;
		//decrease size of previous block
		curHeader->size -= totalBlockSize(size);
		// if current block is empty
		if (!curHeader->size) {
			// get last header
			header *lastHeader = curHeader;
			while (lastHeader->next != firstHeader) {
				lastHeader = lastHeader->next;
			}
			// link out current block
			lastHeader->next = curHeader->next;
			firstHeader = curHeader->next;
		}
		// add header offset
		return getPointer(newHeader);
	}

	header *prevHeader = curHeader;
	curHeader = curHeader->next;
	// while we are not back at the start
	while (curHeader != firstHeader) {
		if (curHeader->size >= size + sizeof(header)) {
			//address of the header of the new mem block
			header *newHeader = (header*)((char*)curHeader + curHeader->size - size);
			//set size of new block
			newHeader->size = size;
			//decrease size of previous block
			curHeader->size -= totalBlockSize(size);
			//link out current block if remaining size is 0
			if (!curHeader->size) {
				prevHeader->next = curHeader->next;
			}
			// add header offset
			return getPointer(newHeader);
		} else {
			// advance to next mem block
			prevHeader = curHeader;
			curHeader = curHeader->next;
		}
	}
	
	// no big enough block found
	return NULL;
}

void myfree(void *ptr) {
	// if ptr is NULL nothing hapends
	if (!ptr) return;
	header *toFreeHeader = getHeader(ptr);
	header *headerBefore = nearestFreeBlockBefore(toFreeHeader);
	// if block after is adjacent
	int afterMerged = 0;
	if (headerBefore->next == nextBlock(toFreeHeader)) {
		// merge block after to toFree block
		toFreeHeader->size += associatedMemory(headerBefore->next);
		// link toFreeHeader into free list
		toFreeHeader->next = headerBefore->next->next;
		headerBefore->next = toFreeHeader;
		afterMerged = 1;
	}
	// if block before is adjacent
	if (nextBlock(headerBefore) == toFreeHeader) {
		// assign memory to block before
		headerBefore->size += associatedMemory(toFreeHeader);
		// if we merged block after we need to reset the links
		if (afterMerged) {
			headerBefore->next = toFreeHeader->next;
		}
	} else if (!afterMerged) {
		// add toFreeHeader into the list
		toFreeHeader->next = headerBefore->next;
		headerBefore->next = toFreeHeader;
	}
}

void *mycalloc(size_t nmemb, size_t size) {
	// allocate memory
	char *mem = mymalloc(nmemb * size);

	if (!mem) return NULL;
	// fill memory with 0
	for (size_t i = 0; i < nmemb * size; i++) {
		mem[i] = 0;
	}
	return mem;
}

void *myrealloc(void *ptr, size_t size) {
	// special cases
	if (!ptr) return mymalloc(size);
	if (!size) {
		myfree(ptr);
		return NULL;
	}

	//get header to the pointer
	header *ptrHeader = getHeader(ptr);
	// if the memory is reduced
	if (ptrHeader->size > size) {
		// if there is enough space to put a header in the now free memory
		if (ptrHeader->size - size > sizeof(header)) {
			size_t originalSize = ptrHeader->size;
			// update size of ptr
			ptrHeader->size = size;
			// get new header
			header *newHeader = nextBlock(ptrHeader);
			// set size of new header
			newHeader->size = originalSize - totalBlockSize(size);
			// link in new header
			header *headerBefore = nearestFreeBlockBefore(newHeader);
			newHeader->next = headerBefore->next;
			headerBefore->next = newHeader;
		}
		return ptr;
	}
	// allocate new memory
	char *mem = mymalloc(size);
	if (!mem) return NULL;
	//copy old mem to new mem
	char *oldMem = (char*)ptr;
	for (size_t i = 0; i < ptrHeader->size; i++) {
		mem[i] = oldMem[i];
	}
	// free old mem
	myfree(ptr);

	return mem;
}