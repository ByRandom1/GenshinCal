//
// Created by 陈劭彬 on 2023/7/25.
//

#include "Artifact.h"
#include "Deployment.h"

#include <utility>

Artifact::Artifact(string name_,
                   string english_name_)
{
    name = std::move(name_);
    english_name = std::move(english_name_);
}

string Artifact::get_name() const
{ return name; }

string Artifact::get_english_name() const
{ return english_name; }

attribute_data<int> Artifact::get_useful_attribute(const Single_Attack *attack_config)
{ return {}; }

attribute_data<double> Artifact::get_extra(const Single_Attack *attack_config)
{ return {}; }

attribute_data<double> Artifact::get_team(const Single_Attack *other_attack_config)
{ return {}; }

void Artifact::get_recharge_energy(const Team_Config *team_config, double &Q_energy_modify, double &energy)
{}

attribute_data<double> Artifact::get_convert(const Single_Attack *attack_config, attribute_data<double> panel)
{ return {}; }

double Artifact::get_extra_rate(const Single_Attack *attack_config, attribute_data<double> panel)
{ return 0; }

double Artifact::get_react_bonus(const Single_Attack *attack_config, string react_type)
{ return 0; }