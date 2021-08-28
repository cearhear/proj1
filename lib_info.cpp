/* COSC302 Project1
 * Carter Earheart-Brown
 * Stephanie Hill
 * Purpose: Import music information from file and organize it by 
 *			artist and album.
 */
#include<iostream>
#include<string>
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

/* Takes in the imported time as a string,
 * converts it to an integer
 * and exports the total time in seconds. 
 */
int timeConvertMtoS(string, string){
	string min, sec;
	int minutes, seconds, totsec;
	minutes = stoi(min);
	minutes = stoi(sec);
	return totsec = (minutes * 60) + seconds;
}

/* Takes in a time integer as seconds,
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

int main(){

	return 0;
}


