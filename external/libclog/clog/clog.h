#ifndef _CLOG_H_
#define _CLOG_H_

#include <stdarg.h>
#include <time.h>

/* represents logging levels */
enum LOG_LEVELS {
	LOG_TRACE,
	LOG_DEBUG,
	LOG_INFO,
	LOG_WARN,
	LOG_ERROR,
	LOG_FATAL
};

/* clog structure
 * hold parameters for _clog_logger
 * level specifies log level
 * file specifies the file where error occurred
 * line specifies the line where error occurred
 * fmt specifies string format
 * ap represents stdargs
 * time represents current time
 * stream represents file descriptor
 */
struct clog_log {
	int level;
	const char *file;
	int line;
	const char *fmt;
	va_list ap;
	struct tm *time;
	void *stream;
};

/* Logger Macros
 * Takes log message as argument
 * calls _clog_logger with specified arguments
 */
#define CLOG_TRACE(...) _clog_logger(LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define CLOG_DEBUG(...) _clog_logger(LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define CLOG_INFO(...) _clog_logger(LOG_INFO, __FILE__, __LINE__, __VA_ARGS__)
#define CLOG_WARN(...) _clog_logger(LOG_WARN, __FILE__, __LINE__, __VA_ARGS__)
#define CLOG_ERROR(...) _clog_logger(LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define CLOG_FATAL(...) _clog_logger(LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__)

/* Internal logger function */
void _clog_logger(int level, const char *file, int line, const char *fmt, ...);

#endif
