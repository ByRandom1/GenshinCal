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

tuple<double, double> Weapon::get_recharge(const Single_Attack *single_attack, const Character *owner)
{ return make_tuple(0, 0); }

attribute_data<int> Weapon::get_useful_attribute(const Single_Attack *single_attack, attribute_data<int> useful)
{ return {}; }

tuple<attribute_data<double>, attribute_data<double>> Weapon::get_buff(const Single_Attack *single_attack, const Character *owner)
{ return make_tuple(attribute_data<double>(), attribute_data<double>()); }

attribute_data<double> Weapon::get_panel_convert(const Single_Attack *single_attack, attribute_data<double> panel)
{ return {}; }

attribute_data<double> Weapon::get_total_convert(const Single_Attack *single_attack, attribute_data<double> panel)
{ return {}; }

double Weapon::get_extra_rate(const Single_Attack *single_attack, attribute_data<double> panel)
{ return 0; }

double Weapon::get_react_damplus(const Single_Attack *single_attack, string react_type)
{ return 0; }

Sword_FengYing::Sword_FengYing(int level_) : Weapon("风鹰剑", "aquilafavonia", "单手剑", 674, attribute_data("伤害加成", 0.413), level_)
{}

tuple<attribute_data<double>, attribute_data<double>> Sword_FengYing::get_buff(const Single_Attack *single_attack, const Character *owner)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Weapon::get_buff(single_attack, owner);

    if (single_attack->attack_config->c_point == owner &&
        single_attack->attack_config->action == "hit")
        result = result + attribute_data("攻击力", 0.15 + level * 0.05);

    //后续伤害不建构

    return make_tuple(result, converted);
}

Sword_TianKong::Sword_TianKong(int level_) : Weapon("天空之刃", "skywardSword", "单手剑", 608, attribute_data("元素充能效率", 0.551), level_)
{}

attribute_data<int> Sword_TianKong::get_useful_attribute(const Single_Attack *single_attack, attribute_data<int> useful)
{
    attribute_data<int> result = Weapon::get_useful_attribute(single_attack, useful);

    for (auto i: single_attack->team_config->rotation)
        if (i->c_point == single_attack->attack_config->c_point && i->action == "release" && i->attack_way == "Q")
            if (single_attack->attack_config->action == "hit" &&
                single_attack->attack_config->attack_way <= "平A_重A" &&
                check_time_constrain(i->attack_time, i->attack_time + 12, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
            {
//                if (0.05 * single_attack->base_atk * (0.15 + level * 0.05) >= 0.05 * single_attack->base_atk * single_attack->base_skillrate)
                result = result + attribute_data("攻击力", 1);
                break;
            }

    return result;
}

tuple<attribute_data<double>, attribute_data<double>> Sword_TianKong::get_buff(const Single_Attack *single_attack, const Character *owner)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Weapon::get_buff(single_attack, owner);

    if (single_attack->attack_config->c_point == owner &&
        single_attack->attack_config->action == "hit")
        result = result + attribute_data("暴击率", 0.03 + level * 0.01);

    return make_tuple(result, converted);
}

double Sword_TianKong::get_extra_rate(const Single_Attack *single_attack, attribute_data<double> panel)
{
    double result = Weapon::get_extra_rate(single_attack, panel);

    for (auto i: single_attack->team_config->rotation)
        if (i->c_point == single_attack->attack_config->c_point && i->action == "release" && i->attack_way == "Q")
            if (single_attack->attack_config->action == "hit" &&
                single_attack->attack_config->attack_way <= "平A_重A" &&
                check_time_constrain(i->attack_time, i->attack_time + 12, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
            {
                result = result + (0.15 + level * 0.05) * panel.get("攻击力") * single_attack->base_atk;
                break;
            }

    return result;
}

Sword_DunJian::Sword_DunJian(int level_) : Weapon("斫峰之刃", "summitshaper", "单手剑", 608, attribute_data("攻击力", 0.496), level_)
{}

tuple<attribute_data<double>, attribute_data<double>> Sword_DunJian::get_buff(const Single_Attack *single_attack, const Character *owner)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Weapon::get_buff(single_attack, owner);

    if (single_attack->attack_config->c_point == owner &&
        single_attack->attack_config->action == "hit")
        result = result + attribute_data("护盾强效", 0.15 + level * 0.05);

    double last_hit_time = -0.3;
    int total_level = 0;
    for (auto i: single_attack->team_config->rotation)
        if (i->c_point == owner && i->c_point == single_attack->team_config->get_front(i->attack_time) && i->action == "hit" && i->attack_time >= last_hit_time + 0.3)
        {
            if (single_attack->attack_config->c_point == owner &&
                single_attack->attack_config->action == "hit" &&
                check_time_constrain(i->attack_time, i->attack_time + 8, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time) &&
                total_level < 5)
            {
                if (single_attack->team_config->get_shield(i->attack_time))
                    result = result + attribute_data("攻击力", 0.6 + level * 0.02);
                else
                    result = result + attribute_data("攻击力", 0.3 + level * 0.01);
                total_level += 1;
            }
            last_hit_time = i->attack_time;
        }

    return make_tuple(result, converted);
}

Sword_LvJian::Sword_LvJian(int level_) : Weapon("磐岩结绿", "primordialjadecutter", "单手剑", 542, attribute_data("暴击率", 0.441), level_)
{}

attribute_data<int> Sword_LvJian::get_useful_attribute(const Single_Attack *single_attack, attribute_data<int> useful)
{
    attribute_data<int> result = Weapon::get_useful_attribute(single_attack, useful);

    if (single_attack->attack_config->action == "hit")
        if (useful.get("攻击力") > 0 && 0.05 * (0.009 + level * 0.003) * single_attack->base_life >= 0.05 * single_attack->base_atk)
            result = result + attribute_data("生命值", 1);

    return result;
}

tuple<attribute_data<double>, attribute_data<double>> Sword_LvJian::get_buff(const Single_Attack *single_attack, const Character *owner)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Weapon::get_buff(single_attack, owner);

    if (single_attack->attack_config->c_point == owner &&
        single_attack->attack_config->action == "hit")
        result = result + attribute_data("生命值", 0.15 + level * 0.05);

    return make_tuple(result, converted);
}

attribute_data<double> Sword_LvJian::get_panel_convert(const Single_Attack *single_attack, attribute_data<double> panel)
{
    attribute_data<double> result = Weapon::get_panel_convert(single_attack, panel);

    if (single_attack->attack_config->action == "hit")
        result = result + attribute_data("攻击力", (0.009 + level * 0.003) * panel.get("生命值") * single_attack->base_life / single_attack->base_atk);

    return result;
}

Sword_CangGu::Sword_CangGu(int level_) : Weapon("苍古自由之誓", "freedomsworn", "单手剑", 608, attribute_data("元素精通", 198.0), level_)
{}

tuple<attribute_data<double>, attribute_data<double>> Sword_CangGu::get_buff(const Single_Attack *single_attack, const Character *owner)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Weapon::get_buff(single_attack, owner);

    if (single_attack->attack_config->c_point == owner &&
        single_attack->attack_config->action == "hit")
        result = result + attribute_data("伤害加成", 0.075 + level * 0.025);

    double last_trigger_time = -20;
    double last_hit_time = -0.5;
    int total_level = 0;
    for (auto i: single_attack->team_config->rotation)
        if (i->c_point == owner && i->action == "hit" && !i->react_type.empty() && i->attack_time >= last_hit_time + 0.5 && i->attack_time >= last_trigger_time + 20)
        {
            total_level += 1;
            last_hit_time = i->attack_time;
            if (total_level == 2)
            {
                total_level = 0;
                last_trigger_time = i->attack_time;
                if (single_attack->attack_config->action == "hit" &&
                    check_time_constrain(i->attack_time, i->attack_time + 12, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
                {
                    result = result + attribute_data("攻击力", 0.15 + level * 0.05);//TODO:千年的大乐章数值不叠加
                    if ("A" <= single_attack->attack_config->attack_way)
                        result = result + attribute_data("伤害加成", 0.12 + level * 0.04);
                    break;
                }
            }
        }

    return make_tuple(result, converted);
}

Sword_WuQie::Sword_WuQie(int level_) : Weapon("雾切之回光", "mistsplitterreforged", "单手剑", 674, attribute_data("暴击伤害", 0.441), level_)
{}

tuple<attribute_data<double>, attribute_data<double>> Sword_WuQie::get_buff(const Single_Attack *single_attack, const Character *owner)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Weapon::get_buff(single_attack, owner);

    if (single_attack->attack_config->c_point == owner &&
        single_attack->attack_config->action == "hit" &&
        single_attack->attack_config->c_point->get_attack_ele_type(single_attack) != "物理")
        result = result + attribute_data("伤害加成", 0.09 + level * 0.03);

    int disable_time_before_Q_release = 3;//TODO:更精准地判断元素能量
    int buff[3] = {0, 0, 0};
    auto temp_single_attack = new Single_Attack(single_attack->self, single_attack->team_config, single_attack->attack_config);
    for (auto i: single_attack->team_config->rotation)
    {
        temp_single_attack->attack_config = i;
        if (i->c_point == owner && i->action == "hit" && i->attack_way == "平A" && i->c_point->get_attack_ele_type(temp_single_attack) != "物理")
            if (single_attack->attack_config->c_point == owner &&
                single_attack->attack_config->action == "hit" &&
                check_time_constrain(i->attack_time, i->attack_time + 5, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time) &&
                single_attack->attack_config->c_point->get_attack_ele_type(single_attack) != "物理")
                buff[0] = 1;
        if (i->c_point == owner && i->action == "release" && i->attack_way == "Q")
        {
            if (single_attack->attack_config->c_point == owner &&
                single_attack->attack_config->action == "hit" &&
                check_time_constrain(i->attack_time, i->attack_time + 10, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time) &&
                single_attack->attack_config->c_point->get_attack_ele_type(single_attack) != "物理")
                buff[1] = 1;
            if (single_attack->attack_config->c_point == owner &&
                single_attack->attack_config->action == "hit" &&
                check_time_constrain(i->attack_time, i->attack_time + single_attack->team_config->rotation_time - disable_time_before_Q_release, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time) &&
                single_attack->attack_config->c_point->get_attack_ele_type(single_attack) != "物理")
                buff[2] = 1;
        }
    }
    delete temp_single_attack;

    int total_level = buff[0] + buff[1] + buff[2];
    if (total_level == 3) result = result + attribute_data("攻击力", 0.21 + level * 0.07);
    else if (total_level == 2) result = result + attribute_data("攻击力", 0.12 + level * 0.04);
    else if (total_level == 1) result = result + attribute_data("攻击力", 0.06 + level * 0.02);

    return make_tuple(result, converted);
}

Sword_BoBo::Sword_BoBo(int level_) : Weapon("波乱月白经津", "harangeppakufutsu", "单手剑", 608, attribute_data("暴击率", 0.331), level_)
{}

tuple<attribute_data<double>, attribute_data<double>> Sword_BoBo::get_buff(const Single_Attack *single_attack, const Character *owner)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Weapon::get_buff(single_attack, owner);

    if (single_attack->attack_config->c_point == owner &&
        single_attack->attack_config->action == "hit" &&
        single_attack->attack_config->c_point->get_attack_ele_type(single_attack) != "物理")
        result = result + attribute_data("伤害加成", 0.09 + level * 0.03);

    double last_E_time = -0.3;
    int total_level = 0;
    for (auto i: single_attack->team_config->rotation)
        if (i->c_point != owner && i->action == "release" && i->attack_way == "E" && i->attack_time >= last_E_time + 0.3)
        {
            total_level = min(2, total_level + 1);
            last_E_time = i->attack_time;
        }
    for (auto i: single_attack->team_config->rotation)
        if (i->c_point == owner && i->action == "release" && i->attack_way == "E")
            if (single_attack->attack_config->c_point == owner &&
                single_attack->attack_config->action == "hit" &&
                single_attack->attack_config->attack_way == "平A" &&
                check_time_constrain(i->attack_time, i->attack_time + 8, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
            {
                result = result + attribute_data("伤害加成", total_level * (0.15 + level * 0.05));
                break;
            }

    return make_tuple(result, converted);
}

Sword_ShengXian::Sword_ShengXian(int level_, int typical_life_) : Weapon("圣显之钥", "keyofkhajnisut", "单手剑", 542, attribute_data("生命值", 0.662), level_)
{ typical_life = typical_life_; }

double Sword_ShengXian::get_buff_convert_value(const Single_Attack *single_attack, const Character *owner)
{
    int total_level = 0;
    double last_E_time = -0.3;
    for (auto i: single_attack->team_config->rotation)
        if (i->c_point == owner && i->c_point == single_attack->team_config->get_front(i->attack_time) && i->action == "hit" && i->attack_way == "E" && i->attack_time >= last_E_time + 0.3)
        {
            if (check_time_constrain(i->attack_time, i->attack_time + 20, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
                total_level = min(3, total_level + 1);
            last_E_time = i->attack_time;
        }

    double result = 0;
    if (single_attack->attack_config->c_point == owner &&
        single_attack->attack_config->action == "hit")
        result = result + total_level * (0.0009 + level * 0.0003);
    if (single_attack->attack_config->action == "hit" &&
        total_level == 3)
        result = result + (0.0015 + level * 0.0005);

    return result;
}

attribute_data<int> Sword_ShengXian::get_useful_attribute(const Single_Attack *single_attack, attribute_data<int> useful)
{
    attribute_data<int> result = Weapon::get_useful_attribute(single_attack, useful);

    if (single_attack->attack_config->action == "hit")
        if (useful.get("元素精通") > 0 && 0.05 * get_buff_convert_value(single_attack, single_attack->attack_config->c_point) * single_attack->base_life >= 20.0)
            result = result + attribute_data("生命值", 1);

    return result;
}

tuple<attribute_data<double>, attribute_data<double>> Sword_ShengXian::get_buff(const Single_Attack *single_attack, const Character *owner)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Weapon::get_buff(single_attack, owner);

    if (single_attack->attack_config->c_point == owner &&
        single_attack->attack_config->action == "hit")
        result = result + attribute_data("生命值", 0.15 + level * 0.05);

    if (single_attack->attack_config->c_point != owner &&
        single_attack->attack_config->action == "hit")
        converted = converted + attribute_data("元素精通", get_buff_convert_value(single_attack, owner) * typical_life);

    return make_tuple(result, converted);
}

attribute_data<double> Sword_ShengXian::get_panel_convert(const Single_Attack *single_attack, attribute_data<double> panel)
{
    attribute_data<double> result = Weapon::get_panel_convert(single_attack, panel);

    if (single_attack->attack_config->action == "hit")
        result = result + attribute_data("元素精通", get_buff_convert_value(single_attack, single_attack->attack_config->c_point) * panel.get("生命值") * single_attack->base_life);

    return result;
}

Sword_CaiYe::Sword_CaiYe(int level_) : Weapon("裁叶萃光", "lightoffoliarincision", "单手剑", 542, attribute_data("暴击伤害", 0.882), level_)
{}

attribute_data<int> Sword_CaiYe::get_useful_attribute(const Single_Attack *single_attack, attribute_data<int> useful)
{
    attribute_data<int> result = Weapon::get_useful_attribute(single_attack, useful);

    //TODO:未考虑次数限制
    double last_A_time = -12;
    auto temp_single_attack = new Single_Attack(single_attack->self, single_attack->team_config, single_attack->attack_config);
    for (auto i: single_attack->team_config->rotation)
    {
        temp_single_attack->attack_config = i;
        if (i->c_point == single_attack->attack_config->c_point && i->action == "hit" && i->attack_way == "平A" && i->c_point->get_attack_ele_type(temp_single_attack) != "物理" && i->attack_time >= last_A_time + 12)
        {
            if (single_attack->attack_config->action == "hit" &&
                single_attack->attack_config->attack_way <= "平A_E" &&
                check_time_constrain(i->attack_time, i->attack_time + 12, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
            {
//                if (20.0 * (0.9 + level * 0.3) >= 0.05 * single_attack->base_atk * single_attack->base_skillrate)
                result = result + attribute_data("元素精通", 1);
                break;
            }
            last_A_time = i->attack_time;
        }
    }
    delete temp_single_attack;

    return result;
}

tuple<attribute_data<double>, attribute_data<double>> Sword_CaiYe::get_buff(const Single_Attack *single_attack, const Character *owner)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Weapon::get_buff(single_attack, owner);

    if (single_attack->attack_config->c_point == owner &&
        single_attack->attack_config->action == "hit")
        result = result + attribute_data("暴击率", 0.03 + level * 0.01);

    return make_tuple(result, converted);
}

double Sword_CaiYe::get_extra_rate(const Single_Attack *single_attack, attribute_data<double> panel)
{
    double result = Weapon::get_extra_rate(single_attack, panel);

    //TODO:未考虑次数限制
    double last_A_time = -12;
    auto temp_single_attack = new Single_Attack(single_attack->self, single_attack->team_config, single_attack->attack_config);
    for (auto i: single_attack->team_config->rotation)
    {
        temp_single_attack->attack_config = i;
        if (i->c_point == single_attack->attack_config->c_point && i->action == "hit" && i->attack_way == "平A" && i->c_point->get_attack_ele_type(temp_single_attack) != "物理" && i->attack_time >= last_A_time + 12)
        {
            if (single_attack->attack_config->action == "hit" &&
                single_attack->attack_config->attack_way <= "平A_E" &&
                check_time_constrain(i->attack_time, i->attack_time + 12, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
            {
                result = result + (0.9 + level * 0.3) * panel.get("元素精通");
                break;
            }
            last_A_time = i->attack_time;
        }
    }
    delete temp_single_attack;

    return result;
}

Sword_XiFeng::Sword_XiFeng(int level_) : Weapon("西风剑", "favoniussword", "单手剑", 454, attribute_data("元素充能效率", 0.613), level_)
{}

tuple<double, double> Sword_XiFeng::get_recharge(const Single_Attack *single_attack, const Character *owner)
{
    double Q_energy_modify = 0;
    double energy = 0;
    tie(Q_energy_modify, energy) = Weapon::get_recharge(single_attack, owner);

    //默认暴击且100%概率产球
    double cd = 13.5 - level * 1.5;
    double last_energy_time = -cd;
    for (auto i: single_attack->team_config->rotation)
        if (i->c_point == owner && i->c_point == single_attack->team_config->get_front(i->attack_time) && i->action == "hit" && i->attack_time >= last_energy_time + cd)
        {
            energy += 6 * (owner == single_attack->attack_config->c_point ? 1 : 0.6);
            last_energy_time = i->attack_time;
        }

    return make_tuple(Q_energy_modify, energy);
}

Sword_XiFuSi::Sword_XiFuSi(int level_, double typical_mastery_) : Weapon("西福斯的月光", "xiphosmoonlight", "单手剑", 510, attribute_data("元素精通", 165.0), level_)
{ typical_mastery = typical_mastery_; }

attribute_data<int> Sword_XiFuSi::get_useful_attribute(const Single_Attack *single_attack, attribute_data<int> useful)
{
    attribute_data<int> result = Weapon::get_useful_attribute(single_attack, useful);

    if (single_attack->attack_config->action == "hit")
        if (useful.get("元素充能效率") > 0 && 20.0 * (0.00027 + level * 0.00009) >= 0.055)
            result = result + attribute_data("元素精通", 1);

    return result;
}

tuple<attribute_data<double>, attribute_data<double>> Sword_XiFuSi::get_buff(const Single_Attack *single_attack, const Character *owner)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Weapon::get_buff(single_attack, owner);

    if (single_attack->attack_config->c_point != owner &&
        single_attack->attack_config->action == "hit")
        converted = converted + attribute_data("元素充能效率", 0.3 * (0.00027 + level * 0.00009) * typical_mastery);

    return make_tuple(result, converted);
}

attribute_data<double> Sword_XiFuSi::get_panel_convert(const Single_Attack *single_attack, attribute_data<double> panel)
{
    attribute_data<double> result = Weapon::get_panel_convert(single_attack, panel);

    if (single_attack->attack_config->action == "hit")
        result = result + attribute_data("元素充能效率", (0.00027 + level * 0.00009) * panel.get("元素精通"));

    return result;
}

Claymore_LangMo::Claymore_LangMo(int level_) : Weapon("狼的末路", "wolfsgravestone", "双手剑", 608, attribute_data("攻击力", 0.496), level_)
{}

tuple<attribute_data<double>, attribute_data<double>> Claymore_LangMo::get_buff(const Single_Attack *single_attack, const Character *owner)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Weapon::get_buff(single_attack, owner);

    if (single_attack->attack_config->c_point == owner &&
        single_attack->attack_config->action == "hit")
        result = result + attribute_data("攻击力", 0.15 + level * 0.05);

    return make_tuple(result, converted);
}

Claymore_TianKong::Claymore_TianKong(int level_) : Weapon("天空之傲", "skywardpride", "双手剑", 674, attribute_data("元素充能效率", 0.368), level_)
{}

tuple<attribute_data<double>, attribute_data<double>> Claymore_TianKong::get_buff(const Single_Attack *single_attack, const Character *owner)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Weapon::get_buff(single_attack, owner);

    if (single_attack->attack_config->c_point == owner &&
        single_attack->attack_config->action == "hit")
        result = result + attribute_data("伤害加成", 0.06 + level * 0.02);

    //附加伤害是单独的物理伤害，不考虑

    return make_tuple(result, converted);
}

Claymore_WuGong::Claymore_WuGong(int level_) : Weapon("无工之剑", "theunforged", "双手剑", 608, attribute_data("攻击力", 0.496), level_)
{}

tuple<attribute_data<double>, attribute_data<double>> Claymore_WuGong::get_buff(const Single_Attack *single_attack, const Character *owner)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Weapon::get_buff(single_attack, owner);

    if (single_attack->attack_config->c_point == owner &&
        single_attack->attack_config->action == "hit")
        result = result + attribute_data("护盾强效", 0.15 + level * 0.05);

    double last_hit_time = -0.3;
    int total_level = 0;
    for (auto i: single_attack->team_config->rotation)
        if (i->c_point == owner && i->c_point == single_attack->team_config->get_front(i->attack_time) && i->action == "hit" && i->attack_time >= last_hit_time + 0.3)
        {
            if (single_attack->attack_config->c_point == owner &&
                single_attack->attack_config->action == "hit" &&
                check_time_constrain(i->attack_time, i->attack_time + 8, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time) &&
                total_level < 5)
            {
                if (single_attack->team_config->get_shield(i->attack_time))
                    result = result + attribute_data("攻击力", 0.6 + level * 0.02);
                else
                    result = result + attribute_data("攻击力", 0.3 + level * 0.01);
                total_level += 1;
            }
            last_hit_time = i->attack_time;
        }

    return make_tuple(result, converted);
}

Claymore_SongLai::Claymore_SongLai(int level_) : Weapon("松籁响起之时", "songofbrokenpines", "双手剑", 741, attribute_data("伤害加成", 0.207), level_)
{}

tuple<attribute_data<double>, attribute_data<double>> Claymore_SongLai::get_buff(const Single_Attack *single_attack, const Character *owner)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Weapon::get_buff(single_attack, owner);

    if (single_attack->attack_config->c_point == owner &&
        single_attack->attack_config->action == "hit")
        result = result + attribute_data("攻击力", 0.12 + level * 0.04);

    double last_trigger_time = -20;
    double last_hit_time = -0.3;
    int total_level = 0;
    for (auto i: single_attack->team_config->rotation)
        if (i->c_point == owner && i->action == "hit" && i->attack_way <= "平A_重A" && i->attack_time >= last_hit_time + 0.3 && i->attack_time >= last_trigger_time + 20)
        {
            total_level += 1;
            last_hit_time = i->attack_time;
            if (total_level == 4)
            {
                total_level = 0;
                last_trigger_time = i->attack_time;
                if (single_attack->attack_config->action == "hit" &&
                    check_time_constrain(i->attack_time, i->attack_time + 12, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
                {
                    result = result + attribute_data("攻击力", 0.15 + level * 0.05);//TODO:千年的大乐章数值不叠加
                    break;
                }
            }
        }

    return make_tuple(result, converted);
}

Claymore_ChiJiao::Claymore_ChiJiao(int level_) : Weapon("赤角石溃杵", "redhornstonethresher", "双手剑", 542, attribute_data("暴击伤害", 0.882), level_)
{}

attribute_data<int> Claymore_ChiJiao::get_useful_attribute(const Single_Attack *single_attack, attribute_data<int> useful)
{
    attribute_data<int> result = Weapon::get_useful_attribute(single_attack, useful);

    if (single_attack->attack_config->action == "hit" &&
        single_attack->attack_config->attack_way <= "平A_重A")
//        if (0.062 * (0.3 + level * 0.1) * single_attack->base_def >= 0.05 * single_attack->base_atk * single_attack->base_skillrate)
        result = result + attribute_data("防御力", 1);
    return result;
}

tuple<attribute_data<double>, attribute_data<double>> Claymore_ChiJiao::get_buff(const Single_Attack *single_attack, const Character *owner)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Weapon::get_buff(single_attack, owner);

    if (single_attack->attack_config->c_point == owner &&
        single_attack->attack_config->action == "hit")
        result = result + attribute_data("防御力", 0.21 + level * 0.07);

    return make_tuple(result, converted);
}

double Claymore_ChiJiao::get_extra_rate(const Single_Attack *single_attack, attribute_data<double> panel)
{
    double result = Weapon::get_extra_rate(single_attack, panel);

    if (single_attack->attack_config->action == "hit" &&
        single_attack->attack_config->attack_way <= "平A_重A")
        result = result + (0.3 + level * 0.1) * panel.get("防御力") * single_attack->base_def;

    return result;
}

Claymore_WeiHai::Claymore_WeiHai(int level_) : Weapon("苇海信标", "beaconofthereedsea", "双手剑", 608, attribute_data("暴击率", 0.331), level_)
{}

tuple<attribute_data<double>, attribute_data<double>> Claymore_WeiHai::get_buff(const Single_Attack *single_attack, const Character *owner)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Weapon::get_buff(single_attack, owner);

    for (auto i: single_attack->team_config->rotation)
        if (i->c_point == owner && i->action == "hit" && i->attack_way == "E")
            if (single_attack->attack_config->c_point == owner &&
                single_attack->attack_config->action == "hit" &&
                check_time_constrain(i->attack_time, i->attack_time + 8, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
            {
                result = result + attribute_data("攻击力", 0.15 + level * 0.05);
                break;
            }

    for (auto i: single_attack->team_config->rotation)
        if (i->c_point == owner && i->action == "hp_change" && i->rate_pos < 0)
            if (single_attack->attack_config->c_point == owner &&
                single_attack->attack_config->action == "hit" &&
                check_time_constrain(i->attack_time, i->attack_time + 8, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
            {
                result = result + attribute_data("攻击力", 0.15 + level * 0.05);
                break;
            }

    if (single_attack->attack_config->c_point == owner &&
        single_attack->attack_config->action == "hit" &&
        !single_attack->team_config->get_shield(single_attack->attack_config->attack_time))
        result = result + attribute_data("生命值", 0.24 + level * 0.08);

    return make_tuple(result, converted);
}

Claymore_XiFeng::Claymore_XiFeng(int level_) : Weapon("西风大剑", "favoniusgreatsword", "双手剑", 454, attribute_data("元素充能效率", 0.613), level_)
{}

tuple<double, double> Claymore_XiFeng::get_recharge(const Single_Attack *single_attack, const Character *owner)
{
    double Q_energy_modify = 0;
    double energy = 0;
    tie(Q_energy_modify, energy) = Weapon::get_recharge(single_attack, owner);

    //默认暴击且100%概率产球
    double cd = 13.5 - level * 1.5;
    double last_energy_time = -cd;
    for (auto i: single_attack->team_config->rotation)
        if (i->c_point == owner && i->c_point == single_attack->team_config->get_front(i->attack_time) && i->action == "hit" && i->attack_time >= last_energy_time + cd)
        {
            energy += 6 * (owner == single_attack->attack_config->c_point ? 1 : 0.6);
            last_energy_time = i->attack_time;
        }

    return make_tuple(Q_energy_modify, energy);
}

Claymore_MaHaiLa::Claymore_MaHaiLa(int level_, double typical_mastery_) : Weapon("玛海菈的水色", "makhairaaquamarine", "双手剑", 510, attribute_data("元素精通", 165.0), level_)
{ typical_mastery = typical_mastery_; }

attribute_data<int> Claymore_MaHaiLa::get_useful_attribute(const Single_Attack *single_attack, attribute_data<int> useful)
{
    attribute_data<int> result = Weapon::get_useful_attribute(single_attack, useful);

    if (single_attack->attack_config->action == "hit")
        if (useful.get("攻击力") > 0 && 20.0 * (0.18 + level * 0.06) >= 0.05 * single_attack->base_atk)
            result = result + attribute_data("元素精通", 1);

    return result;
}

tuple<attribute_data<double>, attribute_data<double>> Claymore_MaHaiLa::get_buff(const Single_Attack *single_attack, const Character *owner)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Weapon::get_buff(single_attack, owner);

    if (single_attack->attack_config->c_point != owner &&
        single_attack->attack_config->action == "hit")
        converted = converted + attribute_data("攻击力", 0.3 * (0.18 + level * 0.06) * typical_mastery / single_attack->base_atk);

    return make_tuple(result, converted);
}

attribute_data<double> Claymore_MaHaiLa::get_panel_convert(const Single_Attack *single_attack, attribute_data<double> panel)
{
    attribute_data<double> result = Weapon::get_panel_convert(single_attack, panel);

    if (single_attack->attack_config->action == "hit")
        result = result + attribute_data("攻击力", (0.18 + level * 0.06) * panel.get("元素精通") / single_attack->base_atk);

    return result;
}

Polearm_HePuYuan::Polearm_HePuYuan(int level_) : Weapon("和璞鸢", "primordialjadewingedspear", "长柄武器", 674, attribute_data("暴击率", 0.221), level_)
{}

tuple<attribute_data<double>, attribute_data<double>> Polearm_HePuYuan::get_buff(const Single_Attack *single_attack, const Character *owner)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Weapon::get_buff(single_attack, owner);

    double last_hit_time = -0.3;
    int total_level = 0;
    for (auto i: single_attack->team_config->rotation)
        if (i->c_point == owner && i->c_point == single_attack->team_config->get_front(i->attack_time) && i->action == "hit" && i->attack_time >= last_hit_time + 0.3)
        {
            if (single_attack->attack_config->c_point == owner &&
                single_attack->attack_config->action == "hit" &&
                check_time_constrain(i->attack_time, i->attack_time + 6, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time) &&
                total_level < 7)
            {
                result = result + attribute_data("攻击力", 0.025 + level * 0.007);
                total_level += 1;
                if (total_level == 7)
                {
                    result = result + attribute_data("伤害加成", 0.09 + level * 0.03);
                    break;
                }
            }
            last_hit_time = i->attack_time;
        }

    return make_tuple(result, converted);
}

Polearm_TianKong::Polearm_TianKong(int level_) : Weapon("天空之脊", "skywardspine", "长柄武器", 674, attribute_data("元素充能效率", 0.368), level_)
{}

tuple<attribute_data<double>, attribute_data<double>> Polearm_TianKong::get_buff(const Single_Attack *single_attack, const Character *owner)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Weapon::get_buff(single_attack, owner);

    if (single_attack->attack_config->c_point == owner &&
        single_attack->attack_config->action == "hit")
        result = result + attribute_data("暴击率", 0.06 + level * 0.02);

    //附加伤害不考虑

    return make_tuple(result, converted);
}

Polearm_DunQiang::Polearm_DunQiang(int level_) : Weapon("贯虹之槊", "vortexvanquisher", "长柄武器", 608, attribute_data("攻击力", 0.496), level_)
{}

tuple<attribute_data<double>, attribute_data<double>> Polearm_DunQiang::get_buff(const Single_Attack *single_attack, const Character *owner)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Weapon::get_buff(single_attack, owner);

    if (single_attack->attack_config->c_point == owner &&
        single_attack->attack_config->action == "hit")
        result = result + attribute_data("护盾强效", 0.15 + level * 0.05);

    double last_hit_time = -0.3;
    int total_level = 0;
    for (auto i: single_attack->team_config->rotation)
        if (i->c_point == owner && i->c_point == single_attack->team_config->get_front(i->attack_time) && i->action == "hit" && i->attack_time >= last_hit_time + 0.3)
        {
            if (single_attack->attack_config->c_point == owner &&
                single_attack->attack_config->action == "hit" &&
                check_time_constrain(i->attack_time, i->attack_time + 8, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time) &&
                total_level < 5)
            {
                if (single_attack->team_config->get_shield(i->attack_time))
                    result = result + attribute_data("攻击力", 0.6 + level * 0.02);
                else
                    result = result + attribute_data("攻击力", 0.3 + level * 0.01);
                total_level += 1;
            }
            last_hit_time = i->attack_time;
        }

    return make_tuple(result, converted);
}

Polearm_HuMo::Polearm_HuMo(int level_) : Weapon("护摩之杖", "staffofhoma", "长柄武器", 608, attribute_data("暴击伤害", 0.662), level_)
{}

attribute_data<int> Polearm_HuMo::get_useful_attribute(const Single_Attack *single_attack, attribute_data<int> useful)
{
    attribute_data<int> result = Weapon::get_useful_attribute(single_attack, useful);

    int life_change = 0;
    for (auto i: single_attack->team_config->rotation)
        if (i->action == "hp_change")
            life_change += i->rate_pos;

    if (single_attack->attack_config->action == "hit")
        if (useful.get("攻击力") > 0 && 0.05 * ((0.006 + level * 0.002) + (life_change < 0 ? (0.008 + level * 0.002) : 0)) * single_attack->base_life >= 0.05 * single_attack->base_atk)
            result = result + attribute_data("生命值", 1);

    return result;
}

tuple<attribute_data<double>, attribute_data<double>> Polearm_HuMo::get_buff(const Single_Attack *single_attack, const Character *owner)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Weapon::get_buff(single_attack, owner);

    if (single_attack->attack_config->c_point == owner &&
        single_attack->attack_config->action == "hit")
        result = result + attribute_data("生命值", 0.15 + level * 0.05);

    return make_tuple(result, converted);
}

attribute_data<double> Polearm_HuMo::get_panel_convert(const Single_Attack *single_attack, attribute_data<double> panel)
{
    attribute_data<double> result = Weapon::get_panel_convert(single_attack, panel);

    if (single_attack->attack_config->action == "hit")
        result = result + attribute_data("攻击力", (0.006 + level * 0.002) * panel.get("生命值") * single_attack->base_life / single_attack->base_atk);

    int life_change = 0;
    for (auto i: single_attack->team_config->rotation)
        if (i->action == "hp_change")
            life_change += i->rate_pos;
    if (single_attack->attack_config->action == "hit" &&
        life_change < 0)
        result = result + attribute_data("攻击力", (0.008 + level * 0.002) * panel.get("生命值") * single_attack->base_life / single_attack->base_atk);

    return result;
}

Polearm_TiDao::Polearm_TiDao(int level_) : Weapon("薙草之稻光", "engulfinglightning", "长柄武器", 608, attribute_data("元素充能效率", 0.551), level_)
{}

attribute_data<int> Polearm_TiDao::get_useful_attribute(const Single_Attack *single_attack, attribute_data<int> useful)
{
    attribute_data<int> result = Weapon::get_useful_attribute(single_attack, useful);

    if (single_attack->attack_config->action == "hit")
        if (useful.get("攻击力") > 0 && 0.055 * (0.21 + level * 0.07) >= 0.05)
            result = result + attribute_data("元素充能效率", 1);

    return result;
}

tuple<attribute_data<double>, attribute_data<double>> Polearm_TiDao::get_buff(const Single_Attack *single_attack, const Character *owner)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Weapon::get_buff(single_attack, owner);

    for (auto i: single_attack->team_config->rotation)
        if (i->c_point == owner && i->action == "release" && i->attack_way == "Q")
            if (single_attack->attack_config->c_point == owner &&
                single_attack->attack_config->action == "hit" &&
                check_time_constrain(i->attack_time, i->attack_time + 12, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
            {
                result = result + attribute_data("元素充能效率", 0.25 + level * 0.05);
                break;
            }

    return make_tuple(result, converted);
}

attribute_data<double> Polearm_TiDao::get_panel_convert(const Single_Attack *single_attack, attribute_data<double> panel)
{
    attribute_data<double> result = Weapon::get_panel_convert(single_attack, panel);

    if (single_attack->attack_config->action == "hit")
        result = result + attribute_data("攻击力", min((0.21 + level * 0.07) * (panel.get("元素充能效率") - 1), 0.7 + level * 0.1));

    return result;
}

Polearm_XiZai::Polearm_XiZai(int level_) : Weapon("息灾", "calamityqueller", "长柄武器", 741, attribute_data("攻击力", 0.165), level_)
{}

tuple<attribute_data<double>, attribute_data<double>> Polearm_XiZai::get_buff(const Single_Attack *single_attack, const Character *owner)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Weapon::get_buff(single_attack, owner);

    if (single_attack->attack_config->c_point == owner &&
        single_attack->attack_config->action == "hit" &&
        single_attack->attack_config->c_point->get_attack_ele_type(single_attack) != "物理")
        result = result + attribute_data("伤害加成", 0.09 + level * 0.03);

    for (auto i: single_attack->team_config->rotation)
        if (i->c_point == owner && i->action == "release" && i->attack_way == "E")
            if (single_attack->attack_config->c_point == owner &&
                single_attack->attack_config->action == "hit" &&
                check_time_constrain(i->attack_time, i->attack_time + 20, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
            {
                double time_diff;
                if (single_attack->attack_config->attack_time < i->attack_time)
                    time_diff = single_attack->attack_config->attack_time + single_attack->team_config->rotation_time - i->attack_time;
                else if (single_attack->attack_config->attack_time > i->attack_time + 20)
                    time_diff = single_attack->attack_config->attack_time - single_attack->team_config->rotation_time - i->attack_time;
                else
                    time_diff = single_attack->attack_config->attack_time - i->attack_time;

                if (single_attack->attack_config->c_point != single_attack->team_config->get_front(single_attack->attack_config->attack_time))
                    result = result + attribute_data("攻击力", 2 * min(6, (int) time_diff) * (0.024 + level * 0.008));
                else
                    result = result + attribute_data("攻击力", min(6, (int) time_diff) * (0.024 + level * 0.008));

                break;
            }

    return make_tuple(result, converted);
}

Polearm_ChuanJiang::Polearm_ChuanJiang(int level_) : Weapon("赤沙之杖", "staffofthescarletsands", "长柄武器", 542, attribute_data("暴击率", 0.441), level_)
{}

attribute_data<int> Polearm_ChuanJiang::get_useful_attribute(const Single_Attack *single_attack, attribute_data<int> useful)
{
    attribute_data<int> result = Weapon::get_useful_attribute(single_attack, useful);

    int total_level = 0;
    for (auto i: single_attack->team_config->rotation)
        if (i->c_point == single_attack->attack_config->c_point && i->c_point == single_attack->team_config->get_front(i->attack_time) && i->action == "hit" && i->attack_way == "E")
            if (single_attack->attack_config->action == "hit" &&
                check_time_constrain(i->attack_time, i->attack_time + 10, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time) &&
                total_level < 3)
            {
                total_level += 1;
            }

    if (single_attack->attack_config->action == "hit")
        if (useful.get("攻击力") > 0 && 20.0 * ((0.39 + level * 0.13) + total_level * (0.21 + level * 0.07)) >= 0.05 * single_attack->base_atk)
            result = result + attribute_data("元素精通", 1);

    return result;
}

attribute_data<double> Polearm_ChuanJiang::get_panel_convert(const Single_Attack *single_attack, attribute_data<double> panel)
{
    attribute_data<double> result = Weapon::get_panel_convert(single_attack, panel);

    if (single_attack->attack_config->action == "hit")
        result = result + attribute_data("攻击力", (0.39 + level * 0.13) * panel.get("元素精通") / single_attack->base_atk);

    int total_level = 0;
    for (auto i: single_attack->team_config->rotation)
        if (i->c_point == single_attack->attack_config->c_point && i->c_point == single_attack->team_config->get_front(i->attack_time) && i->action == "hit" && i->attack_way == "E")
            if (single_attack->attack_config->action == "hit" &&
                check_time_constrain(i->attack_time, i->attack_time + 10, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time) &&
                total_level < 3)
            {
                result = result + attribute_data("攻击力", (0.21 + level * 0.07) * panel.get("元素精通") / single_attack->base_atk);
                total_level += 1;
            }

    return result;
}

Polearm_XiFeng::Polearm_XiFeng(int level_) : Weapon("西风长枪", "favoniuslance", "长柄武器", 565, attribute_data("元素充能效率", 0.306), level_)
{}

tuple<double, double> Polearm_XiFeng::get_recharge(const Single_Attack *single_attack, const Character *owner)
{
    double Q_energy_modify = 0;
    double energy = 0;
    tie(Q_energy_modify, energy) = Weapon::get_recharge(single_attack, owner);

    //默认暴击且100%概率产球
    double cd = 13.5 - level * 1.5;
    double last_energy_time = -cd;
    for (auto i: single_attack->team_config->rotation)
        if (i->c_point == owner && i->c_point == single_attack->team_config->get_front(i->attack_time) && i->action == "hit" && i->attack_time >= last_energy_time + cd)
        {
            energy += 6 * (owner == single_attack->attack_config->c_point ? 1 : 0.6);
            last_energy_time = i->attack_time;
        }

    return make_tuple(Q_energy_modify, energy);
}

Catalyst_SiFeng::Catalyst_SiFeng(int level_) : Weapon("四风原典", "lostprayertothesacredwinds", "法器", 608, attribute_data("暴击率", 0.331), level_)
{}

tuple<attribute_data<double>, attribute_data<double>> Catalyst_SiFeng::get_buff(const Single_Attack *single_attack, const Character *owner)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Weapon::get_buff(single_attack, owner);

    double min_time = single_attack->team_config->rotation_time;
    for (auto i: single_attack->team_config->rotation)
    {
        if (i->c_point == owner && i->action == "switch") min_time = i->attack_time;
        if (i->c_point != owner && i->action == "switch") min_time = -1;
        if (i == single_attack->attack_config) break;
    }
    if (single_attack->attack_config->c_point == owner &&
        single_attack->attack_config->action == "hit" &&
        single_attack->attack_config->c_point->get_attack_ele_type(single_attack) != "物理" &&
        min_time != -1)
    {
        result = result + attribute_data("伤害加成", min((int) ((single_attack->attack_config->attack_time - min_time) / 4), 4) * (0.06 + level * 0.02));
    }

    return make_tuple(result, converted);
}

Catalyst_TianKong::Catalyst_TianKong(int level_) : Weapon("天空之卷", "skywardatlas", "法器", 674, attribute_data("攻击力", 0.331), level_)
{}

tuple<attribute_data<double>, attribute_data<double>> Catalyst_TianKong::get_buff(const Single_Attack *single_attack, const Character *owner)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Weapon::get_buff(single_attack, owner);

    if (single_attack->attack_config->c_point == owner &&
        single_attack->attack_config->action == "hit" &&
        single_attack->attack_config->c_point->get_attack_ele_type(single_attack) != "物理")
        result = result + attribute_data("伤害加成", 0.09 + level * 0.03);

    //附加伤害是单独的物理伤害，不考虑

    return make_tuple(result, converted);
}

Catalyst_DunSuo::Catalyst_DunSuo(int level_) : Weapon("尘世之锁", "memoryofdust", "法器", 608, attribute_data("攻击力", 0.496), level_)
{}

tuple<attribute_data<double>, attribute_data<double>> Catalyst_DunSuo::get_buff(const Single_Attack *single_attack, const Character *owner)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Weapon::get_buff(single_attack, owner);

    if (single_attack->attack_config->c_point == owner &&
        single_attack->attack_config->action == "hit")
        result = result + attribute_data("护盾强效", 0.15 + level * 0.05);

    double last_hit_time = -0.3;
    int total_level = 0;
    for (auto i: single_attack->team_config->rotation)
        if (i->c_point == owner && i->c_point == single_attack->team_config->get_front(i->attack_time) && i->action == "hit" && i->attack_time >= last_hit_time + 0.3)
        {
            if (single_attack->attack_config->c_point == owner &&
                single_attack->attack_config->action == "hit" &&
                check_time_constrain(i->attack_time, i->attack_time + 8, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time) &&
                total_level < 5)
            {
                if (single_attack->team_config->get_shield(i->attack_time))
                    result = result + attribute_data("攻击力", 0.6 + level * 0.02);
                else
                    result = result + attribute_data("攻击力", 0.3 + level * 0.01);
                total_level += 1;
            }
            last_hit_time = i->attack_time;
        }

    return make_tuple(result, converted);
}

Catalyst_YueHua::Catalyst_YueHua(int level_) : Weapon("不灭月华", "everlastingmoonglow", "法器", 608, attribute_data("生命值", 0.496), level_)
{}

tuple<double, double> Catalyst_YueHua::get_recharge(const Single_Attack *single_attack, const Character *owner)
{
    double Q_energy_modify = 0;
    double energy = 0;
    tie(Q_energy_modify, energy) = Weapon::get_recharge(single_attack, owner);

    if (single_attack->attack_config->c_point == owner)
    {
        vector<double> buff_time;
        for (auto i: single_attack->team_config->rotation)
            if (i->c_point == owner && i->action == "release" && i->attack_way == "Q")
                buff_time.push_back(i->attack_time);
        double last_hit_time = -0.1;
        for (auto i: single_attack->team_config->rotation)
            if (i->c_point == owner && i->action == "hit" && i->attack_way == "平A" && i->attack_time >= last_hit_time + 0.1)
                for (auto j: buff_time)
                    if (check_time_constrain(j, j + 12, i->attack_time, single_attack->team_config->rotation_time))
                    {
                        Q_energy_modify -= 0.6;
                        last_hit_time = i->attack_time;
                        break;
                    }
    }

    return make_tuple(Q_energy_modify, energy);
}

attribute_data<int> Catalyst_YueHua::get_useful_attribute(const Single_Attack *single_attack, attribute_data<int> useful)
{
    attribute_data<int> result = Weapon::get_useful_attribute(single_attack, useful);

    if (single_attack->attack_config->action == "hit" &&
        single_attack->attack_config->attack_way == "平A")
//        if (0.05 * (0.005 + level * 0.005) * single_attack->base_life >= 0.05 * single_attack->base_skillrate * single_attack->base_atk)
        result = result + attribute_data("生命值", 1);

    return result;
}

tuple<attribute_data<double>, attribute_data<double>> Catalyst_YueHua::get_buff(const Single_Attack *single_attack, const Character *owner)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Weapon::get_buff(single_attack, owner);

    if (single_attack->attack_config->c_point == owner &&
        single_attack->attack_config->action == "hit")
        result = result + attribute_data("治疗加成", 0.075 + level * 0.025);

    return make_tuple(result, converted);
}

double Catalyst_YueHua::get_extra_rate(const Single_Attack *single_attack, attribute_data<double> panel)
{
    double result = Weapon::get_extra_rate(single_attack, panel);

    if (single_attack->attack_config->action == "hit" &&
        single_attack->attack_config->attack_way == "平A")
        result = result + (0.005 + level * 0.005) * panel.get("生命值") * single_attack->base_life;

    return result;
}

Catalyst_ShenLe::Catalyst_ShenLe(int level_) : Weapon("神乐之真意", "kagurasverity", "法器", 608, attribute_data("暴击伤害", 0.662), level_)
{}

tuple<attribute_data<double>, attribute_data<double>> Catalyst_ShenLe::get_buff(const Single_Attack *single_attack, const Character *owner)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Weapon::get_buff(single_attack, owner);

    int total_level = 0;
    for (auto i: single_attack->team_config->rotation)
        if (i->c_point == owner && i->action == "release" && i->attack_way == "E")
            if (single_attack->attack_config->c_point == owner &&
                single_attack->attack_config->action == "hit" &&
                check_time_constrain(i->attack_time, i->attack_time + 16, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time) &&
                total_level < 3)
            {
                if (single_attack->attack_config->attack_way == "E")
                    result = result + attribute_data("伤害加成", 0.09 + level * 0.03);
                total_level += 1;
                if (total_level == 3 &&
                    single_attack->attack_config->c_point->get_attack_ele_type(single_attack) != "物理")
                {
                    result = result + attribute_data("伤害加成", 0.09 + level * 0.03);
                    break;
                }
            }

    return make_tuple(result, converted);
}

Catalyst_QianYe::Catalyst_QianYe(int level_) : Weapon("千夜浮梦", "athousandfloatingdreams", "法器", 542, attribute_data("元素精通", 265.0), level_)
{}

tuple<attribute_data<double>, attribute_data<double>> Catalyst_QianYe::get_buff(const Single_Attack *single_attack, const Character *owner)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Weapon::get_buff(single_attack, owner);

    int diff_ele_num = 0;
    if (single_attack->team_config->team[0]->c_point->get_ele_type() != owner->get_ele_type())
        diff_ele_num += 1;
    if (single_attack->team_config->team[1]->c_point->get_ele_type() != owner->get_ele_type())
        diff_ele_num += 1;
    if (single_attack->team_config->team[2]->c_point->get_ele_type() != owner->get_ele_type())
        diff_ele_num += 1;
    if (single_attack->team_config->team[3]->c_point->get_ele_type() != owner->get_ele_type())
        diff_ele_num += 1;

    if (single_attack->attack_config->c_point == owner &&
        single_attack->attack_config->action == "hit")
    {
        result = result + attribute_data("元素精通", (24.0 + level * 8.0) * (3 - diff_ele_num));
        if (single_attack->attack_config->c_point->get_attack_ele_type(single_attack) == single_attack->attack_config->c_point->get_ele_type())
            result = result + attribute_data("伤害加成", (0.06 + level * 0.04) * diff_ele_num);
    }

    if (single_attack->attack_config->c_point != owner &&
        single_attack->attack_config->action == "hit")
        result = result + attribute_data("元素精通", (38.0 + level * 2.0));

    return make_tuple(result, converted);
}

Catalyst_HuiYi::Catalyst_HuiYi(int level_) : Weapon("图莱杜拉的回忆", "tulaytullahsremembrance", "法器", 674, attribute_data("暴击伤害", 0.441), level_)
{}

tuple<attribute_data<double>, attribute_data<double>> Catalyst_HuiYi::get_buff(const Single_Attack *single_attack, const Character *owner)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Weapon::get_buff(single_attack, owner);

    double last_hit_time = -0.3;
    int total_level = -1;
    double buff_time = -1;
    for (auto i: single_attack->team_config->rotation)
    {
        if (buff_time != -1 && i->attack_time > buff_time + 14)
        {
            total_level = -1;
            buff_time = -1;
        }
        if (buff_time != -1 &&
            i == single_attack->attack_config &&
            single_attack->attack_config->c_point == owner &&
            single_attack->attack_config->action == "hit" &&
            single_attack->attack_config->attack_way == "平A")
        {
            result = result + attribute_data("伤害加成", min((0.36 + level * 0.12), ((0.036 + level * 0.012) * (int) (single_attack->attack_config->attack_time - buff_time) + (0.072 + level * 0.024) * total_level)));
            break;
        }
        if (buff_time != -1 && i->c_point != owner && i->action == "switch")
        {
            total_level = -1;
            buff_time = -1;
        }
        if (i->c_point == owner && i->action == "release" && i->attack_way == "E")
        {
            total_level = 0;
            buff_time = i->attack_time;
        }
        if (buff_time != -1 && i->c_point == owner && i->action == "hit" && i->attack_way == "平A" && i->attack_time >= last_hit_time + 0.3)
        {
            total_level += 1;
        }
    }

    return make_tuple(result, converted);
}

Catalyst_BiLuo::Catalyst_BiLuo(int level_) : Weapon("碧落之珑", "jadefallssplendor", "法器", 608, attribute_data("生命值", 0.496), level_)
{}

tuple<double, double> Catalyst_BiLuo::get_recharge(const Single_Attack *single_attack, const Character *owner)
{
    double Q_energy_modify = 0;
    double energy = 0;
    tie(Q_energy_modify, energy) = Weapon::get_recharge(single_attack, owner);

    //TODO:未考虑创造护盾
    if (single_attack->attack_config->c_point == owner)
        for (auto i: single_attack->team_config->rotation)
            if (i->c_point == owner && i->action == "release" && i->attack_way == "Q")
                Q_energy_modify -= (4 + level * 0.5);

    return make_tuple(Q_energy_modify, energy);
}

attribute_data<int> Catalyst_BiLuo::get_useful_attribute(const Single_Attack *single_attack, attribute_data<int> useful)
{
    attribute_data<int> result = Weapon::get_useful_attribute(single_attack, useful);

    //TODO:未考虑创造护盾
    for (auto i: single_attack->team_config->rotation)
        if (i->c_point == single_attack->attack_config->c_point && i->action == "release" && i->attack_way == "Q")
            if (single_attack->attack_config->action == "hit" &&
                check_time_constrain(i->attack_time, i->attack_time + 3, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time) &&
                single_attack->attack_config->c_point->get_attack_ele_type(single_attack) == single_attack->attack_config->c_point->get_ele_type())
            {
                if (useful.get("伤害加成") > 0)
                    result = result + attribute_data("生命值", 1);
                break;
            }

    return result;
}

attribute_data<double> Catalyst_BiLuo::get_panel_convert(const Single_Attack *single_attack, attribute_data<double> panel)
{
    attribute_data<double> result = Weapon::get_panel_convert(single_attack, panel);

    //TODO:未考虑创造护盾
    for (auto i: single_attack->team_config->rotation)
        if (i->c_point == single_attack->attack_config->c_point && i->action == "release" && i->attack_way == "Q")
            if (single_attack->attack_config->action == "hit" &&
                check_time_constrain(i->attack_time, i->attack_time + 3, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time) &&
                single_attack->attack_config->c_point->get_attack_ele_type(single_attack) == single_attack->attack_config->c_point->get_ele_type())
            {
                result = result + attribute_data("伤害加成", min((0.04 + level * 0.08), (0.001 + level * 0.002) * panel.get("生命值") * single_attack->base_life / 1000.0));
                break;
            }

    return result;
}

Catalyst_XiFeng::Catalyst_XiFeng(int level_) : Weapon("西风秘典", "favoniuscodex", "法器", 510, attribute_data("元素充能效率", 0.459), level_)
{}

tuple<double, double> Catalyst_XiFeng::get_recharge(const Single_Attack *single_attack, const Character *owner)
{
    double Q_energy_modify = 0;
    double energy = 0;
    tie(Q_energy_modify, energy) = Weapon::get_recharge(single_attack, owner);

    //默认暴击且100%概率产球
    double cd = 13.5 - level * 1.5;
    double last_energy_time = -cd;
    for (auto i: single_attack->team_config->rotation)
        if (i->c_point == owner && i->c_point == single_attack->team_config->get_front(i->attack_time) && i->action == "hit" && i->attack_time >= last_energy_time + cd)
        {
            energy += 6 * (owner == single_attack->attack_config->c_point ? 1 : 0.6);
            last_energy_time = i->attack_time;
        }

    return make_tuple(Q_energy_modify, energy);
}

Catalyst_BaiChen::Catalyst_BaiChen(int level_) : Weapon("白辰之环", "hakushinring", "法器", 565, attribute_data("元素充能效率", 0.306), level_)
{}

tuple<attribute_data<double>, attribute_data<double>> Catalyst_BaiChen::get_buff(const Single_Attack *single_attack, const Character *owner)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Weapon::get_buff(single_attack, owner);

    double last_react_time = -6;
    for (auto i: single_attack->team_config->rotation)
        if (i->c_point == owner && i->action == "hit" && i->attack_time >= last_react_time + 6)
        {
            if ("激化" <= i->react_type)
            {
                if (single_attack->attack_config->action == "hit" &&
                    check_time_constrain(i->attack_time, i->attack_time + 6, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time) &&
                    single_attack->attack_config->c_point->get_ele_type() <= "草_雷" &&
                    single_attack->attack_config->c_point->get_attack_ele_type(single_attack) == single_attack->attack_config->c_point->get_ele_type())
                {
                    result = result + attribute_data("伤害加成", (0.075 + level * 0.025));
                    break;
                }
                last_react_time = i->attack_time;
            }
            else if ("感电" <= i->react_type)
            {
                if (single_attack->attack_config->action == "hit" &&
                    check_time_constrain(i->attack_time, i->attack_time + 6, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time) &&
                    single_attack->attack_config->c_point->get_ele_type() <= "水_雷" &&
                    single_attack->attack_config->c_point->get_attack_ele_type(single_attack) == single_attack->attack_config->c_point->get_ele_type())
                {
                    result = result + attribute_data("伤害加成", (0.075 + level * 0.025));
                    break;
                }
                last_react_time = i->attack_time;
            }
            else if ("超载" <= i->react_type)
            {
                if (single_attack->attack_config->action == "hit" &&
                    check_time_constrain(i->attack_time, i->attack_time + 6, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time) &&
                    single_attack->attack_config->c_point->get_ele_type() <= "火_雷" &&
                    single_attack->attack_config->c_point->get_attack_ele_type(single_attack) == single_attack->attack_config->c_point->get_ele_type())
                {
                    result = result + attribute_data("伤害加成", (0.075 + level * 0.025));
                    break;
                }
                last_react_time = i->attack_time;
            }
            else if ("超导" <= i->react_type)
            {
                if (single_attack->attack_config->action == "hit" &&
                    check_time_constrain(i->attack_time, i->attack_time + 6, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time) &&
                    single_attack->attack_config->c_point->get_ele_type() <= "冰_雷" &&
                    single_attack->attack_config->c_point->get_attack_ele_type(single_attack) == single_attack->attack_config->c_point->get_ele_type())
                {
                    result = result + attribute_data("伤害加成", (0.075 + level * 0.025));
                    break;
                }
                last_react_time = i->attack_time;
            }
            else if ("扩散" <= i->react_type)
            {
                if (single_attack->attack_config->action == "hit" &&
                    check_time_constrain(i->attack_time, i->attack_time + 6, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time) &&
                    single_attack->attack_config->c_point->get_ele_type() <= "风_雷" &&
                    single_attack->attack_config->c_point->get_attack_ele_type(single_attack) == single_attack->attack_config->c_point->get_ele_type())
                {
                    result = result + attribute_data("伤害加成", (0.075 + level * 0.025));
                    break;
                }
                last_react_time = i->attack_time;
            }
            else if ("结晶" <= i->react_type)
            {
                if (single_attack->attack_config->action == "hit" &&
                    check_time_constrain(i->attack_time, i->attack_time + 6, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time) &&
                    single_attack->attack_config->c_point->get_ele_type() <= "岩_雷" &&
                    single_attack->attack_config->c_point->get_attack_ele_type(single_attack) == single_attack->attack_config->c_point->get_ele_type())
                {
                    result = result + attribute_data("伤害加成", (0.075 + level * 0.025));
                    break;
                }
                last_react_time = i->attack_time;
            }
        }

    return make_tuple(result, converted);
}

Catalyst_WanXing::Catalyst_WanXing(int level_, double typical_mastery_) : Weapon("流浪的晚星", "wanderingevenstar", "法器", 510, attribute_data("元素精通", 165.0), level_)
{ typical_mastery = typical_mastery_; }

attribute_data<int> Catalyst_WanXing::get_useful_attribute(const Single_Attack *single_attack, attribute_data<int> useful)
{
    attribute_data<int> result = Weapon::get_useful_attribute(single_attack, useful);

    if (single_attack->attack_config->action == "hit")
        if (useful.get("攻击力") > 0 && 20.0 * (0.18 + level * 0.06) >= 0.05 * single_attack->base_atk)
            result = result + attribute_data("元素精通", 1);

    return result;
}

tuple<attribute_data<double>, attribute_data<double>> Catalyst_WanXing::get_buff(const Single_Attack *single_attack, const Character *owner)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Weapon::get_buff(single_attack, owner);

    if (single_attack->attack_config->c_point != owner &&
        single_attack->attack_config->action == "hit")
        converted = converted + attribute_data("攻击力", 0.3 * (0.18 + level * 0.06) * typical_mastery / single_attack->base_atk);

    return make_tuple(result, converted);
}

attribute_data<double> Catalyst_WanXing::get_panel_convert(const Single_Attack *single_attack, attribute_data<double> panel)
{
    attribute_data<double> result = Weapon::get_panel_convert(single_attack, panel);

    if (single_attack->attack_config->action == "hit")
        result = result + attribute_data("攻击力", (0.18 + level * 0.06) * panel.get("元素精通") / single_attack->base_atk);

    return result;
}

Bow_AMS::Bow_AMS(int level_) : Weapon("阿莫斯之弓", "amosbow", "弓", 608, attribute_data("攻击力", 0.496), level_)
{}

tuple<attribute_data<double>, attribute_data<double>> Bow_AMS::get_buff(const Single_Attack *single_attack, const Character *owner)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Weapon::get_buff(single_attack, owner);

    if (single_attack->attack_config->c_point == owner &&
        single_attack->attack_config->action == "hit" &&
        single_attack->attack_config->attack_way <= "平A_重A")
        result = result + attribute_data("伤害加成", 0.09 + level * 0.03);

    //认为最近的一次release为对应的
    double time_diff = 0;
    for (auto i: single_attack->team_config->rotation)
        if (i->c_point == owner && i->action == "release" && i->attack_way == single_attack->attack_config->attack_way)
        {
            if (single_attack->attack_config->attack_time - i->attack_time < 0)
                time_diff = min(time_diff, single_attack->attack_config->attack_time - i->attack_time + single_attack->team_config->rotation_time);
            else
                time_diff = min(time_diff, single_attack->attack_config->attack_time - i->attack_time);
        }

    if (single_attack->attack_config->c_point == owner &&
        single_attack->attack_config->action == "hit" &&
        single_attack->attack_config->attack_way <= "平A_重A")
        result = result + attribute_data("伤害加成", min((int) (time_diff / 0.1), 5) * (0.06 + level * 0.02));

    return make_tuple(result, converted);
}

Bow_TianKong::Bow_TianKong(int level_) : Weapon("天空之翼", "skywardharp", "弓", 674, attribute_data("暴击率", 0.221), level_)
{}

tuple<attribute_data<double>, attribute_data<double>> Bow_TianKong::get_buff(const Single_Attack *single_attack, const Character *owner)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Weapon::get_buff(single_attack, owner);

    if (single_attack->attack_config->c_point == owner &&
        single_attack->attack_config->action == "hit")
        result = result + attribute_data("暴击伤害", 0.15 + level * 0.05);

    //附加伤害是单独的物理伤害，不考虑

    return make_tuple(result, converted);
}

Bow_ZhongMo::Bow_ZhongMo(int level_) : Weapon("终末嗟叹之诗", "elegyfortheend", "弓", 608, attribute_data("元素充能效率", 0.551), level_)
{}

tuple<attribute_data<double>, attribute_data<double>> Bow_ZhongMo::get_buff(const Single_Attack *single_attack, const Character *owner)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Weapon::get_buff(single_attack, owner);

    if (single_attack->attack_config->c_point == owner &&
        single_attack->attack_config->action == "hit")
        result = result + attribute_data("元素精通", 45.0 + level * 15.0);

    double last_trigger_time = -20;
    double last_hit_time = -0.2;
    int total_level = 0;
    for (auto i: single_attack->team_config->rotation)
        if (i->c_point == owner && i->action == "hit" && i->attack_way <= "E_Q" && i->attack_time >= last_hit_time + 0.2 && i->attack_time >= last_trigger_time + 20)
        {
            total_level += 1;
            last_hit_time = i->attack_time;
            if (total_level == 4)
            {
                total_level = 0;
                last_trigger_time = i->attack_time;
                if (single_attack->attack_config->action == "hit" &&
                    check_time_constrain(i->attack_time, i->attack_time + 12, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
                {
                    result = result + attribute_data("元素精通", 75.0 + level * 25.0);
                    result = result + attribute_data("攻击力", 0.15 + level * 0.05);//TODO:千年的大乐章数值不叠加
                    break;
                }
            }
        }

    return make_tuple(result, converted);
}

Bow_FeiLei::Bow_FeiLei(int level_) : Weapon("飞雷之弦振", "thunderingpulse", "弓", 608, attribute_data("暴击伤害", 0.662), level_)
{}

tuple<attribute_data<double>, attribute_data<double>> Bow_FeiLei::get_buff(const Single_Attack *single_attack, const Character *owner)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Weapon::get_buff(single_attack, owner);

    if (single_attack->attack_config->c_point == owner &&
        single_attack->attack_config->action == "hit")
        result = result + attribute_data("攻击力", 0.15 + level * 0.05);

    int disable_time_before_Q_release = 3;//TODO:更精准地判断元素能量
    int buff[3] = {0, 0, 0};
    for (auto i: single_attack->team_config->rotation)
    {
        if (i->c_point == owner && i->action == "hit" && i->attack_way == "平A")
            if (single_attack->attack_config->c_point == owner &&
                single_attack->attack_config->action == "hit" &&
                single_attack->attack_config->attack_way == "平A" &&
                check_time_constrain(i->attack_time, i->attack_time + 5, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
                buff[0] = 1;
        if (i->c_point == owner && i->action == "release" && i->attack_way == "E")
            if (single_attack->attack_config->c_point == owner &&
                single_attack->attack_config->action == "hit" &&
                single_attack->attack_config->attack_way == "平A" &&
                check_time_constrain(i->attack_time, i->attack_time + 10, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
                buff[1] = 1;
        if (i->c_point == owner && i->action == "release" && i->attack_way == "Q")
            if (single_attack->attack_config->c_point == owner &&
                single_attack->attack_config->action == "hit" &&
                single_attack->attack_config->attack_way == "平A" &&
                check_time_constrain(i->attack_time, i->attack_time + single_attack->team_config->rotation_time - disable_time_before_Q_release, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
                buff[2] = 1;
    }
    int total_level = buff[0] + buff[1] + buff[2];
    if (total_level == 3) result = result + attribute_data("伤害加成", 0.3 + level * 0.1);
    else if (total_level == 2) result = result + attribute_data("伤害加成", 0.18 + level * 0.06);
    else if (total_level == 1) result = result + attribute_data("伤害加成", 0.09 + level * 0.03);

    return make_tuple(result, converted);
}

Bow_DongJi::Bow_DongJi(int level_) : Weapon("冬极白星", "polarstar", "弓", 608, attribute_data("暴击率", 0.331), level_)
{}

tuple<attribute_data<double>, attribute_data<double>> Bow_DongJi::get_buff(const Single_Attack *single_attack, const Character *owner)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Weapon::get_buff(single_attack, owner);

    if (single_attack->attack_config->c_point == owner &&
        single_attack->attack_config->action == "hit" &&
        single_attack->attack_config->attack_way <= "E_Q")
        result = result + attribute_data("伤害加成", 0.09 + level * 0.03);

    int buff[5] = {0, 0, 0, 0, 0};
    for (auto i: single_attack->team_config->rotation)
        if (i->c_point == owner && i->action == "hit")
            if (single_attack->attack_config->c_point == owner &&
                single_attack->attack_config->action == "hit" &&
                check_time_constrain(i->attack_time, i->attack_time + 12, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
            {
                if (i->attack_way == "平A") buff[0] = 1;
                if (i->attack_way == "重A") buff[1] = 1;
                if (i->attack_way == "下落A") buff[2] = 1;
                if (i->attack_way == "E") buff[3] = 1;
                if (i->attack_way == "Q") buff[4] = 1;
            }
    int total_level = buff[0] + buff[1] + buff[2] + buff[3] + buff[4];
    if (total_level >= 4) result = result + attribute_data("攻击力", 0.36 + level * 0.12);
    else if (total_level == 3) result = result + attribute_data("攻击力", 0.225 + level * 0.075);
    else if (total_level == 2) result = result + attribute_data("攻击力", 0.15 + level * 0.05);
    else if (total_level == 1) result = result + attribute_data("攻击力", 0.075 + level * 0.025);

    return make_tuple(result, converted);
}

Bow_RuoShui::Bow_RuoShui(int level_) : Weapon("若水", "aquasimulacra", "弓", 542, attribute_data("暴击伤害", 0.882), level_)
{}

tuple<attribute_data<double>, attribute_data<double>> Bow_RuoShui::get_buff(const Single_Attack *single_attack, const Character *owner)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Weapon::get_buff(single_attack, owner);

    if (single_attack->attack_config->c_point == owner &&
        single_attack->attack_config->action == "hit")
    {
        result = result + attribute_data("生命值", 0.12 + level * 0.04);
        result = result + attribute_data("伤害加成", 0.15 + level * 0.05);//默认触发
    }

    return make_tuple(result, converted);
}

Bow_LieRen::Bow_LieRen(int level_) : Weapon("猎人之径", "hunterspath", "弓", 542, attribute_data("暴击率", 0.441), level_)
{}

attribute_data<int> Bow_LieRen::get_useful_attribute(const Single_Attack *single_attack, attribute_data<int> useful)
{
    attribute_data<int> result = Weapon::get_useful_attribute(single_attack, useful);

    //TODO:未考虑次数限制
    double last_A_time = -12;
    for (auto i: single_attack->team_config->rotation)
        if (i->c_point == single_attack->attack_config->c_point && i->action == "hit" && i->attack_way == "重A" && i->attack_time >= last_A_time + 12)
        {
            if (single_attack->attack_config->action == "hit" &&
                single_attack->attack_config->attack_way == "重A" &&
                check_time_constrain(i->attack_time, i->attack_time + 10, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
            {
//                if (20.0 * (1.2 + level * 0.4) >= 0.05 * single_attack->base_atk * single_attack->base_skillrate)
                result = result + attribute_data("元素精通", 1);
                break;
            }
            last_A_time = i->attack_time;
        }

    return result;
}

tuple<attribute_data<double>, attribute_data<double>> Bow_LieRen::get_buff(const Single_Attack *single_attack, const Character *owner)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Weapon::get_buff(single_attack, owner);

    if (single_attack->attack_config->c_point == owner &&
        single_attack->attack_config->action == "hit" &&
        single_attack->attack_config->c_point->get_attack_ele_type(single_attack) != "物理")
        result = result + attribute_data("伤害加成", 0.09 + level * 0.03);

    return make_tuple(result, converted);
}

double Bow_LieRen::get_extra_rate(const Single_Attack *single_attack, attribute_data<double> panel)
{
    double result = Weapon::get_extra_rate(single_attack, panel);

    //TODO:未考虑次数限制
    double last_A_time = -12;
    for (auto i: single_attack->team_config->rotation)
        if (i->c_point == single_attack->attack_config->c_point && i->action == "hit" && i->attack_way == "重A" && i->attack_time >= last_A_time + 12)
        {
            if (single_attack->attack_config->action == "hit" &&
                single_attack->attack_config->attack_way == "重A" &&
                check_time_constrain(i->attack_time, i->attack_time + 10, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
            {
                result = result + (1.2 + level * 0.4) * panel.get("元素精通");
                break;
            }
            last_A_time = i->attack_time;
        }

    return result;
}

Bow_MoShu::Bow_MoShu(int level_) : Weapon("最初的大魔术", "thefirstgreatmagic", "弓", 608, attribute_data("暴击伤害", 0.662), level_)
{}

tuple<attribute_data<double>, attribute_data<double>> Bow_MoShu::get_buff(const Single_Attack *single_attack, const Character *owner)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Weapon::get_buff(single_attack, owner);

    if (single_attack->attack_config->c_point == owner &&
        single_attack->attack_config->action == "hit" &&
        single_attack->attack_config->attack_way == "重A")
        result = result + attribute_data("伤害加成", 0.12 + level * 0.04);

    int diff_ele_num = 0;
    if (single_attack->team_config->team[0]->c_point->get_ele_type() != owner->get_ele_type())
        diff_ele_num += 1;
    if (single_attack->team_config->team[1]->c_point->get_ele_type() != owner->get_ele_type())
        diff_ele_num += 1;
    if (single_attack->team_config->team[2]->c_point->get_ele_type() != owner->get_ele_type())
        diff_ele_num += 1;
    if (single_attack->team_config->team[3]->c_point->get_ele_type() != owner->get_ele_type())
        diff_ele_num += 1;

    if (single_attack->attack_config->c_point == owner &&
        single_attack->attack_config->action == "hit")
        result = result + attribute_data("攻击力", (0.12 + level * 0.04) * min(3, 4 - diff_ele_num));

    return make_tuple(result, converted);
}

Bow_XiFeng::Bow_XiFeng(int level_) : Weapon("西风秘典", "favoniuscodex", "法器", 510, attribute_data("元素充能效率", 0.459), level_)
{}

tuple<double, double> Bow_XiFeng::get_recharge(const Single_Attack *single_attack, const Character *owner)
{
    double Q_energy_modify = 0;
    double energy = 0;
    tie(Q_energy_modify, energy) = Weapon::get_recharge(single_attack, owner);

    //默认暴击且100%概率产球
    double cd = 13.5 - level * 1.5;
    double last_energy_time = -cd;
    for (auto i: single_attack->team_config->rotation)
        if (i->c_point == owner && i->c_point == single_attack->team_config->get_front(i->attack_time) && i->action == "hit" && i->attack_time >= last_energy_time + cd)
        {
            energy += 6 * (owner == single_attack->attack_config->c_point ? 1 : 0.6);
            last_energy_time = i->attack_time;
        }

    return make_tuple(Q_energy_modify, energy);
}

//SAMPLE
//A::A(int level_) : Weapon("", "", "", , attribute_data("",), level_)
//{}
//
//tuple<double, double> A::get_recharge(const Single_Attack *single_attack, const Character *owner)
//{
//    double Q_energy_modify = 0;
//    double energy = 0;
//    tie(Q_energy_modify, energy) = Weapon::get_recharge(single_attack, owner);
//
//    return make_tuple(Q_energy_modify, energy);
//}
//
//attribute_data<int> A::get_useful_attribute(const Single_Attack *single_attack)
//{
//    attribute_data<int> result = Weapon::get_useful_attribute(single_attack);
//
//    return result;
//}
//
//tuple<attribute_data<double>, attribute_data<double>> A::get_buff(const Single_Attack *single_attack, const Character *owner)
//{
//    attribute_data<double> result;
//    attribute_data<double> converted;
//    tie(result, converted) = Weapon::get_buff(single_attack, owner);
//
//    return make_tuple(result, converted);
//}
//
//attribute_data<double> A::get_panel_convert(const Single_Attack *single_attack, attribute_data<double> panel)
//{
//    attribute_data<double> result = Weapon::get_panel_convert(single_attack, panel);
//
//    return result;
//}
//
//double A::get_extra_rate(const Single_Attack *single_attack, attribute_data<double> panel)
//{
//    double result = Weapon::get_extra_rate(single_attack, panel);
//
//    return result;
//}