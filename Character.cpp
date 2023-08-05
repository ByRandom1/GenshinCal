//
// Created by 陈劭彬 on 2023/7/25.
//

#include "Character.h"
#include "Deployment.h"

#include <utility>

Character::Character(string name_,
                     string english_name_,
                     string ele_type_,
                     string weapon_type_,
                     int life_,
                     int atk_,
                     int def_,
                     const attribute_data<double> &break_value_,
                     int A_level_,
                     const attribute_data<int> &A_useful_attributes_,
                     string normal_A_ele_type_,
                     const vector<double> &normal_A_10, const vector<double> &normal_A_9,
                     string heavy_A_ele_type_,
                     const vector<double> &heavy_A_10, const vector<double> &heavy_A_9,
                     string down_A_ele_type_,
                     const vector<double> &down_A_10, const vector<double> &down_A_9,
                     int E_level_,
                     double E_energy_,
                     bool E_lockface_,
                     const attribute_data<int> &E_useful_attributes_,
                     string E_ele_type_,
                     const vector<double> &E_13, const vector<double> &E_12, const vector<double> &E_10, const vector<double> &E_9,
                     int Q_level_,
                     int Q_energy_,
                     bool Q_lockface_,
                     const attribute_data<int> &Q_useful_attributes_,
                     string Q_ele_type_,
                     const vector<double> &Q_13, const vector<double> &Q_12, const vector<double> &Q_10, const vector<double> &Q_9,
                     int constellation_)
{
    name = std::move(name_);
    english_name = std::move(english_name_);
    ele_type = std::move(ele_type_);
    weapon_type = std::move(weapon_type_);
    life = life_;
    atk = atk_;
    def = def_;
    break_value = break_value_;
    A_level = A_level_;
    A_useful_attributes = A_useful_attributes_;
    normal_A_ele_type = std::move(normal_A_ele_type_);
    normal_A.push_back(normal_A_10);
    normal_A.push_back(normal_A_9);
    heavy_A_ele_type = std::move(heavy_A_ele_type_);
    heavy_A.push_back(heavy_A_10);
    heavy_A.push_back(heavy_A_9);
    down_A_ele_type = std::move(down_A_ele_type_);
    down_A.push_back(down_A_10);
    down_A.push_back(down_A_9);
    E_level = E_level_;
    E_energy = E_energy_;
    E_lockface = E_lockface_;
    E_useful_attributes = E_useful_attributes_;
    E_ele_type = std::move(E_ele_type_);
    E.push_back(E_13);
    E.push_back(E_12);
    E.push_back(E_10);
    E.push_back(E_9);
    Q_level = Q_level_;
    Q_energy = Q_energy_;
    Q_lockface = Q_lockface_;
    Q_useful_attributes = Q_useful_attributes_;
    Q_ele_type = std::move(Q_ele_type_);
    Q.push_back(Q_13);
    Q.push_back(Q_12);
    Q.push_back(Q_10);
    Q.push_back(Q_9);
    constellation = constellation_;
}

string Character::get_name()
{ return name; }

string Character::get_ele_type()
{ return ele_type; }

string Character::get_weapon_type()
{ return weapon_type; }

int Character::get_life() const
{ return life; }

int Character::get_atk() const
{ return atk; }

int Character::get_def() const
{ return def; }

double Character::get_rate(const string &attack_way, int pos)
{
    if (attack_way == "平A")
    {
        if (A_level == 10) return normal_A[0][min(pos, (int) normal_A[0].size() - 1)];
        else return normal_A[1][min(pos, (int) normal_A[1].size() - 1)];
    }
    else if (attack_way == "重A")
    {
        if (A_level == 10) return heavy_A[0][min(pos, (int) heavy_A[0].size() - 1)];
        else return heavy_A[1][min(pos, (int) heavy_A[1].size() - 1)];
    }
    else if (attack_way == "下落A")
    {
        if (A_level == 10) return down_A[0][min(pos, (int) down_A[0].size() - 1)];
        else return down_A[1][min(pos, (int) down_A[1].size() - 1)];
    }
    else if (attack_way == "E")
    {
        if (E_level == 13) return E[0][min(pos, (int) E[0].size() - 1)];
        else if (E_level == 12) return E[1][min(pos, (int) E[1].size() - 1)];
        else if (E_level == 10) return E[2][min(pos, (int) E[2].size() - 1)];
        else return E[3][min(pos, (int) E[3].size() - 1)];
    }
    else if (attack_way == "Q")
    {
        if (Q_level == 13) return Q[0][min(pos, (int) Q[0].size() - 1)];
        else if (Q_level == 12) return Q[1][min(pos, (int) Q[1].size() - 1)];
        else if (Q_level == 10) return Q[2][min(pos, (int) Q[2].size() - 1)];
        else return Q[3][min(pos, (int) Q[3].size() - 1)];
    }
    else return 0;
}

attribute_data<double> Character::get_break(const Single_Attack *single_attack)
{
    if (single_attack->attack_config->c_point->get_attack_ele_type(single_attack) != ele_type)
    {
        attribute_data<double> result = break_value;
        result.data["伤害加成"] = 0.0;
        return result;
    }
    else return break_value;
}

string Character::get_attack_ele_type(const Single_Attack *single_attack)
{
    if (single_attack->attack_config->attack_way == "平A") return normal_A_ele_type;
    else if (single_attack->attack_config->attack_way == "重A") return heavy_A_ele_type;
    else if (single_attack->attack_config->attack_way == "下落A") return down_A_ele_type;
    else if (single_attack->attack_config->attack_way == "E") return E_ele_type;
    else if (single_attack->attack_config->attack_way == "Q") return Q_ele_type;
    else return ele_type;
}

void Character::get_recharge(const Single_Attack *single_attack, double &Q_energy_modify, double &energy)
{}

attribute_data<int> Character::get_useful_attribute(const Single_Attack *single_attack)
{
    if (single_attack->attack_config->attack_way == "平A" || single_attack->attack_config->attack_way == "重A" || single_attack->attack_config->attack_way == "下落A") return A_useful_attributes;
    else if (single_attack->attack_config->attack_way == "E") return E_useful_attributes;
    else if (single_attack->attack_config->attack_way == "Q") return Q_useful_attributes;
    else return {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
}

attribute_data<double> Character::get_buff(const Single_Attack *single_attack)
{ return {}; }

attribute_data<double> Character::get_panel_convert(const Single_Attack *single_attack, attribute_data<double> panel)
{ return {}; }

attribute_data<double> Character::get_total_convert(const Single_Attack *single_attack, attribute_data<double> panel)
{ return {}; }

double Character::get_extra_rate(const Single_Attack *single_attack, attribute_data<double> panel)
{ return 0; }

double Character::get_react_damplus(const Single_Attack *single_attack, string react_type)
{ return 0; }

Hutao::Hutao(int A_level, int E_level, int Q_level, int constellation) : Character("胡桃", "hutao", "火", "长柄武器", 15552, 107, 876, attribute_data("暴击伤害", 0.384),
                                                                                   A_level, attribute_data(0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0), "物理", vector<double>{0.836, 0.861, 1.089, 1.171, 0.594, 0.628, 1.534}, vector<double>{0.789, 0.812, 1.027, 1.104, 0.56, 0.592, 1.446},
                                                                                   "物理", vector<double>{2.426}, vector<double>{2.287}, "物理", vector<double>{2.92}, vector<double>{2.75},
                                                                                   E_level, 2.5, false, attribute_data(0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0), "火", vector<double>{1.36}, vector<double>{1.28}, vector<double>{1.15}, vector<double>{1.09},
                                                                                   Q_level, 60, false, attribute_data(0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0), "火", vector<double>{5.65, 7.06}, vector<double>{5.41, 6.76}, vector<double>{4.94, 6.17}, vector<double>{4.7, 5.88},
                                                                                   constellation)
{}

vector<pair<double, double>> Hutao::get_E_time(const Single_Attack *single_attack)
{
    vector<pair<double, double>> result;
    double E_release_time = -1;
    for (auto i: single_attack->team_config->rotation)
    {
        //time up
        if (E_release_time != -1 && i->attack_time > E_release_time + 11)
        {
            result.emplace_back(E_release_time, E_release_time + 11);
            E_release_time = -1;
        }
        //switch
        if (E_release_time != -1 && i->c_point != this && i->action == "switch")
        {
            result.emplace_back(E_release_time, i->attack_time);
            E_release_time = -1;
        }
        //E
        if (E_release_time == -1 && i->c_point == this && i->action == "release" && i->attack_way == "E") E_release_time = i->attack_time;
    }
    if (E_release_time != -1) result.emplace_back(E_release_time, single_attack->team_config->rotation_time + 0.001);
    return result;
}

string Hutao::get_attack_ele_type(const Single_Attack *single_attack)
{
    string result = Character::get_attack_ele_type(single_attack);
    //skill:E
    auto E_time = get_E_time(single_attack);
    for (auto &i: E_time)
        if (single_attack->attack_config->c_point == this &&
            single_attack->attack_config->action == "hit" &&
            "A" <= single_attack->attack_config->attack_way &&
            check_time_constrain(i.first, i.second, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
        {
            result = "火";
            break;
        }
    return result;
}

void Hutao::get_recharge(const Single_Attack *single_attack, double &Q_energy_modify, double &energy)
{
    if (single_attack->attack_config->c_point == this) Q_energy_modify = Q_energy;
    //E下平A重A，5s
    auto E_time = get_E_time(single_attack);
    double last_A_generate = -5;
    for (auto i: single_attack->team_config->rotation)
        if (i->c_point == this && i->action == "hit" && (i->attack_way == "平A" || i->attack_way == "重A") && i->attack_time >= last_A_generate + 5)
            for (auto &j: E_time)
                if (check_time_constrain(j.first, j.second, i->attack_time, single_attack->team_config->rotation_time))
                {
                    energy += E_energy * (single_attack->attack_config->c_point->get_ele_type() == ele_type ? 3 : 1) * (this == single_attack->attack_config->c_point ? 1 : 0.6);
                    last_A_generate = i->attack_time;
                    break;
                }
}

attribute_data<int> Hutao::get_useful_attribute(const Single_Attack *single_attack)
{
    attribute_data<int> result = Character::get_useful_attribute(single_attack);
    //skill:E
    auto E_time = get_E_time(single_attack);
    for (auto &i: E_time)
        if (single_attack->attack_config->c_point == this &&
            single_attack->attack_config->action == "hit" &&
            check_time_constrain(i.first, i.second, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
        {
            result = result + attribute_data("生命值", 1) + attribute_data("攻击力", -1);
            break;
        }
    return result;
}

attribute_data<double> Hutao::get_buff(const Single_Attack *single_attack)
{
    attribute_data<double> result = Character::get_buff(single_attack);
    //talent 1
    auto E_time = get_E_time(single_attack);
    for (auto &i: E_time)
        if (single_attack->attack_config->c_point != this &&
            single_attack->attack_config->action == "hit" &&
            check_time_constrain(i.second, i.second + 8, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
        {
            result = result + attribute_data("暴击率", 0.12);
            break;
        }
    //talent 2
    bool heal_exist = false;//TODO:add arg
    if (single_attack->attack_config->c_point == this &&
        single_attack->attack_config->action == "hit" &&
        single_attack->attack_config->c_point->get_attack_ele_type(single_attack) == "火" &&
        !heal_exist)
        result = result + attribute_data("伤害加成", 0.33);
    return result;
}

attribute_data<double> Hutao::get_panel_convert(const Single_Attack *single_attack, attribute_data<double> panel)
{
    attribute_data<double> result = Character::get_panel_convert(single_attack, panel);
    //skill:E
    auto E_time = get_E_time(single_attack);
    for (auto &i: E_time)
        if (single_attack->attack_config->c_point == this &&
            single_attack->attack_config->action == "hit" &&
            check_time_constrain(i.first, i.second, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
        {
            result = result + attribute_data("攻击力", min(panel.data["生命值"] * 0.0626 * life / atk, 4.0));
            break;
        }
    return result;
}

double Hutao::get_extra_rate(const Single_Attack *single_attack, attribute_data<double> panel)
{
    double result = Character::get_extra_rate(single_attack, panel);
    //constellation 2:E +10%life
    if (constellation >= 2)
    {
        if (single_attack->attack_config->c_point == this &&
            single_attack->attack_config->action == "hit" &&
            single_attack->attack_config->attack_way == "E")
            result = result + 0.1 * panel.data["生命值"] * life;
    }
    return result;
}

Alhaitham::Alhaitham(int A_level, int E_level, int Q_level, int constellation) : Character("艾尔海森", "alhaitham", "草", "单手剑", 13348, 313, 782, attribute_data("伤害加成", 0.288),
                                                                                           A_level, attribute_data(0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0), "物理", vector<double>{0.979, 1.003, 0.676, 0.676, 1.32, 1.658}, vector<double>{0.91, 0.932, 0.628, 0.628, 1.227, 1.541},
                                                                                           "物理", vector<double>{1.092, 1.092}, vector<double>{1.015, 1.015}, "物理", vector<double>{3.16}, vector<double>{2.93},
                                                                                           E_level, 1, false, attribute_data(0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0), "草", vector<double>{4.114, 1.482, 1.482 * 2, 1.482 * 3}, vector<double>{3.872, 1.344, 1.344 * 2, 1.344 * 3},
                                                                                           vector<double>{3.485, 1.21, 1.21 * 2, 1.21 * 3}, vector<double>{3.291, 1.142, 1.142 * 2, 1.142 * 3},
                                                                                           Q_level, 70, true, attribute_data(0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0), "草", vector<double>{2.584}, vector<double>{2.432}, vector<double>{2.189}, vector<double>{2.067},
                                                                                           constellation)
{}

int get_mirror_num(const vector<pair<int, double>> &result, double time)
{
    int total_mirror = 0;
    for (auto &i: result)
        if (i.second < time)
            total_mirror += i.first;
    return total_mirror;
}

vector<pair<int, double>> Alhaitham::get_mirror_time(const Single_Attack *single_attack)
{
    vector<pair<int, double>> result;
    double last_A_generate = -12;
    double last_del = -1;
    pair<int, double> Q_to_deal = make_pair(-1, -1);
    for (auto i: single_attack->team_config->rotation)
    {
        //退场
        if (i->c_point != this && i->action == "switch")
        {
            int total_mirror = get_mirror_num(result, i->attack_time);
            if (total_mirror != 0) result.emplace_back(-total_mirror, i->attack_time);
        }
        //时间流逝
        if (i->attack_time >= last_del + 4 && get_mirror_num(result, last_del + 4) > 0)
        {
            result.emplace_back(-1, last_del + 4);
            last_del += 4;
        }
        //Q返还
        if (Q_to_deal.second != -1 && i->attack_time >= Q_to_deal.second)
        {
            if (get_front(single_attack->team_config, Q_to_deal.second) == this)
            {
                int total_mirror = get_mirror_num(result, Q_to_deal.second);
                result.emplace_back(Q_to_deal.first, Q_to_deal.second);
                if (total_mirror + Q_to_deal.first - 3 > 0)
                    result.emplace_back(-(total_mirror + Q_to_deal.first - 3), Q_to_deal.second);
                if (total_mirror == 0) last_del = Q_to_deal.second;
            }
            Q_to_deal.first = -1;
            Q_to_deal.second = -1;
        }
        //E
        if (i->c_point == this && i->action == "release" && i->attack_way == "E")
        {
            int total_mirror = get_mirror_num(result, i->attack_time);
            if (total_mirror == 3)
            {
                result.emplace_back(1, i->attack_time);
                result.emplace_back(-1, i->attack_time);
            }
            else if (total_mirror == 0)
            {
                result.emplace_back(2, i->attack_time);
                last_del = i->attack_time;
            }
            else result.emplace_back(1, i->attack_time);
        }
        //talent 1
        if (i->c_point == this && i->action == "hit" && (i->attack_way == "重A" || i->attack_way == "下落A") && i->attack_time >= last_A_generate + 12)
        {
            int total_mirror = get_mirror_num(result, i->attack_time);
            if (total_mirror == 3)
            {
                result.emplace_back(1, i->attack_time);
                result.emplace_back(-1, i->attack_time);
            }
            else if (total_mirror == 0)
            {
                result.emplace_back(1, i->attack_time);
                last_del = i->attack_time;
            }
            else result.emplace_back(1, i->attack_time);
            last_A_generate = i->attack_time;
        }
        //Q
        if (i->c_point == this && i->action == "release" && i->attack_way == "Q")
        {
            int total_mirror = get_mirror_num(result, i->attack_time);
            if (total_mirror != 0) result.emplace_back(-total_mirror, i->attack_time);
            if (total_mirror != 3)
            {
                if (constellation >= 6) Q_to_deal.first = 3;
                else Q_to_deal.first = 3 - total_mirror;
                Q_to_deal.second = i->attack_time + 2;
            }
        }
    }
    int total_mirror = get_mirror_num(result, single_attack->team_config->rotation_time);
    if (total_mirror > 0) result.emplace_back(-total_mirror, single_attack->team_config->rotation_time + 0.001);
    return result;
}

string Alhaitham::get_attack_ele_type(const Single_Attack *single_attack)
{
    string result = Character::get_attack_ele_type(single_attack);
    //state下
    if (single_attack->attack_config->c_point == this &&
        single_attack->attack_config->action == "hit" &&
        "A" <= single_attack->attack_config->attack_way &&
        get_mirror_num(get_mirror_time(single_attack), single_attack->attack_config->attack_time) > 0)
        result = "草";
    return result;
}

void Alhaitham::get_recharge(const Single_Attack *single_attack, double &Q_energy_modify, double &energy)
{
    if (single_attack->attack_config->c_point == this) Q_energy_modify = Q_energy;
    //E命中
    for (auto i: single_attack->team_config->rotation)
        if (i->c_point == this && i->action == "hit" && i->attack_way == "E" && i->rate_pos != 0)
            energy += E_energy * (single_attack->attack_config->c_point->get_ele_type() == ele_type ? 3 : 1) * (this == single_attack->attack_config->c_point ? 1 : 0.6);
}

attribute_data<double> Alhaitham::get_buff(const Single_Attack *single_attack)
{
    attribute_data<double> result = Character::get_buff(single_attack);
    //constellation 2
    if (constellation >= 2)
    {
        auto mirror_time = get_mirror_time(single_attack);
        int total_level = 0;
        for (auto &i: mirror_time)
            if (single_attack->attack_config->c_point == this &&
                single_attack->attack_config->action == "hit" &&
                check_time_constrain(i.second, i.second + 8, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time) &&
                i.first > 0 && total_level < 4)
            {
                result = result + attribute_data("元素精通", i.first * 50.0);
                total_level += i.first;
            }
    }
    //constellation 4
    if (constellation >= 4)
    {
        auto mirror_time = get_mirror_time(single_attack);
        for (auto i: single_attack->team_config->rotation)
            if (i->c_point == this && i->action == "release" && i->attack_way == "Q")
            {
                bool got = false;
                if (single_attack->attack_config->c_point == this &&
                    single_attack->attack_config->action == "hit" &&
                    check_time_constrain(i->attack_time, i->attack_time + 15, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time) &&
                    single_attack->attack_config->c_point->get_attack_ele_type(single_attack) == "草")
                {
                    for (auto j: mirror_time)
                        if (j.first > 0 && j.second == i->attack_time + 2)
                        {
                            result = result + attribute_data("伤害加成", 0.1 * j.first);
                            got = true;
                            break;
                        }
                }
                if (single_attack->attack_config->c_point != this &&
                    single_attack->attack_config->action == "hit" &&
                    check_time_constrain(i->attack_time, i->attack_time + 15, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
                {
                    for (auto j: mirror_time)
                        if (j.first < 0 && j.second == i->attack_time)
                        {
                            result = result + attribute_data("元素精通", 30.0 * (-j.first));
                            got = true;
                            break;
                        }
                }
                if (got) break;
            }
    }
    //constellation 6
    if (constellation >= 6)
    {
        auto mirror_time = get_mirror_time(single_attack);
        stable_sort(mirror_time.begin(), mirror_time.end(), [](pair<int, double> a, pair<int, double> b)
        { return a.second < b.second; });
        //超出上限在vector中呈现出 1、.second相等 2、+在前-在后且连续
        vector<pair<double, double>> time_range;
        double start_time = -1;
        double end_time = -1;
        for (int i = 0; i < mirror_time.size(); ++i)
            if (i + 1 < mirror_time.size() &&
                mirror_time[i].first > 0 && mirror_time[i].second == mirror_time[i + 1].second && mirror_time[i + 1].first < 0)
            {
                if (start_time == -1)
                {
                    start_time = mirror_time[i].second;
                    end_time = mirror_time[i].second + 6;
                }
                else if (start_time <= mirror_time[i].second && mirror_time[i].second <= end_time)
                    end_time += 6;
                else
                {
                    time_range.emplace_back(start_time, end_time);
                    start_time = mirror_time[i].second;
                    end_time = mirror_time[i].second + 6;
                }
            }
        for (auto i: time_range)
            if (single_attack->attack_config->c_point == this &&
                single_attack->attack_config->action == "hit" &&
                check_time_constrain(i.first, i.second, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
            {
                result = result + attribute_data("暴击率", 0.1) + attribute_data("暴击伤害", 0.7);
                break;
            }
    }
    return result;
}

attribute_data<double> Alhaitham::get_total_convert(const Single_Attack *single_attack, attribute_data<double> panel)
{
    attribute_data<double> result = Character::get_total_convert(single_attack, panel);
    //talent 2
    if (single_attack->attack_config->c_point == this &&
        single_attack->attack_config->action == "hit" &&
        (single_attack->attack_config->attack_way == "E" || single_attack->attack_config->attack_way == "Q"))
        result = result + attribute_data("伤害加成", min(panel.data["元素精通"] * 0.001, 1.0));
    return result;
}

double Alhaitham::get_extra_rate(const Single_Attack *single_attack, attribute_data<double> panel)
{
    double result = Character::get_extra_rate(single_attack, panel);
    //skill:E,Q
    vector<double> E_13{3.291, 2.856, 2.856 * 2, 2.856 * 3};
    vector<double> E_12{3.098, 2.688, 2.688 * 2, 2.688 * 3};
    vector<double> E_10{2.788, 2.419, 2.419 * 2, 2.419 * 3};
    vector<double> E_9{2.633, 2.285, 2.285 * 2, 2.285 * 3};
    vector<double> Q_13{2.067};
    vector<double> Q_12{1.946};
    vector<double> Q_10{1.751};
    vector<double> Q_9{1.654};

    if (single_attack->attack_config->c_point == this &&
        single_attack->attack_config->action == "hit" &&
        single_attack->attack_config->attack_way == "E")
    {
        if (E_level == 13) result = result + E_13[single_attack->attack_config->rate_pos] * panel.data["元素精通"];
        else if (E_level == 12) result = result + E_12[single_attack->attack_config->rate_pos] * panel.data["元素精通"];
        else if (E_level == 10) result = result + E_10[single_attack->attack_config->rate_pos] * panel.data["元素精通"];
        else result = result + E_9[single_attack->attack_config->rate_pos] * panel.data["元素精通"];
    }
    else if (single_attack->attack_config->c_point == this &&
             single_attack->attack_config->action == "hit" &&
             single_attack->attack_config->attack_way == "Q")
    {
        if (Q_level == 13) result = result + Q_13[single_attack->attack_config->rate_pos] * panel.data["元素精通"];
        else if (Q_level == 12) result = result + Q_12[single_attack->attack_config->rate_pos] * panel.data["元素精通"];
        else if (Q_level == 10) result = result + Q_10[single_attack->attack_config->rate_pos] * panel.data["元素精通"];
        else result = result + Q_9[single_attack->attack_config->rate_pos] * panel.data["元素精通"];
    }
    return result;
}

Raiden::Raiden(int A_level, int E_level, int Q_level, int constellation) : Character("雷电将军", "raiden", "雷", "长柄武器", 12907, 337, 789, attribute_data("元素充能效率", 0.32),
                                                                                     A_level, attribute_data(0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0), "物理", vector<double>{0.784, 0.785, 0.986, 0.573, 0.573, 1.294}, vector<double>{0.728, 0.73, 0.916, 0.533, 0.533, 1.202},
                                                                                     "物理", vector<double>{1.969}, vector<double>{1.83}, "物理", vector<double>{3.16}, vector<double>{2.93},
                                                                                     E_level, 0.5, false, attribute_data(0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0), "雷", vector<double>{2.491, 0.893}, vector<double>{2.344, 0.84}, vector<double>{2.11, 0.756}, vector<double>{1.992, 0.714},
                                                                                     Q_level, 90, false, attribute_data(0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0), "雷",
                                                                                     vector<double>{8.52 + 0.0826 * 60, 0.935 + 0.0154 * 60, 0.919 + 0.0154 * 60, 1.125 + 0.0154 * 60, 0.646 + 0.0154 * 60, 0.646 + 0.0154 * 60, 1.546 + 0.0154 * 60, 1.288 + 0.0154 * 60, 1.555 + 0.0154 * 60, 3.82 + 0.0154 * 60},
                                                                                     vector<double>{8.02 + 0.0778 * 60, 0.89 + 0.0145 * 60, 0.874 + 0.0145 * 60, 1.07 + 0.0145 * 60, 0.614 + 0.0145 * 60, 0.614 + 0.0145 * 60, 1.471 + 0.0145 * 60, 1.225 + 0.0145 * 60, 1.479 + 0.0145 * 60, 3.6 + 0.0154 * 60},
                                                                                     vector<double>{7.21 + 0.07 * 60, 0.798 + 0.0131 * 60, 0.784 + 0.0131 * 60, 0.96 + 0.0131 * 60, 0.551 + 0.0131 * 60, 0.551 + 0.0131 * 60, 1.319 + 0.0131 * 60, 1.099 + 0.0131 * 60, 1.327 + 0.0131 * 60, 3.16 + 0.0154 * 60},
                                                                                     vector<double>{6.81 + 0.0661 * 60, 0.752 + 0.0123 * 60, 0.739 + 0.0123 * 60, 0.905 + 0.0123 * 60, 0.52 + 0.0123 * 60, 0.52 + 0.0123 * 60, 1.244 + 0.0123 * 60, 1.036 + 0.0123 * 60, 1.251 + 0.0123 * 60, 2.93 + 0.0154 * 60},
                                                                                     constellation)
{}

vector<pair<double, double>> Raiden::get_Q_time(const Single_Attack *single_attack)
{
    vector<pair<double, double>> result;
    double Q_release_time = -1;
    for (auto i: single_attack->team_config->rotation)
    {
        //time up
        if (Q_release_time != -1 && i->attack_time > Q_release_time + 7)
        {
            result.emplace_back(Q_release_time, Q_release_time + 7);
            Q_release_time = -1;
        }
        //switch
        if (Q_release_time != -1 && i->c_point != this && i->action == "switch")
        {
            result.emplace_back(Q_release_time, i->attack_time);
            Q_release_time = -1;
        }
        //Q
        if (Q_release_time == -1 && i->c_point == this && i->action == "hit" && i->attack_way == "Q" && i->rate_pos == 0)
            Q_release_time = i->attack_time;
    }
    if (Q_release_time != -1) result.emplace_back(Q_release_time, single_attack->team_config->rotation_time + 0.001);
    return result;
}

void Raiden::get_recharge(const Single_Attack *single_attack, double &Q_energy_modify, double &energy)
{
    if (single_attack->attack_config->c_point == this) Q_energy_modify = Q_energy;
    //skill:E
    for (auto i: single_attack->team_config->rotation)
        if (i->c_point == this && i->action == "hit" && i->attack_way == "E" && i->rate_pos != 0)
            energy += E_energy * (single_attack->attack_config->c_point->get_ele_type() == ele_type ? 3 : 1) * (get_front(single_attack->team_config, i->attack_time) == single_attack->attack_config->c_point ? 1 : 0.6);
    //skill:Q talent 2
    double typical_recharge = 2.7;
    double Q_hit_time_point = -11;
    int count = 0;
    for (auto i: single_attack->team_config->rotation)
        if (i->c_point == this && i->action == "hit" && i->attack_way == "Q" && i->rate_pos != 0)
        {
            if (i->attack_time > Q_hit_time_point + 10) count = 0;
            if (i->attack_time >= Q_hit_time_point + 1 && count < 5)
            {
                Q_energy_modify -= 2.5 * (1 + (typical_recharge - 1) * 0.6);
                Q_hit_time_point = i->attack_time;
                count++;
            }
        }
}

attribute_data<int> Raiden::get_useful_attribute(const Single_Attack *single_attack)
{
    attribute_data<int> result = Character::get_useful_attribute(single_attack);
    //talent 2
    if (single_attack->attack_config->c_point == this &&
        single_attack->attack_config->action == "hit" &&
        single_attack->attack_config->c_point->get_attack_ele_type(single_attack) == "雷")
        result = result + attribute_data("元素充能效率", 1);
    return result;
}

attribute_data<double> Raiden::get_buff(const Single_Attack *single_attack)
{
    attribute_data<double> result = Character::get_buff(single_attack);
    //skill:E
    for (auto i: single_attack->team_config->rotation)
        if (i->c_point == this && i->action == "release" && i->attack_way == "E")
            if (single_attack->attack_config->action == "hit" &&
                single_attack->attack_config->attack_way == "Q" &&
                check_time_constrain(i->attack_time, i->attack_time + 25, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
            {
                result = result + attribute_data("伤害加成", 0.003 * single_attack->attack_config->c_point->Q_energy);
                break;
            }
    //constellation 2
    if (constellation >= 2)
    {
        auto Q_time = get_Q_time(single_attack);
        for (auto &i: Q_time)
            if (single_attack->attack_config->c_point == this &&
                single_attack->attack_config->action == "hit" &&
                check_time_constrain(i.first, i.second, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
            {
                result = result + attribute_data("防御无视", 0.6);
                break;
            }
    }
    //constellation 4
    if (constellation >= 4)
    {
        auto Q_time = get_Q_time(single_attack);
        for (auto &i: Q_time)
            if (single_attack->attack_config->c_point != this &&
                single_attack->attack_config->action == "hit" &&
                check_time_constrain(i.second, i.second + 10, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
            {
                result = result + attribute_data("攻击力", 0.3);
                break;
            }
    }
    return result;
}

attribute_data<double> Raiden::get_panel_convert(const Single_Attack *single_attack, attribute_data<double> panel)
{
    attribute_data<double> result = Character::get_panel_convert(single_attack, panel);
    //talent 2
    if (single_attack->attack_config->c_point == this &&
        single_attack->attack_config->action == "hit" &&
        single_attack->attack_config->c_point->get_attack_ele_type(single_attack) == "雷")
        result = result + attribute_data("伤害加成", (panel.data["元素充能效率"] - 1) * 0.4);
    return result;
}

Ayaka::Ayaka(int A_level, int E_level, int Q_level, int constellation) : Character("神里绫华", "ayaka", "冰", "单手剑", 12858, 342, 784, attribute_data("暴击伤害", 0.384),
                                                                                   A_level, attribute_data(0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0), "物理", vector<double>{0.904, 0.962, 1.238, 0.448, 0.448, 0.448, 1.545}, vector<double>{0.84, 0.894, 1.15, 0.416, 0.416, 0.416, 1.436},
                                                                                   "物理", vector<double>{1.09}, vector<double>{1.013}, "物理", vector<double>{3.16}, vector<double>{2.93},
                                                                                   E_level, 4.5, false, attribute_data(0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0), "冰", vector<double>{5.083}, vector<double>{4.784}, vector<double>{4.305}, vector<double>{4.066},
                                                                                   Q_level, 80, true, attribute_data(0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0), "冰", vector<double>{2.386, 3.58}, vector<double>{2.246, 3.369}, vector<double>{2.021, 3.032}, vector<double>{1.909, 2.864},
                                                                                   constellation)
{}

string Ayaka::get_attack_ele_type(const Single_Attack *single_attack)
{
    string result = Character::get_attack_ele_type(single_attack);
    //dash
    double dash_time = -1;
    for (auto i: single_attack->team_config->rotation)
    {
        //time up
        if (dash_time != -1 && i->attack_time > dash_time + 5) dash_time = -1;
        //dash
        if (i->c_point == this && i->action == "dash") dash_time = i->attack_time;
        //switch
        if (i->c_point != this && i->action == "switch") dash_time = -1;

        if (single_attack->attack_config->c_point == this &&
            single_attack->attack_config->action == "hit" &&
            "A" <= single_attack->attack_config->attack_way &&
            i == single_attack->attack_config && dash_time != -1)
        {
            result = "冰";
            break;
        }
    }
    return result;
}

void Ayaka::get_recharge(const Single_Attack *single_attack, double &Q_energy_modify, double &energy)
{
    if (single_attack->attack_config->c_point == this) Q_energy_modify = Q_energy;
    //skill:E
    for (auto i: single_attack->team_config->rotation)
        if (i->c_point == this && i->action == "hit" && i->attack_way == "E")
            energy += E_energy * (single_attack->attack_config->c_point->get_ele_type() == ele_type ? 3 : 1) * (this == single_attack->attack_config->c_point ? 1 : 0.6);
}

attribute_data<double> Ayaka::get_buff(const Single_Attack *single_attack)
{
    attribute_data<double> result = Character::get_buff(single_attack);
    //talent 1
    for (auto &i: single_attack->team_config->rotation)
        if (i->c_point == this && i->action == "release" && i->attack_way == "E")
            if (single_attack->attack_config->c_point == this &&
                single_attack->attack_config->action == "hit" &&
                (single_attack->attack_config->attack_way == "平A" || single_attack->attack_config->attack_way == "重A") &&
                check_time_constrain(i->attack_time, i->attack_time + 6, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
            {
                result = result + attribute_data("伤害加成", 0.3);
                break;
            }
    //talent 2
    for (auto &i: single_attack->team_config->rotation)
        if (i->c_point == this && i->action == "dash")
            if (single_attack->attack_config->c_point == this &&
                single_attack->attack_config->action == "hit" &&
                single_attack->attack_config->c_point->get_attack_ele_type(single_attack) == "冰" &&
                check_time_constrain(i->attack_time, i->attack_time + 10, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
            {
                result = result + attribute_data("伤害加成", 0.18);
                break;
            }
    //constellation 4
    if (constellation >= 4)
    {
        for (auto &i: single_attack->team_config->rotation)
            if (i->c_point == this && i->attack_way == "Q" && i->action == "hit")
                if (single_attack->attack_config->action == "hit" &&
                    check_time_constrain(i->attack_time, i->attack_time + 6, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
                {
                    result = result + attribute_data("防御削弱", 0.3);
                    break;
                }
    }
    return result;
}

Ganyu::Ganyu(int A_level, int E_level, int Q_level, int constellation) : Character("甘雨", "ganyu", "冰", "弓", 9797, 335, 630, attribute_data("暴击伤害", 0.384),
                                                                                   A_level, attribute_data(0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0), "物理", vector<double>{0.627, 0.704, 0.899, 0.899, 0.954, 1.139}, vector<double>{0.583, 0.654, 0.836, 0.836, 0.886, 1.059},
                                                                                   "冰", vector<double>{2.3, 3.92}, vector<double>{2.18, 3.7}, "物理", vector<double>{2.81}, vector<double>{2.61},
                                                                                   E_level, 2, true, attribute_data(0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0), "冰", vector<double>{2.81, 2.81}, vector<double>{2.64, 2.64}, vector<double>{2.38, 2.38}, vector<double>{2.24, 2.24},
                                                                                   Q_level, 60, true, attribute_data(0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0), "冰", vector<double>{1.49}, vector<double>{1.41}, vector<double>{1.26}, vector<double>{1.19},
                                                                                   constellation)
{}

void Ganyu::get_recharge(const Single_Attack *single_attack, double &Q_energy_modify, double &energy)
{
    if (single_attack->attack_config->c_point == this) Q_energy_modify = Q_energy;
    //skill:E
    for (auto i: single_attack->team_config->rotation)
        if (i->c_point == this && i->action == "hit" && i->attack_way == "E")
            energy += E_energy * (single_attack->attack_config->c_point->get_ele_type() == ele_type ? 3 : 1) * (get_front(single_attack->team_config, i->attack_time) == single_attack->attack_config->c_point ? 1 : 0.6);
    //constellation 1
    if (single_attack->attack_config->c_point == this && constellation >= 1)
    {
        for (auto i: single_attack->team_config->rotation)
            if (i->c_point == this && i->action == "hit" && i->attack_way == "重A" && i->rate_pos == 0)
                Q_energy_modify -= 2;
    }
}

attribute_data<double> Ganyu::get_buff(const Single_Attack *single_attack)
{
    attribute_data<double> result = Character::get_buff(single_attack);
    //talent 1
    for (auto i: single_attack->team_config->rotation)
        if (i->c_point == this && i->action == "release" && i->attack_way == "重A")
            if (single_attack->attack_config->c_point == this &&
                single_attack->attack_config->action == "hit" &&
                single_attack->attack_config->attack_way == "重A" &&
                check_time_constrain(i->attack_time, i->attack_time + 5, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
            {
                result = result + attribute_data("暴击率", 0.2);
                break;
            }
    //talent 2
    for (auto i: single_attack->team_config->rotation)
        if (i->c_point == this && i->action == "release" && i->attack_way == "Q")
            if (single_attack->attack_config->c_point == get_front(single_attack->team_config, single_attack->attack_config->attack_time) &&
                single_attack->attack_config->action == "hit" &&
                check_time_constrain(i->attack_time + 2, i->attack_time + 17, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time) &&
                single_attack->attack_config->c_point->get_attack_ele_type(single_attack) == "冰")
            {
                result = result + attribute_data("伤害加成", 0.2);
                break;
            }
    //constellation 1
    if (constellation >= 1)
    {
        for (auto i: single_attack->team_config->rotation)
            if (i->c_point == this && i->action == "hit" && i->attack_way == "重A")
                if (single_attack->attack_config->action == "hit" &&
                    check_time_constrain(i->attack_time, i->attack_time + 6, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time) &&
                    single_attack->attack_config->c_point->get_attack_ele_type(single_attack) == "冰")
                {
                    result = result + attribute_data("抗性削弱", 0.15);
                    break;
                }
    }
    //constellation 4
    if (constellation >= 4)
    {
        vector<pair<double, double>> buff_time;
        double buff_start_time = -1;
        double buff_end_time = -1;
        for (auto i: single_attack->team_config->rotation)
        {
            //time up
            if (buff_start_time != -1 && i->attack_time > buff_end_time)
            {
                buff_time.emplace_back(buff_start_time, buff_end_time);
                buff_start_time = buff_end_time = -1;
            }
            //Q
            if (i->c_point == this && i->action == "release" && i->attack_way == "Q")
            {
                if (buff_start_time == -1)
                {
                    buff_start_time = i->attack_time + 2;
                    buff_end_time = i->attack_time + 20;
                }
                else buff_end_time = i->attack_time + 20;
            }
        }
        if (buff_start_time != -1) buff_time.emplace_back(buff_start_time, single_attack->team_config->rotation.back()->attack_time + 0.001);

        for (auto &i: buff_time)
            if (single_attack->attack_config->action == "hit" &&
                check_time_constrain(i.first, i.second, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
            {
                double time_diff = (single_attack->attack_config->attack_time - i.first > 0) ?
                                   (single_attack->attack_config->attack_time - i.first) :
                                   (single_attack->attack_config->attack_time - i.first + single_attack->team_config->rotation_time);
                result = result + attribute_data("伤害加成", min(0.25, 0.05 + 0.05 * (int) (time_diff / 3)));
                break;
            }
    }
    return result;
}

Nahida::Nahida(int A_level, int E_level, int Q_level, int constellation) : Character("纳西妲", "nahida", "草", "法器", 10360, 299, 630, attribute_data("元素精通", 115.0),
                                                                                     A_level, attribute_data(0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0), "草", vector<double>{0.726, 0.666, 0.826, 1.051}, vector<double>{0.685, 0.629, 0.78, 0.993},
                                                                                     "草", vector<double>{2.376}, vector<double>{2.244}, "草", vector<double>{2.81}, vector<double>{2.61},
                                                                                     E_level, 3, false, attribute_data(0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0), "草", vector<double>{2.771, 2.193}, vector<double>{2.608, 2.064}, vector<double>{2.347, 1.858}, vector<double>{2.217, 1.754},
                                                                                     Q_level, 50, false, attribute_data(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0), "草", vector<double>{}, vector<double>{}, vector<double>{}, vector<double>{},
                                                                                     constellation)
{}

void Nahida::get_recharge(const Single_Attack *single_attack, double &Q_energy_modify, double &energy)
{
    if (single_attack->attack_config->c_point == this) Q_energy_modify = Q_energy;
    //E
    double last_E_generate = -7;
    for (auto i: single_attack->team_config->rotation)
        if (i->c_point == this && i->action == "hit" && i->attack_way == "E" && i->rate_pos == 1 && i->attack_time >= last_E_generate + 7)
        {
            energy += E_energy * (single_attack->attack_config->c_point->get_ele_type() == ele_type ? 3 : 1) * (get_front(single_attack->team_config, i->attack_time) == single_attack->attack_config->c_point ? 1 : 0.6);
            last_E_generate = i->attack_time;
        }
}

attribute_data<double> Nahida::get_buff(const Single_Attack *single_attack)
{
    attribute_data<double> result = Character::get_buff(single_attack);
    //constellation 1
    int water_num = (constellation >= 1 ? 1 : 0) +
                    (single_attack->team_config->team[0]->c_point->get_ele_type() == "水" ? 1 : 0) +
                    (single_attack->team_config->team[1]->c_point->get_ele_type() == "水" ? 1 : 0) +
                    (single_attack->team_config->team[2]->c_point->get_ele_type() == "水" ? 1 : 0) +
                    (single_attack->team_config->team[3]->c_point->get_ele_type() == "水" ? 1 : 0);
    double Q_extend_time = 0;
    if (water_num >= 2)
    {
        if (Q_level == 13) Q_extend_time = 10.66;
        else if (Q_level == 12) Q_extend_time = 10.03;
        else if (Q_level == 10) Q_extend_time = 9.03;
        else Q_extend_time = 8.53;
    }
    else if (water_num == 1)
    {
        if (Q_level == 13) Q_extend_time = 7.11;
        else if (Q_level == 12) Q_extend_time = 6.69;
        else if (Q_level == 10) Q_extend_time = 6.02;
        else Q_extend_time = 5.68;
    }
    int fire_num = (constellation >= 1 ? 1 : 0) +
                   (single_attack->team_config->team[0]->c_point->get_ele_type() == "火" ? 1 : 0) +
                   (single_attack->team_config->team[1]->c_point->get_ele_type() == "火" ? 1 : 0) +
                   (single_attack->team_config->team[2]->c_point->get_ele_type() == "火" ? 1 : 0) +
                   (single_attack->team_config->team[3]->c_point->get_ele_type() == "火" ? 1 : 0);
    double bonus = 0;
    if (fire_num >= 2)
    {
        if (Q_level == 13) bonus = 0.474;
        else if (Q_level == 12) bonus = 0.446;
        else if (Q_level == 10) bonus = 0.402;
        else bonus = 0.379;
    }
    else if (fire_num == 1)
    {
        if (Q_level == 13) bonus = 0.316;
        else if (Q_level == 12) bonus = 0.298;
        else if (Q_level == 10) bonus = 0.268;
        else bonus = 0.253;
    }

    //Q
    for (auto i: single_attack->team_config->rotation)
        if (i->c_point == this && i->action == "release" && i->attack_way == "Q")
            if (single_attack->attack_config->c_point == this &&
                single_attack->attack_config->action == "hit" &&
                single_attack->attack_config->attack_way == "E" &&
                single_attack->attack_config->rate_pos != 0 &&
                check_time_constrain(i->attack_time + 2, i->attack_time + 17 + Q_extend_time, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
            {
                result = result + attribute_data("伤害加成", bonus);
                break;
            }
    //talent 1
    double typical_max_mastery = 800;
    for (auto i: single_attack->team_config->rotation)
        if (i->c_point == this && i->action == "release" && i->attack_way == "Q")
            if (single_attack->attack_config->c_point == get_front(single_attack->team_config, single_attack->attack_config->attack_time) &&
                single_attack->attack_config->action == "hit" &&
                check_time_constrain(i->attack_time + 2, i->attack_time + 17 + Q_extend_time, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
            {
                single_attack->converted_percentage = single_attack->converted_percentage + attribute_data("元素精通", 0.25 * typical_max_mastery);
                break;
            }
    //constellation 2
    if (constellation >= 2)
    {
        double E_release_time = -26;
        double quicken_time = -9;
        for (auto i: single_attack->team_config->rotation)
        {
            if (i->c_point == this && i->action == "release" && i->attack_way == "E") E_release_time = i->attack_time;
            if (i->action == "hit" && "激化" <= i->react_type) quicken_time = i->attack_time;
            if (i == single_attack->attack_config &&
                single_attack->attack_config->action == "hit" &&
                check_time_constrain(E_release_time, E_release_time + 25, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time) &&
                check_time_constrain(quicken_time, quicken_time + 8, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
            {
                result = result + attribute_data("防御削弱", 0.3);
                break;
            }
        }
    }
    //constellation 4
    if (constellation >= 4)
    {
        for (auto i: single_attack->team_config->rotation)
            if (i->c_point == this && i->action == "release" && i->attack_way == "E")
                if (single_attack->attack_config->c_point == this &&
                    single_attack->attack_config->action == "hit" &&
                    check_time_constrain(i->attack_time, i->attack_time + 25, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
                {
                    result = result + attribute_data("元素精通", 100.0);
                    break;
                }
    }
    return result;
}

attribute_data<double> Nahida::get_total_convert(const Single_Attack *single_attack, attribute_data<double> panel)
{
    attribute_data<double> result = Character::get_total_convert(single_attack, panel);
    //talent 2
    if (single_attack->attack_config->c_point == this &&
        single_attack->attack_config->action == "hit" &&
        single_attack->attack_config->attack_way == "E" &&
        single_attack->attack_config->rate_pos == 1)
    {
        result = result + attribute_data("伤害加成", min((panel.data["元素精通"] - 200.0) * 0.001, 0.8));
        result = result + attribute_data("暴击率", min((panel.data["元素精通"] - 200.0) * 0.0003, 0.24));
    }
    return result;
}

double Nahida::get_extra_rate(const Single_Attack *single_attack, attribute_data<double> panel)
{
    double result = Character::get_extra_rate(single_attack, panel);
    //E
    if (single_attack->attack_config->c_point == this &&
        single_attack->attack_config->action == "hit" &&
        single_attack->attack_config->attack_way == "E" &&
        single_attack->attack_config->rate_pos == 1)
    {
        if (E_level == 13) result = result + 4.386 * panel.data["元素精通"];
        else if (E_level == 12) result = result + 4.128 * panel.data["元素精通"];
        else if (E_level == 10) result = result + 3.715 * panel.data["元素精通"];
        else result = result + 3.509 * panel.data["元素精通"];
    }
    return result;
}

Yelan::Yelan(int A_level, int E_level, int Q_level, int constellation) : Character("夜兰", "yelan", "水", "弓", 14450, 244, 548, attribute_data("暴击率", 0.192),
                                                                                   A_level, attribute_data(0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0), "物理", vector<double>{0.804, 0.772, 1.02, 0.643, 0.643}, vector<double>{0.747, 0.717, 0.948, 0.597, 0.597},
                                                                                   "物理", vector<double>{2.23}, vector<double>{2.11}, "物理", vector<double>{2.81}, vector<double>{2.61},
                                                                                   E_level, 4, false, attribute_data(1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0), "水", vector<double>{0}, vector<double>{0}, vector<double>{0}, vector<double>{0},
                                                                                   Q_level, 70, false, attribute_data(1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0), "水", vector<double>{0, 0, 0}, vector<double>{0, 0, 0}, vector<double>{0, 0, 0}, vector<double>{0, 0, 0},
                                                                                   constellation)
{}

void Yelan::get_recharge(const Single_Attack *single_attack, double &Q_energy_modify, double &energy)
{
    if (single_attack->attack_config->c_point == this) Q_energy_modify = Q_energy;
    //skill:E
    for (auto i: single_attack->team_config->rotation)
        if (i->c_point == this && i->action == "hit" && i->attack_way == "E")
            energy += E_energy * (single_attack->attack_config->c_point->get_ele_type() == ele_type ? 3 : 1) * (this == single_attack->attack_config->c_point ? 1 : 0.6);
}

attribute_data<double> Yelan::get_buff(const Single_Attack *single_attack)
{
    attribute_data<double> result = Character::get_buff(single_attack);
    //talent 1
    int diff_ele_num = 1;
    if (single_attack->team_config->team[1]->c_point->get_ele_type() != single_attack->team_config->team[0]->c_point->get_ele_type())
        diff_ele_num += 1;
    if (single_attack->team_config->team[2]->c_point->get_ele_type() != single_attack->team_config->team[0]->c_point->get_ele_type() &&
        single_attack->team_config->team[2]->c_point->get_ele_type() != single_attack->team_config->team[1]->c_point->get_ele_type())
        diff_ele_num += 1;
    if (single_attack->team_config->team[3]->c_point->get_ele_type() != single_attack->team_config->team[0]->c_point->get_ele_type() &&
        single_attack->team_config->team[3]->c_point->get_ele_type() != single_attack->team_config->team[1]->c_point->get_ele_type() &&
        single_attack->team_config->team[3]->c_point->get_ele_type() != single_attack->team_config->team[2]->c_point->get_ele_type())
        diff_ele_num += 1;
    if (single_attack->attack_config->c_point == this &&
        single_attack->attack_config->action == "hit")
    {
        if (diff_ele_num <= 3) result = result + attribute_data("生命值", 0.06 * diff_ele_num);
        else result = result + attribute_data("生命值", 0.3);
    }
    //talent 2
    vector<pair<double, double>> buff_time;
    double buff_start_time = -1;
    double buff_end_time = -1;
    for (auto i: single_attack->team_config->rotation)
    {
        //time up
        if (buff_start_time != -1 && i->attack_time > buff_end_time)
        {
            buff_time.emplace_back(buff_start_time, buff_end_time);
            buff_start_time = buff_end_time = -1;
        }
        //Q
        if (i->c_point == this && i->action == "hit" && i->attack_way == "Q" && i->rate_pos == 0)
        {
            if (buff_start_time != -1) buff_time.emplace_back(buff_start_time, buff_end_time);
            buff_start_time = i->attack_time;
            buff_end_time = i->attack_time + 15;
        }
    }
    if (buff_start_time != -1) buff_time.emplace_back(buff_start_time, single_attack->team_config->rotation.back()->attack_time + 0.001);

    for (auto &i: buff_time)
        if (single_attack->attack_config->c_point == get_front(single_attack->team_config, single_attack->attack_config->attack_time) &&
            single_attack->attack_config->action == "hit" &&
            check_time_constrain(i.first, i.second, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time))
        {
            double time_diff = (single_attack->attack_config->attack_time - i.first > 0) ?
                               (single_attack->attack_config->attack_time - i.first) :
                               (single_attack->attack_config->attack_time - i.first + single_attack->team_config->rotation_time);
            result = result + attribute_data("伤害加成", min(0.5, 0.01 + 0.035 * (int) time_diff));
            break;
        }
    //constellation 4
    if (constellation >= 4)
    {
        int count = 0;
        for (auto i: single_attack->team_config->rotation)
            if (i->c_point == this && i->action == "hit" && i->attack_way == "E")
                if (single_attack->attack_config->action == "hit" &&
                    check_time_constrain(i->attack_time, i->attack_time + 25, single_attack->attack_config->attack_time, single_attack->team_config->rotation_time) &&
                    count < 4)
                {
                    result = result + attribute_data("生命值", 0.1);
                    count++;
                }
    }
    return result;
}

double Yelan::get_extra_rate(const Single_Attack *single_attack, attribute_data<double> panel)
{
    double result = Character::get_extra_rate(single_attack, panel);
    //E Q talent 2
    if (single_attack->attack_config->c_point == this &&
        single_attack->attack_config->action == "hit" &&
        single_attack->attack_config->attack_way == "E")
    {
        if (E_level == 13) result = result + 0.481 * life * panel.data["生命值"];
        else if (E_level == 12) result = result + 0.452 * life * panel.data["生命值"];
        else if (E_level == 10) result = result + 0.407 * life * panel.data["生命值"];
        else result = result + 0.384 * life * panel.data["生命值"];
    }
    else if (single_attack->attack_config->c_point == this &&
             single_attack->attack_config->action == "hit" &&
             single_attack->attack_config->attack_way == "Q")
    {
        if (Q_level == 13)
        {
            if (single_attack->attack_config->rate_pos == 0) result = result + 0.1553 * life * panel.data["生命值"];
            else if (single_attack->attack_config->rate_pos == 1) result = result + 0.1035 * life * panel.data["生命值"];
            else if (constellation >= 2 && single_attack->attack_config->rate_pos == 2) result = result + 0.14 * life * panel.data["生命值"];
        }
        else if (Q_level == 12)
        {
            if (single_attack->attack_config->rate_pos == 0) result = result + 0.1462 * life * panel.data["生命值"];
            else if (single_attack->attack_config->rate_pos == 1) result = result + 0.0974 * life * panel.data["生命值"];
            else if (constellation >= 2 && single_attack->attack_config->rate_pos == 2) result = result + 0.14 * life * panel.data["生命值"];
        }
        else if (Q_level == 10)
        {
            if (single_attack->attack_config->rate_pos == 0) result = result + 0.1315 * life * panel.data["生命值"];
            else if (single_attack->attack_config->rate_pos == 1) result = result + 0.0877 * life * panel.data["生命值"];
            else if (constellation >= 2 && single_attack->attack_config->rate_pos == 2) result = result + 0.14 * life * panel.data["生命值"];
        }
        else if (Q_level == 9)
        {
            if (single_attack->attack_config->rate_pos == 0) result = result + 0.1242 * life * panel.data["生命值"];
            else if (single_attack->attack_config->rate_pos == 1) result = result + 0.0828 * life * panel.data["生命值"];
            else if (constellation >= 2 && single_attack->attack_config->rate_pos == 2) result = result + 0.14 * life * panel.data["生命值"];
        }
    }
    return result;
}