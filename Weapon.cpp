//
// Created by 陈劭彬 on 2023/7/25.
//

#include "Weapon.h"

#include <utility>

Weapon::Weapon(string name_,
               string english_name_,
               string weapon_type_,
               int atk_,
               const attribute_data<double> &break_value_,
               int level_)
{
    name = std::move(name_);
    english_name = std::move(english_name_);
    weapon_type = std::move(weapon_type_);
    atk = atk_;
    break_value = break_value_;
    level = level_;
}

int Weapon::get_atk() const
{
    return atk;
}

attribute_data<double> Weapon::get_break(const string &ele_type)
{
    if (ele_type != "物理")
    {
        attribute_data<double> result = break_value;
        result.data["伤害加成"] = 0.0;
        return result;
    }
    else return break_value;
}

Weapon *find_weapon_by_name(const string &name)
{
    for (auto &w: Weapon_list)
        if (w->name == name)
            return w;
    return nullptr;
}

void init_Weapon_list()
{

}