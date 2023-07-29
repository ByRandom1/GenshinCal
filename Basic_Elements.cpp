//
// Created by 陈劭彬 on 2023/7/26.
//

#include "Basic_Elements.h"

bool operator<=(string inf, string target)
{
    return (target == "ALL") || (target.find(inf) != string::npos);
}