#ifndef PHP_MIGEMO_H
#define PHP_MIGEMO_H

#define PHP_MIGEMO_EXTNAME "migemo"
#define PHP_MIGEMO_EXTVER "0.1"


#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include <migemo.h>

extern zend_module_entry migemo_module_entry;
#define phpext_migemo_ptr &migemo_module_entry;

PHPAPI zend_class_entry *migemo_class_entry;

#endif /* PHP_MIGEMO_H */
