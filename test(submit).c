#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "MinPopVote.h"

bool test_totalEVs() {
    State aStates[10];
    int res;
    
    aStates[0].electoralVotes = 10;
    aStates[1].electoralVotes = 9;
    aStates[2].electoralVotes = 8;
    aStates[3].electoralVotes = 7;
    
    printf(" Checking totalPVs() for 4 States:\n");
    res = totalEVs(aStates,4);
    if (res != 34) {
        printf("Individual state EVs are 10, 9, 18, 7\n");
        printf("Expected total EVs = 34, actual total PVs = %d\n",res);
        return false;
    }
    aStates[0].electoralVotes = 5;
    aStates[1].electoralVotes = 6;
    aStates[2].electoralVotes = 7;
    aStates[3].electoralVotes = 8;
    aStates[4].electoralVotes = 9;
    aStates[5].electoralVotes = 10;

    printf(" Checking totalPVs() for 6 States:\n");
    res = totalEVs(aStates,6);
    if (res != 45) {
        printf("Individual state EVs are 5, 6, 7, 8, 9, 10\n");
        printf("Expected total EVs = 45, actual total PVs = %d\n",res);
        return false;
    }
    return true;
}

bool test_totalPVs() {
    State popStates[10];
    int res;
    
    popStates[0].popularVotes = 10;
    popStates[1].popularVotes = 9;
    popStates[2].popularVotes = 8;
    popStates[3].popularVotes = 7;
    
    printf(" Checking totalPVs() for 4 States:\n");
    res = totalPVs(popStates,4);
    if (res != 34) {
        printf("Individual state PVs are 10, 9, 18, 7\n");
        printf("Expected total PVs = 34, actual total PVs = %d\n",res);
        return false;
    }
    popStates[0].popularVotes = 5;
    popStates[1].popularVotes = 6;
    popStates[2].popularVotes = 7;
    popStates[3].popularVotes = 8;
    popStates[4].popularVotes = 9;
    popStates[5].popularVotes = 10;

    printf(" Checking totalPVs() for 6 States:\n");
    res = totalPVs(popStates,6);
    if (res != 45) {
        printf("Individual state EVs are 5, 6, 7, 8, 9, 10\n");
        printf("Expected total PVs = 45, actual total PVs = %d\n",res);
        return false;
    }
    return true;
}

bool test_setSettings() {
    bool fastMode = false;
    bool quietMode = false;
    int year = 0;
    
    char* test[50]  = {"./app.exe", "-f", "-q", "-y", "2004", NULL};
    char* test2[50] = {"./app.exe", "-q", "-f", "-y", "1776", NULL};
    char* test3[50] = {"./app.exe", "-f", "-y", "2004", NULL};
    char* test4[50] = {"./app.exe", "-q", NULL};
    char* test5[50] = {"./app.exe", NULL};
    
    bool testSettings  = setSettings(5, test, &year, &fastMode, &quietMode);
    bool testSettings2 = setSettings(5, test2, &year, &fastMode, &quietMode);
    bool testSettings3 = setSettings(4, test3, &year, &fastMode, &quietMode);
    bool testSettings4 = setSettings(2, test4, &year, &fastMode, &quietMode);
    bool testSettings5 = setSettings(1, test5, &year, &fastMode, &quietMode);

    if(!testSettings){
        printf("Test1 Expected: true,Actual: false\n");
    }
    else if(!testSettings2){
        printf("Test2 Expected: true, Actual: false\n");
    }
    else if(!testSettings3){
        printf("Test3 Expected: true, Actual: false\n");
    }
    else if(!testSettings4){
        printf("Test4 Expected: true, Actual: false\n");
    }
    else if(!testSettings5){
        printf("Test5 Expected: true, Actual: false\n");
    }
    else{
        return true;
    }

    return false;
}

bool test_inFilename() {
    char filename[50]; 
    char filename2[50];
    char filename3[50];
    int year = 2004; 
    int year2 = 1828; 
    int year3 = 1924;
   
    printf(" Checking inFilename():\n");
    inFilename(filename, year);
    inFilename(filename2, year2);
    inFilename(filename3, year3);
    
    if (strcmp(filename, "data/2004.csv") != 0) {
        printf("Invalid input,try again.\n");
        printf("Expected input: data/2004.csv, Actual input: data/%d.csv\n",year);
        return false;
    }
    if (strcmp(filename2, "data/1828.csv") != 0) {
        printf("Invalid input,try again.\n");
        printf("Expected input: data/1828.csv, Actual input: data/%d.csv\n",year);
        return false;
    }
    if (strcmp(filename3, "data/1924.csv") != 0) {
        printf("Invalid input,try again.\n");
        printf("Expected input: data/1924.csv, Actual input: data/%d.csv\n",year);
        return false;
    }
    return true;
}

bool test_outFilename() {
    char filenameOut[50]; 
    char filenameOut2[50];
    char filenameOut3[50];
    int year = 2004; 
    int year2 = 1828; 
    int year3 = 1924;
    
    outFilename(filenameOut, year);
    outFilename(filenameOut2, year2);
    outFilename(filenameOut3, year3);
    
    if (strcmp(filenameOut, "toWin/2004_win.csv") != 0) {
        printf("Invalid input,try again.\n");
        printf("Expected input: toWin/2004_win.csv, Actual input: toWin/%d_win.csv\n",year);
        return false;
    }
    if (strcmp(filenameOut2, "toWin/1828_win.csv") != 0) {
        printf("Invalid input,try again.\n");
        printf("Expected input: toWin/1828_win.csv, Actual input: toWin/%d_win.csv\n",year);
        return false;
    }
    if (strcmp(filenameOut3, "toWin/1924_win.csv") != 0) {
        printf("Invalid input,try again.\n");
        printf("Expected input: toWin/1924_win.csv, Actual input: toWin/%d_win.csv\n",year);
        return false;
    }
    return true;
}

bool test_parseLine() {
   State testParse;
   State testParse2; 
   State testParse3; 
   char line[50] = "Illinois,IL,21,5350493";
   char line2[50] = "New York,31,7448266";
   char line3[50] = "California,CA,55,12589367";

   if(parseLine(line, &testParse) == false){
       printf("Invalid Parse");
       printf("Expected: true, Actual: false");
       return false;
    }
   if(parseLine(line2, &testParse2) == true){
       printf("Invalid Parse");
       printf("Expected: false, Actual: true");
       return false;
    }
   if(parseLine(line3, &testParse3) == false){
       printf("Invalid Parse");
       printf("Expected: true, Actual: false");
       return false;
    }

    return true; 
}

bool test_readElectionData() {
    State allStates[5];
    char* storeLine[50];
    // int nStates = 0;
    // FILE* testElecData = fopen(testFile.txt, "r");
    // if(testElecData == NULL){
    //     printf("Invalid File\n");
    //     return false;
    // }
    // while(fgets(storeLine, sizeof(storeLine), testElecData)){
    //     if(parseLine(storeLine, &allStates[nStates])){
    //         nStates++;
    //     }
    // }
    // fclose(testElecData);
    
    return true; //modify this
}

bool test_minPVsSlow() {
    State testStates[3];
    MinInfo res; 
    testStates[0].electoralVotes = 6;
    testStates[0].popularVotes = 16;
    strcpy(testStates[0].name , "State A");
    testStates[1].electoralVotes = 7;
    testStates[1].popularVotes = 25;
    strcpy(testStates[1].name , "State N");
    testStates[2].electoralVotes = 8;
    testStates[2].popularVotes = 56;
    strcpy(testStates[2].name , "State Q");
    testStates[3].electoralVotes = 9;
    testStates[3].popularVotes = 65;
    strcpy(testStates[3].name , "State X");

    res = minPopVoteToWin(testStates, 4);

    if(res.subsetPVs == 46){
        printf("Correct! The expected subset Pop Vote is: %d\n", res.subsetPVs);
        return true;
    }else{
        printf(" Expected subset Pop Vote is: 47, Actual subset Pop Vote is: %d\n", res.subsetPVs);
        return false; 
    }
}

bool test_minPVsFast() {
    State testStates[3];
    MinInfo res; 
    testStates[0].electoralVotes = 6;
    testStates[0].popularVotes = 16;
    strcpy(testStates[0].name , "State A");
    testStates[1].electoralVotes = 7;
    testStates[1].popularVotes = 25;
    strcpy(testStates[1].name , "State N");
    testStates[2].electoralVotes = 8;
    testStates[2].popularVotes = 56;
    strcpy(testStates[2].name , "State Q");
    testStates[3].electoralVotes = 9;
    testStates[3].popularVotes = 65;
    strcpy(testStates[3].name , "State X");

    res = minPopVoteToWinFast(testStates, 4);

    if(res.subsetPVs == 46){
        printf("Correct! The expected subset Pop Vote is: %d\n", res.subsetPVs);
        return true;
    }
    else{
        printf(" Expected subset Pop Vote is: 47, Actual subset Pop Vote is: %d\n", res.subsetPVs);
        return false; 
    }
}

int main() {
    printf("Welcome to the Popular Vote Minimizer Testing Suite!\n\n");
    
    printf("Testing totalEVs()...\n"); 
    if (test_totalEVs()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing totalPVs()...\n"); 
    if (test_totalPVs()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing setSettings()...\n"); 
    if (test_setSettings()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }
    
    printf("Testing inFilename()...\n"); 
    if (test_inFilename()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing outFilename()...\n"); 
    if (test_outFilename()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing parseLine()...\n"); 
    if (test_parseLine()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing readElectionData()...\n"); 
    if (test_readElectionData()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }
    
    printf("Testing minPopVoteToWin()...\n"); 
    if (test_minPVsSlow()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing minPopVoteToWinFast()...\n"); 
    if (test_minPVsFast()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    return 0;
}
