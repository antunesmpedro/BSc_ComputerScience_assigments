var game;
var mult =0;

function loadStats() {
	var x = document.getElementById("statsdiv");
    if (x.style.display === "none") {
        x.style.display = "block";
    } else {
        x.style.display = "none";
    }
}

function updateStats() {
	
}


function loadGame() {
	document.getElementById("start").addEventListener("click",startGame);
	document.getElementById("board").style.display= "none";
	document.getElementById('message').style.visibility= "hidden";
	enableConfigs(); 
}

function resetGame() {
	enableConfigs();
	// document.getElementById("board").style.visibility ="hidden";
	document.getElementById('message').innerHTML = "Game Reset!";
	disableOnClickBoard();
}

function startGame() {
	document.getElementById("base").innerHTML = "";
	disableConfigs();
	
	// get values from cfg
	var rows = document.getElementById("rows").value;
	var columns = document.getElementById("columns").value;
	var multiplayer = document.getElementById("singleOrMulti").value;
	var firstplayer = document.getElementById("firstplayer").value;
	var ailevel = document.getElementById("ailevel").value;
	
	// Get html ellemnts
	const baseElement = document.getElementById('base');
	const boardElement = document.getElementById('board');
	const messageElement = document.getElementById('message');
	
	if(multiplayer === "single" && nickG!== null) {
		// config Multigame
		loadMultiplayer(rows, columns);
		mult = 1;
		messageElement.innerHTML = "Online Game Started, Waiting for player";
	}
	else if(multiplayer === "single" && nickG==null) {
		messageElement.innerHTML = "Not Logged, Cannot Start Online Game";
		mult = 0;
	}
	else if(multiplayer === "singleai") {
	// config LOCAL game
	game = new Game(rows, columns, multiplayer, firstplayer, ailevel);
	messageElement.innerHTML = "Local AI Game Started";
	mult = 0;
	}
	else {
		game = new Game(rows, columns, multiplayer, firstplayer, ailevel);
		messageElement.innerHTML = "Local Multiplayer Game Started";
		mult = 0;
	}
	
	
	// css board settings
	// Enable & Create Board
	document.getElementById("board").style.display= "block";
	x = columns * 100 + "px";
	boardElement.style.width = x;
	messageElement.style.width = x;
	x =  rows* 100 + "px";
	boardElement.style.height = x;
	boardElement.style.visibility = "visible";
	boardElement.style.marginLeft = 1000 / columns + "px";
	messageElement.style.visibility = "visible";
	// css dynamic width board
	var x = columns * 100 + "px";
	baseElement.style.width = x;
	const board = [];

	for (var i = 0; i < rows; i++) {
		var row = [];
		for (var j = 0; j < columns; j++) {
			var cell = {};
			// Create a <div></div> and store it in the cell object
			cell.element = document.createElement('div');
			cell.element.className = "playbtn";
			cell.element.value = j;
			// Add it to the board
			baseElement.appendChild(cell.element);
			// Add to list of all
			row.push(cell);
		}
		// Add this row to the board
		board.push(row);
	}
	// Add onclick events
	enableOnClickBoard()
}

function enableOnClickBoard() {
	cells = document.getElementsByClassName("playbtn");
	 var i;
	    for (i = 0; i < cells.length; i += 1) {
	        (function (i) {
	            cells[i].onclick = function (e) {
	            	if(mult == 1) {
	            		makePlayMult(this.value);
	            	}
	            	else {
	                game.makePlay(this.value);
	            	}
	            };
	        })(i);
	    }
}

function disableOnClickBoard() {
	cells = document.getElementsByClassName("playbtn");
	 var i;
	    for (i = 0; i < cells.length; i += 1) {
	        (function (i) {
	            cells[i].onclick = "";
	        })(i);
	    }
}


function disableConfigs() {
	document.getElementById("start").disabled = true;
	document.getElementById("rows").disabled = true;
	document.getElementById("columns").disabled = true;
	document.getElementById("singleOrMulti").disabled = true;
	document.getElementById("firstplayer").disabled = true;
	document.getElementById("ailevel").disabled = true;
}

function enableConfigs() {
	document.getElementById("start").disabled = false;
	document.getElementById("rows").disabled = false;
	document.getElementById("columns").disabled = false;
	document.getElementById("singleOrMulti").disabled = false;
	document.getElementById("firstplayer").disabled = false;
	document.getElementById("ailevel").disabled = false;
}

class Game {
	constructor(rows, columns, multiplayer, firstplayer, ailevel) {
		this.rows = rows;
		this.columns = columns;
		this.multiplayer = multiplayer;
		this.firstplayer = firstplayer;
		this.ailevel = ailevel;
		this.matrix = this.createMatrix();
		if(this.firstplayer === "1")
			this.turn = 1;
		else this.turn = 2;
		this.updateMessage();
	}
	
	createMatrix() {
		let matrix = new Array(this.rows);
		for (var i=0;i<this.rows;i++){
			matrix[i]=new Array(this.columns);
			for (var j=0;j<this.columns;j++){
				matrix[i][j]=0;
			}
		}
		return matrix;
	}
	
	makePlay(columnPlay) {
		// console.log(this.turn);
		if(this.matrix[0][columnPlay] != 0) {
			document.getElementById("message").innerHTML = ("Player: " + this.turn + "  Message: Full Stack!");
			return;
		}
		 for(var i=this.rows-1; i>-1;i--){
				 if(this.matrix[i][columnPlay] ===  0) {
					 this.matrix[i][columnPlay] = this.turn;
					 console.log("User played row:"+ columnPlay);
					 if(this.turn === 1)
						 this.turn = 2;
					 else this.turn = 1;
					 this.updateBoard();
					 this.updateMessage();
					 break;
				 }
			 }
		 if(this.evaluator())
			 return;
		 if(this.multiplayer === "singleai")
			 this.aiPlay();
	}
	
	aiPlay() {
		let x = Math.floor(Math.random() * this.columns); 
		if(this.matrix[0][x] !== 0) {
			this.aiPlay();
			return;
		}
		else {
		 for(var i=this.rows-1; i>-1;i--){
				 if(this.matrix[i][x] ===  0) {
					 this.matrix[i][x] = this.turn;
					 if(this.turn === 1)
						 this.turn = 2;
					 else this.turn = 1;
					 console.log("AI played row:"+ x);
					 this.updateBoard();
					 this.updateMessage();
					 this.evaluator();
					 return;
				 }
			 }
		}
	}
	
	updateBoard() {
		let cells = document.getElementsByClassName("playbtn");
		let k=0;
		for (var i=0;i<this.rows;i++){
			for (var j=0;j<this.columns;j++){
				if(this.matrix[i][j]===0) {
					cells[k].style.backgroundColor="white";
					}
				else if(this.matrix[i][j]===1) {
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
	
	updateMessage() {
		document.getElementById("message").innerHTML = ("Player: " + this.turn);
	}
	
	evaluator() {
		if(this.win()) {
			if(this.turn === 1)
				this.turn =2;
			else this.turn = 1;
			document.getElementById("message").innerHTML = ("Player " + this.turn + " won game!");
			console.log("Player " + this.turn + " won game!");
			document.getElementById("start").disabled = false;
			document.getElementById("rows").disabled = false;
			document.getElementById("columns").disabled = false;
			document.getElementById("singleOrMulti").disabled = false;
			document.getElementById("firstplayer").disabled = false;
			document.getElementById("ailevel").disabled = false;
			disableOnClickBoard();
			this.updateStats("win");
			return true;
		}
		else if(this.isFull()) {
			disableOnClickBoard();
			resetGame();
			document.getElementById("board").style.visibility ="visible";
			document.getElementById("message").innerHTML = ("Game ended on a Draw!");
			this.updateStats("draw");
			return true;
		}
		return false;
	}
	
	win() {
		for (var i=0;i<this.rows;i++){
			for (var j=0;j<this.columns-3;j++){
				if(this.matrix[i][j] !== 0)
					if(this.matrix[i][j] === this.matrix[i][j+1] && this.matrix[i][j+2] === this.matrix[i][j+3]
					&& this.matrix[i][j] === this.matrix[i][j+2])
						return true;
			}
			}
		
		for (var j=0;j<this.columns;j++){
		for (var i=0;i<this.rows-3;i++){
			if(this.matrix[i][j] !== 0)
				if(this.matrix[i][j] === this.matrix[i+1][j] && this.matrix[i+2][j] === this.matrix[i+3][j]
				&& this.matrix[i][j] === this.matrix[i+2][j])
					return true;
		}
		}	
		for (var j=0;j<this.columns;j++){
			for (var i=0;i<this.rows-3;i++){
				if(this.matrix[i][j] !== 0)
					if(this.matrix[i][j] === this.matrix[i+1][j+1] && this.matrix[i+2][j+2] === this.matrix[i+3][j+3]
					&& this.matrix[i][j] === this.matrix[i+2][j+2])
						return true;
			}
		}
		
		for (var i=0;i<this.rows-3;i++){
			for (var j=this.columns-1;j>2;j--){
				if(this.matrix[i][j] !== 0)
					if(this.matrix[i][j] === this.matrix[i+1][j-1] && this.matrix[i+2][j-2] === this.matrix[i+3][j-3]
					&& this.matrix[i][j] === this.matrix[i+2][j-2])
						return true;
			}
			}
		
	}
	isFull() {
		for (var j=0;j<this.columns;j++){
		if(this.matrix[0][j]===0)
			return false;
		}
		return true;
		}
	updateStats() {
}
}





