void removeBike_db(String slotnum){
if (client.connect(host, 80)){
    data = "terminal=" + terminal;
    data2= "&slotnum=" + slotnum;
    data+=data2;
    Serial.println("\nData: "+data);
    Serial.println("slotnum="+slotnum);
    client.println("POST /wemos_php/update_remove.php HTTP/1.1"); 
    client.println("Host: 192.168.100.4"); // SERVER ADDRESS HERE TOO
    client.println("Content-Type: application/x-www-form-urlencoded"); 
    client.print("Content-Length: ");
    client.println(data.length()); 
    client.println(); 
    client.print(data); 

//    Serial.println("\n[Response:]");
//    while (client.connected())
//    {
//      if (client.available())
//      {       
//        String line = client.readStringUntil('\n'); //read string line per line
//        Serial.println(line);
//      }
//    }
  }
  else{
    removeBike_db(String(svPin));
  }
}
