/* Copyright (C) 2003 Mads Martin Joergensen <mmj at mmj.dk>
 *
 * $Id$
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "mlmmj.h"
#include "send_help.h"
#include "strgen.h"
#include "find_email_adr.h"
#include "getlistaddr.h"
#include "getlistdelim.h"
#include "log_error.h"
#include "chomp.h"
#include "wrappers.h"
#include "mygetline.h"
#include "prepstdreply.h"
#include "memory.h"

void send_help(const char *listdir, const char *emailaddr,
	       const char *mlmmjsend)
{
	char *queuefilename, *listaddr, *listdelim, *listname, *listfqdn;
	char *fromaddr;

	listaddr = getlistaddr(listdir);
	listdelim = getlistdelim(listdir);
	listname = genlistname(listaddr);
	listfqdn = genlistfqdn(listaddr);

	fromaddr = concatstr(4, listname, listdelim, "bounces-help@", listfqdn);
	myfree(listdelim);

	queuefilename = prepstdreply(listdir, "listhelp", "$listowner$",
					emailaddr, NULL, 0, NULL);
	if(queuefilename == NULL) {
		log_error(LOG_ARGS, "Could not prepare help mail");
		exit(EXIT_FAILURE);
	}
	
	myfree(listaddr);
	myfree(listname);
	myfree(listfqdn);

	execlp(mlmmjsend, mlmmjsend,
				"-l", "1",
				"-T", emailaddr,
				"-F", fromaddr,
				"-m", queuefilename, (char *)NULL);

	log_error(LOG_ARGS, "execlp() of '%s' failed", mlmmjsend);
	exit(EXIT_FAILURE);
}
