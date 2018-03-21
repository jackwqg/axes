
#ifndef PHP_AXES_H
#define PHP_AXES_H

extern zend_module_entry axes_module_entry;
#define phpext_axes_ptr &axes_module_entry

#define PHP_AXES_VERSION "0.1.0" /* Replace with version number for your extension */

#ifdef PHP_WIN32
#	define PHP_AXES_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_AXES_API __attribute__ ((visibility("default")))
#else
#	define PHP_AXES_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(axes);
PHP_MSHUTDOWN_FUNCTION(axes);
PHP_RINIT_FUNCTION(axes);
PHP_RSHUTDOWN_FUNCTION(axes);
PHP_MINFO_FUNCTION(axes);

PHP_FUNCTION(conv_wgs84_bdmercator);

/* 
  	Declare any global variables you may need between the BEGIN
	and END macros here:     

ZEND_BEGIN_MODULE_GLOBALS(axes)
	long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(axes)
*/

/* In every utility function you add that needs to use variables 
   in php_axes_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as AXES_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define AXES_G(v) TSRMG(axes_globals_id, zend_axes_globals *, v)
#else
#define AXES_G(v) (axes_globals.v)
#endif

#endif	/* PHP_AXES_H */

