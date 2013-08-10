PHP_ARG_ENABLE(my_extension, whether to enable my extension,
[ --enable-my-extension   Enable my extension])
 
if test "$PHP_MY_EXTENSION" = "yes"; then
  AC_DEFINE(HAVE_MY_EXTENSION, 1, [enable koellner_phonetik])
  PHP_NEW_EXTENSION(koellner_phonetik, koellner_phonetik.c, $ext_shared)
fi
