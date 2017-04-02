<?php

	function Connection(){
		$server="localhost";
		$user="root";
		$pass="";
		$db="sas";
	   	
		$connection = mysql_connect($server, $user, $pass);

		if (!$connection) {
	    	die('MySQL ERROR: ' . mysql_error());
		}
		else{
			echo "Database connected...";
		}
		
		mysql_select_db($db) or die( 'MySQL ERROR: '. mysql_error() );

		return $connection;
	}
?>
