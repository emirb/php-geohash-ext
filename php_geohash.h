/* 
 * Geohash extension for PHP
 * 
 * Copyright (c) 2017 Emir Beganovic. All rights reserved.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * @package     php_geohash
 * @author      Emir Beganovic <emir@php.net>
 * @copyright   2017 Emir Beganovic
 * @license     http://www.opensource.org/licenses/mit-license.php  MIT License
*/

#ifndef PHP_GEOHASH_H
#define PHP_GEOHASH_H

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"

#include "php_geohash.h"

extern zend_module_entry geohash_module_entry;
#define phpext_geohash_ptr &geohash_module_entry

#define PHP_GEOHASH_VERSION "1.0.0"

#ifdef ZTS
#include "TSRM.h"
#endif


PHP_FUNCTION(geohash_encode);
PHP_FUNCTION(geohash_decode);

#ifdef ZTS
#define GEOHASH_G(v) TSRMG(geohash_globals_id, zend_geohash_globals *, v)
#else
#define GEOHASH_G(v) (geohash_globals.v)
#endif

#endif


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
