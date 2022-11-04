
"use strict";

var nickG = null;
var passG = null;
var gameG = null;
var groupG = 31;
var boardG = [];
var rowsG;
var columnsG;

function loginClick() {
	// console.log(document.getElementById("user").value);
	// console.log(document.getElementById("pw").value);
	register(document.getElementById("user").value, document.getElementById("pw").value);
}

function logoutClick() {
	nickG = null;
	passG = null;
	document.getElementById("logoutbt").style.visibility = "hidden";
	document.getElementById("loginbt").style.visibility = "visible";
	document.getElementById("loginstatus").innerHTML = "STATUS: LOGGED OFF";
	document.getElementById("pw").value = "";
	document.getElementById("user").value = "";
	document.getElementById("loginInput").style.display = "inline";
}

function register(nick, pass) {
    var xhr = new XMLHttpRequest();
    xhr.open("POST", "http://twserver.alunos.dcc.fc.up.pt:8008/register", true);
    xhr.onreadystatechange = function() {
 	if (xhr.readyState === 4) {
	    var response = JSON.parse(xhr.responseText);
	    if (xhr.status === 200) {
	    	console.log("Login With:" + nick);
	    	document.getElementById("loginbt").style.visibility = "hidden";
	    	document.getElementById("logoutbt").style.visibility = "visible";
	    	document.getElementById("loginstatus").innerHTML = "STATUS: LOGIN USER: " + nick;
	    	document.getElementById("loginInput").style.display = "none";
	    	nickG = nick;
	    	passG = pass;
	    } else {
	    	document.getElementById("loginstatus").innerHTML = response.error;
	    }
	}
    }
    xhr.send(JSON.stringify({nick: nick, pass: pass}));
}

function leaveGame() {
	leave(nickG,passG,gameG);
	document.getElementById("message").innerHTML = "Disconnecting from game";
	enableConfigs();
}

function leave(nick, pass, game) {
    var xhr = new XMLHttpRequest();
    xhr.open("POST", "http://twserver.alunos.dcc.fc.up.pt:8008/leave", true);
    xhr.onreadystatechange = function() {
 	if (xhr.readyState === 4) {
	    var response = JSON.parse(xhr.responseText);
	    if (xhr.status === 200) {
	    disableOnClickBoard();
	    } else {
	    	document.getElementById("message").innerHTML =  response.error;
	    }
	}
    }
    xhr.send(JSON.stringify({nick: nick, pass: pass, game: game}));
}

function join(group, nick, pass, rows, columns) {
    var xhr = new XMLHttpRequest();
    xhr.open("POST", "http://twserver.alunos.dcc.fc.up.pt:8008/join", true);
    xhr.onreadystatechange = function() {
 	if (xhr.readyState === 4) {
	    var response = JSON.parse(xhr.responseText);
	    console.log(response);
	    if (xhr.status === 200) {
		gameG = response.game;
		console.log("new Game " + gameG);
		show_canvas_loading();
		update(gameG, nickG);
	    } else {
	    	document.getElementById("message").innerHTML =response.error;
	    }
	}
    }
    
    xhr.send(JSON.stringify({group: group, nick: nick, pass: pass, size :{ "rows": rows, "columns": columns}}));
}

function notify(nick, pass, game, column) {
    var xhr = new XMLHttpRequest();
    xhr.open("POST", "http://twserver.alunos.dcc.fc.up.pt:8008/notify", true);
    xhr.onreadystatechange = function() {
 	if (xhr.readyState === 4) {
	    var response = JSON.parse(xhr.responseText);
	    console.log(response);
	    if (xhr.status !== 200) {
	    	document.getElementById("message").innerHTML =response.error;
	    }
	}
    }
    xhr.send(JSON.stringify({nick: nick, pass: pass, game: game, column: column}));
}

var flag_update = 0;

function update(game, nick) {
    var source = new EventSource("http://twserver.alunos.dcc.fc.up.pt:8008/update?nick="+nick+"&game="+game);
    source.onmessage = function(event) {
    	if(flag_update === 0) {
    		hide_canvas_loading();
			show_canvas_startgame();
			setTimeout(function() { hide_canvas_startgame()	} , 1500);
    	}

	var response = JSON.parse(event.data);
	if (response.error) {
		document.getElementById("message").innerHTML =response.error;
	} 
	if (response.winner === null) {
		document.getElementById("message").innerHTML =  "You left the game";
	} 
	else if (response.winner) {
		if (response.winner === nickG) {
			enableConfigs();
		    disableOnClickBoard();
		    document.getElementById("message").innerHTML = "You Won!";
		    source.close();
		} else {
			enableConfigs();
		    disableOnClickBoard();
			document.getElementById("message").innerHTML = "you Lost";
		    source.close();
			}  
	    } 
	else if(response.turn === nickG) {
			disableConfigs();
			enableOnClickBoard();
			document.getElementById("message").innerHTML = "Your turn";
		} else {
			disableConfigs();
			disableOnClickBoard();
			document.getElementById("message").innerHTML = "Opponent turn";
		}
	if (response.column != null) {
		if(response.turn == nickG)
		receivePlay(response.column, 1);
		else receivePlay(response.column, 2);
	}
	flag_update = 1;
	}   
}

function updateBoard() {
	let cells = document.getElementsByClassName("playbtn");
	let k=0;
	for (var i=0;i<rowsG;i++){
		for (var j=0;j<columnsG;j++){
			if(boardG[i][j]===0) {
				cells[k].style.backgroundColor="white";
				}
			else if(boardG[i][j]===1) {
				cells[k].style.backgroundColor="red";
				}
			else {
				cells[k].style.backgroundColor="yellow";
			}
			k++;
				}
			}
	return;
}

function receivePlay(column, turn) {
	 for(var i=rowsG-1; i>-1;i--){
		 if(boardG[i][column] ===  0) {
			 boardG[i][column] = turn;
			 updateBoard()
			 return;
		 }
	 }
}


function makePlayMult(value) {
	notify(nickG, passG, gameG, value);
	console.log("User  NOTIFY row:"+ value);
}

function loadMultiplayer(rows,columns) {
	rowsG = rows;
	columnsG = columns;
	boardG= new Array(rows);
	for (var i=0;i<rows;i++){
		boardG[i]=new Array(columns);
		for (var j=0;j<columns;j++){
			boardG[i][j]=0;
		}
	}
	join(groupG,nickG,passG,parseInt(rows), parseInt(columns));
}

// ------------------------------
// ------------CANVAS------------
// ------------------------------
function show_canvas_loading(){

	//console.log("show canvas loading");

	(function(){
  		var base = document.getElementById('searching_game'),
    	gc = base.getContext('2d'),
    	pi = Math.PI,
    	xCenter = base.width/2,
    	yCenter = base.height/2,
    	radius = base.width/3,
    	startSize = radius/3,
    	num=5,
    	posX=[],posY=[],angle,size,i;

  		window.setInterval(function() {
    		num++;
   			gc.clearRect ( 0 , 0 , xCenter*2 , yCenter*2 );
   			for (i=0; i<9; i++){
      		gc.beginPath();
      		gc.fillStyle = 'rgba(0,0,0,'+.1*i+')';
      		if (posX.length==i){
        		angle = pi*i*.25;
        		posX[i] = xCenter + radius * Math.cos(angle);
        		posY[i] = yCenter + radius * Math.sin(angle);
      		}
      		gc.arc(
        		posX[(i+num)%8],
        		posY[(i+num)%8],
        		startSize/9*i,
        		0, pi*2, 1); 
      		gc.fill();
    		}
  		}, 75);
  	})();

	document.getElementById("searching_game").style.visibility = "visible";
}

function hide_canvas_loading(){
	document.getElementById("searching_game").style.visibility = "hidden";
}

function show_canvas_startgame(){
		document.getElementById("game_started").style.visibility = "visible";
		console.log("show canvas");
		var tela = document.getElementById('game_started');
		var gc = tela.getContext("2d");

		gc.fillStyle = 'rgb(239,60,66)';
		gc.font = 'bold 22px Helvetica';
		gc.fillText("GAME STARTED!!!", 100,100);
}

function hide_canvas_startgame(){
	document.getElementById("game_started").style.visibility = "hidden";
}