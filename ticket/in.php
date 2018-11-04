﻿<?php

    /* import machine key file */
    require_once("key.php");

    /*
    echo "test: ".MK;
    echo "<br>";
    */

    /* undefined key */
    /* invalid access */
    if(!isset($_POST["MACHINE_KEY"])){
        echo "err: access denied, invalid access";
    }

    /* check whether key is valid or not */
    else{

        $k = $_POST["MACHINE_KEY"];

        /*
        echo "<br>";
        echo "key: ".$k;
        */

        /* key is wrong */
        if($k != MK){
            echo "err: access denied, invalid key";
        }
        /* valid key */
        /* count up */
        else{


            /* STEP 1 import database */
            /* make a database connection */
            require_once("db_connect.php");


            /* ======================= */


            /* STEP 2 get current count */
            $sql = "SELECT *
                    FROM people";

            /* prepare */
            $stmt = $s->prepare($sql);

            /* execute */
            $stmt->execute();

            /* get result */
            $result = $stmt->get_result();


            while($row = $result->fetch_assoc()){

                $current_n[] = $row['num'];

            }


            $stmt->close();


            /*
            echo "currnet: ".$current_n[0];
            */

            /* ======================= */

            /* STEP 3 Count Up */
            $sql = "UPDATE people
                    SET num = ?, last_t = ?
                    WHERE id = ?";

            /* prepare */
            $stmt = $s->prepare($sql);

            /* bind */
            $stmt->bind_param("sis", $bn, $bt, $bid);

            /* set parameters */

            /* ascend */
            $bn = $current_n[0] + 1;

            /* time에 현재 문제 있음 수정요망 */
            $bt = date('Y-m-d H:i:s', time());

            $bid = MK;


            /*
            echo "test<br>";
            echo $bn;
            echo "test<br>";
            echo $bt;
            echo "test<br>";
            echo $bid;
            */

            /* execute */
            $stmt->execute();

            /* close statement */
            $stmt->close();

            /* disconnect db */
            mysqli_close($s);



        }
    }


?>