/*
 * @author: Bobby Thompson (robert.h.thompson@wsu.edu)
 * @description: Example Code on how to Parse a JSON file into a DOM and then use the data
 *
 * compiling instructions: make rapidJSONFile
**/
#include "readJSONFile.h"

Document parseJSONFile(const char * fileLocation)
{
    FILE* fp = fopen(fileLocation, "rb"); // non-Windows use "r"
    char readBuffer[65536];
    FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    Document d;
    d.ParseStream(is);
    fclose(fp);

    return d;
};