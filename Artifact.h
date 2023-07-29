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
protected:
    string name;
    string english_name;

public:
    Artifact(string name_,
             string english_name_);

    virtual attribute_data<int> get_useful_attribute(const Single_Attack *attack_config) = 0;

    virtual attribute_data<double> get_extra(const Single_Attack *attack_config) = 0;

    virtual attribute_data<int> modify_allowed_attribute(const Single_Attack *attack_config) = 0;

    virtual attribute_data<double> get_team(const Single_Attack *attack_config) = 0;

    virtual void get_recharge_energy(const Single_Attack *attack_config, double &Q_energy_modify, double &energy) = 0;

    virtual attribute_data<double> get_convert(const Single_Attack *attack_config, attribute_data<double> panel) = 0;

    virtual double get_extra_rate(const Single_Attack *attack_config, attribute_data<double> panel) = 0;

    virtual double get_react_bonus(const Single_Attack *attack_config, string react_type) = 0;

    virtual ~Artifact() = default;

    friend void generate_gcsim_script(Config_File *config);

    friend Artifact *find_artifact_by_name(string name);
};

vector<Artifact*> Artifact_list;

Artifact *find_artifact_by_name(string name);

void init_Artifact_list();

#endif //GENSHINCAL_ARTIFACT_H
