dnl $Id$
dnl config.m4 for extension netutil

PHP_ARG_ENABLE(netutil, whether to enable netutil support,
Make sure that the comment is aligned:
[  --enable-netutil           Enable netutil support])

if test "$PHP_NETUTIL" != "no"; then
  PHP_NEW_EXTENSION(netutil, netutil.c, $ext_shared)
fi
