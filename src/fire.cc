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
#include "fire.h"
#include <X11/Xlib.h>
#include <math.h>
#include <stdio.h>

Fire::Fire() {
	const char *ofc = "org.freedesktop.compiz";
	GError *error = 0;
	bus = dbus_g_bus_get(DBUS_BUS_SESSION, &error);
	if (!bus) {
		g_error_free(error);
		throw DBusException();
	}
	char add[256];
	char clear[256];
	snprintf(add, sizeof(add), "/org/freedesktop/compiz/firepaint/screen%d/add_particle", DefaultScreen(dpy));
	snprintf(clear, sizeof(clear), "/org/freedesktop/compiz/firepaint/screen%d/clear_key", DefaultScreen(dpy));

	point_proxy = dbus_g_proxy_new_for_name(bus, ofc, add, ofc);
	clear_proxy = dbus_g_proxy_new_for_name(bus, ofc, clear, ofc);
}

void Fire::add_point(float x, float y) {
	dbus_g_proxy_call_no_reply(point_proxy, "activate",
			G_TYPE_STRING, "root", G_TYPE_INT,    gint(ROOT),
			G_TYPE_STRING, "x",   G_TYPE_DOUBLE, gdouble(x),
			G_TYPE_STRING, "y",   G_TYPE_DOUBLE, gdouble(y),
			G_TYPE_INVALID);
}

void Fire::draw(Point p, Point q) {
	float dist = hypot(p.x-q.x, p.y-q.y);
	leftover -= dist;
	while (leftover < 0.01) {
		add_point(q.x + (q.x-p.x)*leftover/dist, q.y + (q.y-p.y)*leftover/dist);
		leftover += 5.0;
	}
}
void Fire::timeout() {
	dbus_g_proxy_call_no_reply(clear_proxy, "activate",
			G_TYPE_STRING, "root", G_TYPE_INT,    gint(ROOT),
			G_TYPE_INVALID);
}
