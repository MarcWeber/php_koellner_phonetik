Köllner Phonetik für PHP in C
=============================
http://de.wikipedia.org/wiki/K%C3%B6lner_Phonetik

compile:
========
phpize
./configure && make && NO_INTERACTION=1 make test

provides koellner_phonetik(str) returning str


BE CAREFUL
==========
There are many different implementations, eg what is the correct encoding of
czaska ? According to wikipedia c before z does not exist, z is the same as s,
thus the result is 84. Some PHP implementations don't implement this this way

Also word separators are treated differently in some cases.
So whatever transcription you use, stick to it.
