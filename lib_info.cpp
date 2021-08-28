/* 
 * COSC302 Project1
 * Carter Earheart-Brown
 * Stephanie Hill
 * Purpose: Import music information from file and organize it by 
 *			artist and album.
 */
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<algorithm>
#include<map>

using namespace std;

//Borrowed from assignment instructions
struct Song {
    string title;
    int time;  // could also be a string
    int track;
};

struct Album {
    map <int, Song > songs;
    string name;
    int time;
    int nsongs;  // optional variable but makes it easier
};

struct Artist {
    map <string, Album > albums;
    string name;
    int time;
    int nsongs;
};

/*
 * Takes in the imported time as a string,
 * seperates it, converts it to an integer
 * and exports the total time in seconds. 
 */
int timeConvertMtoS(string time){
	int totsec, minutes, seconds;
	string min, sec;

	min=time.substr(0, time.find(":"));
	sec=time.substr(time.find(":") + 1);
	
	minutes=stoi(min);
	seconds=stoi(sec);
	
	return totsec = (minutes * 60) + seconds;
}

/*
 * Reads in file and converts all underscores to spaces 
 * Source: https://stackoverflow.com/questions/7868936/read-file-line-by-line-using-ifstream-in-c
 * https://stackoverflow.com/questions/2896600/how-to-replace-all-occurrences-of-a-character-in-string
*/
void readFile(string file){

	fstream infile(file);
	string line, title, time, artist, album, genre;
	int track; 
	
	while (getline(infile, line)){
		istringstream iss(line); 
		//replace(line.begin(), line.end(), '_', ' '); //this line will remove underscores (I'm not sure where to place it)
		iss >> title >> time >> artist >> album >> genre >> track; //reads in values and assigns to variables
				
		//cout<< title << " " << timeConvertMtoS(time) << endl; //testing
	
	}
	infile.close();
}

/* 
 * Takes in a time integer as seconds,
 * calculates the minutes and remaining seconds,
 * and exports it in the form MM:SS
 */
string timeConvertStoM(int)
{
	int seconds, minutes, rem;
	string time;
	minutes = seconds / 60;
	return minutes + ": " +rem;
}

int main(int argc, char *argv[]){
	string song, time, artist, album, genre;
	int track;
	readFile(argv[1]);

	
	return 0;
}


