#include <time.h>

/**
 * Get the current time
 *
 * @return the time now
 */
time_t get_time( void);

/**
 * Calacute the differnece between start and end.
 *
 * @param	start	time_t
 * @param	end 	time_t
 *
 * @return time the difference in time
 */
double diff_time( time_t start, time_t end);
