#include "clog.h"
#include "ansi_colors.h"
#include <stdio.h>
#include <stdlib.h>

const char *level_colors[] = { LIGHT_BLUE, CYAN, GREEN, YELLOW, RED, MAGENTA };

const char *level_strings[] = { "TRACE", "DEBUG", "INFO",
				"WARN",	 "ERROR", "FATAL" };

/* Write to stdout
 * file stream specified in log->stream
 */
void clog_stdout(struct clog_log *log)
{
	/* Extract Time */
	char time_str[32];
	size_t ret =
		strftime(time_str, sizeof(time_str), "%H:%M:%S", log->time);
	time_str[ret] = 0;

/* Writes to stdout */
#ifdef NCLOGDEBUG
	fprintf(log->stream, "%s %s%-5s\x1b[0m ", time_str,
		level_colors[log->level], level_strings[log->level]);
#else
	fprintf(log->stream, "%s %s%-5s\x1b[0m \x1b[90m%s:%d:\x1b[0m ",
		time_str, level_colors[log->level], level_strings[log->level],
		log->file, log->line);
#endif

	vfprintf(log->stream, log->fmt, log->ap);
	fprintf(log->stream, "\n");
	fflush(log->stream);
}

/* Internal logger function */
void _clog_logger(int level, const char *file, int line, const char *fmt, ...)
{
#ifdef NCLOGDEBUG
	if(level == LOG_DEBUG)
		return;
#endif

	time_t t = time(NULL);

	/* Initalize clog structure with specified data */
	struct clog_log log;
	log.level = level;
	log.file = file;
	log.line = line;
	log.fmt = fmt;
	log.time = localtime(&t);
	log.stream = stderr;

	/* Write log messages to stdout with specified file stream in log.stream */
	va_start(log.ap, fmt);
	clog_stdout(&log);
	va_end(log.ap);

#ifdef CLOGABORTFATAL
	/* Aborts applciation */
	if (level == LOG_FATAL)
		abort();
#endif
}
