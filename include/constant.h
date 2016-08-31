/**
 * @file This file is about constant limitation and we can
 *				declare the process number
 */

#ifndef DEBUG_H
#define DEBUG_H
/**
 * Parallel Parameter
 */

#ifndef PROCESS_NUM
	#define PROCESS_NUM 4
#endif

#ifndef IN_CALLS_NUM
	#define IN_CALLS_NUM 10
#endif

/**
 * Max Length
 */
#define MAX_NAME_LENGTH 30
#define MAX_INSTR_LENGTH 50
#define MAX_PATTERN_LENGTH 1000
#define MAX_FILE_PATH 200

/**
 *	Max File Num
 */
#define MAX_TRACE_NUM 50
#define MAX_CATE_NUM 10

#endif
