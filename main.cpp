#include "crow_all.h"

using namespace std;
using namespace crow;



// function to send the file
void sendFile(response &res,string filename,string contentType){

	// read the file
	ifstream in("public/"+filename,ifstream::in);
	
	// if there is no error while reading the file 
	if(in){

		// convert it into the string o/p stream
		ostringstream contents;
		contents << in.rdbuf();
		in.close();
		// set the header of the response
		res.set_header("Content-Type",contentType);
		res.write(contents.str());

	}else{

		res.code = 404; // file not found on server
		res.write("Page Not Found");
	}
	res.end();
}

// send the html file
void sendHTML(response &res,string filename){

	sendFile(res,filename+".html","text/html");
}
// send the script file
void sendScript(response &res,string filename){

	sendFile(res,"scripts/"+filename,"text/javascript");
}

// send the style file
void sendStyle(response &res,string filename){

	sendFile(res,"styles/"+filename,"text/css");
}

// send the Image style
void sendImage(response &res,string filename){

	sendFile(res,"images/"+filename,"image/jpeg");
}


int main(int argc,char *argv[]){


	crow::SimpleApp app;

	CROW_ROUTE(app,"/")
		(
		 [](const request &req,response &res)
		 {  
			sendHTML(res,"index");
		 }
	);


	// route for about page 
	
	  CROW_ROUTE(app,"/about")(
	 
	 	[](const request &req,response &res){
	 
	 	// now read the about.html file
	 	ifstream in("public/about.html",ifstream::in);
	 	// if read is successfull
	 	if(in){
	 
	 	// convert to string stream
	 	ostringstream contents;
	 	contents << in.rdbuf();
	 	in.close();
	 
	 	res.set_header("Content-Type","text/html");
	 	res.code = 200;
	 
	 	// write the reposne on the browser
	 	res.write(contents.str());
	 
	 
	 	}
	 	else{
	 
	 	res.code=404;
	 	res.write("aaa Page Not found");
	 
	 	
	 
	 	}
	     res.end();
		}
	 
	  );
	 
	   
	 
	 
	 
	 
	 
	 
	 
	 





	// route for the images
	
	CROW_ROUTE(app,"/images/<string>")(

			[](const request &req,response &res,string filename){

			
				sendImage(res,filename);
			}
	);
	
	
	// route for the script
	 CROW_ROUTE(app,"/scripts/<string>") // string is a argument after that scripts
	(
		[](const request &req,response &res,string filename) // filename is the parameter received from the request
		{

			sendScript(res,filename); 
		}
	

	);

	// route for styles
	CROW_ROUTE(app,"/styles/<string>") // string is a argument after that scripts
	(
		[](const request &req,response &res,string filename) // filename is the parameter received from the request
		{

			sendStyle(res,filename); 
		}
	);

	char* port = getenv("PORT");
	uint16_t iPort = static_cast<uint16_t>(port!=NULL?stoi(port):18080);
	app.port(iPort).multithreaded().run();


}




