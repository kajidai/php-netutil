/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2007 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id: header,v 1.16.2.1.2.1 2007/01/01 19:32:09 iliaa Exp $ */

#ifndef PHP_NETUTIL_H
#define PHP_NETUTIL_H

extern zend_module_entry netutil_module_entry;
#define phpext_netutil_ptr &netutil_module_entry

#ifdef PHP_WIN32
#define PHP_NETUTIL_API __declspec(dllexport)
#else
#define PHP_NETUTIL_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(netutil);
PHP_MSHUTDOWN_FUNCTION(netutil);
PHP_RINIT_FUNCTION(netutil);
PHP_RSHUTDOWN_FUNCTION(netutil);
PHP_MINFO_FUNCTION(netutil);

PHP_FUNCTION(get_hwaddr);
PHP_FUNCTION(get_addr);

#ifdef ZTS
#define NETUTIL_G(v) TSRMG(netutil_globals_id, zend_netutil_globals *, v)
#else
#define NETUTIL_G(v) (netutil_globals.v)
#endif

#endif	/* PHP_NETUTIL_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
