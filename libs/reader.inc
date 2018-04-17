<?php
function read_from_stdin()
{
    while($d = fgets(STDIN)) {
        yield $d;
    }
}