//
// Created by 陈劭彬 on 2023/7/26.
//

#ifndef GENSHINCAL_DEPLOYMENT_H
#define GENSHINCAL_DEPLOYMENT_H

#include "Basic_Elements.h"
#include "Character.h"
#include "Weapon.h"
#include "Artifact.h"

//cal parameters
extern int max_up_num_per_base;
extern double max_attribute_num_per_pos;
extern int max_entry_num;
extern int artifact_2_2_max_entry_bonus;

struct Combination
{
    Character *c_point;
    Weapon *w_point;
    Artifact *suit1;
    Artifact *suit2;
    string a_main3;
    string a_main4;
    string a_main5;

    Combination(Character *c_point_,
                Weapon *w_point_,
                Artifact *suit1_,
                Artifact *suit2_,
                string a_main3_,
                string a_main4_,
                string a_main5_);
};

struct Attack_Config
{
    Character *c_point;
    string attack_way;
    string release_or_hit;
    int rate_pos;
    bool background;
    string react_type;
    double attack_time;

    Attack_Config(Character *c_point_,
                  string attack_way_,
                  string release_or_hit_,
                  int rate_pos_,
                  bool background_,
                  string react_type_,
                  double attack_time_);
};

struct Team_Config
{
public:
    Combination *team[4];
    int E_energy_num[4];
    string ele_attach_type;
    vector<Attack_Config *> rotation;
    double rotation_time;

    Team_Config(Combination *c1, Combination *c2, Combination *c3, Combination *c4,
                int E_energy_num1, int E_energy_num2, int E_energy_num3, int E_energy_num4,
                string ele_attach_type_,
                vector<Attack_Config *> rotation_,
                double rotation_time_);

    ~Team_Config();
};

class Single_Attack
{
public:
    Combination *self;
    Team_Config *team_config;
    Attack_Config *attack_config;
    //get_data
    int base_life;
    int base_atk;
    int base_def;
    double base_skillrate;
    attribute_data<int> useful;
    attribute_data<double> percentage;
    attribute_data<double> converted_percentage;

    Single_Attack(Combination *self_,
                  Team_Config *team_config_,
                  Attack_Config *attack_config_);

    void get_data(bool &suit1_valid, bool &suit2_valid, bool &main3_valid, bool &main4_valid, bool &main5_valid, double min_recharge);

    double cal_damage(const attribute_data<double> &entry_value, double min_recharge) const;

private:
    void get_react_value(double mastery, double &extra_rate, double &grow_rate, double &extra_damage) const;
};

class Deployment
{
public:
    vector<Single_Attack *> attack_list;
    //get_all_data
    double min_recharge;
    attribute_data<int> collected_useful;
    //cal_optimal_entry_num
    attribute_data<int> entry_num;
    double total_damage;

    Deployment(Combination *self_, Team_Config *team_config_);

    ~Deployment();

    int get_all_data();

    void cal_optimal_entry_num();
};

#endif //GENSHINCAL_DEPLOYMENT_H
