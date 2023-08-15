//
// Created by 陈劭彬 on 2023/7/25.
//

#include "Artifact.h"
#include "Character.h"
#include "Deployment.h"

#include <utility>

Artifact::Artifact(string name_,
                   string english_name_)
{
    name = std::move(name_);
    english_name = std::move(english_name_);
}

string Artifact::get_name() const
{ return name; }

tuple<double, double> Artifact::get_recharge(const Single_Attack *single_attack)
{ return make_tuple(0, 0); }

attribute_data<int> Artifact::get_useful_attribute(const Single_Attack *single_attack)
{ return {}; }

tuple<attribute_data<double>, attribute_data<double>> Artifact::get_buff(const Single_Attack *single_attack, bool self, bool piece4)
{ return make_tuple(attribute_data<double>(), attribute_data<double>()); }

attribute_data<double> Artifact::get_panel_convert(const Single_Attack *single_attack, attribute_data<double> panel)
{ return {}; }

attribute_data<double> Artifact::get_total_convert(const Single_Attack *single_attack, attribute_data<double> panel)
{ return {}; }

double Artifact::get_extra_rate(const Single_Attack *single_attack, attribute_data<double> panel)
{ return 0; }

double Artifact::get_react_damplus(const Single_Attack *single_attack, string react_type)
{ return 0; }

YueTuan::YueTuan() : Artifact("流浪大地的乐团", "wandererstroupe")
{}

tuple<attribute_data<double>, attribute_data<double>> YueTuan::get_buff(const Single_Attack *single_attack, bool self, bool piece4)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Artifact::get_buff(single_attack, self, piece4);

    if (piece4)
    {
        if (self &&
            single_attack->attack_config->action == "hit" &&
            single_attack->attack_config->attack_way == "重A" &&
            single_attack->attack_config->c_point->get_weapon_type() <= "法器_弓")
            result = result + attribute_data("伤害加成", 0.35);
    }
    else if (self)
    {
        result = result + attribute_data("元素精通", 80.0);
    }

    return make_tuple(result, converted);
}

JueDou::JueDou() : Artifact("角斗士的终幕礼", "gladiatorsfinale")
{}

tuple<attribute_data<double>, attribute_data<double>> JueDou::get_buff(const Single_Attack *single_attack, bool self, bool piece4)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Artifact::get_buff(single_attack, self, piece4);

    if (piece4)
    {
        if (self &&
            single_attack->attack_config->action == "hit" &&
            single_attack->attack_config->attack_way == "平A" &&
            single_attack->attack_config->c_point->get_weapon_type() <= "单手剑_双手剑_长柄武器")
            result = result + attribute_data("伤害加成", 0.35);
    }
    else if (self)
    {
        result = result + attribute_data("攻击力", 0.18);
    }

    return make_tuple(result, converted);
}

BingTao::BingTao() : Artifact("冰风迷途的勇士", "blizzardstrayer")
{}

tuple<attribute_data<double>, attribute_data<double>> BingTao::get_buff(const Single_Attack *single_attack, bool self, bool piece4)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Artifact::get_buff(single_attack, self, piece4);

    if (piece4)
    {
        map<string, int> team_ele_num;
        team_ele_num["水"] = 0;
        team_ele_num["火"] = 0;
        team_ele_num["雷"] = 0;
        team_ele_num["冰"] = 0;
        team_ele_num["风"] = 0;
        team_ele_num["岩"] = 0;
        team_ele_num["草"] = 0;
        for (auto &i: single_attack->team_config->team) team_ele_num[i->c_point->get_ele_type()] += 1;
        bool has_ice = ((team_ele_num["火"] == 0) && (team_ele_num["雷"] < team_ele_num["冰"]));//TODO:更精准的判断元素附着

        if (self &&
            single_attack->attack_config->action == "hit" &&
            has_ice)
        {
            result = result + attribute_data("暴击率", 0.2);
            if ("冻结" <= single_attack->attack_config->react_type)//TODO:更精准的判断元素附着
                result = result + attribute_data("暴击率", 0.2);
        }
    }
    else if (self)
    {
        if (single_attack->attack_config->c_point->get_attack_ele_type(single_attack) == "冰")
            result = result + attribute_data("伤害加成", 0.15);
    }

    return make_tuple(result, converted);
}

ShuiTao::ShuiTao() : Artifact("沉沦之心", "heartofdepth")
{}

tuple<attribute_data<double>, attribute_data<double>> ShuiTao::get_buff(const Single_Attack *single_attack, bool self, bool piece4)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Artifact::get_buff(single_attack, self, piece4);

    if (piece4)
    {
        for (auto i: single_attack->team_config->rotation)
            if (i->c_point == single_attack->attack_config->c_point && i->action == "release" && i->attack_way == "E")
                if (self &&
                    single_attack->attack_config->action == "hit" &&
                    single_attack->attack_config->attack_way <= "平A_重A" &&
                    check_time_constrain(i->attack_time, i->attack_time + 15, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
                    result = result + attribute_data("伤害加成", 0.3);
    }
    else if (self)
    {
        if (single_attack->attack_config->c_point->get_attack_ele_type(single_attack) == "水")
            result = result + attribute_data("伤害加成", 0.15);
    }

    return make_tuple(result, converted);
}

//SAMPLE
//A::A() : Artifact("", "")
//{}
//
//tuple<attribute_data<double>, attribute_data<double>> A::get_buff(const Single_Attack *single_attack, bool self, bool piece4)
//{
//    attribute_data<double> result;
//    attribute_data<double> converted;
//    tie(result, converted) = Artifact::get_buff(single_attack, self, piece4);
//
//    if (piece4)
//    {
//
//    }
//    else if (self)
//    {
//
//    }
//
//    return make_tuple(result, converted);
//}
//
//double A::get_react_damplus(const Single_Attack *single_attack, string react_type)
//{
//    double result = Artifact::get_react_damplus(single_attack, react_type);
//
//    return result;
//}