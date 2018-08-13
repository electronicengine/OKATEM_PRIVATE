
function pageUpdate() {
	var xhttp = new XMLHttpRequest();
	xhttp.onreadystatechange = function() {
		if (this.readyState == 4 && this.status == 200) {
			var xmldoc = xhttp.responseXML;

			if (xmldoc.getElementsByTagName('connected').item(0).textContent.toString() == "False")
				return

			document.getElementById("laser-posx").innerHTML = xmldoc.getElementsByTagName('laser_x').item(0).textContent.toString();
			document.getElementById("laser-posy").innerHTML = xmldoc.getElementsByTagName('laser_y').item(0).textContent.toString();
			document.getElementById("upper_terminal_temperature").innerHTML = xmldoc.getElementsByTagName('upper_terminal_temp').item(0).textContent.toString();
			document.getElementById("reg_temp").innerHTML = xmldoc.getElementsByTagName('regulator_temp').item(0).textContent.toString();
			document.getElementById("motor_driver_temp").innerHTML = xmldoc.getElementsByTagName('motor_driver_temp').item(0).textContent.toString();
			document.getElementById("baro_temperature").innerHTML = xmldoc.getElementsByTagName('barometer_temp').item(0).textContent.toString();
			document.getElementById("upper-heading").innerHTML = xmldoc.getElementsByTagName('upper_heading').item(0).textContent.toString();
			document.getElementById("lower-heading").innerHTML = xmldoc.getElementsByTagName('lower_heading').item(0).textContent.toString();
			document.getElementById("pressure").innerHTML = xmldoc.getElementsByTagName('pressure').item(0).textContent.toString();
			document.getElementById("altitude").innerHTML = xmldoc.getElementsByTagName('altitude').item(0).textContent.toString();
			document.getElementById("cpu").innerHTML = xmldoc.getElementsByTagName('cpu').item(0).textContent.toString();
			document.getElementById("memory").innerHTML = xmldoc.getElementsByTagName('memory').item(0).textContent.toString();
			document.getElementById("textarea").innerHTML = xmldoc.getElementsByTagName('log').item(0).textContent.toString();
			document.getElementById("sfp_temp").innerHTML = xmldoc.getElementsByTagName('sfp_temp').item(0).textContent.toString();
			document.getElementById("sfp_vcc").innerHTML = xmldoc.getElementsByTagName('sfp_vcc').item(0).textContent.toString();
			document.getElementById("sfp_tx_bias").innerHTML = xmldoc.getElementsByTagName('sfp_tx_bias').item(0).textContent.toString();
			document.getElementById("sfp_tx_power").innerHTML = xmldoc.getElementsByTagName('sfp_tx_power').item(0).textContent.toString();
			document.getElementById("sfp_rx_power").innerHTML = xmldoc.getElementsByTagName('sfp_rx_power').item(0).textContent.toString();

			var first_ssid = document.getElementById("remote_ssid").getAttribute("first_value");			
			var terminal_list = document.getElementById("terminal_list").getElementsByClassName("list-group-item");
			var terminal_size = xmldoc.getElementsByTagName("term_ssid").length;
			for (var i = 0; i < terminal_size; i++) {
				var terminal_ssid = xmldoc.getElementsByTagName("term_ssid").item(i).textContent.toString();
				var terminal_mac = xmldoc.getElementsByTagName("term_mac").item(i).textContent.toString();
				var terminal_onclick = " onclick=\"terminalClick(\'" + terminal_ssid + "\'"  + ' , \'' + terminal_mac + "\')\"";
				var selected = (terminal_ssid == first_ssid) ? ' active' : ""; 
				var term_list_item = "<a href=\"#\" class='list-group-item" + selected + "'" + terminal_onclick +">" + terminal_ssid + "&emsp;" + terminal_mac + "</a>";

				
				if (terminal_list.size == 0 || terminal_list.item(i) == null || terminal_list.item(i).textContent.toString() == term_list_item)
					$("#terminal_list").append(term_list_item);
			}

		}
	};
	xhttp.open("GET", "index_info.fcgi", true);
	xhttp.send();
}

function terminalClick(ssid, mac) {
	document.getElementById("remote_ssid").value = ssid;
	document.getElementById("remote_mac").value = mac;
	document.getElementById("remote_password").focus();
}

pageUpdate();
var timer = setInterval(pageUpdate, 1000);
