function swOnLoad() {
	if (document.getElementById('progresspage') != null) {
		resizeWindow();
		if (document.getElementById('progresspagedone') == null) {
			makeRequest();
		}
	}
}

function swOnClick() {
	if (document.getElementById('continuesession') != null) {
		resizeWindow();
		if (document.getElementById('progresspagedone') == null) {
			makeRequest();
		}
	}
}

function writeToDocument (stringToWrite) {
	if (stringToWrite != '') {
		document.write(stringToWrite);
	}
}

function computeLastQuotaURL (url, urlprefix) {
	if (url.indexOf(urlprefix) >= 0) {
		var pos = url.indexOf("url=") + 4;
		url = url.substring(pos);
		url = decodeURIComponent(url);
	}
	break_line(url);
}

function encodeBase64 (inputStr) {
	var charsForEncoding = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=';
	var encodedString = '';
	var byte1, byte2, byte3;
	var encByte1, encByte2, encByte3, encByte4;
	var i = 0;
	
	do {
		byte1 = inputStr.charCodeAt(i);
		++i;
		byte2 = inputStr.charCodeAt(i);
		++i;
		byte3 = inputStr.charCodeAt(i);
		++i;
		
		encByte1 = byte1 >> 2;
		encByte2 = ((byte1 & 3) << 4) | (byte2 >> 4);
		encByte3 = ((byte2 & 15) << 2) | (byte3 >> 6);
		encByte4 = byte3 & 63;
		
		if (isNaN(byte3)) {
			encByte4 = 64;
			if (isNaN(byte2)) {
				encByte3 = 64;
			}
		}
		encodedString += charsForEncoding.charAt(encByte1) + charsForEncoding.charAt(encByte2) + charsForEncoding.charAt(encByte3) + charsForEncoding.charAt(encByte4);
	} while (i < inputStr.length);
	return encodedString;
}

var pluginRequest;
function activateSession(url,user,oldurl) {
	var userNameAO = document.getElementById('username');
	var pwAO = document.getElementById('password');
	var slAO = document.getElementById('sessionlength');
	var activateButton = document.getElementById('activatebutton');
	var hasLoginAndPW = false;
	activateButton.disabled = true;
	if ( (userNameAO != null) && (pwAO != null) && (slAO != null) ) {
		if ( (userNameAO.value == "") || (pwAO.value == "") || (slAO.value == "")) {
			alert ("Please insert your login, password and session length!");
			activateButton.disabled = false;
			return;
		}
		hasLoginAndPW = true;
	}
	if (typeof XMLHttpRequest != 'undefined') {
		pluginRequest = new XMLHttpRequest();
	}
	if (!pluginRequest) {
		try {
			pluginRequest = new ActiveXObject("Msxml2.XMLHTTP");
		} catch(e) {
			try {
				pluginRequest = new ActiveXObject("Microsoft.XMLHTTP");
			} catch(e) {
				pluginRequest = null;
			}
		}
	}
	
	//encode data and set header 'Quota-Data'
	var quotaDataStr = "";
	if (user != "" )
		quotaDataStr = encodeBase64(user);
	if (hasLoginAndPW) {
		quotaDataStr = quotaDataStr + "+1AB2+" + encodeBase64(userNameAO.value) + "+2CD3+" + encodeBase64(pwAO.value) + "+3EF4+" + encodeBase64(slAO.value);
	}
	if (quotaDataStr != "")
		quotaDataStr = encodeBase64( quotaDataStr );
	
	if (pluginRequest) {
		pluginRequest.open("POST", url, true);
		
		pluginRequest.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
		pluginRequest.setRequestHeader("Content-length", 0);
		pluginRequest.setRequestHeader("Quota-Data", quotaDataStr);
		pluginRequest.setRequestHeader("Quota-URL", oldurl);
		pluginRequest.setRequestHeader("Connection", "close");
		pluginRequest.onreadystatechange = function () {
			if(pluginRequest.readyState == 4 && (pluginRequest.status == "undefined" || pluginRequest.status < 400 || pluginRequest.status == 403)) {
				location.reload(true);
			} else {
				setTimeout(abortPluginRequest, 4000);
			}
    		};
		pluginRequest.send('');
	}
	activateButton.disabled = false;
}


function abortPluginRequest (url, withNewRequest) {
	if (! pluginRequest) {
		alert ("No plugin request");
		return;
	}
        if (pluginRequest.readyState != 4) {
		pluginRequest.abort();
	}
}

function break_line(lineToBreak) {
	if (lineToBreak != '') {
		var stringWords = lineToBreak.split(' ');
		for (var i = 0; i < stringWords.length; i++) {
			if (stringWords[i].length > 20) {
				stringWords[i] = stringWords[i].split('').join('<wbr />');
			}
		}
		lineToBreak = stringWords.join(' ');
		document.write(lineToBreak);
	}
}

function resizeWindow() {
	var x,y;
	if (self.innerHeight) { // all except Explorer
		x = self.innerWidth;
		y = self.innerHeight;
	} else if (document.documentElement && document.documentElement.clientHeight) {
		// Explorer 6 Strict Mode
		x = document.documentElement.clientWidth;
		y = document.documentElement.clientHeight;
	} else if (document.body) {
		// other Explorers
		x = document.body.clientWidth;
		y = document.body.clientHeight;
	}
	if (x < 700 || y < 500) {
		window.resizeTo (700,500);
	}
}

var httpRequest;
var firstRun = 1;

function makeRequest() {
	if (typeof XMLHttpRequest != 'undefined') {
		window.httpRequest = new XMLHttpRequest();
	}
	if (!window.httpRequest) {
		try {
			window.httpRequest  = new ActiveXObject("Msxml2.XMLHTTP");
		} catch(e) {
			try {
				window.httpRequest  = new ActiveXObject("Microsoft.XMLHTTP");
			} catch(e) {
				window.httpRequest  = null;
			}
		}
	}
	if (window.httpRequest) {
		var old = document.location + "";
		if (old.indexOf ("?")) {
			old = old.substr (0, old.indexOf ("?"));
		}
		window.httpRequest.open("GET", old + "?id=" + document.getElementById("progresspageid").content + "&a=1&" + (new Date()).getTime(), true);
		window.httpRequest.onreadystatechange = getResponse; // Callback Function
		window.httpRequest.send('');
	}
}

var progressBarCount = 20;
var progressBarImageWidth = 15;
var progressBarImageHeight = 20;
var progressBarImageBlue = new Image();
var progressBarImageGrey = new Image();

function getResponse()
{
	if (window.httpRequest.readyState == 4 && window.httpRequest.status == 200) {
		var res = window.httpRequest.responseText.split(";");
		if (res[3] == 1 || res[3] == undefined) { window.location.reload();}
		if( res[4] == 0) {
			document.getElementById ("progress").firstChild.nodeValue = "Downloaded " + res[0] + " of " + res[1];
		} else {
			document.getElementById ("progress").firstChild.nodeValue = "Scanning in progress (" + res[4] + "s)";
		}

		for (i=0; i<progressBarCount; i++) {
			var img = document.getElementById (("i" + i));
			if (img != null) {
				if ((res[4] == 0 && res[2] >= (i * 100 / progressBarCount))
					|| (res[4] > 0 && i == Math.round(res[4]/3) % progressBarCount) )
					img.src = window.progressBarImageBlue.src;
				else
					img.src = window.progressBarImageGrey.src;
				img.width = window.progressBarImageWidth;
				img.height = window.progressBarImageHeight;
			}
		}
		var timeElem = document.getElementById ("time");
		if (timeElem) {
			var now = new Date();
			timeElem.firstChild.nodeValue = now;
		}
		if (window.firstRun == 1 ) { window.setInterval("makeRequest()", 3000); window.firstRun = 0;}
	}
}

function printProgressBar(imgCount,imgDone,img,width,height)
{
	window.progressBarCount = imgCount;
	window.progressBarImageWidth = width;
	window.progressBarImageHeight = height;
	window.progressBarImageBlue.src = imgDone;
	window.progressBarImageGrey.src = img;
	
	for (i=0; i<imgCount; i++) {
		document.write ('<img id ="i' + i + '" src="' + img + '" height="' + height + '" width="' + width + '">\n');
	}		
}
