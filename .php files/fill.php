<?php
   	include("connect_db.php");	//Contains "function()" function
   	
	//Connect to MySQL database using function in the included file
   	$link=Connection();

	$terminal=$_POST['terminal'];
	echo $terminal;
	//MySQL queries goes here
	$query ="SELECT `slotnum`,`status` FROM ".$terminal;
	
   	$result = mysql_query($query,$link);		//get resource data from database, copy it it $result

	//Show the query.
	echo "\nYour query : ".$query."\n";			//echo the query
	
	//Do this routine if $result contains resource data.
	if($result!==FALSE){
		while($row = mysql_fetch_array($result)) {
		    echo "breakpoint"."\n";
			echo $row["slotnum"]."\n";
			echo $row["status"]."\n";
		}	
	}
	
	mysql_free_result($result);
	mysql_close();
   	header("Location: index.php");
?>
