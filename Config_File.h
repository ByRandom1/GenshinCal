//
// Created by 陈劭彬 on 2023/7/27.
//

#ifndef GENSHINCAL_CONFIG_FILE_H
#define GENSHINCAL_CONFIG_FILE_H

#include "Basic_Elements.h"
#include "Character.h"
#include "Weapon.h"
#include "Artifact.h"
#include "Deployment.h"

class Config_File
{
public:
    string team_name;
    string options;
    string target;
    vector<string> attack_list;

    Combination* team[4];
    vector<Combination *> gcsim[4];
    vector<Combination *> cal_entry[4];
    vector<Combination *> cal_artifact[4];
    vector<Single_Attack *> attack_config[4];

    Config_File(string team_name_, vector<string> file);

    ~Config_File();

    static string generate_sample_config();
};

#endif //GENSHINCAL_CONFIG_FILE_H
