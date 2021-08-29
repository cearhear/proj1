/* 
 * COSC302 Project1
 * Carter Earheart-Brown
 * Stephanie Hill
 * Purpose: Import music information from file and organize it by 
 *			artist and album.
 */
#include<iostream>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<string>
#include<algorithm>
#include<map>
#include<set>

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

void readFile(string file);
void fixUnderscores(string &s);
int timeConvertMtoS(string time);
string timeConvertStoM(int time);

int main(int argc, char *argv[]){
	string song, time, artist, album, genre;
	int track;
	readFile(argv[1]);

	
	return 0;
}


/*
 * Reads in file and converts all underscores to spaces 
 * Source: https://stackoverflow.com/questions/7868936/read-file-line-by-line-using-ifstream-in-c
 * https://stackoverflow.com/questions/2896600/how-to-replace-all-occurrences-of-a-character-in-string
*/
void readFile(string file){

	ifstream infile(file);
	string line, songName, time, artistName, albumName, genre;
	int track; 
	istringstream iss(line); 
	map<string, Artist> musicLibrary;
	
	while (getline(infile, line)){
		iss.clear();
		iss >> songName >> time >> artistName >> albumName >> genre >> track; //reads in values and assigns to variables
		fixUnderscores(songName);
		fixUnderscores(artistName);
		fixUnderscores(albumName);
		Song song = {songName, timeConvertMtoS(time), track};
		//creates new artist instance if artist is not in library
		//used this as a refresher for checking contents of map
		//https://www.geeksforgeeks.org/map-count-function-in-c-stl/
		if(!musicLibrary.count(artistName)){
			Artist artist;
			artist.name = artistName;
			artist.time = 0;
			artist.nsongs = 0;
			musicLibrary.insert(make_pair(artistName, artist));
		}
		//creates new album instance if album is not in library
		if(!musicLibrary[artistName].albums.count(albumName)){
			Album album;
			album.name = albumName;
			musicLibrary[artistName].albums.insert(make_pair(albumName, album));
		}
		
		//adds song to album
		musicLibrary[artistName].albums[albumName].songs.insert(make_pair(track, song));
		musicLibrary[artistName].nsongs++;
		//updating times
		musicLibrary[artistName].albums[albumName].time += song.time;
		musicLibrary[artistName].time += song.time;
		//cout<< title << " " << timeConvertMtoS(time) << endl; //testing
		
	}
	infile.close();
}

void fixUnderscores(string &s){
	replace(s.begin(), s.end(), '_', ' ');
}

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
 * Takes in a time integer as seconds,
 * calculates the minutes and remaining seconds,
 * and exports it in the form MM:SS
 */
string timeConvertStoM(int time)
{
	string formattedTime;
	stringstream ss;
	int minutes = 0, seconds = 0;
	minutes = time / 60;
	seconds = time % 60;
	ss << minutes << ":" << setfill('0') << setw(2) << seconds;
	return formattedTime = ss.str();
}



