//
// Created by 陈劭彬 on 2023/7/25.
//

#include "Artifact.h"

#include <utility>

Artifact::Artifact(string name_,
                   string english_name_)
{
    name = std::move(name_);
    english_name = std::move(english_name_);
}

attribute_data<int> Artifact::get_useful_attribute(const Single_Attack *attack_config)
{
    return attribute_data<int>();
}

attribute_data<double> Artifact::get_extra(const Single_Attack *attack_config)
{
    return attribute_data<double>();
}

attribute_data<double> Artifact::get_team(const Single_Attack *attack_config)
{
    return attribute_data<double>();
}

void Artifact::get_recharge_energy(Combination *ori_team[], double &Q_energy_modify, double &energy)
{}

attribute_data<double> Artifact::get_convert(const Single_Attack *attack_config, attribute_data<double> panel)
{
    return attribute_data<double>();
}

double Artifact::get_extra_rate(const Single_Attack *attack_config, attribute_data<double> panel)
{
    return 0;
}

double Artifact::get_react_bonus(const Single_Attack *attack_config, string react_type)
{
    return 0;
}

Artifact *find_artifact_by_name(const string &name)
{
    for (auto &a: Artifact_list)
        if (a->name == name)
            return a;
    return nullptr;
}

void init_Artifact_list()
{

}