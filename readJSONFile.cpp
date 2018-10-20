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

    // for (auto& v : d["offices"].GetArray())
    // {
    //     cout << v["name"].GetString() << endl << v["divisionId"].GetString() << endl;
    //     if(v.HasMember("roles"))
    //     {
    //         for(auto& w : v["roles"].GetArray())
    //         {
    //             cout << w.GetString() << endl;
    //         }
    //     }
    //     cout << endl;
    // }

    return d;
};