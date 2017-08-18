PHP Geohash library
=======
[![Build Status](https://travis-ci.org/emirb/php-geohash.svg?branch=master)](https://travis-ci.org/emirb/php-geohash)

Installation
======

	git clone git@github.com:emirb/geohash.git
	cd geohash
    
	phpize
	./configure
	make
	make install

Add geohash.so to your php.ini.
	

Usage
====

	/**
	 *  $latitude    //纬度
	 *  $longitude   //经度
	 *  $precision   //精密度, 默认是12
	 *  返回 $precision 长度的 string 
	 */
	geohash_encode($latitude, $longitude, $precision=12);  



	/**
	 *  $hash    //geohash_encode后的值
	 *  返回 array // Array
	 *					(
	 *					    [latitude] => 39.416916975752
	 *					    [longitude] => 100.92223992571
	 *					    [north] => 39.416917059571
	 *					    [east] => 100.92224009335
	 *					    [south] => 100.92223992571
	 *					    [west] => 100.92223975807
	 *					)
	 */
	geohash_decode($hash);

	/**
	 *  $hash    //geohash_encode后的值
	 *  返回 在$hash 8个方向的hash值 （顺序：N, NE, E, SE, S, SW, W, NW）
	 *  
	 *		  NW N NE
	 *		    \|/
	 *		  W - - E
	 *		    /|\
	 *		  SW S SE
	 * 
	 */
	geohash_neighbors($hash);

	/**
	 *  $precision    //精密度
	 *  返回 数组，array("width"=>12.0, "height"=>12.0) 
	 *  表示矩形的宽和高
	 */
	geohash_dimension($precision);
