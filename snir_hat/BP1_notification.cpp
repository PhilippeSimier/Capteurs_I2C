/*!
    @file     BP1_notification.cpp
    @author   Philippe SIMIER (Touchard Wahington le Mans)
    @license  BSD (see license.txt)
    @brief    Programme pour envoyer une notification sur mon smartphone via ifttt
    @date     Aout 2018
    @version  v1.0 - First release
    @detail   Prérequis    : apt-get update
                             apt-get install libcurl4-openssl-dev
              Compilation  : g++  BP1_notification.cpp  -lcurl -lwiringPi -o BP1_notification
              Execution    : ./BP1_notification
*/

#include <iostream>
#include <curl/curl.h>
#include <wiringPi.h>

#define BP1 13
#define D1  21

using namespace std;

void envoyer()
{
    CURL *hnd = curl_easy_init();

    curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(hnd, CURLOPT_URL, "https://maker.ifttt.com/trigger/BP_1/with/key/bj9LiLkl3fvaV4jVx-JdUL");

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Cache-Control: no-cache");
    curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

    CURLcode ret = curl_easy_perform(hnd);
    cout << endl;

    long response_code;
    curl_easy_getinfo(hnd, CURLINFO_RESPONSE_CODE, &response_code);
    cout << "Réponse code : " << response_code << endl;
}


int main()
{

    wiringPiSetupGpio();
    pinMode(BP1, INPUT);
    pinMode(D1, OUTPUT);
    digitalWrite(D1, HIGH);  // D1 est allumée

    while(digitalRead (BP1)){
        delay(500);
    }
    digitalWrite(D1, LOW);
    envoyer();
    return 0;

}
