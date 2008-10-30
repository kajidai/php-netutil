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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_netutil.h"

#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>

/* True global resources - no need for thread safety here */
static int le_netutil;

/* {{{ netutil_functions[]
 *
 * Every user visible function must have an entry in netutil_functions[].
 */
zend_function_entry netutil_functions[] = {
	PHP_FE(get_hwaddr,	NULL)		/* For testing, remove later. */
	PHP_FE(get_addr,	NULL)		/* For testing, remove later. */
	{NULL, NULL, NULL}	/* Must be the last line in netutil_functions[] */
};
/* }}} */

/* {{{ netutil_module_entry
 */
zend_module_entry netutil_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"netutil",
	netutil_functions,
	PHP_MINIT(netutil),
	PHP_MSHUTDOWN(netutil),
	PHP_RINIT(netutil),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(netutil),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(netutil),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_NETUTIL
ZEND_GET_MODULE(netutil)
#endif

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(netutil)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(netutil)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(netutil)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(netutil)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(netutil)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "netutil support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

// {{{ PHP_FUNCTION(get_hwaddr)
PHP_FUNCTION(get_hwaddr)
{
    const char *key = NULL;
    int key_len = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &key, &key_len) == FAILURE) {
        return;
    }

    int fd;
    struct ifreq ifr;
    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    }
    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name, key, IFNAMSIZ-1);
    if (ioctl(fd, SIOCGIFHWADDR, &ifr) < 0) {
        close(fd);
    }
    char str[100];
    sprintf(str, "%.2x:%.2x:%.2x:%.2x:%.2x:%.2x",
            (unsigned char)ifr.ifr_hwaddr.sa_data[0],
            (unsigned char)ifr.ifr_hwaddr.sa_data[1],
            (unsigned char)ifr.ifr_hwaddr.sa_data[2],            (unsigned char)ifr.ifr_hwaddr.sa_data[3],
            (unsigned char)ifr.ifr_hwaddr.sa_data[4],
            (unsigned char)ifr.ifr_hwaddr.sa_data[5]);    ZVAL_STRINGL(return_value, str, strlen(str), 1);
}
// }}}

// {{{ PHP_FUNCTION(get_addr)
PHP_FUNCTION(get_addr)
{
    const char *key = NULL;
    int key_len = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &key, &key_len) == FAILURE) {
        return;
    }

    int fd;
    struct ifreq ifr;
    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    }
    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name, key, IFNAMSIZ-1);
    if (ioctl(fd, SIOCGIFADDR, &ifr) < 0) {
        close(fd);
    }
    char str[100];
    sprintf(str, "%s", inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));

    ZVAL_STRINGL(return_value, str, strlen(str), 1);
    close(fd);
}
// }}}
/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
