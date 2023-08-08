//
// Created by 陈劭彬 on 2023/7/26.
//

#include "Basic_Elements.h"

bool operator<=(const string &inf, const string &target)
{
    return target.find(inf) != string::npos;
}

bool check_time_constrain(double buff_start, double buff_end, double attack_time, double rotation_time)
{
    if (buff_start < attack_time && attack_time <= buff_end) return true;
    else if (attack_time <= buff_start && buff_start < attack_time + rotation_time && attack_time + rotation_time <= buff_end) return true;
    else if (buff_end < attack_time && buff_start + rotation_time < attack_time && attack_time <= buff_end + rotation_time) return true;
    return false;
}