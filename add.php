<?php
   	include("connect_db.php");
   	
   	$link=Connection();

	$npm=$_POST['npm'];
	
	$query = "SELECT `valid` FROM `sas_tb` WHERE `npm`=".$npm;
	
   	$result = mysql_query($query,$link);
	//Show the query.
	echo "\nYour query : ".$query;
	
	if($result!==FALSE){
		$row = mysql_fetch_array($result);
		if($row["valid"]==1){
			echo "\nAccess granted, you may now borrow the bike.\n";
			echo "end of preamble\n";
			echo $row["valid"];
		}
		elseif($row["valid"]==0){
			echo "\nInvalid npm, student not exist.\n";
			echo "end of preamble\n";
			echo $row["valid"];
		}
		else{
			echo "\nUnknown..\n";
			echo "end of preamble\n";
			echo $row["valid"];
		}
		mysql_close($link);
	}
   	else{
		echo "\nInvalid SQL query\n";
		echo "end of preamble\n";
		echo 24;
		mysql_close($link);
	}
	
   	header("Location: index.php");
?>
