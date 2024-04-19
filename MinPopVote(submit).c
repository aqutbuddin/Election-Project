#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "MinPopVote.h"

bool setSettings(int argc, char** argv, int* year, bool* fastMode, bool* quietMode) {
    *year = 0; 
    *quietMode = false; 
    *fastMode = false;
    bool checkAll = true;

    for(int i = 1; i < argc; i++){
        if(strcmp(argv[i], "-f") == 0){
            *fastMode = true;
        }
        else if (strcmp(argv[i], "-q") == 0){
            *quietMode = true; 
        }
        else if(strcmp(argv[i], "-y") == 0 && i + 1 < argc){
            int validYear = atoi(argv[i + 1]);
            if (validYear >= 1828 && validYear <= 2020 && (validYear % 4 == 0)){
                *year = validYear;
            }
            i++; // necessary bc checking the index+1, for the year, need to check an additinal space for the command line arg
        }
        else{
            checkAll = false; 
        }
    }
    return checkAll;
}

void inFilename(char* filename, int year) {
  sprintf(filename, "data/%d.csv", year);
  return;
}

void outFilename(char* filename, int year) {
    sprintf(filename,"toWin/%d_win.csv", year);
    return;
}

bool parseLine(char* line, State* myState) {
    int countCommas = 0; 
    char* dataStorage = line; 
    bool validParse = true; 

    while(*dataStorage != '\0'){
        if (*dataStorage == ','){
            countCommas++; 
        }
        dataStorage++;
    }

    if(countCommas != 3){
        validParse = false; 
        return validParse; 
    }

    int parsedData = sscanf(line, "%50[^,], %3[^,], %d, %d", myState->name,myState->postalCode,&myState->electoralVotes,&myState->popularVotes);

    if(parsedData == 4){
        return validParse; 
    }
    else{
        validParse = false; 
        return validParse;
    }
}

bool readElectionData(char* filename, State* allStates, int* nStates) {
    *nStates = 0; //required initialization prior to incrementing. 
    char line[100];
    FILE* filePtr = fopen(filename, "r");
    if (filePtr == NULL){
        return false; 
    }
    while(fgets(line, sizeof(line), filePtr)){
        //fgets(line, sizeof(line), filePtr);
        if(parseLine(line, &allStates[*nStates])){
            (*nStates)++;
        }
    }
    fclose(filePtr);

    return true; 
}

int totalEVs(State* states, int szStates) {
    int EVsum = 0;
    for(int i = 0; i < szStates; i++){
        EVsum = EVsum + states[i].electoralVotes; 

    }
    return EVsum; // modify or replace this line
}

int totalPVs(State* states, int szStates) {
    int PVsum = 0;
    for(int i = 0; i < szStates; i++){
        PVsum = PVsum + states[i].popularVotes; 
    }
    return PVsum;
    // modify or replace this line
}

MinInfo minPopVoteAtLeast(State* states, int szStates, int start, int EVs) { 
    MinInfo res; 
    if(EVs <= 0){ //base case, when less or equal to 0, adequate number of EVs reached
        res.subsetPVs = 0;
        res.sufficientEVs = true;
        res.szSomeStates = 0;
        return res;
    }
    else if(start == szStates){//base case, when start equal to all not enough number of EVs reached
        res.subsetPVs = 0;
        res.sufficientEVs = false; 
        res.szSomeStates = 0;
        return res;
    }
    // add in subset resursive call, need to substrat the EVs to see how many more still remain 
    MinInfo addIn = minPopVoteAtLeast(states,szStates,start+1,EVs - states[start].electoralVotes);
    
    addIn.subsetPVs = addIn.subsetPVs + (states[start].popularVotes/2)+1; //compiling the popular votes
    addIn.someStates[addIn.szSomeStates] = states[start];
    addIn.szSomeStates++;

    // move to the next recursive call, no adjustment to EV needed
    MinInfo nextIn = minPopVoteAtLeast(states, szStates, start+1, EVs);

    if(nextIn.subsetPVs < addIn.subsetPVs && nextIn.sufficientEVs){
        return nextIn;
    }
    else{
        return addIn;
    }
}

MinInfo minPopVoteToWin(State* states, int szStates) {
    int totEVs = totalEVs(states,szStates);
    int reqEVs = totEVs/2 + 1; // required EVs to win election
    return minPopVoteAtLeast(states, szStates, 0, reqEVs);
}

MinInfo minPopVoteAtLeastFast(State* states, int szStates, int start, int EVs, MinInfo** memo) {
    MinInfo res; 
    if(EVs <= 0){ //base case, when less or equal to 0, adequate number of EVs reached
        res.subsetPVs = 0;
        res.sufficientEVs = true;
        res.szSomeStates = 0;
        return res;
    }
    else if(start == szStates){//base case, when start equal to all not enough number of EVs reached
        res.subsetPVs = 0;
        res.sufficientEVs = false; 
        res.szSomeStates = 0;
        return res;
    }
    else if(memo[start][EVs].subsetPVs != -1){
        return memo[start][EVs];
    }
    // add in subset resursive call, need to substrat the EVs to see how many more still remain 
    MinInfo addIn = minPopVoteAtLeastFast(states,szStates,start+1,EVs - states[start].electoralVotes, memo);
    
    addIn.subsetPVs = addIn.subsetPVs + (states[start].popularVotes/2)+1; //compiling the popular votes
    addIn.someStates[addIn.szSomeStates] = states[start];
    addIn.szSomeStates++;

    // move to the next recursive call, no adjustment to EV needed
    MinInfo nextIn = minPopVoteAtLeastFast(states, szStates, start+1, EVs, memo);

    if(nextIn.subsetPVs < addIn.subsetPVs && nextIn.sufficientEVs){
        memo[start][EVs] = nextIn;
        return nextIn;
    }
    else{
        memo[start][EVs] = addIn;
        return addIn;
    }
}

MinInfo minPopVoteToWinFast(State* states, int szStates) {
    int totEVs = totalEVs(states,szStates);
    int reqEVs = totEVs/2 + 1; // required EVs to win election

    MinInfo** memo = (MinInfo**)malloc((szStates+1)*sizeof(MinInfo*));
    for (int i = 0; i < szStates+1; ++i) {
        memo[i] = (MinInfo*)malloc((reqEVs+1)*sizeof(MinInfo));
        for (int j = 0; j < reqEVs+1; ++j) {
            memo[i][j].subsetPVs = -1;
        }
    }
    MinInfo res = minPopVoteAtLeastFast(states, szStates, 0, reqEVs, memo);
    
    for(int i = 0; i <szStates +1; i++){
        free(memo[i]);
    }
    free(memo);
    
    return res;
}

bool writeSubsetData(char* filenameW, int totEVs, int totPVs, int wonEVs, MinInfo toWin) {
    FILE* dataFile = fopen(filenameW,"w");
    if(dataFile == NULL){
        return false;
    }
    fprintf(dataFile,"%d, %d, %d, %d\n",totEVs,totPVs,wonEVs,toWin.subsetPVs);
    for(int i = toWin.szSomeStates -1; i >= 0; i--){
        fprintf(dataFile, "%s, %s, %d, %d\n",
        toWin.someStates[i].name,
        toWin.someStates[i].postalCode,
        toWin.someStates[i].electoralVotes,
        (toWin.someStates[i].popularVotes /2 + 1));
    }
    fclose(dataFile);
    return true; //modify or replace this
}
