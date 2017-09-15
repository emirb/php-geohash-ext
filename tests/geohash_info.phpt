--TEST--
Check geohash extension info
--SKIPIF--
<?php if (!extension_loaded("geohash")) print "skip"; ?>
--FILE--
<?php

$ext = new ReflectionExtension('geohash');
$ext->info();
?>
--EXPECT--
geohash

geohash support => enabled
geohash version => 1.0.0
