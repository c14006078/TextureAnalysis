#include <time.h>

time_t get_time( void)
{
	return time( NULL);
}

double diff_time( time_t start, time_t end)
{
	return difftime(end, start);
}
