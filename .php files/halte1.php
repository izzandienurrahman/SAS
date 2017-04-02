<?php

	include("connect_db.php"); 	
	
	$link=Connection();
	$query ="SELECT * FROM `halte1`";
	$result=mysql_query($query,$link);
?>

<html>
   <head>
      <title>Halte Database</title>
   </head>
<body>
   <h1>Halte 1</h1>

   <table border="1" cellspacing="1" cellpadding="3">
		<tr>
			<td>&nbsp;Slot Number&nbsp;</td>
			<td>&nbsp;Status&nbsp;</td>
		</tr>

      <?php 
		  if($result!==FALSE){
		     while($row = mysql_fetch_array($result)) {
		        printf("<tr><td> &nbsp;%s&nbsp; </td><td> &nbsp;%s&nbsp; </td></tr>", 
		           $row["slotnum"], $row["status"]);
		     }
		     mysql_free_result($result);
		     mysql_close();
		  }
      ?>

   </table>
</body>
</html>
