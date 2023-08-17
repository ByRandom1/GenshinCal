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

tuple<double, double> Artifact::get_recharge(const Single_Attack *single_attack, const Character *owner)
{ return make_tuple(0, 0); }

attribute_data<int> Artifact::get_useful_attribute(const Single_Attack *single_attack)
{ return {}; }

tuple<attribute_data<double>, attribute_data<double>> Artifact::get_buff(const Single_Attack *single_attack, const Character *owner, bool piece4)
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

tuple<attribute_data<double>, attribute_data<double>> YueTuan::get_buff(const Single_Attack *single_attack, const Character *owner, bool piece4)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Artifact::get_buff(single_attack, owner, piece4);

    if (piece4)
    {
        if (single_attack->attack_config->c_point == owner &&
            single_attack->attack_config->action == "hit" &&
            single_attack->attack_config->attack_way == "重A" &&
            single_attack->attack_config->c_point->get_weapon_type() <= "法器_弓")
            result = result + attribute_data("伤害加成", 0.35);
    }
    else
    {
        if (single_attack->attack_config->c_point == owner &&
            single_attack->attack_config->action == "hit")
            result = result + attribute_data("元素精通", 80.0);
    }

    return make_tuple(result, converted);
}

JueDou::JueDou() : Artifact("角斗士的终幕礼", "gladiatorsfinale")
{}

tuple<attribute_data<double>, attribute_data<double>> JueDou::get_buff(const Single_Attack *single_attack, const Character *owner, bool piece4)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Artifact::get_buff(single_attack, owner, piece4);

    if (piece4)
    {
        if (single_attack->attack_config->c_point == owner &&
            single_attack->attack_config->action == "hit" &&
            single_attack->attack_config->attack_way == "平A" &&
            single_attack->attack_config->c_point->get_weapon_type() <= "单手剑_双手剑_长柄武器")
            result = result + attribute_data("伤害加成", 0.35);
    }
    else
    {
        if (single_attack->attack_config->c_point == owner &&
            single_attack->attack_config->action == "hit")
            result = result + attribute_data("攻击力", 0.18);
    }

    return make_tuple(result, converted);
}

BingTao::BingTao() : Artifact("冰风迷途的勇士", "blizzardstrayer")
{}

tuple<attribute_data<double>, attribute_data<double>> BingTao::get_buff(const Single_Attack *single_attack, const Character *owner, bool piece4)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Artifact::get_buff(single_attack, owner, piece4);

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

        if (single_attack->attack_config->c_point == owner &&
            single_attack->attack_config->action == "hit" &&
            has_ice)
        {
            result = result + attribute_data("暴击率", 0.2);
            if ("冻结" <= single_attack->attack_config->react_type)//TODO:更精准的判断元素附着
                result = result + attribute_data("暴击率", 0.2);
        }
    }
    else
    {
        if (single_attack->attack_config->c_point == owner &&
            single_attack->attack_config->action == "hit" &&
            single_attack->attack_config->c_point->get_attack_ele_type(single_attack) == "冰")
            result = result + attribute_data("伤害加成", 0.15);
    }

    return make_tuple(result, converted);
}

ShuiTao::ShuiTao() : Artifact("沉沦之心", "heartofdepth")
{}

tuple<attribute_data<double>, attribute_data<double>> ShuiTao::get_buff(const Single_Attack *single_attack, const Character *owner, bool piece4)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Artifact::get_buff(single_attack, owner, piece4);

    if (piece4)
    {
        for (auto i: single_attack->team_config->rotation)
            if (i->c_point == owner && i->action == "release" && i->attack_way == "E")
                if (single_attack->attack_config->c_point == owner &&
                    single_attack->attack_config->action == "hit" &&
                    single_attack->attack_config->attack_way <= "平A_重A" &&
                    check_time_constrain(i->attack_time, i->attack_time + 15, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
                {
                    result = result + attribute_data("伤害加成", 0.3);
                    break;
                }
    }
    else
    {
        if (single_attack->attack_config->c_point == owner &&
            single_attack->attack_config->action == "hit" &&
            single_attack->attack_config->c_point->get_attack_ele_type(single_attack) == "水")
            result = result + attribute_data("伤害加成", 0.15);
    }

    return make_tuple(result, converted);
}

PanYan::PanYan() : Artifact("悠古的磐岩", "archaicpetra")
{}

tuple<attribute_data<double>, attribute_data<double>> PanYan::get_buff(const Single_Attack *single_attack, const Character *owner, bool piece4)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Artifact::get_buff(single_attack, owner, piece4);

    if (piece4)
    {
        //不建构
    }
    else
    {
        if (single_attack->attack_config->c_point == owner &&
            single_attack->attack_config->action == "hit" &&
            single_attack->attack_config->c_point->get_attack_ele_type(single_attack) == "岩")
            result = result + attribute_data("伤害加成", 0.15);
    }

    return make_tuple(result, converted);
}

NiFei::NiFei() : Artifact("逆飞的流星", "retracingbolide")
{}

tuple<attribute_data<double>, attribute_data<double>> NiFei::get_buff(const Single_Attack *single_attack, const Character *owner, bool piece4)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Artifact::get_buff(single_attack, owner, piece4);

    if (piece4)
    {
        if (single_attack->attack_config->c_point == owner &&
            single_attack->attack_config->action == "hit" &&
            single_attack->attack_config->attack_way <= "平A_重A" &&
            single_attack->team_config->get_shield(single_attack->attack_config->attack_time))
            result = result + attribute_data("伤害加成", 0.4);
    }
    else
    {
        if (single_attack->attack_config->c_point == owner &&
            single_attack->attack_config->action == "hit")
            result = result + attribute_data("护盾强效", 0.35);
    }

    return make_tuple(result, converted);
}

RanXue::RanXue() : Artifact("染血的骑士道", "bloodstainedchivalry")
{}

tuple<attribute_data<double>, attribute_data<double>> RanXue::get_buff(const Single_Attack *single_attack, const Character *owner, bool piece4)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Artifact::get_buff(single_attack, owner, piece4);

    if (piece4)
    {
        //不建构
    }
    else
    {
        if (single_attack->attack_config->c_point == owner &&
            single_attack->attack_config->action == "hit" &&
            single_attack->attack_config->c_point->get_attack_ele_type(single_attack) == "物理")
            result = result + attribute_data("伤害加成", 0.25);
    }

    return make_tuple(result, converted);
}

ZongShi::ZongShi() : Artifact("昔日宗室之仪", "noblesseoblige")
{}

tuple<attribute_data<double>, attribute_data<double>> ZongShi::get_buff(const Single_Attack *single_attack, const Character *owner, bool piece4)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Artifact::get_buff(single_attack, owner, piece4);

    if (piece4)
    {
        for (auto i: single_attack->team_config->rotation)
            if (i->c_point == owner && i->action == "release" && i->attack_way == "Q")
                if (single_attack->attack_config->action == "hit" &&
                    check_time_constrain(i->attack_time, i->attack_time + 12, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
                {
                    result = result + attribute_data("攻击力", 0.2);
                    break;
                }
    }
    else
    {
        if (single_attack->attack_config->c_point == owner &&
            single_attack->attack_config->action == "hit" &&
            single_attack->attack_config->attack_way == "Q")
            result = result + attribute_data("伤害加成", 0.2);
    }

    return make_tuple(result, converted);
}

FengTao::FengTao() : Artifact("翠绿之影", "viridescentvenerer")
{}

tuple<attribute_data<double>, attribute_data<double>> FengTao::get_buff(const Single_Attack *single_attack, const Character *owner, bool piece4)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Artifact::get_buff(single_attack, owner, piece4);

    if (piece4)
    {
        for (auto i: single_attack->team_config->rotation)
            if (i->c_point == owner && i->action == "hit" && "扩散" <= i->react_type)
                if (single_attack->attack_config->action == "hit" &&
                    check_time_constrain(i->attack_time, i->attack_time + 10, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time) &&
                    ("扩散" + single_attack->attack_config->c_point->get_attack_ele_type(single_attack)) <= i->react_type)
                {
                    result = result + attribute_data("抗性削弱", 0.4);
                    break;
                }
    }
    else
    {
        if (single_attack->attack_config->c_point == owner &&
            single_attack->attack_config->action == "hit" &&
            single_attack->attack_config->c_point->get_attack_ele_type(single_attack) == "风")
            result = result + attribute_data("伤害加成", 0.15);
    }

    return make_tuple(result, converted);
}

double FengTao::get_react_damplus(const Single_Attack *single_attack, string react_type)
{
    double result = Artifact::get_react_damplus(single_attack, react_type);

    if (single_attack->attack_config->action == "hit" &&
        react_type == "扩散")
        result = result + 0.6;

    return result;
}

ShaoNv::ShaoNv() : Artifact("被怜爱的少女", "maidenbeloved")
{}

tuple<attribute_data<double>, attribute_data<double>> ShaoNv::get_buff(const Single_Attack *single_attack, const Character *owner, bool piece4)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Artifact::get_buff(single_attack, owner, piece4);

    if (piece4)
    {
        //不建构
    }
    else
    {
        if (single_attack->attack_config->c_point == owner &&
            single_attack->attack_config->action == "hit")
            result = result + attribute_data("治疗加成", 0.15);
    }

    return make_tuple(result, converted);
}

CangBai::CangBai() : Artifact("苍白之火", "paleflame")
{}

tuple<attribute_data<double>, attribute_data<double>> CangBai::get_buff(const Single_Attack *single_attack, const Character *owner, bool piece4)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Artifact::get_buff(single_attack, owner, piece4);

    if (piece4)
    {
        int total_level = 0;
        double last_E_time = -0.5;
        for (auto i: single_attack->team_config->rotation)
            if (i->c_point == owner && i->action == "hit" && i->attack_way == "E" && i->attack_time >= last_E_time + 0.3)
            {
                if (single_attack->attack_config->c_point == owner &&
                    single_attack->attack_config->action == "hit" &&
                    check_time_constrain(i->attack_time, i->attack_time + 7, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time) &&
                    total_level < 2)
                {
                    result = result + attribute_data("攻击力", 0.09);
                    total_level += 1;
                    if (total_level == 2 &&
                        single_attack->attack_config->c_point->get_attack_ele_type(single_attack) == "物理")
                        result = result + attribute_data("伤害加成", 0.25);
                }
                last_E_time = i->attack_time;
            }
    }
    else
    {
        if (single_attack->attack_config->c_point == owner &&
            single_attack->attack_config->action == "hit" &&
            single_attack->attack_config->c_point->get_attack_ele_type(single_attack) == "物理")
            result = result + attribute_data("伤害加成", 0.25);
    }

    return make_tuple(result, converted);
}

QianYan::QianYan() : Artifact("千岩牢固", "tenacityofthemillelith")
{}

tuple<attribute_data<double>, attribute_data<double>> QianYan::get_buff(const Single_Attack *single_attack, const Character *owner, bool piece4)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Artifact::get_buff(single_attack, owner, piece4);

    if (piece4)
    {
        double last_E_time = -0.5;
        for (auto i: single_attack->team_config->rotation)
            if (i->c_point == owner && i->action == "hit" && i->attack_way == "E" && i->attack_time >= last_E_time + 0.5)
            {
                if (single_attack->attack_config->action == "hit" &&
                    check_time_constrain(i->attack_time, i->attack_time + 3, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
                {
                    result = result + attribute_data("攻击力", 0.2);
                    result = result + attribute_data("护盾强效", 0.3);
                    break;
                }
                last_E_time = i->attack_time;
            }
    }
    else
    {
        if (single_attack->attack_config->c_point == owner &&
            single_attack->attack_config->action == "hit")
            result = result + attribute_data("生命值", 0.2);
    }

    return make_tuple(result, converted);
}

MoNv::MoNv() : Artifact("炽烈的炎之魔女", "crimsonwitchofflames")
{}

tuple<attribute_data<double>, attribute_data<double>> MoNv::get_buff(const Single_Attack *single_attack, const Character *owner, bool piece4)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Artifact::get_buff(single_attack, owner, piece4);

    if (piece4)
    {
        int total_level = 0;
        for (auto i: single_attack->team_config->rotation)
            if (i->c_point == owner && i->action == "release" && i->attack_way == "E")
                if (single_attack->attack_config->c_point == owner &&
                    single_attack->attack_config->action == "hit" &&
                    check_time_constrain(i->attack_time, i->attack_time + 10, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time) &&
                    single_attack->attack_config->c_point->get_attack_ele_type(single_attack) == "火" &&
                    total_level < 3)
                {
                    result = result + attribute_data("伤害加成", 0.075);
                    total_level += 1;
                }
    }
    else
    {
        if (single_attack->attack_config->c_point == owner &&
            single_attack->attack_config->action == "hit" &&
            single_attack->attack_config->c_point->get_attack_ele_type(single_attack) == "火")
            result = result + attribute_data("伤害加成", 0.15);
    }

    return make_tuple(result, converted);
}

double MoNv::get_react_damplus(const Single_Attack *single_attack, string react_type)
{
    double result = Artifact::get_react_damplus(single_attack, react_type);

    if (single_attack->attack_config->action == "hit" &&
        react_type <= "超载_燃烧_烈绽放")
        result = result + 0.4;
    else if (single_attack->attack_config->action == "hit" &&
             react_type <= "蒸发_融化")
        result = result + 0.15;

    return result;
}

DuHuo::DuHuo() : Artifact("渡过烈火的贤人", "lavawalker")
{}

tuple<attribute_data<double>, attribute_data<double>> DuHuo::get_buff(const Single_Attack *single_attack, const Character *owner, bool piece4)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Artifact::get_buff(single_attack, owner, piece4);

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
        bool has_fire = ((team_ele_num["水"] == 0) && (team_ele_num["雷"] < team_ele_num["火"]));//TODO:更精准的判断元素附着

        if (single_attack->attack_config->c_point == owner &&
            single_attack->attack_config->action == "hit" &&
            has_fire)
        {
            result = result + attribute_data("伤害加成", 0.35);
        }
    }
    else
    {
        //不构建
    }

    return make_tuple(result, converted);
}

RuLei::RuLei() : Artifact("如雷的盛怒", "thunderingfury")
{}

tuple<attribute_data<double>, attribute_data<double>> RuLei::get_buff(const Single_Attack *single_attack, const Character *owner, bool piece4)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Artifact::get_buff(single_attack, owner, piece4);

    if (piece4)
    {
        //不建构
    }
    else
    {
        if (single_attack->attack_config->c_point == owner &&
            single_attack->attack_config->action == "hit" &&
            single_attack->attack_config->c_point->get_attack_ele_type(single_attack) == "雷")
            result = result + attribute_data("伤害加成", 0.15);
    }

    return make_tuple(result, converted);
}

double RuLei::get_react_damplus(const Single_Attack *single_attack, string react_type)
{
    double result = Artifact::get_react_damplus(single_attack, react_type);

    if (single_attack->attack_config->action == "hit" &&
        react_type <= "超载_感电_超导_超绽放")
        result = result + 0.4;
    else if (single_attack->attack_config->action == "hit" &&
             react_type <= "超激化")
        result = result + 0.2;

    return result;
}

PingLei::PingLei() : Artifact("平息鸣雷的尊者", "thundersoother")
{}

tuple<attribute_data<double>, attribute_data<double>> PingLei::get_buff(const Single_Attack *single_attack, const Character *owner, bool piece4)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Artifact::get_buff(single_attack, owner, piece4);

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
        bool has_electro = (team_ele_num["草"] + team_ele_num["火"] + team_ele_num["冰"] < team_ele_num["雷"]);//TODO:更精准的判断元素附着

        if (single_attack->attack_config->c_point == owner &&
            single_attack->attack_config->action == "hit" &&
            has_electro)
        {
            result = result + attribute_data("伤害加成", 0.35);
        }
    }
    else
    {
        //不构建
    }

    return make_tuple(result, converted);
}

ZhuiYi::ZhuiYi() : Artifact("追忆之注连", "shimenawasreminiscence")
{}

tuple<double, double> ZhuiYi::get_recharge(const Single_Attack *single_attack, const Character *owner)
{
    double Q_energy_modify = 0;
    double energy = 0;
    tie(Q_energy_modify, energy) = Artifact::get_recharge(single_attack, owner);

    int disable_time_after_Q_release = 6;//TODO:更精准的判断能量
    //E
    double last_E_release = -11;
    for (auto i: single_attack->team_config->rotation)
    {
        if (i->c_point == owner && i->action == "release" && i->attack_way == "Q")
            last_E_release = max(last_E_release, i->attack_time + disable_time_after_Q_release - 10);
        if (i->c_point == owner && i->action == "release" && i->attack_way == "E" && i->attack_time >= last_E_release + 10)
        {
            if (single_attack->attack_config->c_point == owner)
                Q_energy_modify += 15;
            last_E_release = i->attack_time;
        }
    }

    return make_tuple(Q_energy_modify, energy);
}

tuple<attribute_data<double>, attribute_data<double>> ZhuiYi::get_buff(const Single_Attack *single_attack, const Character *owner, bool piece4)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Artifact::get_buff(single_attack, owner, piece4);

    if (piece4)
    {
        int disable_time_after_Q_release = 6;//TODO:更精准的判断能量
        //E
        double last_E_release = -11;
        for (auto i: single_attack->team_config->rotation)
        {
            if (i->c_point == owner && i->action == "release" && i->attack_way == "Q")
                last_E_release = max(last_E_release, i->attack_time + disable_time_after_Q_release - 10);
            if (i->c_point == owner && i->action == "release" && i->attack_way == "E" && i->attack_time >= last_E_release + 10)
            {
                if (single_attack->attack_config->c_point == owner &&
                    single_attack->attack_config->action == "hit" &&
                    "A" <= single_attack->attack_config->attack_way &&
                    check_time_constrain(i->attack_time, i->attack_time + 10, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
                {
                    result = result + attribute_data("伤害加成", 0.5);
                    break;
                }
                last_E_release = i->attack_time;
            }
        }
    }
    else
    {
        if (single_attack->attack_config->c_point == owner &&
            single_attack->attack_config->action == "hit")
            result = result + attribute_data("攻击力", 0.18);
    }

    return make_tuple(result, converted);
}

JueYuan::JueYuan() : Artifact("绝缘之旗印", "emblemofseveredfate")
{}

attribute_data<int> JueYuan::get_useful_attribute(const Single_Attack *single_attack)
{
    attribute_data<int> result = Artifact::get_useful_attribute(single_attack);

    if (single_attack->attack_config->action == "hit" &&
        single_attack->attack_config->attack_way == "Q")
        result = result + attribute_data("元素充能效率", 1);

    return result;
}

tuple<attribute_data<double>, attribute_data<double>> JueYuan::get_buff(const Single_Attack *single_attack, const Character *owner, bool piece4)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Artifact::get_buff(single_attack, owner, piece4);

    if (piece4)
    {
        //get_panel_convert
    }
    else
    {
        if (single_attack->attack_config->c_point == owner &&
            single_attack->attack_config->action == "hit")
            result = result + attribute_data("元素充能效率", 0.2);
    }

    return make_tuple(result, converted);
}

attribute_data<double> JueYuan::get_panel_convert(const Single_Attack *single_attack, attribute_data<double> panel)
{
    attribute_data<double> result = Artifact::get_panel_convert(single_attack, panel);

    if (single_attack->attack_config->action == "hit" &&
        single_attack->attack_config->attack_way == "Q")
        result = result + attribute_data("伤害加成", min(0.75, panel.get("元素充能效率") * 0.25));

    return result;
}

HuaGuan::HuaGuan() : Artifact("华馆梦醒形骸记", "huskofopulentdreams")
{}

tuple<attribute_data<double>, attribute_data<double>> HuaGuan::get_buff(const Single_Attack *single_attack, const Character *owner, bool piece4)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Artifact::get_buff(single_attack, owner, piece4);

    if (piece4)
    {
        //TODO:不准确，认为只有岩元素角色有加成，且默认满层
        if (single_attack->attack_config->c_point == owner &&
            single_attack->attack_config->action == "hit" &&
            single_attack->attack_config->c_point->get_ele_type() == "岩")
        {
            result = result + attribute_data("防御力", 0.24);
            if (single_attack->attack_config->c_point->get_attack_ele_type(single_attack) == "岩")
                result = result + attribute_data("伤害加成", 0.24);
        }
    }
    else
    {
        if (single_attack->attack_config->c_point == owner &&
            single_attack->attack_config->action == "hit")
            result = result + attribute_data("防御力", 0.3);
    }

    return make_tuple(result, converted);
}

HaiRan::HaiRan() : Artifact("海染砗磲", "oceanhuedclam")
{}

tuple<attribute_data<double>, attribute_data<double>> HaiRan::get_buff(const Single_Attack *single_attack, const Character *owner, bool piece4)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Artifact::get_buff(single_attack, owner, piece4);

    if (piece4)
    {
        //不建构
    }
    else
    {
        if (single_attack->attack_config->c_point == owner &&
            single_attack->attack_config->action == "hit")
            result = result + attribute_data("治疗加成", 0.15);
    }

    return make_tuple(result, converted);
}

ChenSha::ChenSha() : Artifact("辰砂往生录", "vermillionhereafter")
{}

tuple<attribute_data<double>, attribute_data<double>> ChenSha::get_buff(const Single_Attack *single_attack, const Character *owner, bool piece4)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Artifact::get_buff(single_attack, owner, piece4);

    if (piece4)
    {
        double Q_release_time = -1;
        double last_hp_drop_time = -0.8;
        int level = 0;
        for (auto i: single_attack->team_config->rotation)
        {
            //time up
            if (Q_release_time != -1 && i->attack_time > Q_release_time + 16)
            {
                Q_release_time = -1;
                level = -1;
            }
            //switch
            if (Q_release_time != -1 && i->c_point != owner && i->action == "switch")
            {
                Q_release_time = -1;
                level = -1;
            }
            //Q
            if (i->c_point == owner && i->action == "release" && i->attack_way == "Q")
            {
                Q_release_time = i->attack_time;
                level = 0;
            }
            if (Q_release_time != -1 && i->c_point == owner && i->action == "hp_change" && i->rate_pos < 0 && i->attack_time >= last_hp_drop_time + 0.8)
            {
                level = min(4, level + 1);
                last_hp_drop_time = i->attack_time;
            }
            if (i == single_attack->attack_config)
            {
                if (Q_release_time != -1 &&
                    single_attack->attack_config->c_point == owner &&
                    single_attack->attack_config->action == "hit")
                    result = result + attribute_data("攻击力", 0.08 + level * 0.1);
                break;
            }
        }
    }
    else
    {
        if (single_attack->attack_config->c_point == owner &&
            single_attack->attack_config->action == "hit")
            result = result + attribute_data("攻击力", 0.18);
    }

    return make_tuple(result, converted);
}

YuXiang::YuXiang() : Artifact("来歆余响", "echoesofanoffering")
{}

tuple<attribute_data<double>, attribute_data<double>> YuXiang::get_buff(const Single_Attack *single_attack, const Character *owner, bool piece4)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Artifact::get_buff(single_attack, owner, piece4);

    if (piece4)
    {
        //get_extra_rate
    }
    else
    {
        if (single_attack->attack_config->c_point == owner &&
            single_attack->attack_config->action == "hit")
            result = result + attribute_data("攻击力", 0.18);
    }

    return make_tuple(result, converted);
}

double YuXiang::get_extra_rate(const Single_Attack *single_attack, attribute_data<double> panel)
{
    double result = Artifact::get_extra_rate(single_attack, panel);

    if (single_attack->attack_config->action == "hit" &&
        single_attack->attack_config->attack_way == "平A")
    {
        result = result + 0.35 * panel.get("攻击力") * single_attack->base_atk;
    }

    return result;
}

CaoTao::CaoTao() : Artifact("深林的记忆", "deepwoodmemories")
{}

tuple<attribute_data<double>, attribute_data<double>> CaoTao::get_buff(const Single_Attack *single_attack, const Character *owner, bool piece4)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Artifact::get_buff(single_attack, owner, piece4);

    if (piece4)
    {
        for (auto i: single_attack->team_config->rotation)
            if (i->c_point == owner && i->action == "hit" && i->attack_way <= "E_Q")
                if (single_attack->attack_config->action == "hit" &&
                    check_time_constrain(i->attack_time, i->attack_time + 8, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time) &&
                    single_attack->attack_config->c_point->get_attack_ele_type(single_attack) == "草")
                {
                    result = result + attribute_data("抗性削弱", 0.3);
                    break;
                }
    }
    else
    {
        if (single_attack->attack_config->c_point == owner &&
            single_attack->attack_config->action == "hit" &&
            single_attack->attack_config->c_point->get_attack_ele_type(single_attack) == "草")
            result = result + attribute_data("伤害加成", 0.15);
    }

    return make_tuple(result, converted);
}

ShiJin::ShiJin() : Artifact("饰金之梦", "gildeddreams")
{}

tuple<attribute_data<double>, attribute_data<double>> ShiJin::get_buff(const Single_Attack *single_attack, const Character *owner, bool piece4)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Artifact::get_buff(single_attack, owner, piece4);

    if (piece4)
    {
        int diff_ele_num = 0;
        if (single_attack->team_config->team[0]->c_point->get_ele_type() != owner->get_ele_type())
            diff_ele_num += 1;
        if (single_attack->team_config->team[1]->c_point->get_ele_type() != owner->get_ele_type())
            diff_ele_num += 1;
        if (single_attack->team_config->team[2]->c_point->get_ele_type() != owner->get_ele_type())
            diff_ele_num += 1;
        if (single_attack->team_config->team[3]->c_point->get_ele_type() != owner->get_ele_type())
            diff_ele_num += 1;

        double last_react_time = -8;
        for (auto i: single_attack->team_config->rotation)
            if (i->c_point == owner && i->action == "hit" && !i->react_type.empty() && i->attack_time >= last_react_time + 8)
                if (single_attack->attack_config->c_point == owner &&
                    single_attack->attack_config->action == "hit" &&
                    check_time_constrain(i->attack_time, i->attack_time + 8, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
                {
                    result = result + attribute_data("攻击力", 0.14 * (3 - diff_ele_num));
                    result = result + attribute_data("元素精通", 50.0 * diff_ele_num);
                    break;
                }
    }
    else
    {
        if (single_attack->attack_config->c_point == owner &&
            single_attack->attack_config->action == "hit")
            result = result + attribute_data("元素精通", 80.0);
    }

    return make_tuple(result, converted);
}

LouGe::LouGe() : Artifact("沙上楼阁史话", "desertpavilionchronicle")
{}

tuple<attribute_data<double>, attribute_data<double>> LouGe::get_buff(const Single_Attack *single_attack, const Character *owner, bool piece4)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Artifact::get_buff(single_attack, owner, piece4);

    if (piece4)
    {
        for (auto i: single_attack->team_config->rotation)
            if (i->c_point == owner && i->action == "hit" && i->attack_way == "重A")
                if (single_attack->attack_config->c_point == owner &&
                    single_attack->attack_config->action == "hit" &&
                    "A" <= single_attack->attack_config->attack_way &&
                    check_time_constrain(i->attack_time, i->attack_time + 15, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
                {
                    result = result + attribute_data("伤害加成", 0.4);
                    break;
                }
    }
    else
    {
        if (single_attack->attack_config->c_point == owner &&
            single_attack->attack_config->action == "hit" &&
            single_attack->attack_config->c_point->get_attack_ele_type(single_attack) == "风")
            result = result + attribute_data("伤害加成", 0.15);
    }

    return make_tuple(result, converted);
}

LeYuan::LeYuan() : Artifact("乐园遗落之花", "flowerofparadiselost")
{}

tuple<attribute_data<double>, attribute_data<double>> LeYuan::get_buff(const Single_Attack *single_attack, const Character *owner, bool piece4)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Artifact::get_buff(single_attack, owner, piece4);

    if (piece4)
    {
        //get_react_damplus
    }
    else
    {
        if (single_attack->attack_config->c_point == owner &&
            single_attack->attack_config->action == "hit")
            result = result + attribute_data("元素精通", 80.0);
    }

    return make_tuple(result, converted);
}

double LeYuan::get_react_damplus(const Single_Attack *single_attack, string react_type)
{
    double result = Artifact::get_react_damplus(single_attack, react_type);

    if (single_attack->attack_config->action == "hit" &&
        react_type <= "绽放_超绽放_烈绽放")
        result = result + 0.4;
    int total_level = 0;
    for (auto i: single_attack->team_config->rotation)
        if (i->c_point == single_attack->attack_config->c_point && i->action == "hit" && "绽放" <= i->react_type)
            if (single_attack->attack_config->action == "hit" &&
                react_type <= "绽放_超绽放_烈绽放" &&
                check_time_constrain(i->attack_time, i->attack_time + 10, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time) &&
                total_level < 4)
            {
                result = result + 0.1;
                total_level += 1;
            }
    return result;
}

ShuiXian::ShuiXian() : Artifact("水仙之梦", "nymphsdream")
{}

tuple<attribute_data<double>, attribute_data<double>> ShuiXian::get_buff(const Single_Attack *single_attack, const Character *owner, bool piece4)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Artifact::get_buff(single_attack, owner, piece4);

    if (piece4)
    {
        int buff[5] = {0, 0, 0, 0, 0};
        for (auto i: single_attack->team_config->rotation)
            if (i->c_point == owner && i->action == "hit")
                if (single_attack->attack_config->c_point == owner &&
                    single_attack->attack_config->action == "hit" &&
                    check_time_constrain(i->attack_time, i->attack_time + 8, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
                {
                    if (i->attack_way == "平A") buff[0] = 1;
                    if (i->attack_way == "重A") buff[1] = 1;
                    if (i->attack_way == "下落A") buff[2] = 1;
                    if (i->attack_way == "E") buff[3] = 1;
                    if (i->attack_way == "Q") buff[4] = 1;
                }
        int level = buff[0] + buff[1] + buff[2] + buff[3] + buff[4];
        if (level >= 3)
        {
            result = result + attribute_data("攻击力", 0.25);
            if (single_attack->attack_config->c_point->get_attack_ele_type(single_attack) == "水")
                result = result + attribute_data("伤害加成", 0.15);
        }
        else if (level == 2)
        {
            result = result + attribute_data("攻击力", 0.16);
            if (single_attack->attack_config->c_point->get_attack_ele_type(single_attack) == "水")
                result = result + attribute_data("伤害加成", 0.09);
        }
        else if (level == 1)
        {
            result = result + attribute_data("攻击力", 0.07);
            if (single_attack->attack_config->c_point->get_attack_ele_type(single_attack) == "水")
                result = result + attribute_data("伤害加成", 0.04);
        }
    }
    else
    {
        if (single_attack->attack_config->c_point == owner &&
            single_attack->attack_config->action == "hit" &&
            single_attack->attack_config->c_point->get_attack_ele_type(single_attack) == "水")
            result = result + attribute_data("伤害加成", 0.15);
    }

    return make_tuple(result, converted);
}

HuaHai::HuaHai() : Artifact("花海甘露之光", "dewflowersglow")
{}

tuple<attribute_data<double>, attribute_data<double>> HuaHai::get_buff(const Single_Attack *single_attack, const Character *owner, bool piece4)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Artifact::get_buff(single_attack, owner, piece4);

    if (piece4)
    {
        if (single_attack->attack_config->c_point == owner &&
            single_attack->attack_config->action == "hit" &&
            single_attack->attack_config->attack_way <= "E_Q")
            result = result + attribute_data("伤害加成", 0.1);
        int total_level = 0;
        for (auto i: single_attack->team_config->rotation)
            if (i->c_point == owner && i->action == "hp_change" && i->rate_pos < 0)
                if (single_attack->attack_config->c_point == owner &&
                    single_attack->attack_config->action == "hit" &&
                    single_attack->attack_config->attack_way <= "E_Q" &&
                    check_time_constrain(i->attack_time, i->attack_time + 5, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time) &&
                    total_level < 5)
                {
                    result = result + attribute_data("伤害加成", 0.08);
                    total_level += 1;
                }
    }
    else
    {
        if (single_attack->attack_config->c_point == owner &&
            single_attack->attack_config->action == "hit")
            result = result + attribute_data("生命值", 0.2);
    }

    return make_tuple(result, converted);
}

ZhuYing::ZhuYing() : Artifact("逐影猎人", "")
{}

tuple<attribute_data<double>, attribute_data<double>> ZhuYing::get_buff(const Single_Attack *single_attack, const Character *owner, bool piece4)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Artifact::get_buff(single_attack, owner, piece4);

    if (piece4)
    {
        int total_level = 0;
        for (auto i: single_attack->team_config->rotation)
            if (i->c_point == owner && i->action == "hp_change")
                if (single_attack->attack_config->c_point == owner &&
                    single_attack->attack_config->action == "hit" &&
                    check_time_constrain(i->attack_time, i->attack_time + 5, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time) &&
                    total_level < 3)
                {
                    result = result + attribute_data("暴击率", 0.12);
                    total_level += 1;
                }
    }
    else
    {
        if (single_attack->attack_config->c_point == owner &&
            single_attack->attack_config->action == "hit" &&
            single_attack->attack_config->attack_way <= "平A_重A")
            result = result + attribute_data("伤害加成", 0.15);
    }

    return make_tuple(result, converted);
}

JuTuan::JuTuan() : Artifact("黄金剧团", "")
{}

tuple<attribute_data<double>, attribute_data<double>> JuTuan::get_buff(const Single_Attack *single_attack, const Character *owner, bool piece4)
{
    attribute_data<double> result;
    attribute_data<double> converted;
    tie(result, converted) = Artifact::get_buff(single_attack, owner, piece4);

    if (piece4)
    {
        if (single_attack->attack_config->c_point == owner &&
            single_attack->attack_config->action == "hit" &&
            single_attack->attack_config->attack_way == "E")
            result = result + attribute_data("伤害加成", 0.25);
        vector<pair<double, double>> buff_time;
        double start_time = -1;
        for (auto i: single_attack->team_config->rotation)
        {
            if (start_time == -1 && i->c_point != owner && i->action == "switch") start_time = i->attack_time;
            if (start_time != -1 && i->c_point == owner && i->action == "switch")
            {
                buff_time.emplace_back(start_time, i->attack_time + 2);
                start_time = -1;
            }
        }
        if (start_time != -1) buff_time.emplace_back(start_time, single_attack->team_config->rotation_time + 2);
        for (auto i: buff_time)
            if (single_attack->attack_config->c_point == owner &&
                single_attack->attack_config->action == "hit" &&
                single_attack->attack_config->attack_way == "E" &&
                check_time_constrain(i.first, i.second, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
            {
                result = result + attribute_data("伤害加成", 0.25);
                break;
            }
    }
    else
    {
        if (single_attack->attack_config->c_point == owner &&
            single_attack->attack_config->action == "hit" &&
            single_attack->attack_config->attack_way == "E")
            result = result + attribute_data("伤害加成", 0.2);
    }

    return make_tuple(result, converted);
}

//SAMPLE
//A::A() : Artifact("", "")
//{}
//
//tuple<attribute_data<double>, attribute_data<double>> A::get_buff(const Single_Attack *single_attack, const Character* owner, bool piece4)
//{
//    attribute_data<double> result;
//    attribute_data<double> converted;
//    tie(result, converted) = Artifact::get_buff(single_attack, owner, piece4);
//
//    if (piece4)
//    {
//
//    }
//    else
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