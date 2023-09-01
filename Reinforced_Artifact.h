//
// Created by 陈劭彬 on 2023/9/1.
//

#ifndef GENSHINCAL_REINFORCED_ARTIFACT_H
#define GENSHINCAL_REINFORCED_ARTIFACT_H

#include "Basic_Elements.h"

class Reinforced_Artifact
{
public:
    int level;
    string name;
    pair<string, double> main;
    vector<pair<string, double>> entry;

    Reinforced_Artifact(int level_,
                        string name_,
                        const pair<string, double>& main_,
                        const vector<pair<string, double>>& entry_);

    static string suit_name_convert(string suit_name_);

    static string type_name_convert(string type_name_);

    attribute_data<double> get_entry_num();
};

#endif //GENSHINCAL_REINFORCED_ARTIFACT_H
