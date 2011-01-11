#include "php_migemo.h"

PHPAPI function_entry php_migemo_methods[] = {
    {NULL, NULL, NULL}
};

PHP_MINIT_FUNCTION(migemo) {
    return SUCCESS;
}

PHP_MINFO_FUNCTION(migemo)
{
    return SUCCESS;
}

zend_module_entry migemo_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_MIGEMO_EXTNAME,
    NULL, 					/* Functions */
    PHP_MINIT(migemo),	    /* MINIT */
    NULL, 	                /* MSHUTDOWN */
    NULL, 	                /* RINIT */
    NULL,	                /* RSHUTDOWN */
    PHP_MINFO(migemo),	    /* MINFO */
#if ZEND_MODULE_API_NO >= 20010901
    PHP_MIGEMO_EXTVER,
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_MIGEMO
ZEND_GET_MODULE(migemo)
#endif
