dnl config.m4 for extension php_screw
dnl don't forget to call PHP_EXTENSION(php_screw)
dnl If your extension references something external, use with:

PHP_ARG_WITH(php_screw, for php_screw support,
dnl Make sure that the comment is aligned:
[  --with-php_screw             Include php_screw support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(php_screw, whether to enable php_screw support,
dnl Make sure that the comment is aligned:
[  --enable-php_screw           Enable php_screw support])

if test "$PHP_php_screw" != "no"; then
  dnl Action..
  PHP_EXTENSION(php_screw, $ext_shared)
fi
