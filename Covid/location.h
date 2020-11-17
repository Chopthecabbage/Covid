#ifndef LOCATION_H
#define LOCATION_H

#include "Common.h"

class Location
{
private:
    char province[BASIC_SIZE];
    char city[BASIC_SIZE];
    char medical_institution[BASIC_SIZE];
    char address[SPECIFIC_SIZE];
    char weekday_operating_hours[BASIC_SIZE];
    char saturday_operating_hours[BASIC_SIZE];
    char sunday_operating_hours[BASIC_SIZE];
    char representative_phone[BASIC_SIZE];
    char lat[BASIC_SIZE];
    char lng[BASIC_SIZE];

public:
    Location();
    void SetLocation(char* province, char* city, char* medical_institution, char* address, char* weekday_operating_hours, char* saturday_operating_hours, char* sunday_operating_hours, char* representative_phone, char* lat, char* lng);

    char* GetProvince();
    char* GetCity();
    char* GetMedical();
    char* GetAddress();
    char* GetWeekday();
    char* GetSaturday();
    char* GetSunday();
    char* GetPhone();
    char* GetLat();
    char* GetLng();

    void SetProvince(char* province);
    void SetCity(char* city);
    void SetMedical(char* medical_institution);
    void SetAddress(char* address);
    void SetWeekday(char* weekday_operating_hours);
    void SetSaturday(char* saturday_operating_hours);
    void SetSunday(char* sunday_operating_hours);
    void SetPhone(char* representative_phone);
    void SetLat(char* lat);
    void SetLng(char* lng);

    void ShowLocation();
};

#endif // LOCATION_H
