/* Copyright (C) 2004 Mads Martin Joergensen <mmj at mmj.dk>
 *
 * $Id$
 *
 * This file is redistributable under version 2 of the GNU General
 * Public License as described at http://www.gnu.org/licenses/gpl.txt
 */

#ifndef MLMMJ_MAINTD_H
#define MLMMJ_MAINTD_H

#include <sys/types.h>

int delolder(const char *dirname, time_t than);
int clean_moderation(const char *listdir);
int clean_discarded(const char *listdir);
int resend_queue(const char *listdir, const char *mlmmjsend);
int resend_requeue(const char *listdir, const char *mlmmjsend);
int clean_nolongerbouncing(const char *listdir);
int probe_bouncers(const char *listdir, const char *mlmmjbounce);
int unsub_bouncers(const char *listdir);

#define WRITELOGOK writen(maintdlogfd, " ... ok\n" , sizeof(" ... ok\n"));

#define WRITEMAINTLOG4( s1, s2, s3, s4 ) do { \
		logstr = concatstr( s1, s2, s3, s4 ) ;\
		writen(maintdlogfd, logstr, strlen(logstr)); \
		free(logstr); \
		} while (0);

#define WRITEMAINTLOG6( s1, s2, s3, s4, s5, s6 ) do { \
		logstr = concatstr( s1, s2, s3, s4, s5, s6 ) ;\
		writen(maintdlogfd, logstr, strlen(logstr)); \
		free(logstr); \
		} while (0);

#endif /* MLMMJ_MAINTD_H */
