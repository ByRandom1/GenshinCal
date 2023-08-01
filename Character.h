//
// Created by 陈劭彬 on 2023/7/25.
//

#ifndef GENSHINCAL_CHARACTER_H
#define GENSHINCAL_CHARACTER_H

#include "Basic_Elements.h"

using namespace std;

class Single_Attack;

class Combination;

class Config_File;

class Character
{
    //static data (unconditional)
public:
    string name;
    string english_name;
    string ele_type;
    string weapon_type;
protected:
    int life;
    int atk;
    int def;
    attribute_data<double> break_value;
    int A_level;
    attribute_data<int> A_useful_attributes;
    string normal_A_ele_type;
    vector<vector<double>> normal_A;
    string heavy_A_ele_type;
    vector<vector<double>> heavy_A;
    string down_A_ele_type;
    vector<vector<double>> down_A;
    int E_level;
    double E_energy;
    bool E_lockface;
    attribute_data<int> E_useful_attributes;
    string E_ele_type;
    vector<vector<double>> E;
    int Q_level;
    double Q_energy;
    bool Q_lockface;
    attribute_data<int> Q_useful_attributes;
    string Q_ele_type;
    vector<vector<double>> Q;
    int constellation;

public:
    Character(string name_,
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
              int constellation_);

    int get_life() const;

    int get_atk() const;

    int get_def() const;

    attribute_data<double> get_break();

    string get_ele_type(const string &attack_way);

    double get_rate(const string &attack_way, int pos);

    attribute_data<int> get_useful_attribute(const string &attack_way);

    //动作是自己的
    virtual attribute_data<double> get_extra(const Single_Attack *attack_config);

    //动作是别人的
    virtual attribute_data<double> get_team(const Single_Attack *attack_config);

    //[0]是求取充能的人
    virtual void get_recharge_energy(Combination *ori_team[], double &Q_energy_modify, double &energy);

    //动作是自己的
    virtual attribute_data<double> get_convert(const Single_Attack *attack_config, attribute_data<double> panel);

    //动作是自己的
    virtual double get_extra_rate(const Single_Attack *attack_config, attribute_data<double> panel);

    //动作是自己的
    virtual double get_react_bonus(const Single_Attack *attack_config, string react_type);

    friend void generate_gcsim_script(Config_File *config);
};

class Hutao : public Character
{
    //默认半血开E
public:
    Hutao(int A_level, int E_level, int Q_level, int constellation);

    attribute_data<double> get_extra(const Single_Attack *attack_config);

    attribute_data<double> get_team(const Single_Attack *attack_config);

    void get_recharge_energy(Combination *ori_team[], double &Q_energy_modify, double &energy);

    attribute_data<double> get_convert(const Single_Attack *attack_config, attribute_data<double> panel);

    double get_extra_rate(const Single_Attack *attack_config, attribute_data<double> panel);
};

#endif //GENSHINCAL_CHARACTER_H
