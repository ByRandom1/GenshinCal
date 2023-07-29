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
protected:
    //static data (unconditional)
    string name;
    string english_name;
    string ele_type;
    string weapon_type;
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
    vector<vector<double>> E;
    int Q_level;
    double Q_energy;
    bool Q_lockface;
    attribute_data<int> Q_useful_attributes;
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
              attribute_data<double> break_value_,
              int A_level_,
              attribute_data<int> A_useful_attributes_,
              string normal_A_ele_type_,
              vector<double> normal_A_10, vector<double> normal_A_9,
              string heavy_A_ele_type_,
              vector<double> heavy_A_10, vector<double> heavy_A_9,
              string down_A_ele_type_,
              vector<double> down_A_10, vector<double> down_A_9,
              int E_level_,
              double E_energy_,
              bool E_lockface_,
              attribute_data<int> E_useful_attributes_,
              vector<double> E_13, vector<double> E_12, vector<double> E_10, vector<double> E_9,
              int Q_level_,
              int Q_energy_,
              bool Q_lockface_,
              attribute_data<int> Q_useful_attributes_,
              vector<double> Q_13, vector<double> Q_12, vector<double> Q_10, vector<double> Q_9,
              int constellation_);

    int get_life();

    int get_atk();

    int get_def();

    attribute_data<double> get_break();

    string get_ele_type(string attack_way);

    double get_rate(string attack_way, int pos);

    attribute_data<int> get_useful_attribute(string attack_way);

    virtual attribute_data<double> get_extra(const Single_Attack *attack_config) = 0;

    virtual attribute_data<int> modify_allowed_attribute(const Single_Attack *attack_config) = 0;

    virtual attribute_data<double> get_team(const Single_Attack *attack_config) = 0;

    virtual void get_recharge_energy(const Single_Attack *attack_config, double &Q_energy_modify, double &energy) = 0;

    virtual attribute_data<double> get_convert(const Single_Attack *attack_config, attribute_data<double> panel) = 0;

    virtual double get_extra_rate(const Single_Attack *attack_config, attribute_data<double> panel) = 0;

    virtual double get_react_bonus(const Single_Attack *attack_config, string react_type) = 0;

    virtual ~Character() = default;

    friend void generate_gcsim_script(Config_File *config);

    friend Character *find_character_by_name(string name);
};

vector<Character*> Character_list;

Character *find_character_by_name(string name);

void init_Character_list();

#endif //GENSHINCAL_CHARACTER_H
