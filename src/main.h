/*
 * Copyright (c) 2008-2009, Thomas Jaeger <ThJaeger@gmail.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#ifndef __MAIN_H__
#define __MAIN_H__

#include <string>
#include <X11/X.h>

bool is_file(std::string filename);
bool is_dir(std::string dirname);
void quit();

extern std::string config_dir;
extern const char *prefs_versions[];
extern const char *actions_versions[];
extern int verbosity;
extern bool experimental;

extern "C" {
struct _XDisplay;
typedef struct _XDisplay Display;
}

extern Display *dpy;
extern Window ROOT;

class Win;
extern Win *win;

#endif
