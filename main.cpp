/*
 * @author: Bobby Thompson (robert.h.thompson@wsu.edu)
 * @description: Example program to pull data from an API and output it to stdout
 * Code used as a template for the original program was found at https://curl.haxx.se/libcurl/c/https.html
 *
 * compiling instructions: make
**/
#include "main.h"

int main(int argc, char* argv[])
{
    // string address = "";
    // address = getAddress();
    // cURLaddressProPublica(address, MEMBER_LIST);
    // cURLaddressToFile(address, VOTE_INFO_CALL);
    // char * fileName = "repCallByAddress.json";
    // char * fileName = "senateMemberList.json";
    showMemberFromList("houseMemberList.json", "Ralph Abraham");
    // showCandidates(fileName);
    // showReferendums(fileName);
    // showRepresentatives(fileName);

    return 0;
}