<?php
/**
 * Print the information, using for debug
 */
function p()
{
    $end_of_line = '<br/>'.PHP_EOL;
    php_sapi_name() == 'cli' && $end_of_line = PHP_EOL;
    $args = func_get_args();
    array_unshift($args, $end_of_line);
    echo call_user_func_array('v_debug_settle', $args);
}

function l()
{
    $args = func_get_args();
    array_unshift($args, PHP_EOL);
    $data = call_user_func_array('v_debug_settle', $args);
    file_put_contents('/tmp/v.debug.log', $data, FILE_APPEND);
}

function v_debug_settle()
{
    $file = '';
    $line = '';
    if (true) {
        $trace = debug_backtrace();
        if (isset($trace[1])) {
            isset($trace[1]['file']) && $file = $trace[1]['file'];
            isset($trace[1]['line']) && $line = $trace[1]['line'];
        }
    }
    $args = func_get_args();
    $end_of_line = array_shift($args);
    $repc = 1;
    $head_line = str_repeat('-', $repc).' FILE:['.$file.'] -- LINE: ['.$line.'] '.str_repeat('-', $repc).$end_of_line;
    $dec_line = str_repeat('-', strlen($head_line) - 1).$end_of_line;
    $target = '';
    $target .= $dec_line;
    $target .= $head_line;
    $target .= $dec_line;
    foreach($args as $_arg) {
        if (empty($_arg) || is_bool($_arg)) {
            $target .= var_export($_arg, true);
            $target .= $end_of_line;
        } elseif (is_scalar($_arg)) {
            $target .= $_arg;
            $target .= $end_of_line;
        } else {
            $target .= json_encode($_arg);
            $target .= $end_of_line;
        }
    }
    $target .= str_repeat('=', strlen($head_line) - 1).$end_of_line;
    return $target;
}