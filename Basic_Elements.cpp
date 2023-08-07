//
// Created by 陈劭彬 on 2023/7/26.
//

#include "Basic_Elements.h"
#include "Deployment.h"

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

Character *get_front(const Team_Config *team_config, double time_point)
{
    //switch release hit 组成 rotation
    Character *front = nullptr;
    time_point = (time_point > team_config->rotation_time) ? time_point - team_config->rotation_time : time_point;
    for (auto i: team_config->rotation)
    {
        if (i->attack_time > time_point) break;
        if (i->action == "switch") front = i->c_point;
    }
    return front;
}