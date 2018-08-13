
function saveSettings() {
	var method = "post";
	var path = "/connection.fcgi";
    var form = document.createElement("form");
    form.setAttribute("method", method);
    form.setAttribute("action", path);
    form.setAttribute("target", "emptyframe");
    form.setAttribute("style", "display: none");

    var field_ssid = document.createElement("input");
	field_ssid.setAttribute("name", "local_ssid");
	field_ssid.setAttribute("value", document.getElementById("local_ssid").value);
	form.appendChild(field_ssid);

	var field_rssid = document.createElement("input");
	field_rssid.setAttribute("name", "remote_ssid");
	field_rssid.setAttribute("value", document.getElementById("remote_ssid").value);
	form.appendChild(field_rssid);

	var field_rmac = document.createElement("input");
	field_rmac.setAttribute("name", "remote_mac");
	field_rmac.setAttribute("value", document.getElementById("remote_mac").value);
	form.appendChild(field_rmac);

	var field_rpasswd = document.createElement("input");
	field_rpasswd.setAttribute("name", "remote_password");
	field_rpasswd.setAttribute("value", document.getElementById("remote_password").value);
	form.appendChild(field_rpasswd);

	var field_connection = document.createElement("input");
	field_connection.setAttribute("name", "connection_establish");

	var connection_buttons = document.getElementsByName('connection_establish');
	if (connection_buttons[0].checked)
		field_connection.setAttribute("value", "True");
	else
		field_connection.setAttribute("value", "False");
	
	form.appendChild(field_connection);	

	var laser_connection = document.createElement("input");
	laser_connection.setAttribute("name", "laser_diode");
	var laser_buttons = document.getElementsByName('laser_diode');
	if (laser_buttons[0].checked)
		laser_connection.setAttribute("value", "Enable");
	else if (laser_buttons[1].checked)
		laser_connection.setAttribute("value", "Disable");
	else 
		laser_connection.setAttribute("value", "Auto");

	form.appendChild(laser_connection);	

    document.body.appendChild(form);
    form.submit();
}