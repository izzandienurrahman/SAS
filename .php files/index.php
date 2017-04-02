<?php

	include("connect_db.php"); 	
	
	$link=Connection();
	$query ="SELECT * FROM `sas_tb`";
	$result=mysql_query($query,$link);
?>

<html>
   <head>
      <title>S.A.S Database</title>
   </head>
<body>
   <h1>S.A.S Student Database</h1>

   <table border="1" cellspacing="1" cellpadding="3">
		<tr>
			<td>&nbsp;NPM&nbsp;</td>
			<td>&nbsp;Nama&nbsp;</td>
			<td>&nbsp;Valid&nbsp;</td>
			<td>&nbsp;In_use&nbsp;</td>
			<td>&nbsp;Last_usage&nbsp;</td>
		</tr>

      <?php 
		  if($result!==FALSE){
		     while($row = mysql_fetch_array($result)) {
		        printf("<tr><td> &nbsp;%s&nbsp; </td><td> &nbsp;%s&nbsp; </td><td> &nbsp;%s&nbsp; </td><td> &nbsp;%s&nbsp; </td><td> &nbsp;%s&nbsp; </td></tr>", 
		           $row["npm"], $row["nama"], $row["valid"], $row["in_use"], $row["time"]);
		     }
		     mysql_free_result($result);
		     mysql_close();
		  }
      ?>

   </table>
</body>
</html>
