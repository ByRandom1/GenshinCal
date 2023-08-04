//
// Created by 陈劭彬 on 2023/7/25.
//

#ifndef GENSHINCAL_CHARACTER_H
#define GENSHINCAL_CHARACTER_H

#include "Basic_Elements.h"

using namespace std;

class Single_Attack;

class Config_File;

class Character
{
    //static data (unconditional)
protected:
    string name;
    string english_name;
    string weapon_type;
    int life;
    int atk;
    int def;
    attribute_data<double> break_value;

    string ele_type;
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

    string get_name();

    string get_weapon_type();

    int get_life() const;

    int get_atk() const;

    int get_def() const;

    double get_rate(const string &attack_way, int pos);

    attribute_data<double> get_break(const string &ele_type_);

    virtual string get_ele_type(const Single_Attack *single_attack);

    virtual attribute_data<int> get_useful_attribute(const Single_Attack *single_attack);

    virtual attribute_data<double> get_extra(const Single_Attack *single_attack);

    virtual attribute_data<double> get_team(const Single_Attack *other_single_attack);

    virtual void get_recharge_energy(const Single_Attack *single_attack, double &Q_energy_modify, double &energy);

    virtual attribute_data<double> get_convert(const Single_Attack *single_attack, attribute_data<double> panel);

    virtual double get_extra_rate(const Single_Attack *single_attack, attribute_data<double> panel);

    virtual double get_react_bonus(const Single_Attack *single_attack, string react_type);

    friend void generate_gcsim_script(Config_File *config);

    friend class Raiden;//Q_energy
};

class Hutao : public Character
{
    //4、6命不建构：条件难触发
public:
    Hutao(int A_level, int E_level, int Q_level, int constellation);

    string get_ele_type(const Single_Attack *single_attack) override;

    attribute_data<int> get_useful_attribute(const Single_Attack *single_attack) override;

    attribute_data<double> get_extra(const Single_Attack *single_attack) override;

    attribute_data<double> get_team(const Single_Attack *other_single_attack) override;

    void get_recharge_energy(const Single_Attack *single_attack, double &Q_energy_modify, double &energy) override;

    attribute_data<double> get_convert(const Single_Attack *single_attack, attribute_data<double> panel) override;

    double get_extra_rate(const Single_Attack *single_attack, attribute_data<double> panel) override;

private:
    vector<pair<double, double>> get_E_time(const Single_Attack *single_attack);
};

class Alhaitham : public Character
{
    //1命不建构：不需要
public:
    Alhaitham(int A_level, int E_level, int Q_level, int constellation);

    string get_ele_type(const Single_Attack *single_attack) override;

    attribute_data<double> get_extra(const Single_Attack *single_attack) override;

    attribute_data<double> get_team(const Single_Attack *other_single_attack) override;

    void get_recharge_energy(const Single_Attack *single_attack, double &Q_energy_modify, double &energy) override;

    attribute_data<double> get_convert(const Single_Attack *single_attack, attribute_data<double> panel) override;

    double get_extra_rate(const Single_Attack *single_attack, attribute_data<double> panel) override;

private:
    vector<pair<int, double>> get_mirror_time(const Single_Attack *single_attack);
};

class Raiden : public Character
{
    //天赋1、1命不建构：默认满层愿力；6命不建构
public:
    Raiden(int A_level, int E_level, int Q_level, int constellation);

    attribute_data<int> get_useful_attribute(const Single_Attack *single_attack) override;

    attribute_data<double> get_extra(const Single_Attack *single_attack) override;

    attribute_data<double> get_team(const Single_Attack *other_single_attack) override;

    void get_recharge_energy(const Single_Attack *single_attack, double &Q_energy_modify, double &energy) override;

    attribute_data<double> get_convert(const Single_Attack *single_attack, attribute_data<double> panel) override;

private:
    vector<pair<double, double>> get_Q_time(const Single_Attack *single_attack);
};

class Ayaka :public Character
{
    //1命不建构：不需要；2命不建构：对单；6命不建构
public:
    Ayaka(int A_level, int E_level, int Q_level, int constellation);

    string get_ele_type(const Single_Attack *single_attack) override;

    attribute_data<double> get_extra(const Single_Attack *single_attack) override;

    attribute_data<double> get_team(const Single_Attack *other_single_attack) override;

    void get_recharge_energy(const Single_Attack *single_attack, double &Q_energy_modify, double &energy) override;
};

class Ganyu : public Character
{
    //2命不建构：不需要；6命不建构
public:
    Ganyu(int A_level, int E_level, int Q_level, int constellation);

    attribute_data<double> get_extra(const Single_Attack *single_attack) override;

    attribute_data<double> get_team(const Single_Attack *other_single_attack) override;

    void get_recharge_energy(const Single_Attack *single_attack, double &Q_energy_modify, double &energy) override;
};

#endif //GENSHINCAL_CHARACTER_H
