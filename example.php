<?php
$hash = geohash_encode(39.4169170000,100.92224000000);
echo $hash.PHP_EOL;
$arr = geohash_decode($hash);
print_r($arr);
