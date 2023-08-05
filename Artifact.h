//
// Created by 陈劭彬 on 2023/7/25.
//

#ifndef GENSHINCAL_ARTIFACT_H
#define GENSHINCAL_ARTIFACT_H

#include "Basic_Elements.h"

class Single_Attack;

class Config_File;

class Artifact
{
public:
    string name;
    string english_name;

    Artifact(string name_,
             string english_name_);

    string get_name() const;

    virtual attribute_data<int> get_useful_attribute(const Single_Attack *single_attack);

    virtual attribute_data<double> get_extra(const Single_Attack *single_attack);

    virtual attribute_data<double> get_team(const Single_Attack *other_single_attack);

    virtual void get_recharge_energy(const Single_Attack *single_attack, double &Q_energy_modify, double &energy);

    virtual attribute_data<double> get_convert(const Single_Attack *single_attack, attribute_data<double> panel);

    virtual attribute_data<double> get_extra_convert_rate(const Single_Attack *single_attack, attribute_data<double> panel, double &extra_rate);

    virtual double get_react_bonus(const Single_Attack *single_attack, string react_type);

    friend void generate_gcsim_script(Config_File *config);
};

#endif //GENSHINCAL_ARTIFACT_H
