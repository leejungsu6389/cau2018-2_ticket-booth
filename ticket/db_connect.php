<?php

  define("DB_SERVER", "localhost");
  define("DB_USER", "root");
  define("DB_PSWD", "1234");
  define("DB_NAME", "ticketbooth");

  /* connect to mysql */
  $s = new mysqli(DB_SERVER, DB_USER, DB_PSWD, DB_NAME);

  if($s->connect_error){
    die("connection failed: ". $s->connect_error);
  }


  /* notify mysql utf-8, avoid korean character crashing */
  mysqli_query($s, "set session character_set_connection=utf8;");
  mysqli_query($s, "set session character_set_results=utf8;");
  mysqli_query($s, "set session character_set_client=utf8;");

  /*
  echo "test_connectedwell";
  */

?>