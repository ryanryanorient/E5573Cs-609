/**
 * \file config.h
 *
 *  Based on XySSL: Copyright (C) 2006-2008  Christophe Devine
 *
 *  Copyright (C) 2009  Paul Bakker <polarssl_maintainer at polarssl dot org>
 *
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *    * Neither the names of PolarSSL or XySSL nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 *  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 *  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 *  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * This set of compile-time options may be used to enable
 * or disable features selectively, and reduce the global
 * memory footprint.
 */
#include "atpconfig.h"

#ifndef POLARSSL_CONFIG_H
#define POLARSSL_CONFIG_H

#ifndef _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE 1
#endif

/*
 * Uncomment if native integers are 8-bit wide.
 *
#define POLARSSL_HAVE_INT8
 */

/*
 * Uncomment if native integers are 16-bit wide.
 *
#define POLARSSL_HAVE_INT16
 */

/*
 * Uncomment if the compiler supports long long.
 *
#define POLARSSL_HAVE_LONGLONG
 */

/*
 * Uncomment to enable the use of assembly code.
 *
 * Requires support for asm() in compiler.
 *
 * Used in:
 *      library/timing.c
 *      library/padlock.c
 *      include/polarssl/bn_mul.h
 *
 */
#define POLARSSL_HAVE_ASM

/*
 * Uncomment if the CPU supports SSE2 (IA-32 specific).
 *
#define POLARSSL_HAVE_SSE2
 */

/*
 * Enable all SSL/TLS debugging messages.
 */
//#define POLARSSL_DEBUG_MSG

/*
 * Enable the checkup functions (*_self_test).
 */
//#define POLARSSL_SELF_TEST

/*
 * Enable the prime-number generation code.
 */
#define POLARSSL_GENPRIME

/*
 * Uncomment this macro to store the AES tables in ROM.
 *
#define POLARSSL_AES_ROM_TABLES
 */

/*
 * Module:  library/aes.c
 * Caller:  library/ssl_tls.c
 *
 * This module enables the following ciphersuites:
 *      SSL_RSA_AES_128_SHA
 *      SSL_RSA_AES_256_SHA
 *      SSL_EDH_RSA_AES_256_SHA
 */
#ifdef SUPPORT_ATP_MINISSL_AES
#define POLARSSL_AES_C
#endif

/*
 * Module:  library/arc4.c
 * Caller:  library/ssl_tls.c
 *
 * This module enables the following ciphersuites:
 *      SSL_RSA_RC4_128_MD5
 *      SSL_RSA_RC4_128_SHA
 */
#ifdef SUPPORT_ATP_MINISSL_RC4
#define POLARSSL_ARC4_C
#endif

/*
 * Module:  library/base64.c
 * Caller:  library/x509parse.c
 *
 * This module is required for X.509 support.
 */
#define POLARSSL_BASE64_C

/*
 * Module:  library/bignum.c
 * Caller:  library/dhm.c
 *          library/rsa.c
 *          library/ssl_tls.c
 *          library/x509parse.c
 *
 * This module is required for RSA and DHM support.
 */
#define POLARSSL_BIGNUM_C

/*
 * Module:  library/camellia.c
 * Caller:  library/ssl_tls.c
 *
 * This module enabled the following cipher suites:
 *      SSL_RSA_CAMELLIA_128_SHA
 *      SSL_RSA_CAMELLIA_256_SHA
 *      SSL_EDH_RSA_CAMELLIA_256_SHA
 */
//#define POLARSSL_CAMELLIA_C

/*
 * Module:  library/certs.c
 * Caller:
 *
 * This module is used for testing (ssl_client/server).
 */
//#define POLARSSL_CERTS_C

/*
 * Module:  library/debug.c
 * Caller:  library/ssl_cli.c
 *          library/ssl_srv.c
 *          library/ssl_tls.c
 *
 * This module provides debugging functions.
 */
//#define POLARSSL_DEBUG_C

/*
 * Module:  library/des.c
 * Caller:  library/ssl_tls.c
 *
 * This module enables the following ciphersuites:
 *      SSL_RSA_DES_168_SHA
 *      SSL_EDH_RSA_DES_168_SHA
 */
#ifdef SUPPORT_ATP_MINISSL_DES3
#define POLARSSL_DES_C
#endif

/*
 * Module:  library/dhm.c
 * Caller:  library/ssl_cli.c
 *          library/ssl_srv.c
 *
 * This module enables the following ciphersuites:
 *      SSL_EDH_RSA_DES_168_SHA
 *      SSL_EDH_RSA_AES_256_SHA
 *      SSL_EDH_RSA_CAMELLIA_256_SHA
 */
#ifdef SUPPORT_ATP_MINISSL_DH
#define POLARSSL_DHM_C
#endif

/*
 * Module:  library/havege.c
 * Caller:
 *
 * This module enables the HAVEGE random number generator.
 */
#define POLARSSL_HAVEGE_C

/*
 * Module:  library/md2.c
 * Caller:  library/x509parse.c
 *
 * Uncomment to enable support for (rare) MD2-signed X.509 certs.
 *
#define POLARSSL_MD2_C
 */

/*
 * Module:  library/md4.c
 * Caller:  library/x509parse.c
 *
 * Uncomment to enable support for (rare) MD4-signed X.509 certs.
 *
#define POLARSSL_MD4_C
 */

/*
 * Module:  library/md5.c
 * Caller:  library/ssl_tls.c
 *          library/x509parse.c
 *
 * This module is required for SSL/TLS and X.509.
 */
#define POLARSSL_MD5_C

/*
 * Module:  library/net.c
 * Caller:
 *
 * This module provides TCP/IP networking routines.
 */
#define POLARSSL_NET_C

/*
 * Module:  library/padlock.c
 * Caller:  library/aes.c
 *
 * This modules adds support for the VIA PadLock on x86.
 */
//#define POLARSSL_PADLOCK_C

/*
 * Module:  library/rsa.c
 * Caller:  library/ssl_cli.c
 *          library/ssl_srv.c
 *          library/ssl_tls.c
 *          library/x509.c
 *
 * This module is required for SSL/TLS and MD5-signed certificates.
 */
#ifdef SUPPORT_ATP_MINISSL_RSA
#define POLARSSL_RSA_C
#endif
/*
 * Module:  library/sha1.c
 * Caller:  library/ssl_cli.c
 *          library/ssl_srv.c
 *          library/ssl_tls.c
 *          library/x509parse.c
 *
 * This module is required for SSL/TLS and SHA1-signed certificates.
 */
#define POLARSSL_SHA1_C

/*
 * Module:  library/sha2.c
 * Caller:
 *
 * This module adds support for SHA-224 and SHA-256.
 */
#ifdef SUPPORT_ATP_MINISSL_SHA256
#define POLARSSL_SHA2_C
#endif

/*
 * Module:  library/sha4.c
 * Caller:
 *
 * This module adds support for SHA-384 and SHA-512.
 */
#define POLARSSL_SHA4_C

/*
 * Module:  library/ssl_cli.c
 * Caller:
 *
 * This module is required for SSL/TLS client support.
 */

#ifdef SUPPORT_ATP_MINISSL_CLIENT
#define POLARSSL_SSL_CLI_C
#endif

/*
 * Module:  library/ssl_srv.c
 * Caller:
 *
 * This module is required for SSL/TLS server support.
 */
#ifdef SUPPORT_ATP_MINISSL_CLIENT
#define POLARSSL_SSL_SRV_C
#endif

/*
 * Module:  library/ssl_tls.c
 * Caller:  library/ssl_cli.c
 *          library/ssl_srv.c
 *
 * This module is required for SSL/TLS.
 */
#ifdef SUPPORT_ATP_MINISSL_TLS
#define POLARSSL_SSL_TLS_C
#endif

/*
 * Module:  library/timing.c
 * Caller:  library/havege.c
 *
 * This module is used by the HAVEGE random number generator.
 */
#define POLARSSL_TIMING_C

/*
 * Module:  library/x509parse.c
 * Caller:  library/ssl_cli.c
 *          library/ssl_srv.c
 *          library/ssl_tls.c
 *
 * This module is required for X.509 certificate parsing.
 */
#ifdef SUPPORT_ATP_MINISSL_X509
#define POLARSSL_X509_PARSE_C
#endif

/*
 * Module:  library/x509_write.c
 * Caller:
 *
 * This module is required for X.509 certificate writing.
 */
#ifdef SUPPORT_ATP_MINISSL_X509
//#define POLARSSL_X509_WRITE_C
#endif

/*
 * Module:  library/xtea.c
 * Caller:
 */
//#define POLARSSL_XTEA_C

#endif /* config.h */
