#pragma once

#include "../header/Libs.h"

#define ID_MAX      (15)
#define NAME_MAX    (30)
#define PHONE_MAX   (15)

typedef struct MyAddress_
{
    char id[ID_MAX];
    char name[NAME_MAX];
    char phone[PHONE_MAX];
}MyAddr;