#include "php_migemo.h"


ZEND_BEGIN_ARG_INFO_EX(arginfo_migemo_query, 0, 0, 1)
    ZEND_ARG_INFO(0, query)
ZEND_END_ARG_INFO()
PHP_METHOD(migemo, query)
{
    migemo *m;
    char *query;
    int ret = 0;
    int query_len = 0;
    unsigned char *result;
    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "s", &query, &query_len) == FAILURE){
        return;
    }

    m =  migemo_open("/usr/local/share/migemo/utf-8/migemo-dict");
    result = migemo_query(m, query);

    RETVAL_STRING(result, 1);
    migemo_release(m, result);
    migemo_close(m);
}


PHPAPI function_entry php_migemo_methods[] = {
    PHP_ME(migemo, query, arginfo_migemo_query, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

PHP_MINIT_FUNCTION(migemo) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "Migemo", php_migemo_methods);
    migemo_class_entry = zend_register_internal_class(&ce TSRMLS_CC);

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
