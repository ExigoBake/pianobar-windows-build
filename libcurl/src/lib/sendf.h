#ifndef HEADER_CURL_SENDF_H
#define HEADER_CURL_SENDF_H
/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2014, Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at http://curl.haxx.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/

#include "curl_setup.h"

CURL_STATIC CURLcode Curl_sendf(curl_socket_t sockfd, struct connectdata *,
                    const char *fmt, ...);
CURL_STATIC void Curl_infof(struct SessionHandle *, const char *fmt, ...);
CURL_STATIC void Curl_failf(struct SessionHandle *, const char *fmt, ...);

#if defined(CURL_DISABLE_VERBOSE_STRINGS)

#if defined(HAVE_VARIADIC_MACROS_C99)
#define infof(...)  Curl_nop_stmt
#elif defined(HAVE_VARIADIC_MACROS_GCC)
#define infof(x...)  Curl_nop_stmt
#else
#define infof (void)
#endif

#else /* CURL_DISABLE_VERBOSE_STRINGS */

#define infof Curl_infof

#endif /* CURL_DISABLE_VERBOSE_STRINGS */

#define failf Curl_failf

#define CLIENTWRITE_BODY   (1<<0)
#define CLIENTWRITE_HEADER (1<<1)
#define CLIENTWRITE_BOTH   (CLIENTWRITE_BODY|CLIENTWRITE_HEADER)

CURL_STATIC CURLcode Curl_client_chop_write(struct connectdata *conn, int type, char *ptr,
                                size_t len) WARN_UNUSED_RESULT;

CURL_STATIC CURLcode Curl_client_write(struct connectdata *conn, int type, char *ptr,
                           size_t len) WARN_UNUSED_RESULT;

/* internal read-function, does plain socket only */
CURL_STATIC CURLcode Curl_read_plain(curl_socket_t sockfd,
                         char *buf,
                         size_t bytesfromsocket,
                         ssize_t *n);

CURL_STATIC ssize_t Curl_recv_plain(struct connectdata *conn, int num, char *buf,
                        size_t len, CURLcode *code);
CURL_STATIC ssize_t Curl_send_plain(struct connectdata *conn, int num,
                        const void *mem, size_t len, CURLcode *code);

/* internal read-function, does plain socket, SSL and krb4 */
CURL_STATIC CURLcode Curl_read(struct connectdata *conn, curl_socket_t sockfd,
                   char *buf, size_t buffersize,
                   ssize_t *n);
/* internal write-function, does plain socket, SSL, SCP, SFTP and krb4 */
CURL_STATIC CURLcode Curl_write(struct connectdata *conn,
                    curl_socket_t sockfd,
                    const void *mem, size_t len,
                    ssize_t *written);

/* internal write-function, does plain sockets ONLY */
CURL_STATIC CURLcode Curl_write_plain(struct connectdata *conn,
                          curl_socket_t sockfd,
                          const void *mem, size_t len,
                          ssize_t *written);

/* the function used to output verbose information */
CURL_STATIC int Curl_debug(struct SessionHandle *handle, curl_infotype type,
               char *data, size_t size,
               struct connectdata *conn);


#endif /* HEADER_CURL_SENDF_H */
