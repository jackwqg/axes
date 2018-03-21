<?php
$br = (php_sapi_name() == "cli")? "":"<br>";

if(!extension_loaded('axes')) {
	dl('axes.' . PHP_SHLIB_SUFFIX);
}
$module = 'axes';
$functions = get_extension_funcs($module);
echo "Functions available in the {$module} extension:$br\n";
foreach($functions as $func) {
    echo $func."$br\n";
}
echo "$br\n";


$b = conv_wgs84_bdmercator(40.055211, 116.302095);
var_dump($b);
echo PHP_EOL;
