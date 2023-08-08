//
// Created by 陈劭彬 on 2023/7/25.
//

#include "Weapon.h"
#include "Deployment.h"

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

string Weapon::get_name()
{ return name; }

string Weapon::get_weapon_type()
{ return weapon_type; }

int Weapon::get_atk() const
{ return atk; }

attribute_data<double> Weapon::get_break(const string &ele_type)
{
    if (ele_type != "物理") return break_value + attribute_data("伤害加成", -break_value.get("伤害加成"));
    else return break_value;
}

tuple<double, double> Weapon::get_recharge(const Single_Attack *single_attack)
{ return make_tuple(0, 0); }

attribute_data<int> Weapon::get_useful_attribute(const Single_Attack *single_attack)
{ return {}; }

tuple<attribute_data<double>, attribute_data<double>> Weapon::get_buff(const Single_Attack *single_attack)
{ return make_tuple(attribute_data<double>(), attribute_data<double>()); }

attribute_data<double> Weapon::get_panel_convert(const Single_Attack *single_attack, attribute_data<double> panel)
{ return {}; }

attribute_data<double> Weapon::get_total_convert(const Single_Attack *single_attack, attribute_data<double> panel)
{ return {}; }

double Weapon::get_extra_rate(const Single_Attack *single_attack, attribute_data<double> panel)
{ return 0; }

double Weapon::get_react_damplus(const Single_Attack *single_attack, string react_type)
{ return 0; }