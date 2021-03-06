/*
 * @author: Bobby Thompson (robert.h.thompson@wsu.edu)
 * @description: Example program to pull data from an API and output it to stdout
 * Code used as a template for the original cURL program was found at https://curl.haxx.se/libcurl/c/https.html
 *
 * compiling instructions: make
**/
#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <curl/curl.h>
#include "readJSONFile.h"

// Google Constants
#define VOTE_INFO_CALL              1
#define REP_INFO_CALL               2

// Propublica Constants
#define SENATE_MEMBER_LIST          1
#define HOUSE_MEMBER_LIST           2

const char * PROPUBLICA_API_KEY = "X-API-Key: vwdaGCyxpz530UzNiYVQloeKwgMLXVo2t5bfr8iG";
const char * GOOGLE_CIVIC_API_KEY = "AIzaSyC2XdRudeNVGITKbkMESaCSdnebxTi9bm0";
const char * GOOGLE_URL = "https://www.googleapis.com/civicinfo/v2/representatives?key=AIzaSyC2XdRudeNVGITKbkMESaCSdnebxTi9bm0&address=1263%20Pacific%20Ave.%20Kansas%20City%20KS";

using namespace std;

/*
* Write function for cURL to write to files
**/
static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
   size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
   return written;
}

/*
* Creates a Google URI in char * type so it can be fed into cURL as a parameter
*
* @param[in]  string parsedAddress - parsed Address suitable for converting into a char * URI
*
* @return	   char *     URI       - the completed URI to send into the cURL function
**/
char * createGoogleURL(string parsedAddress, int dataToCall)
{
   stringstream buffer;
   char c;
   static char URI[200];
   int i = 0;

   switch (dataToCall)
   {
       case VOTE_INFO_CALL:
           buffer << "https://www.googleapis.com/civicinfo/v2/voterinfo?address=" << parsedAddress << "&key=" << GOOGLE_CIVIC_API_KEY << "#";
           break;
       case REP_INFO_CALL:
           buffer << "https://www.googleapis.com/civicinfo/v2/representatives?address=" << parsedAddress << "&key=" << GOOGLE_CIVIC_API_KEY << "#";
           break;
       default:
           break;
   }
   buffer >> c;
   while(c != '#')
   {
       URI[i++] = c;
       buffer >> c;
   }

   return URI;
};

/*
 * Creates a ProPublica URI in char * type so it can be fed into cURL as a parameter
 *
 * @param[in]  string parsedAddress - parsed Address suitable for converting into a char * URI
 *
 * @return	   char *     URI       - the completed URI to send into the cURL function
**/
char * createProPublicaURL(string parsedAddress, int dataToCall)
{
    stringstream buffer;
    char c;
    static char URI[200];
    int i = 0;

    switch (dataToCall)
    {
        case HOUSE_MEMBER_LIST:
            buffer << "https://api.propublica.org/congress/v2/115/house/members.json" << "#";
            break;
        case SENATE_MEMBER_LIST:
            buffer << "https://api.propublica.org/congress/v2/115/senate/members.json" << "#";
            break;
        default:
            break;
    }
    buffer >> c;
    while(c != '#')
    {
        URI[i++] = c;
        buffer >> c;
    }

    return URI;
};

/*
 * Takes a plain text string address and converts it to the proper format for Google URI injection
 *
 * @param[in]  string   address     - Plain text address string to be parsed
 *
 * @return	   string   address     - Parsed string variable ready to be inserted in Google API call
**/
string parseAddress(string address)
{
    char c;
    string parsedAddress = "";
    stringstream streamIn, streamOut;

    streamIn << address;
    streamIn >> c;

    while(!streamIn.eof())
    {
        if(c == ' ')
        {
            streamOut << "%20";
        }
        else
        {
            streamOut << c;
        }
        streamIn.get(c);
    }

    streamOut >> parsedAddress;
    return parsedAddress;
}

/*
* cURL function to call Google Civic API with an embedded address
*
* @param[in]  string   address     - Parsed address to be searched for
*
**/
void cURLaddressProPublica(string address, int dataToCall)
{
   CURL *curl;                                                     // cURL Object that will do requests for us
   struct curl_slist *headers = NULL;                              // Headers list object, will be used for API Key
   char * URL;

   static const char * pagefilename;
   FILE *pagefile;

   curl_global_init(CURL_GLOBAL_DEFAULT);                          // Initialize Global defaults required
   curl = curl_easy_init();                                        // Initialize cURL object

   URL = createProPublicaURL(address, HOUSE_MEMBER_LIST);

   switch (dataToCall)
   {
       case SENATE_MEMBER_LIST:
           pagefilename = "senateMemberList.json";
           break;
       case HOUSE_MEMBER_LIST:
           pagefilename = "houseMemberList.json";
           break;
       default:
           break;
   }

   curl_easy_setopt(curl, CURLOPT_URL, URL);
   // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
   curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);        // curl_easy_setopt(curl, CURLOPT_URL, "https://api.propublica.org/congress/v1/members/K000388/votes.json");
   headers = curl_slist_append(headers, PROPUBLICA_API_KEY);         // API Key goes into the header, to send with the request
   curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
                                                                       // Check for errors
   pagefile = fopen(pagefilename, "wb");
   if(pagefile)
   {
       curl_easy_setopt(curl, CURLOPT_WRITEDATA, pagefile);
       curl_easy_perform(curl);

       fclose(pagefile);
   }

   curl_easy_cleanup(curl);                                    // Always cleanup
   curl_global_cleanup();                                          // Cleaning up global settings
}

/*
* cURL function to call Google Civic API with an embedded address and write data to file
*
* @param[in]  string   address     - Parsed address to be searched for
*
**/
void cURLaddressToFile(string address, int dataToCall)
{
   CURL * curl;                                                     // cURL Object that will do requests for us
   struct curl_slist * headers = NULL;                              // Headers list object, will be used for API Key
   char * URL;

   static const char * pagefilename;
   FILE *pagefile;

   curl_global_init(CURL_GLOBAL_DEFAULT);                          // Initialize Global defaults required
   curl = curl_easy_init();                                        // Initialize cURL object

   URL = createGoogleURL(parseAddress(address), dataToCall);


   switch (dataToCall)
   {
       case VOTE_INFO_CALL:
           pagefilename = "voteCallByAddress.json";
           break;
       case REP_INFO_CALL:
           pagefilename = "repCallByAddress.json";
           break;
       default:
           break;
   }

   curl_easy_setopt(curl, CURLOPT_URL, URL);
   // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
   curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);        // curl_easy_setopt(curl, CURLOPT_URL, "https://api.propublica.org/congress/v1/members/K000388/votes.json");

   pagefile = fopen(pagefilename, "wb");
   if(pagefile)
   {
       curl_easy_setopt(curl, CURLOPT_WRITEDATA, pagefile);
       curl_easy_perform(curl);

       fclose(pagefile);
   }

   curl_easy_cleanup(curl);                                    // Always cleanup
   curl_global_cleanup();                                          // Cleaning up global settings
}

/*
 * Parses JSON then displays condidate data to stdout
 *
 * @param[in]  char *   fileName    - name of the JSON file with appropriate candidate data (probably voteCallByAddress.json)
 *
**/
void showCandidates(char * fileName)
{
    Document d = parseJSONFile(fileName);

    for (auto& v : d["contests"].GetArray())
    {
        if(v["type"] != "Referendum")
        {
            cout << "Type: " << v["type"].GetString() << endl;
            for(auto& level : v["level"].GetArray())
            {
                cout << "Level: " << level.GetString() << endl;
            }
            cout << "Office: " << v["office"].GetString() << endl;
            if(v.HasMember("roles"))
            {
                for(auto& w : v["roles"].GetArray())
                {
                    cout << "Role: " << w.GetString() << endl;
                }
            }
            if(v.HasMember("district"))
            {
                cout << "District: " << v["district"]["name"].GetString() << endl;
            }
            cout << endl;
            if(v.HasMember("candidates"))
            {
                for(auto& w : v["candidates"].GetArray())
                {
                    if(w.HasMember("name"))
                    {
                        cout << "\tName:\t" << w["name"].GetString() << endl;
                    }
                    if(w.HasMember("party"))
                    {
                        cout << "\tParty:\t" << w["party"].GetString() << endl;
                    }
                    if(w.HasMember("phone"))
                    {
                        cout << "\t" << w["phone"].GetString() << endl;
                    }
                    if(w.HasMember("email"))
                    {
                        cout << "\t" << w["email"].GetString() << endl;
                    }
                    if(w.HasMember("channels"))
                    {
                        for(auto& z : w["channels"].GetArray())
                        {
                            cout << "\t" << z["type"].GetString() << ":\t" << z["id"].GetString() << endl;
                        }
                    }
                    cout << endl;
                }
            }
        }
    }
}

/*
 * Parses JSON then displays condidate data to stdout
 *
 * @param[in]  char *   fileName    - name of the JSON file with appropriate candidate data (probably voteCallByAddress.json)
 *
**/
void makeCandidatesJSON(char * fileName)
{
    Document d = parseJSONFile(fileName);

    cout << "{" << endl << " \"names\": [";

    for (auto& v : d["contests"].GetArray())
    {
        if(v["type"] != "Referendum")
        {
            if(v.HasMember("candidates"))
            {
                for(auto& w : v["candidates"].GetArray())
                {
                    if(w.HasMember("name"))
                    {
                        cout << "\"" << w["name"].GetString() << "\", ";
                    }
                }
            }
        }
    }
    cout << "] " << endl << "}";
}

/*
* Parses JSON then displays referendum data on stdout
*
* @param[in]  char *   fileName    - name of the JSON file with appropriate referendum data (probably voteCallByAddress.json)
*
**/
void showReferendums(char * fileName)
{
   Document d = parseJSONFile(fileName);

   for (auto& v : d["contests"].GetArray())
   {
       if(v["type"] == "Referendum")
       {
           if(v.HasMember("ballotTitle"))
           {
               cout << "Ballot Title:" << v["ballotTitle"].GetString() << endl;
           }
           if(v.HasMember("district"))
           {
               cout << "District: " << v["district"]["name"].GetString() << "\t\t";
               if(v.HasMember("scope"))
               {
                   cout << v["scope"].GetString();
               }
               cout << endl;
           }
           if(v.HasMember("referendumTitle"))
           {
               cout << v["referendumTitle"].GetString() << endl;
           }
           if(v.HasMember("referendumSubtitle"))
           {
               cout << v["referendumSubtitle"].GetString() << endl;
           }
           if(v.HasMember("referendumText"))
           {
               cout << v["referendumText"].GetString() << endl;
           }
           cout << endl;
       }
   }
}

/*
* Parses JSON then displays referendum data on stdout
*
* @param[in]  char *   fileName    - name of the JSON file with appropriate referendum data (probably voteCallByAddress.json)
*
**/
void showRepresentatives(char * fileName)
{
   Document d = parseJSONFile(fileName);

   for (auto& v : d["officials"].GetArray())
   {
       cout << "Name: " << v["name"].GetString() << endl;

       if(v.HasMember("party"))
       {
           cout << "Party: " << v["party"].GetString() << endl;
       }

       if(v.HasMember("address"))
       {
           for (auto& e : v["address"].GetArray())
           {
               if(e.HasMember("line1"))
               {
                   cout << "\t" << e["line1"].GetString() << endl;
               }
               if(e.HasMember("line2"))
               {
                   cout << "\t" << e["line2"].GetString() << endl;
               }
               if(e.HasMember("line3"))
               {
                   cout << "\t" << e["line3"].GetString() << endl;
               }
               if(e.HasMember("city"))
               {
                   cout << "\t" << e["city"].GetString()  << " ";
                   if(e.HasMember("state"))
                   {
                       cout << e["state"].GetString() << " ";
                       if(e.HasMember("zip"))
                       {
                           cout << e["zip"].GetString();
                       }
                   }
                   cout << endl;
               }
           }
       }

       if(v.HasMember("phones"))
       {
           for (auto& w : v["phones"].GetArray())
           {
               cout << "\t" << w.GetString() << endl;
           }
       }

       if(v.HasMember("urls"))
       {
           for(auto& w : v["urls"].GetArray())
           {
               cout << "\t" << "Website @: " << w.GetString() << endl;
           }
       }

       if(v.HasMember("photoUrl"))
       {
           cout << "\t" << "Photo @: " << v["photoUrl"].GetString() << endl;
       }

       if(v.HasMember("channels"))
       {
           for(auto& w : v["channels"].GetArray())
           {
               cout << "\t" << w["type"].GetString() << ":\t" << w["id"].GetString() << endl;
           }
       }

       cout << endl;
   }
}

/*
* Parses House or Senate Member List, searches for a certain member from the list, then outputs
* data from that list if the member is found
*
* @param[in]  char *   fileName    - name of the JSON file with appropriate referendum data (probably voteCallByAddress.json)
*
**/void showMemberFromList(char * fileName, string memberName)
{
   Document d = parseJSONFile(fileName);

   for (auto& v : d["results"].GetArray())
   {
       for (auto& w : v["members"].GetArray())
       {
           if(w.HasMember("name"))
           {
               if(memberName == w["name"].GetString())
               {
                   cout << "\t\t" << w["name"].GetString() << endl;

                   if(w.HasMember("party"))
                   {
                       cout << "Party:\t\t\t"  << w["party"].GetString() << endl;
                   }
                   if(w.HasMember("gender"))
                   {
                       cout << "Gender:\t\t\t"  << w["gender"].GetString() << endl;
                   }
                   if(w.HasMember("total_votes"))
                   {
                       cout << "Total Votes:\t\t"  << w["total_votes"].GetInt() << endl;
                   }
                   if(w.HasMember("missed_votes"))
                   {
                       cout << "Missed Votes:\t\t"  << w["missed_votes"].GetInt() << endl;
                   }
                   if(w.HasMember("missed_votes_pct"))
                   {
                       cout << "Missed Vote:\t\t"  << w["missed_votes_pct"].GetDouble() << "%" << endl;
                   }
                   if(w.HasMember("votes_with_party_pct"))
                   {
                       cout << "Votes With Party:\t"  << w["votes_with_party_pct"].GetDouble() << "%" << endl;
                   }
               }
           }
       }
   }
}

/*
* Function to get plain text string from stdin
*
* @return	 string     address     - plain text string with the address to be searched for
*
**/
string getAddress()
{
   string address = "";
   char c = ' ';

   cout << "Enter an address to search for: ";

   while(c != '\n')
   {
       c = getchar();
       address = address + c;
   }

   return address;
}

char * makeCharStar(string words)
{
    stringstream buffer;
    char c;
    static char URI[200];
    int i = 0;
    buffer << words;
    buffer >> c;
    while(c != '#')
    {
        URI[i++] = c;
        buffer >> c;
    }

    return URI;
}

string getCandidateName(char * fileName, int offset)
{
    Document d = parseJSONFile(fileName);
    int i = 0;

    for (auto& v : d["contests"].GetArray())
    {
        if(v["type"] != "Referendum")
        {
            if(v.HasMember("candidates"))
            {
                for(auto& w : v["candidates"].GetArray())
                {
                    if(w.HasMember("name"))
                    {
                        if(offset != i)
                        {
                            i++;
                        }
                        else
                        {
                            return w["name"].GetString();
                        }
                    }
                }
            }
        }
    }
}

string getCandidateParty(char * fileName, int offset)
{
    Document d = parseJSONFile(fileName);
    int i = 0;

    for (auto& v : d["contests"].GetArray())
    {
        if(v["type"] != "Referendum")
        {
            if(v.HasMember("candidates"))
            {
                for(auto& w : v["candidates"].GetArray())
                {
                    if(w.HasMember("party"))
                    {
                        if(offset != i)
                        {
                            i++;
                        }
                        else
                        {
                            return w["party"].GetString();
                        }
                    }
                }
            }
        }
    }
}

string getCandidateEmail(char * fileName, int offset)
{
    Document d = parseJSONFile(fileName);
    int i = 0;

    for (auto& v : d["contests"].GetArray())
    {
        if(v["type"] != "Referendum")
        {
            if(v.HasMember("candidates"))
            {
                for(auto& w : v["candidates"].GetArray())
                {
                    if(w.HasMember("email"))
                    {
                        if(offset != i)
                        {
                            i++;
                        }
                        else
                        {
                            return w["email"].GetString();
                        }
                    }
                }
            }
        }
    }
}