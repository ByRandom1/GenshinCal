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

int Character::get_life() const
{
    return life;
}

int Character::get_atk() const
{
    return atk;
}

int Character::get_def() const
{
    return def;
}

attribute_data<double> Character::get_break()
{
    return break_value;
}

string Character::get_ele_type(const string &attack_way)
{
    if (attack_way == "平A") return normal_A_ele_type;
    else if (attack_way == "重A") return heavy_A_ele_type;
    else if (attack_way == "下落A") return down_A_ele_type;
    else if (attack_way == "E") return E_ele_type;
    else if (attack_way == "Q") return Q_ele_type;
    else return ele_type;
}

attribute_data<int> Character::get_useful_attribute(const string &attack_way)
{
    if (attack_way == "平A" || attack_way == "重A" || attack_way == "下落A") return A_useful_attributes;
    else if (attack_way == "E") return E_useful_attributes;
    else if (attack_way == "Q") return Q_useful_attributes;
    else return {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
}

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
    return 0;
}

attribute_data<double> Character::get_extra(const Single_Attack *attack_config)
{
    return {};
}

attribute_data<double> Character::get_team(const Single_Attack *attack_config)
{
    return {};
}

void Character::get_recharge_energy(Combination *ori_team[], double &Q_energy_modify, double &energy)
{}

attribute_data<double> Character::get_convert(const Single_Attack *attack_config, attribute_data<double> panel)
{
    return {};
}

double Character::get_extra_rate(const Single_Attack *attack_config, attribute_data<double> panel)
{
    return 0;
}

double Character::get_react_bonus(const Single_Attack *attack_config, string react_type)
{
    return 0;
}

Hutao::Hutao(int A_level, int E_level, int Q_level, int constellation) : Character("胡桃", "hutao", "火", "长柄武器", 15552, 107, 876, attribute_data("暴击伤害", 0.384),
                                                                                   A_level, attribute_data(1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0), "火", vector<double>{0.836, 0.861, 1.089, 1.171, 0.594, 0.628, 1.534}, vector<double>{0.789, 0.812, 1.027, 1.104, 0.56, 0.592, 1.446},
                                                                                   "火", vector<double>{2.426}, vector<double>{2.287}, "火", vector<double>{2.92}, vector<double>{2.75},
                                                                                   E_level, 2.5, false, attribute_data(1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0), "火", vector<double>{1.36}, vector<double>{1.28}, vector<double>{1.15}, vector<double>{1.09},
                                                                                   Q_level, 60, false, attribute_data(1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0), "火", vector<double>{7.06}, vector<double>{6.76}, vector<double>{6.17}, vector<double>{5.88},
                                                                                   constellation)
{}

attribute_data<double> Hutao::get_extra(const Single_Attack *attack_config)
{
    attribute_data<double> result;
    //talent:半血、火伤
    result = result + attribute_data("伤害加成", 0.33);
    return result;
}

attribute_data<double> Hutao::get_team(const Single_Attack *attack_config)
{
    attribute_data<double> result;
    //talent:E结束后（11s）队友暴击率提升12% 8s
    for (int i = 1; i < 4; ++i)
        if (attack_config->team[i]->c_point == this)
        {
            for (auto x: attack_config->team[i]->ori_attack_list)
                if (x->attack_way == "E" && "release" <= x->release_or_hit &&
                    check_time_constrain(x->attack_time, attack_config->attack_time, attack_config->rotation_time, 8 + 11))
                {
                    result = result + attribute_data("暴击率", 0.12);
                    break;
                }
            break;
        }
    return result;
}

void Hutao::get_recharge_energy(Combination *ori_team[], double &Q_energy_modify, double &energy)
{
    //E下A，2.5/5s
}

attribute_data<double> Hutao::get_convert(const Single_Attack *attack_config, attribute_data<double> panel)
{
    attribute_data<double> result;
    //skill:E下 生命->攻击
    result = result + attribute_data("攻击力", min(panel.data["生命值"] * 0.0626 * life / atk, 4.0));
    return result;
}

double Hutao::get_extra_rate(const Single_Attack *attack_config, attribute_data<double> panel)
{
    double result = 0;
    //constellation 2:E +10%life
    if (constellation >= 2 && attack_config->attack_way == "E" && "hit" <= attack_config->release_or_hit)
        result = result + 0.1 * life * panel.data["生命值"];
    return result;
}