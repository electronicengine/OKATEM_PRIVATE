<!DOCTYPE html>


<style>

    *, *:before, *:after {
      margin: 0;
      padding: 0;
      box-sizing: border-box;
    }

    html, body {
      height: 100%;
    }

    body {
      font: 14px/1 'Open Sans', sans-serif;
      color: #555;
      background: #eee;
    }

    h1 {
      padding: 15px 0;
      font-weight: 400;
      text-align: center;
    }

    p {
      margin: 0 0 20px;
      line-height: 1.5;
    }

    main {
      min-width: 1020px;
      min-height: 900px;
      max-width: 1800px;
      padding: 50px;
      margin: 0 auto;
      background: #fff;
    }

    section {
      display: none;
      padding: 20px 0 0;
      border-top: 1px solid #ddd;
    }

    .hidden_input {
      display: none;
    }

    label {
      display: inline-block;
      margin: 0 0 -1px;
      padding: 15px 25px;
      font-weight: 600;
      text-align: center;
      color: #bbb;
      border: 1px solid transparent;
    }

    #LogoutLabel {
        float: right;
    }

    #myProgress {
        position: relative;
        width: 100px;
        height: 30px;
        background-color: grey;
    }
    #myBar {
        position: absolute;
        width: 1%;
        height: 100%;
        background-color: red;
    }

    #terminalInfo {
        padding-left: 3em;
        padding-top: 5px;
    }

    label:hover {
      color: #888;
      cursor: pointer;
    }

    input:checked + label {
      color: #555;
      border: 1px solid #ddd;
      border-top: 2px solid orange;
      border-bottom: 1px solid #fff;
    }

    #tab1:checked ~ #content1,
    #tab2:checked ~ #content2,
    #tab3:checked ~ #content3,
    #tab4:checked ~ #content4 {
      display: block;
    }

    @media screen and (max-width: 650px) {
      label {
        font-size: 0;
      }

      label:before {
        margin: 0;
        font-size: 18px;
      }
    }
    @media screen and (max-width: 400px) {
      label {
        padding: 15px;
      }
    }

</style>


<script src="jquery-3.3.1.min.js"></script>

<script>

    function logoutFunc() {
     /* window.location = "http://logout@" + window.location.host + "/logout";*/
      // To invalidate a basic auth login:
  //
  //  1. Call this logout function.
  //  2. It makes a GET request to an URL with false Basic Auth credentials
  //  3. The URL returns a 401 Unauthorized
  //  4. Forward to some "you-are-logged-out"-page
  //  5. Done, the Basic Auth header is invalid now

    jQuery.ajax({
              type: "GET",
              url: "/index.fcgi",
              async: false,
              username: "logmeout",
              password: "123456",
              headers: { "Authorization": "Basic xxx" }
    })
    .done(function(){
        // If we don't get an error, we actually got an error as we expect an 401!
    })
    .fail(function(){
        // We expect to get an 401 Unauthorized error! In this case we are successfully
              // logged out and we redirect the user.
        window.location = "/logout.html";
      });

      return false;
    }


    $(document).ready(
     function() {
     setInterval(function() {

     readInfoFile("json");

     readLogFile("log.txt");
   }, 1000);  //Delay here = 5 seconds
    });


    function readInfoFile(file)
    {
        var rawFile = new XMLHttpRequest();
        rawFile.open("GET", file, false);
        rawFile.onreadystatechange = function ()
        {
            if(rawFile.readyState === 4)
            {
                if(rawFile.status === 200 || rawFile.status == 0)
                {
                    var allText = rawFile.responseText;

                    obj = JSON.parse(allText);

                    document.getElementById("terminal_status").innerHTML = obj.terminal_status;

                    document.getElementById("laser_diagonal").innerHTML = obj.laser_diagonal;
                    document.getElementById("laser_edge").innerHTML = obj.laser_diagonal;
                    document.getElementById("sfp_temp").innerHTML = obj.sfp_temp;
                    document.getElementById("sfp_vcc").innerHTML = obj.sfp_vcc;
                    document.getElementById("sfp_tx_bias").innerHTML = obj.sfp_tx_bias;
                    document.getElementById("sfp_tx_power").innerHTML = obj.sfp_tx_power;
                    document.getElementById("sfp_rx_power").innerHTML = obj.sfp_rx_power;

                    document.getElementById("terminal_temperature").innerHTML = obj.terminal_temperature;
                    document.getElementById("terminal_pressure").innerHTML = obj.terminal_pressure;
                    document.getElementById("terminal_altitude").innerHTML = obj.terminal_altitude;
                    document.getElementById("terminal_compass").innerHTML = obj.terminal_compass;
                    document.getElementById("terminal_gps_string").innerHTML = obj.terminal_gps_string;
                    document.getElementById("terminal_latitude").innerHTML = obj.terminal_latitude;
                    document.getElementById("terminal_ns_indicator").innerHTML = obj.terminal_ns_indicator;
                    document.getElementById("terminal_longnitude").innerHTML = obj.terminal_longnitude;
                    document.getElementById("terminal_we_indicator").innerHTML = obj.terminal_we_indicator;

                    document.getElementById("servo_motor1_degree").innerHTML = obj.servo_motor1_degree;
                    document.getElementById("servo_motor2_degree").innerHTML = obj.servo_motor2_degree;
                    document.getElementById("step_motor1_position").innerHTML = obj.step_motor1_position;
                    document.getElementById("step_motor2_position").innerHTML = obj.step_motor2_position;

                    document.getElementById("cpu_usage").innerHTML = obj.cpu_usage;
                    document.getElementById("memory_usage").innerHTML = obj.memory_usage;

                    document.getElementById("remote_terminal_status").innerHTML = obj.remote_terminal_status;
                    document.getElementById("remote_sfp_temp").innerHTML = obj.remote_sfp_temp;
                    document.getElementById("remote_sfp_vcc").innerHTML = obj.remote_sfp_vcc;
                    document.getElementById("remote_sfp_tx_bias").innerHTML = obj.remote_sfp_tx_bias;
                    document.getElementById("remote_sfp_tx_power").innerHTML = obj.remote_sfp_tx_power;
                    document.getElementById("remote_sfp_rx_power").innerHTML = obj.remote_sfp_rx_power;

                    document.getElementById("remote_terminal_temperature").innerHTML = obj.remote_terminal_temperature;
                    document.getElementById("remote_terminal_pressure").innerHTML = obj.remote_terminal_pressure;
                    document.getElementById("remote_terminal_altitude").innerHTML = obj.remote_terminal_altitude;
                    document.getElementById("remote_terminal_compass").innerHTML = obj.remote_terminal_compass;
                    document.getElementById("remote_terminal_gps_string").innerHTML = obj.remote_terminal_gps_string;
                    document.getElementById("remote_terminal_latitude").innerHTML = obj.remote_terminal_latitude;
                    document.getElementById("remote_terminal_ns_indicator").innerHTML = obj.remote_terminal_ns_indicator;
                    document.getElementById("remote_terminal_longnitude").innerHTML = obj.remote_terminal_longnitude;
                    document.getElementById("remote_terminal_we_indicator").innerHTML = obj.remote_terminal_we_indicator;

                    //




                    // alert(allText);s
                }
                else {
                  // alert("text file busy");
                }
            }
        }
        rawFile.send(null);
    }


    function readLogFile(file)
    {
        var rawFile = new XMLHttpRequest();
        rawFile.open("GET", file, false);
        rawFile.onreadystatechange = function ()
        {
            if(rawFile.readyState === 4)
            {
                if(rawFile.status === 200 || rawFile.status == 0)
                {
                    var allText = rawFile.responseText;
                    document.getElementById("textarea").innerHTML = allText;



                        $(document).ready(function(){
                            var $textarea = $('#textarea');
                            $textarea.scrollTop($textarea[0].scrollHeight);
                        });

                }
                else {
                  // alert("text file busy");
                }
            }
        }
        rawFile.send(null);
    }



</script>


<?php


		$user=$_GET['uname'];
		$pass=$_GET['psw'];

		if($user === "admin" && $pass == "1234") {

		}
		else {
	    echo "<script> alert('Wrong Password or Username');";
      echo "window.location.href = 'index.php'; </script>";
		}


?>


<html >
  <head>
    <meta charset="UTF-8">
    <!-- <meta http-equiv="refresh" content="5" > -->
    <title>FSO Web Interface</title>

  </head>

    <body >

      <p align="center"> <img src="./img/hyperion.png" style="width:400px; align:center;"> </p>
      <!-- <h1>FSO Web Application</h1> -->

      <main>

        <input id="tab1" type="radio" name="tabs" class="hidden_input" checked>
        <label for="tab1">Host FSO</label>

        <input id="tab2" type="radio" name="tabs" class="hidden_input">
        <label for="tab2">Remote FSO</label>

        <input id="tab3" type="radio" name="tabs" class="hidden_input">
        <label for="tab3">Log</label>

        <input id="tab4" type="button" name="tabs" class="hidden_input">
        <label for="tab4" id="LogoutLabel" onclick="logoutFunc()">Logout</label>




        <!-- <div class="section" id="content1"> -->
        <section id="content1">
            <!-- {% if connected %} -->

            <div class="card" z-default=1 z-hover=1 no-height=1 style="height:410px">
              <p style="float: left;"><img src="./img/laser.png" style="width:32px;height:32px;"></p><p id="terminalInfo">  &emsp; Terminal Information</p>
              <br>
              <br> Status: <span id="terminal_status"></span> <br>
              <br> Image Diagonal Rate: <span id="laser_diagonal"></span> <br>
              <br> Image Edge Rate: <span id="laser_edge"></span> <br>
              <br> SFP Temperature: <span id="sfp_temp"></span> deg;F<br>
              <br> SFP Voltage: <span id="sfp_vcc"></span> V<br>
              <br> SFP Tx Bias: <span id="sfp_tx_bias"></span> mA<br>
              <br> SFP Tx Power: <span id="sfp_tx_power"></span> dBM<br>
              <br> SFP Rx Power: <span id="sfp_rx_power"></span> dBM<br>
              <br> Servo Motor1 Degree: <span id="servo_motor1_degree"></span> d<br>
              <br> Servo Motor2 Degree: <span id="servo_motor2_degree"></span> d<br>
              <br> Step Motor1 Position: <span id="step_motor1_position"></span> d<br>
              <br> Step Motor2 Position: <span id="step_motor2_position"></span> d<br>
            </div>

            <div class="card" z-default=1 z-hover=1 no-height=1 style="height:190px">
              <p style="float: left;"><img src="./img/mcu.png" style="width:32px;height:32px;"></p> <p>  &emsp; Sensor Information </p>
              <br>
              <br> Temperature: <span id="terminal_temperature"></span> °C <br>
              <br> Pressure: <span id="terminal_pressure"></span> mhba<br>
              <br> Altitude: <span id="terminal_altitude"></span> m<br>
              <br> Compass Degree: <span id="terminal_compass"></span> deg<br>
            </div>

            <div class="card" z-default=1 z-hover=1 no-height=1 style="height:220px">
              <p style="float: left;"><img src="./img/gps.png" style="width:32px;height:32px;"></p><p <tid="gpsinfo">  &emsp; Gps Information</p>
              <br>
              <br> NMEA Output: <span id="terminal_gps_string"></span> <br>
              <br> Latitude: <span id="terminal_latitude"></span> °<br>
              <br> NS Indicator: <span id="terminal_ns_indicator"></span> <br>
              <br> Longnitude: <span id="terminal_longnitude"></span> °<br>
              <br> WE Indicator: <span id="terminal_we_indicator"></span> <br>

            </div>

            <div class="card" z-default=1 z-hover=1 no-height=1 id="mydiv">

              <p style="float: left;"><img src="./img/router.png" style="width:32px;height:32px;"></p><p id="terminalInfo"> &emsp; RouterBoard Information</p>
              <br>
              <br> Cpu Usage: % <span id="cpu_usage"></span>  <br>
              <br> Memory Usage: % <span id="memory_usage"></span><br>
            </div>
            <!-- {% endif %} -->

          <script type="text/javascript" src="./script/card-depth.js"></script>
          <script type="text/javascript" src="./script/page_updater.js"></script>

        </section>
      <!-- </div> -->

        <section id="content2">
           <!-- {% include "connection.html" %} -->
           <div class="card" z-default=1 z-hover=1 no-height=1 style="height:260px">
             <p style="float: left;"><img src="./img/laser.png" style="width:32px;height:32px;"></p><p id="terminalInfo">  &emsp; Terminal Information</p>
             <br>
             <br> Status: <span id="remote_terminal_status"></span> <br>
             <br> SFP Temperature: <span id="remote_sfp_temp"></span> deg;F<br>
             <br> SFP Voltage: <span id="remote_sfp_vcc"></span> V<br>
             <br> SFP Tx Bias: <span id="remote_sfp_tx_bias"></span> mA<br>
             <br> SFP Tx Power: <span id="remote_sfp_tx_power"></span> dBM<br>
             <br> SFP Rx Power: <span id="remote_sfp_rx_power"></span> dBM<br>
           </div>

           <div class="card" z-default=1 z-hover=1 no-height=1 style="height:190px">
             <p style="float: left;"><img src="./img/mcu.png" style="width:32px;height:32px;"></p> <p>  &emsp; Sensor Information </p>
             <br>
             <br> Temperature: <span id="remote_terminal_temperature"></span> °C <br>
             <br> Pressure: <span id="remote_terminal_pressure"></span> mhba<br>
             <br> Altitude: <span id="remote_terminal_altitude"></span> m<br>
             <br> Compass Degree: <span id="remote_terminal_compass"></span> deg<br>
           </div>

           <div class="card" z-default=1 z-hover=1 no-height=1 style="height:220px">
             <p style="float: left;"><img src="./img/gps.png" style="width:32px;height:32px;"></p><p <tid="gpsinfo">  &emsp; Gps Information</p>
             <br>
             <br> NMEA Output: <span id="remote_terminal_gps_string"></span> <br>
             <br> Latitude: <span id="remote_terminal_latitude"></span> °<br>
             <br> NS Indicator: <span id="remote_terminal_ns_indicator"></span> <br>
             <br> Longnitude: <span id="remote_terminal_longnitude"></span> °<br>
             <br> WE Indicator: <span id="remote_terminal_we_indicator"></span> <br>

           </div>

           <script type="text/javascript" src="./script/card-depth.js"></script>
           <script type="text/javascript" src="./script/page_updater.js"></script>

        </section>

        <section id="content3">
          <textarea id="textarea" cols="63" rows="27" readonly="readonly" style="width:98%; height:800px; font-family:'Courier New', Courier, mono; font-size:13px;background:#475A5F;color:#FFFFFF; white-space: pre-line; "  wrap="off">
            <!-- {{log}} -->
            <script>

            </script>
          </textarea>
        </section>


      </main>

    </body>

</html>
