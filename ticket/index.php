<!DOCTYPE html>
<html lang="en">
<head>
	<!-- CHARACTER SET -->
	<meta charset="utf-8">

	<!-- VIEWPORT SIZING FOR ALL DEVICES -->
	<meta name="viewport" content="width=device-width, initial-scale=1.0">

	<!-- AUTHOR -->
	<meta name="author" content="Tyler West">
	
	<!-- DESCRIPTION -->
	<meta name="description" content="A simple digital clock built with html, css, and javascript.  It will give you the time of day in 12 hour format and the day of the week.">
	
	<!-- TITLE -->
	<title>Digital Clock</title>

	<!-- SHORTCUT ICON -->
	<!-- <link rel="shortcut icon" href="img/favicon.ico"> -->

	<!-- CUSTOM EXTERNAL STYLESHEET -->
	<link rel="stylesheet" href="css/main.css">	

</head>

<body>

	<main>
		<!-- DAY OF THE WEEK -->
		<div class="days">
		
			<div class="day">
				<p class="sunday">sunday</p>
			</div>

			<div class="day">
				<p class="monday">monday</p>
			</div>

			<div class="day">
				<p class="tuesday">tuesday</p>
			</div>

			<div class="day">
				<p class="wednesday">wednesday</p>
			</div>

			<div class="day">
				<p class="thursday">thursday</p>
			</div>

			<div class="day">
				<p class="friday">friday</p>
			</div>

			<div class="day">
				<p class="saturday">saturday</p>
			</div>

		</div>
		<!-- CLOCK -->
		<div class="clock">
			<!-- HOUR -->
			<div class="numbers">
				<p class="hours"></p>
				<p class="placeholder">88</p>
			</div>

			<div class="colon">
				<p>:</p>
			</div>

			<!-- MINUTE -->
			<div class="numbers">
				<p class="minutes"></p>
				<p class="placeholder">88</p>
			</div>

			<div class="colon">
				<p>:</p>
			</div>

			<!-- number -->
			<div class="numbers">
				<p class="seconds"></p>
				<p class="placeholder">88</p>
			</div>



		</div><!-- END CLOCK -->

		<!-- NUMBER -->
		<div>
		    <p class="test">1234</p>
		</div>

	</main>



	<!-- CUSTOM JAVASCRIPT STYLESHEET -->
	<script src="javascript/main.php"></script>

    <script>setTimeout("location.reload()",5000)</script>

</body>

</html>