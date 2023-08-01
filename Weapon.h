//
// Created by 陈劭彬 on 2023/7/25.
//

#ifndef GENSHINCAL_WEAPON_H
#define GENSHINCAL_WEAPON_H

#include "Basic_Elements.h"

class Team_Config;

class Single_Attack;

class Config_File;

class Weapon
{
    //static data (unconditional)
protected:
    string name;
    string english_name;
    string weapon_type;
    int atk;
    attribute_data<double> break_value;
    int level;

public:
    Weapon(string name_,
           string english_name_,
           string weapon_type_,
           int atk_,
           const attribute_data<double> &break_value_,
           int level_);

    string get_name();

    string get_english_name();

    string get_weapon_type();

    int get_atk() const;

    attribute_data<double> get_break(const string &ele_type);

    virtual attribute_data<int> get_useful_attribute(const Single_Attack *attack_config);

    virtual attribute_data<double> get_extra(const Single_Attack *attack_config);

    virtual attribute_data<double> get_team(const Single_Attack *other_attack_config);

    virtual void get_recharge_energy(const Team_Config *team_config, double &Q_energy_modify, double &energy);

    virtual attribute_data<double> get_convert(const Single_Attack *attack_config, attribute_data<double> panel);

    virtual double get_extra_rate(const Single_Attack *attack_config, attribute_data<double> panel);

    virtual double get_react_bonus(const Single_Attack *attack_config, string react_type);

    friend void generate_gcsim_script(Config_File *config);
};

#endif //GENSHINCAL_WEAPON_H
