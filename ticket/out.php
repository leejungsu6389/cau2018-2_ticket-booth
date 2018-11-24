<?php

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
            $stmt->bind_param("iss", $bn, $bt, $bid);

            /* set parameters */

            /* ascend */
            $bn = $current_n[0] - 1;

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










            /* STEP4 LOG */
            $sql = "SELECT *
                    FROM _records
                    ORDER BY _od ASC";

            /* prepare */
            $stmt = $s->prepare($sql);

            /* execute */
            $stmt->execute();

            /* get result */
            $result = $stmt->get_result();

            while($row = $result->fetch_assoc()){

                $od[] = $row['_od'];
                $t[] = $row['t'];
                $io[] = $row['io'];

            }

            echo "od ".$od[0];
            echo "<br/>";


            echo "t ".$t[0];
            echo "<br/>";


            echo "io ".$io[0];
            echo "<br/>";


            $nn = count($od);

            echo "count ".$nn;
            echo "<br/>";

            for($i=0; $i < $nn; $i++){

                echo $od[$i]." : ".$t[$i]." : ".$io[$i];
                echo "<br/>";

            }


            /* close statement */
            $stmt->close();





            $sql = "INSERT INTO _records(_od, t, io)
                    VALUES(?, ?, ?)";

            /* prepare */
            $stmt = $s->prepare($sql);

            /* bind */
            $stmt->bind_param("iss", $bod, $btt, $bio);



            /* time에 현재 문제 있음 수정요망 */
            $tt = date('Y-m-d H:i:s', time());

            /* set parameters */

            /* ascend */
            $bod = $nn + 1;
            $btt = $tt;
            $bio = "OUT";


            /* execute */
            $stmt->execute();


            /* close statement */
            $stmt->close();


            /* disconnect db */
            mysqli_close($s);



        }
    }


?>