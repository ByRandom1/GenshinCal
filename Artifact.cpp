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

attribute_data<int> Artifact::get_useful_attribute(const Single_Attack *single_attack)
{ return {}; }

attribute_data<double> Artifact::get_extra(const Single_Attack *single_attack)
{ return {}; }

attribute_data<double> Artifact::get_team(const Single_Attack *other_single_attack)
{ return {}; }

void Artifact::get_recharge_energy(const Single_Attack *single_attack, double &Q_energy_modify, double &energy)
{}

attribute_data<double> Artifact::get_convert(const Single_Attack *single_attack, attribute_data<double> panel)
{ return {}; }

attribute_data<double> Artifact::get_extra_convert_rate(const Single_Attack *single_attack, attribute_data<double> panel, double &extra_rate)
{ return {}; }

double Artifact::get_react_bonus(const Single_Attack *single_attack, string react_type)
{ return 0; }