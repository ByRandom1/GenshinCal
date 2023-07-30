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

class Single_Attack;

struct Combination
{
    Character *c_point;
    Weapon *w_point;
    Artifact *suit1;
    Artifact *suit2;
    string a_main3;
    string a_main4;
    string a_main5;

    vector<Single_Attack *> ori_attack_list;
    bool require_recharge;

    Combination(Character *c_point_,
                Weapon *w_point_,
                Artifact *suit1_,
                Artifact *suit2_,
                string a_main3_,
                string a_main4_,
                string a_main5_,
                vector<Single_Attack *> ori_attack_list_);

    void add_attack_list(const vector<Single_Attack *> &ori_attack_list_);
};

class Single_Attack
{
public:
    //team info (global)
    Combination *team[4];
    string ele_attach_type;
    //attack info (independent)
    string attack_way;
    string release_or_hit;
    int rate_pos;
    bool background;
    string react_type;
    double attack_time;
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
                  string attack_way_,
                  string release_or_hit_,
                  int rate_pos_,
                  bool background_,
                  string react_type_,
                  double attack_time_);

    void get_data(bool &suit1_valid, bool &suit2_valid, bool &main3_valid, bool &main4_valid, bool &main5_valid);

    void cal_damage(const attribute_data<double> &entry_value, double min_recharge);

    void get_react_value(double mastery, double &extra_rate, double &grow_rate, double &extra_damage);
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

    explicit Deployment(const vector<Single_Attack *> &rotation_);

    ~Deployment();

    inline bool operator<(const Deployment &other) const;

    int get_all_data();

    void cal_optimal_entry_num();
};

#endif //GENSHINCAL_DEPLOYMENT_H
