#include <stddef.h>
#ifndef STRQUEUE_H
#define STRQUEUE_H

#ifdef __cplusplus
namespace cxx{

extern "C" {
#endif

	// Creates a new, empty string queue and returns its identifier.
	unsigned long strqueue_new();

	// Deletes the queue with the given identifier.
	void strqueue_delete(unsigned long id);

	// Returns the number of strings in the queue.
	size_t strqueue_size(unsigned long id);

	// Appends a copy of the string to the queue at a given position.
	void strqueue_insert_at(unsigned long id, size_t position, const char* str);

	// Removes the string at a given position from the queue.
	void strqueue_remove_at(unsigned long id, size_t position);

	// Returns a copy of the string at a given position in the queue.
	const char* strqueue_get_at(unsigned long id, size_t position);

	// Clears the queue.
	void strqueue_clear(unsigned long id);

	/* Compares lexically two queues. The result is:
	 * -1 if queue(id1) < queue(id2),
	 *  0 if queue(id1) = queue(id2),
	 *  1 if queue(id1) > queue(id2).
	 * If the queue is NULL it is treated as an empty queue. 
	 */
	int strqueue_comp(unsigned long id1, unsigned long id2);

#ifdef __cplusplus
} // extern "C"

}
#endif

#endif // STRQUEUE_H