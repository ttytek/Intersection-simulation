#ifndef BUFFER_H
#define BUFFER_H

#ifndef ID_LEN
#define ID_LEN 32
#endif

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 32
#endif

typedef enum direction { NORTH, EAST, SOUTH, WEST } direction;

typedef enum state { RED, REDYELLOW, GREEN, YELLOW } state;

/**
 * @brief Represents a vehicle in the simulation.
 * 
 * Each vehicle has a unique string identifier and a starting
 * and ending direction on the intersection.
 */

typedef struct vehicle {
  char id[ID_LEN + 1];
  direction start;
  direction end;
} vehicle;

/**
 * @brief Circular buffer to store vehicles.
 * 
 * Implements a fixed-size ring buffer that holds `vehicle` structs.
 * It supports push/pop operations and tracks buffer state using head/tail indices.
 */

typedef struct v_buffer {
  vehicle vs[BUFFER_SIZE];
  int head;
  int tail;
  int count;
} v_buffer;

/**
 * @brief Initializes the vehicle buffer.
 * 
 * Sets the head, tail, and count of the circular buffer to zero.
 * 
 * @param buf Pointer to the buffer to initialize.
 */

void buf_init(v_buffer *buf);

/**
 * @brief Pushes a vehicle onto the buffer.
 * 
 * Adds a vehicle to the head of the circular buffer if there is space.
 * 
 * @param buf Pointer to the buffer.
 * @param v Pointer to the vehicle to add.
 * @return 1 if successful, 0 if the buffer is full.
 */

int buf_push(v_buffer *buf, const vehicle *v);

/**
 * @brief Pops a vehicle from the buffer.
 * 
 * Removes the vehicle at the tail of the circular buffer and stores it in `out`.
 * 
 * @param buf Pointer to the buffer.
 * @param out Pointer to the vehicle where the removed data will be stored.
 * @return 1 if successful, 0 if the buffer is empty.
 */

int buf_pop(v_buffer *buf, vehicle *out);

/**
 * @brief Returns the number of vehicles currently in the buffer.
 * 
 * @param buf Pointer to the buffer.
 * @return Number of vehicles in the buffer.
 */

int buf_count(v_buffer *buf);

/**
 * @brief Retrieves the first vehicle from the buffer without removing it.
 * 
 * Copies the vehicle at the front (tail) of the buffer into `out`.
 * 
 * @param buf Pointer to the buffer.
 * @param out Pointer to the vehicle where the data will be copied.
 * @return 1 if successful, 0 if the buffer is empty.
 */

int buf_first(v_buffer *buf, vehicle *out);

/**
 * @brief Gets the last character of the vehicle ID at position n in the buffer.
 * 
 * 
 * @param buf Pointer to the buffer.
 * @param n Index from the front of the buffer (0-based).
 * @return The last character of the vehicle's ID at the nth position.
 */

char buf_nth_v_id(v_buffer *buf, int n);

#endif // BUFFER_H