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

attribute_data<int> Weapon::get_useful_attribute(const Single_Attack *attack_config)
{
    return attribute_data<int>();
}

attribute_data<double> Weapon::get_extra(const Single_Attack *attack_config)
{
    return attribute_data<double>();
}

attribute_data<double> Weapon::get_team(const Single_Attack *attack_config)
{
    return attribute_data<double>();
}

void Weapon::get_recharge_energy(Combination *ori_team[], double &Q_energy_modify, double &energy)
{}

attribute_data<double> Weapon::get_convert(const Single_Attack *attack_config, attribute_data<double> panel)
{
    return attribute_data<double>();
}

double Weapon::get_extra_rate(const Single_Attack *attack_config, attribute_data<double> panel)
{
    return 0;
}

double Weapon::get_react_bonus(const Single_Attack *attack_config, string react_type)
{
    return 0;
}