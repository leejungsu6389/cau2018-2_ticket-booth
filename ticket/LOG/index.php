<?php
header( "Content-type: application/vnd.ms-excel" );
header( "Content-type: application/vnd.ms-excel; charset=utf-8");
header( "Content-Disposition: attachment; filename = invoice.xls" );
header( "Content-Description: PHP4 Generated Data" );


require_once("../key.php");
require_once("../db_connect.php");





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



$nn = count($od);



/* close statement */
$stmt->close();

/* disconnect db */
mysqli_close($s);




$EXCEL_STR = "
            <table border='1'>
            <tr>
               <td>order</td>
               <td>time</td>
               <td>Description</td>
            </tr>";

for($i=0; $i < $nn; $i++){

   $EXCEL_STR .= "
   <tr>
       <td>".$od[$i]."</td>
       <td>".$t[$i]."</td>
       <td>".$io[$i]."</td>
   </tr>
   ";


}


$EXCEL_STR .= "</table>";

echo "<meta content=\"application/vnd.ms-excel; charset=UTF-8\" name=\"Content-type\"> ";
echo $EXCEL_STR;

?>