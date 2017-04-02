<?php
   	include("connect_db.php");	//Contains "function()" function
   	
	//Connect to MySQL database using function in the included file
   	$link=Connection();
	$terminal=$_POST['terminal'];
	$slotnum=$_POST['slotnum'];
	
	echo "\nterminal= ".$terminal."\n";
	echo "slotnum= ".$slotnum."\n";
	//MySQL queries goes here
	$query ="UPDATE ".$terminal." SET `status` = 0 WHERE slotnum = ".$slotnum;
	
   	$result = mysql_query($query,$link);		//get resource data from database, copy it it $result

	//Show the query.
	echo "\nYour query : ".$query."\n";			//echo the query
	
	//Do this routine if $result contains resource data.
	if($result!==FALSE){
		echo "bike slot has been removed";
		}	
	mysql_close();
   	header("Location: index.php");
?>
