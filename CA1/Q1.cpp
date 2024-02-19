#include <iostream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

void inputStations(vector<vector<int>>& stationDeltas, vector<vector<string>>& stationNames, int count, int i)
{
    for(int j=0; j < count; j++) {
        int delta;
        string stationName;
        cin >> delta >> stationName;
        stationNames[i].push_back(stationName);
        stationDeltas[i].push_back(delta);
    }
}

int findDestination(string destination, int n, vector<vector<int>>& lineStationCounts, vector<vector<string>>& stationNames, bool& towardEnd, int& stationDistance)
{
    for(int i = 0; i < n; i++) {

        vector<string> stations = stationNames[i];

        for (int j = 0; j < stations.size(); j++) {

            if(stations[j] == destination) {

                if (j + 1 > lineStationCounts[i][0]) {
                    stationDistance = j + 1 - lineStationCounts[i][0];
                    towardEnd = true;

                } else {
                    stationDistance = j + 1;
                    towardEnd = false;
                }

                return i;
            } 
        }
    }

    return 0;
}

int findCost(int stationCount)
{
    double log_result = log10(10 * stationCount);
    int result = ceil(1000 * log_result);
    return result;
}

int findArrivalMinutes(int distance, vector<int> deltas, vector<int> stationCounts, bool towardEnd)
{
    int final = 0;
    int start = towardEnd ? stationCounts[0] : 0;

    for (int i = start; i < start + distance; i++) {
        final += deltas[i];
    }

    return final;
}

string findArrivalTime(string now, int defaultDuration, int arrivalMinutes)
{
    string minutes = now.substr(3, 2);
    string hours = now.substr(0, 2);
    int minute = stoi(minutes);
    int hour = stoi(hours);

    int d = ceil((float)minute / defaultDuration);
    int startMinute = d * defaultDuration;


    if (startMinute == 60) {
        startMinute = 0;
        hour += 1;
    }

    int endMinute = startMinute + arrivalMinutes;

    while (endMinute >= 60) {
        endMinute -= 60;
        hour += 1;
    }

    if (hour >= 24) {
        hour -= 24;
    }

    hours = to_string(hour);
    minutes = to_string(endMinute);

    if (hours.length() == 1) {
        hours = '0' + hours;
    }

    if (minutes.length() == 1) {
        minutes = '0' + minutes;
    }
    
    return hours + ':' + minutes;
}

void printOutput(bool towardEnd, string lineName, int distance, string arrivalTime, int cost)
{
    string toward = towardEnd ? "end" : "start";

    cout << "Towards " << toward << " of " << lineName << " in " << distance << " station(s)" << endl << arrivalTime << endl << cost;
}

int main()
{
    int distance, n, i = 0;
    string now, destination, toward;
    bool towardEnd;

    cin >> n >> now;

    vector<int> lineDurations(n, 0);
    vector<string> lineNames(n);

    vector< vector<int> > lineStationCounts(n, {0,0}); // each line a vector containing count of starting stations , ending stations
    vector< vector<string> > stationNames(n); // contains stations names of each line
    vector< vector<int> > stationDeltas(n); // contains time deltas between stations of each line

    for (int i=0; i<n; i++) {
        string lineName;
        int duration, startCount, endCount;

        cin >> lineName >> duration;
        lineNames[i] = lineName;
        lineDurations[i] = duration;

        cin >> startCount;
        lineStationCounts[i][0] = startCount;
        inputStations(stationDeltas, stationNames, startCount, i);

        cin >> endCount;
        lineStationCounts[i][1] = endCount;
        inputStations(stationDeltas, stationNames, endCount, i);
    }

    cin >> destination;

    int lineIndex = findDestination(destination, n, lineStationCounts, stationNames, towardEnd, distance);

    int cost = findCost(distance);

    int arrivalMinutes = findArrivalMinutes(distance, stationDeltas[lineIndex], lineStationCounts[lineIndex], towardEnd);
    string arrivalTime = findArrivalTime(now, lineDurations[lineIndex], arrivalMinutes);

    printOutput(towardEnd, lineNames[lineIndex], distance, arrivalTime, cost);

    return 0;
}
