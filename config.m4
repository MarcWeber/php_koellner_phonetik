PHP_ARG_ENABLE(koellner_phonetik_extension, whether to enable my extension,
[ --enable-koellner-phonetik-extension   Enable my extension])
 
if test "$PHP_KOELLNER_PHONETIK_EXTENSION" = "yes"; then
  AC_DEFINE(HAVE_KOELLNER_PHONETIK_EXTENSION, 1, [enable koellner_phonetik])
  PHP_NEW_EXTENSION(koellner_phonetik_extension, koellner_phonetik_extension.c, $ext_shared)
fi
