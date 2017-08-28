--TEST--
Check for geohash presence
--SKIPIF--
<?php if (!extension_loaded("geohash")) print "skip"; ?>
--FILE--
<?php
echo geohash_encode(48.2, 16.4, 12).PHP_EOL;
echo geohash_encode(90, 90, 6).PHP_EOL;
echo geohash_encode(48.21, 16.363, 32).PHP_EOL;
echo geohash_encode(95, 95, 6).PHP_EOL;
echo geohash_encode(185, 185, 12).PHP_EOL;
echo geohash_encode(-185, -90, 12).PHP_EOL;
var_dump(geohash_decode('ezs42'));
$ext = new ReflectionExtension('geohash');
$ext->info();
?>
--EXPECT--
u2edjnw17enr
vzzzzz
u2edk275te35u5s6504t7yfpbpbpbpbp
ypgxcz
zzzzzzzzzzzz
1bpbpbpbpbpb
array(2) {
  ["latitude"]=>
  float(42.60498046875)
  ["longitude"]=>
  float(-5.60302734375)
}

geohash

geohash support => enabled
geohash version => 1.0
