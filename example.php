<?php
$hash = geohash_encode(39.4169170000,100.92224000000);
$arr = geohash_decode($hash);
print_r($arr);
