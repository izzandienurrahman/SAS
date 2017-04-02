<?php
   	include("connect_db.php");	//Contains "function()" function
   	
	//Connect to MySQL database using function in the included file
   	$link=Connection();

	$npm=$_POST['npm'];	//get the value of npm, copy it to $npm
	$checkborrow=$_POST["checkborrow"];
	$checkreturn=$_POST["checkreturn"];
	echo "\ncheckborrow=".$checkborrow;
	echo "\ncheckreturn=".$checkreturn;
	//MySQL queries goes here
	$query ="SELECT `valid`,`in_use` FROM `sas_tb` WHERE `npm`=".$npm;
	$timestamp ="SELECT `time` FROM `sas_tb` WHERE `npm`=".$npm;
	
   	$result = mysql_query($query,$link);		//get resource data from database, copy it it $result

	
	//Show the query.
	echo "\nYour query : ".$query."\n";			//echo the query
	
	//Do this routine if $result contains resource data.
	if($result!==FALSE){
		
		$time_result= mysql_query($timestamp,$link);//get resource data from database, copy it it $time_result
	
		//Fetch the result's row, copy it to $row
		$row=mysql_fetch_assoc($time_result);		//transform resource data to associative array
		echo "Current time : ".$row['time'];		//echo the timestamp
		
		//Fetch the result's row by overwriting $row  		
		$row=mysql_fetch_array($result);
		
		if($row["valid"]==1){
			echo "\nAccess granted.\n";
			echo "check_before: ".$row["in_use"]."\n";
			$check_before=$row["in_use"];
				if($row["in_use"]==0&&$checkborrow==1){					
					$query ="UPDATE `sas_tb` SET `in_use` = 1 WHERE `npm`=".$npm;		//Overwrite $query with this query
					mysql_query($query,$link);											//update `in_use` column in database		
				}
				elseif($row["in_use"]==1&&$checkreturn==1){				
					$query ="UPDATE `sas_tb` SET `in_use` = 0 WHERE `npm`=".$npm;		//Overwrite $query with this query
					mysql_query($query,$link);											//update `in_use` column in database
				}
				else{
					echo "No more bike/parking slot, contact terminal waden.\n";
				}
			//Fetch newer database
			$query ="SELECT `valid`,`nama`,`in_use` FROM `sas_tb` WHERE `npm`=".$npm;	//Overwrite $query with this query
			$result = mysql_query($query,$link);										//get resource data from database, copy it it $result
			
			//Fetch the result's row by overwriting $row  		
			$row = mysql_fetch_array($result);
			$check_after=$row["in_use"];
			echo "check_after: ".$row["in_use"]."\n";
			
			echo "end of preamble\n";													//Sentinel String for detecting next important line(s)
			echo $row["valid"]."\n";
			echo $row["nama"]."\n";
			echo $check_before."\n";
			echo $check_after;
		}
		elseif($row["valid"]==0){
			echo "\nAccess denied, Invalid npm or student not exist.\n";
			echo "end of preamble\n";
			echo $row["valid"]."\n";
		}
		else{
			echo "\nUnknown..\n";
			echo "end of preamble\n";
			echo $row["valid"]."\n";
		}
		//Free the resource, although not necessary thanks to garbage collector					
		mysql_free_result($time_result);
		mysql_free_result($result);
		mysql_close($link);
	}
	
	//Do this routine if $result contains no resource data.
   	else{
		echo "\nInvalid SQL query\n";
		echo "end of preamble\n";
		echo 24;								//My custom error code for invalid SQL query
		mysql_close($link);
	}
	
   	header("Location: index.php");
?>
