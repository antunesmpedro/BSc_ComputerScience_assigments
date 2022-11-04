var express = require('express');
var body_parser = require('body_parser');
var crypto = require('crypto');
var port = process.env.port || 8031;
var app = express();

app.use(function(request, response, next)){
	response.header("Access.Control-Allow-Origin", "*");
	response.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
	next();
}, body_parser.urlenconded({extended: true}), body_parser.json());

//ficheiros estaticos css
app.use(express.static('/'));

//////////////
//          //
// register //
//          //
//////////////

app.post("/register", function(request, response){
	var user = request.body.nick;
	var pass = request.body.pass;

	if(user !== null && user !== "" && pass !== null && pass !== ""){
		if(checkLogin(user,pass) === true)
			responde.end(JSON.stringify({}));
		else
			response.end(JSON.stringify({error: "User registered with a different password"}));
	}
	else
		response.end(JSON.stringify({error: "Parametros nick/pass vazios"}));
});

app.listen(port, 'twserver.alunos.dcc.fc.up.pt');


////////////////
//            //
// auxiliares //
//            //
////////////////

function checkLogin(nick, pass){
	pass = crypto
				.createHash('md5')
				.update(pass)
				.digest('hex');

	try{
		var storage_file = fs.readFileSync("Server/Data/users.json");
		var data = JSON.parse(storage_file.toString())["users"];
	}
	catch(err){
		console.log("Error reading from file 'users.json'.");
		console.log(err);
		return false;
	}

	var found = false;
	var i;
	for(i=0; i<data.length; i++){
		if(data[i]["nick"] === nick){
			found = true;
			break;
		}
	}
	if(found === false){
		data.push({nick: nick, pass: pass});
		storage_file = {users: data};
		try{
			fs.writeFileSync(__dirname+"/users.json", JSON.stringify(storage_file));
		}
		catch(err){
			console.log("Error writing to file 'users.json'.");
			console.log(err);
			return false;
		}
	}
	else{
		if(storage_file[i]["pass"] === pass){
			return true;
		}
		else{
			console.log("Wrong Password of user "+nick+".");
			return false;
		}
	}
}