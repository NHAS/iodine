/*
 * Copyright (c) 2006-2014 Erik Ekman <yarrick@kryo.se>,
 * 2006-2009 Bjorn Andersson <flex@kryo.se>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <check.h>
#include <string.h>
#include <stdio.h>

#include "test.h"
#include "login.h"

START_TEST(test_login_hash)
{
	char ans[32];
	char good[] = "\xdc\xba\x44\xe8\x78\x90\xcf\x25\xe\x9b\xb8\xfc\x1b\xda\x67\x2a\x5f\xae\xbf\x68\x7a\xe2\x32\x9f\x81\x37\xb1\x96\x75\xf\x35\xd1";
	char pass[32] = "iodine is the shit";
	int len;
	int seed;

	len = sizeof(ans);
	seed = 15;

	memset(ans, 0, sizeof(ans));
	login_calculate(ans, len, pass, seed);

	fail_unless(strncmp(ans, good, len) == 0, NULL);
}
END_TEST

START_TEST(test_login_hash_short)
{
	char ans[8];
	char check[sizeof(ans)];
	char pass[32] = "iodine is the shit";
	int len;
	int seed;

	len = sizeof(ans);
	seed = 15;

	memset(ans, 0, sizeof(ans));
	memset(check, 0, sizeof(check));

	/* If len < 32, it should do nothing */
	login_calculate(ans, len, pass, seed);
	fail_if(memcmp(ans, check, sizeof(ans)));
}
END_TEST

TCase *
test_login_create_tests()
{
	TCase *tc;

	tc = tcase_create("Login");
	tcase_add_test(tc, test_login_hash);
	tcase_add_test(tc, test_login_hash_short);

	return tc;
}
