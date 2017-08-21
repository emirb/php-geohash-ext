/* Geohash extension for PHP */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_geohash.h"

static char char_map[32] =  "0123456789bcdefghjkmnpqrstuvwxyz";

static char*
_geohash_encode(double lat, double lng, int precision) {

    char* hash;


    hash = (char*)emalloc(sizeof(char) * (precision + 1));
    if (hash == NULL)
        return NULL;

    hash[precision] = '\0';

    precision *= 5.0;

    Interval lat_interval = {MAX_LAT, MIN_LAT};
    Interval lng_interval = {MAX_LONG, MIN_LONG};

    Interval *interval;
    double coord, mid;
    int is_even = 1;
    unsigned int hashChar = 0;
    int i;
    for(i = 1; i <= precision; i++) {

        if(is_even) {

            interval = &lng_interval;
            coord = lng;

        } else {

            interval = &lat_interval;
            coord = lat;
        }

        mid = (interval->low + interval->high) / 2.0;
        hashChar = hashChar << 1;

        if(coord > mid) {

            interval->low = mid;
            hashChar |= 0x01;

        } else
            interval->high = mid;

        if(!(i % 5)) {

            hash[(i - 1) / 5] = char_map[hashChar];
            hashChar = 0;

        }

        is_even = !is_even;
    }


    return hash;
}


static unsigned int index_for_char(char c, char *string) {

    unsigned int index = -1;
    int string_amount = strlen(string);
    int i;
    for(i = 0; i < string_amount; i++) {

        if(c == string[i]) {

            index = i;
            break;
        }

    }

    return index;
}

GeoCoord _geohash_decode(char *hash) {

    GeoCoord coordinate = {0.0, 0.0};

    if (hash) {

        int char_amount = strlen(hash);

        if(char_amount) {

            unsigned int char_mapIndex;
            Interval lat_interval = {MAX_LAT, MIN_LAT};
            Interval lng_interval = {MAX_LONG, MIN_LONG};
            Interval *interval;

            int is_even = 1;
            double delta;
            int i, j;
            for(i = 0; i < char_amount; i++) {

                char_mapIndex = index_for_char(hash[i], (char*)char_map);

                //JPM always false if(char_mapIndex < 0)
                //JPM    break;

                // Interpret the last 5 bits of the integer
                for(j = 0; j < 5; j++) {

                    interval = is_even ? &lng_interval : &lat_interval;

                    delta = (interval->high - interval->low) / 2.0;

                    if((char_mapIndex << j) & 0x0010)
                        interval->low += delta;
                    else
                        interval->high -= delta;

                    is_even = !is_even;
                }

            }

            coordinate.latitude = lat_interval.high - ((lat_interval.high - lat_interval.low) / 2.0);
            coordinate.longitude = lng_interval.high - ((lng_interval.high - lng_interval.low) / 2.0);
        }
    }

    return coordinate;
}

/* }}} */

/* {{{ string geohash_encode( [ float $lat, float $lng, int $precision = 12 ] )
 */
PHP_FUNCTION(geohash_encode)
{
    double lat;
    double lng;
    int precision = 12;
    zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dd|l", &lat, &lng, &precision);
    char *hash;
    hash = _geohash_encode(lat, lng, precision);
    #if PHP_MAJOR_VERSION < 7
    RETURN_STRING(hash, 0);
    #else
    RETURN_STRING(hash);
    #endif

    efree(hash);
}


/* {{{ string geohash_decode( [ string $geohash ] )
 */
PHP_FUNCTION(geohash_decode)
{
    char *hash;
    long hash_len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &hash, &hash_len) == FAILURE) {
            return;
    }

    GeoCoord area =  _geohash_decode(hash);

    array_init(return_value);
    add_assoc_double(return_value,"latitude",area.latitude);
    add_assoc_double(return_value,"longitude",area.longitude);
}

/* }}}*/


/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(geohash)
{
    php_info_print_table_start();
    php_info_print_table_row(2, "geohash support", "enabled");
    php_info_print_table_row(2, "geohash version", PHP_GEOHASH_VERSION);

    php_info_print_table_end();
}
/* }}} */

/* {{{ arginfo
 */

ZEND_BEGIN_ARG_INFO(arginfo_geohash_encode, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_geohash_decode, 0)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ geohash_functions[]
 */
const zend_function_entry geohash_functions[] = {
    PHP_FE(geohash_encode,      arginfo_geohash_encode)
        PHP_FE(geohash_decode,          arginfo_geohash_decode)
    PHP_FE_END
};
/* }}} */

/* {{{ geohash_module_entry
 */
zend_module_entry geohash_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    "geohash",                    /* Extension name */
    geohash_functions,            /* zend_function_entry */
    NULL,                           /* PHP_MINIT - Module initialization */
    NULL,                           /* PHP_MSHUTDOWN - Module shutdown */
    NULL,            /* PHP_RINIT - Request initialization */
    NULL,                           /* PHP_RSHUTDOWN - Request shutdown */
    PHP_MINFO(geohash),           /* PHP_MINFO - Module info */
#if ZEND_MODULE_API_NO >= 20010901
    PHP_GEOHASH_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_GEOHASH
ZEND_GET_MODULE(geohash)
#endif

