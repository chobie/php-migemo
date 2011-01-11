PHP_ARG_ENABLE(migemo,
  [Whether to enable the "migemo" extension]
  [  --enable-migemo      Enable "migemo" extension support])

if test $PHP_MIGEMO != "no"; then
  export CFLAGS="$CFLAGS -lmigemo"
  PHP_SUBST(MIGEMO_SHARED_LIBADD)
  PHP_NEW_EXTENSION(migemo, migemo.c, $ext_shared)
fi
