//
// Created by 陈劭彬 on 2023/7/25.
//

#include "Weapon.h"

Weapon::Weapon(string name_,
               string english_name_,
               string weapon_type_,
               int atk_,
               attribute_data<double> break_value_,
               int level_)
{
    name = name_;
    english_name = english_name_;
    weapon_type = weapon_type_;
    atk = atk_;
    break_value = break_value_;
    level = level_;
}

int Weapon::get_atk()
{
    return atk;
}

attribute_data<double> Weapon::get_break(string ele_type)
{
    if (ele_type != "物理")
    {
        attribute_data<double> result = break_value;
        result.data["伤害加成"] = 0.0;
        return result;
    }
    else return break_value;
}

Weapon *find_weapon_by_name(string name)
{
    for (auto &w: Weapon_list)
        if (w->name == name)
            return w;
    return nullptr;
}

void init_Weapon_list()
{

}