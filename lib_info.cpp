/* 
 * COSC302 Project1
 * Carter Earheart-Brown
 * Stephanie Hill
 * Purpose: Import music information from file and organize it by 
 *			artist and album.
 */
#include<iostream>
#include<iomanip>
#include<stdlib.h>
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

void readFile(string file, map<string, Artist> &musicLibrary);
void printLibrary(map<string, Artist> &musicLibrary);
void fixUnderscores(string &s);
int timeConvertMtoS(string time);
string timeConvertStoM(int time);

int main(int argc, char *argv[]){
	string song, time, artist, album, genre;
	int track;
	map<string, Artist> musicLibrary;
	readFile(argv[1], musicLibrary);
	printLibrary(musicLibrary);
	
	return 0;
}


/*
 * Reads in file and converts all underscores to spaces 
 * Source: https://stackoverflow.com/questions/7868936/read-file-line-by-line-using-ifstream-in-c
 * https://stackoverflow.com/questions/2896600/how-to-replace-all-occurrences-of-a-character-in-string
*/
void readFile(string file, map<string, Artist> &musicLibrary){

	ifstream infile(file);
	string line, songName, time, artistName, albumName, genre;
	int track; 
	istringstream iss(line); 
	
	
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
		
	}
	infile.close();
}

void printLibrary(map <string, Artist> &musicLibrary){

	
	for(auto const&artist_it : musicLibrary){
		cout << artist_it.first << ": " << artist_it.second.nsongs << ", "<< timeConvertStoM(artist_it.second.time) << "\n";
		for(auto const&album_it : artist_it.second.albums){
			cout << "        " << album_it.first << ": " << album_it.second.songs.size() <<", " << timeConvertStoM(album_it.second.time) << "\n";
			for(auto const&song_it : album_it.second.songs){
				cout << "                " << song_it.first << ". " << song_it.second.title << ": " << timeConvertStoM(song_it.second.time) << "\n";
			}
		}
	}
}

void fixUnderscores(string &s){
	replace(s.begin(), s.end(), '_', ' ');
}

/*
 * Takes in the imported time as a string
 * converts it to an integer
 * and exports the total time in seconds. 
 * https://stackoverflow.com/questions/24270236/how-to-convert-formatted-string-hhmmss-to-seconds-in-c
 */
int timeConvertMtoS(string time){
	int mins = 0, secs = 0;
	sscanf(time.c_str(), "%d:%d",&mins,&secs);
	secs = (mins*60) + secs;
	return secs;
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



