//invokes functions as soon as window loads
window.onload = function(){
	time();
	whatDay();
	setInterval(function(){
		time();
		whatDay();
	}, 1000);
};





// check whether the machine is on or not
function onOff(){


}


//gets current time and changes html to reflect it
function time(){

<?php
require_once("../db_connect.php");

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


$result = $current_n[0];

?>


var test = '<?php echo $result; ?>';


	var date = new Date(),
		hours = date.getHours(),
		minutes = date.getMinutes(),
		seconds = date.getSeconds();

	//make clock a 12 hour clock instead of 24 hour clock
	hours = (hours > 12) ? (hours - 12) : hours;
	hours = (hours === 0) ? 12 : hours;

	//invokes function to make sure number has at least two digits
	hours = addZero(hours);
	minutes = addZero(minutes);
	seconds = addZero(seconds);

	//changes the html to match results
	document.getElementsByClassName('hours')[0].innerHTML = hours;
	document.getElementsByClassName('minutes')[0].innerHTML = minutes;
	document.getElementsByClassName('seconds')[0].innerHTML = seconds;
	document.getElementsByClassName('test')[0].innerHTML = test;
}

//turns single digit numbers to two digit numbers by placing a zero in front
function addZero (val){
	return (val <= 9) ? ("0" + val) : val;
}


//lights up what day of the week it is
function whatDay(){
	var date = new Date(),
		currentDay = date.getDay(),
		days = document.getElementsByClassName("day");

	//iterates through all divs with a class of "day"
	for (x in days){
		//list of classes in current div
		var classArr = days[x].classList;

		(classArr !== undefined) && ((x == currentDay) ? classArr.add("light-on") : classArr.remove("light-on"));
	}
}