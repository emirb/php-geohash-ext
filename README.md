PHP Geohash library
=======
[![Build Status](https://travis-ci.org/emirb/php-geohash-ext.svg?branch=master)](https://travis-ci.org/emirb/php-geohash-etx)
![PHP >5.4](https://img.shields.io/badge/php-%3E%3D%205.4-8892BF.svg)

Introduction
=======
Geohash is a geocoding system invented by Gustavo Niemeyer. This is a PHP extension that can be used for improved performance compared to user-land libraries. Requires at least PHP > 5.4.

Installation
======

	git clone git@github.com:emirb/geohash.git
	cd geohash
    
	phpize
	./configure
	make
	make install

Add `extension=geohash.so` to your php.ini.
	

Usage
====
```php
/**
 *  Encodes latitude and longitude to geohash string with given precision.
 */
geohash_encode(float $latitude, float $longitude, int $precision=12): string;

/**
 *  Returns array with latitude and longitude, i.e.
 *  Array
 *	(
 *		[latitude] => 45.18
 *		[longitude] => 12.19
 *	)
 */
geohash_decode(string $hash): array;
```
