<?php

    /* import PHP Excel library */


    /* read current.xlsx */



    /* get HTTP request */
    $s = $_POST["Signal"];



    /* write to current.xlsx */
    if($s == 'IN'){
        echo "incre";
    }
    else if($s == 'OUT'){
        echo "decre";
    }
    else{
        echo "error occur: INVALID sign";
    }


    
    /* for every 30 seconds Log */
    /* write to LOG.xlsx */




?>