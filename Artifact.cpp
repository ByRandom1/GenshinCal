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

tuple<double, double> Artifact::get_recharge(const Single_Attack *single_attack)
{ return make_tuple(0, 0); }

attribute_data<int> Artifact::get_useful_attribute(const Single_Attack *single_attack)
{ return {}; }

tuple<attribute_data<double>, attribute_data<double>> Artifact::get_buff(const Single_Attack *single_attack)
{ return make_tuple(attribute_data<double>(), attribute_data<double>()); }

attribute_data<double> Artifact::get_panel_convert(const Single_Attack *single_attack, attribute_data<double> panel)
{ return {}; }

attribute_data<double> Artifact::get_total_convert(const Single_Attack *single_attack, attribute_data<double> panel)
{ return {}; }

double Artifact::get_extra_rate(const Single_Attack *single_attack, attribute_data<double> panel)
{ return 0; }

double Artifact::get_react_damplus(const Single_Attack *single_attack, string react_type)
{ return 0; }