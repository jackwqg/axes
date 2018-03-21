
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_axes.h"

#include "axes_lib.c"
/* If you declare any globals in php_axes.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(axes)
*/

/* True global resources - no need for thread safety here */
static int le_axes;

/* {{{ axes_functions[]
 *
 * Every user visible function must have an entry in axes_functions[].
 */
const zend_function_entry axes_functions[] = {
	PHP_FE(conv_wgs84_bdmercator,	NULL)		
	{NULL, NULL, NULL}	/* Must be the last line in axes_functions[] */
};
/* }}} */

/* {{{ axes_module_entry
 */
zend_module_entry axes_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"axes",
	axes_functions,
	PHP_MINIT(axes),
	PHP_MSHUTDOWN(axes),
	PHP_RINIT(axes),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(axes),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(axes),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_AXES_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_AXES
ZEND_GET_MODULE(axes)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("axes.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_axes_globals, axes_globals)
    STD_PHP_INI_ENTRY("axes.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_axes_globals, axes_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_axes_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_axes_init_globals(zend_axes_globals *axes_globals)
{
	axes_globals->global_value = 0;
	axes_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(axes)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(axes)
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
PHP_RINIT_FUNCTION(axes)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(axes)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(axes)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "axes support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string conv_wgs84_bdmercator(double lat, double lon)
   Return a struce */

PHP_FUNCTION(conv_wgs84_bdmercator)
{
	double lat = 0;
	double lon = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dd", &lat, &lon) == FAILURE) {
		return;
	}

	struct_coor coor = axes_wgs84togcj02(lat, lon);
    
	coor = axes_gcj02tobd09(coor.lat, coor.lng);
	coor = axes_bd09toMc(coor.lng, coor.lat);
	
	array_init(return_value);
	add_assoc_double(return_value,"latitude",coor.lat);
	add_assoc_double(return_value,"longitude",coor.lng);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
