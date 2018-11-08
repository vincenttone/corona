<?php
function v_rcli($m, $mod = 1)
{
    $x = null;
    global $argv;
    if (isset($argv[1])) {
        $query = $argv[1];
        $x = call_user_func($m, $query);
    } else {
        while($query = fgets(STDIN)) {
            $x = call_user_func($m, $query);
        }
    }
    if ($x !== null) {
        if ($mod == 2) {
            echo $x;
        } elseif ($mod == 3) {
            print_r($x);
        }
        echo PHP_EOL;
    }
}