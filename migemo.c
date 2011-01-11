#include "php_migemo.h"

typedef struct{
    zend_object zo;
    migemo *migemo;
} php_migemo;

static void php_migemo_free_storage(php_migemo *object TSRMLS_DC)
{
    zend_object_std_dtor(&object->zo TSRMLS_CC);
    
    if(!object->migemo){
      migemo_free(object->migemo);
    }
    object->migemo = NULL;
    efree(object);
}

zend_object_value php_migemo_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	php_migemo *obj;
	zval *tmp;

	obj = ecalloc(1, sizeof(*obj));
	zend_object_std_init( &obj->zo, ce TSRMLS_CC );
	zend_hash_copy(obj->zo.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref, (void *) &tmp, sizeof(zval *));

	retval.handle = zend_objects_store_put(obj, 
        (zend_objects_store_dtor_t)zend_objects_destroy_object,
        (zend_objects_free_object_storage_t)php_migemo_free_storage,
        NULL TSRMLS_CC);
	retval.handlers = zend_get_std_object_handlers();
	return retval;
}



ZEND_BEGIN_ARG_INFO_EX(arginfo_migemo_query, 0, 0, 1)
    ZEND_ARG_INFO(0, query)
ZEND_END_ARG_INFO()
PHP_METHOD(migemo, query)
{
    php_migemo *this = (php_migemo *) zend_object_store_get_object(getThis() TSRMLS_CC);
    char *query;
    int ret = 0;
    int query_len = 0;
    unsigned char *result;
    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "s", &query, &query_len) == FAILURE){
        return;
    }

    result = migemo_query(this->migemo, query);

    RETVAL_STRING(result, 1);
    migemo_release(this->migemo, result);
}

PHP_METHOD(migemo, __construct){
    php_migemo *this = (php_migemo *) zend_object_store_get_object(getThis() TSRMLS_CC);

    this->migemo = migemo_open("/usr/local/share/migemo/utf-8/migemo-dict");
}


PHPAPI function_entry php_migemo_methods[] = {
    PHP_ME(migemo, __construct, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(migemo, query, arginfo_migemo_query, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

PHP_MINIT_FUNCTION(migemo) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "Migemo", php_migemo_methods);
    migemo_class_entry = zend_register_internal_class(&ce TSRMLS_CC);
  	migemo_class_entry->create_object = php_migemo_new;

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
