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

    int E_energy_time;
    bool require_recharge;

    Combination(Character *c_point_,
                Weapon *w_point_,
                Artifact *suit1_,
                Artifact *suit2_,
                string a_main3_,
                string a_main4_,
                string a_main5_,
                int E_energy_time_,
                bool require_recharge_);
};

class Single_Attack
{
public:
    //team info (global)
    Combination *team[4];
    string ele_attach_type;
    string ele_allow_spread;
    //attack info (independent)
    string attack_way;
    int rate_pos;
    bool background;
    string react_type;
    manual_args args;
    int attack_time;
    //get_data
    int base_life;
    int base_atk;
    int base_def;
    double base_skillrate;
    attribute_data<int> useful;
    attribute_data<double> percentage;
    attribute_data<double> converted_percentage;
    //cal_damage
    double damage;

    Single_Attack(Combination *self,
                  Combination *teammate1,
                  Combination *teammate2,
                  Combination *teammate3,
                  string ele_attach_type_,
                  string ele_allow_spread_,
                  string attack_way_,
                  int rate_pos_,
                  bool background_,
                  string react_type_,
                  int attack_time_,
                  manual_args args_);

    void get_data(bool &suit1_valid, bool &suit2_valid, bool &main3_valid, bool &main4_valid, bool &main5_valid);

    void cal_damage(attribute_data<double> entry_value, double min_recharge);

    void get_react_value(attribute_data<double> &panel, double &extra_rate, double &grow_rate, double &extra_damage);
};

class Deployment
{
public:
    vector<Single_Attack *> rotation;
    //get_all_data
    attribute_data<int> collected_useful;
    double min_recharge;
    //cal_optimal_entry_num
    attribute_data<int> entry_num;
    double *damage;
    double total_damage;

    Deployment(vector<Single_Attack *> rotation_);

    ~Deployment();

    int get_all_data();

    void cal_optimal_entry_num();
};

#endif //GENSHINCAL_DEPLOYMENT_H
