--TEST--
koellner_phonetik
--INI--
--SKIPIF--
--FILE--
<?php
echo koellner_phonetik("Mueller")."\n";
echo koellner_phonetik("Müller")."\n";
echo koellner_phonetik("Meyer")."\n";
echo koellner_phonetik("Meier")."\n";
echo koellner_phonetik("Maier")."\n";
echo koellner_phonetik("Maier")."\n";
echo koellner_phonetik("Müller-Lüdenscheidt")."\n";
echo koellner_phonetik("Zumpe")."\n";
?>
--EXPECT--
657
657
67
67
67
67
65752682
861
