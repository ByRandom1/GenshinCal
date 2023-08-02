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

Character *find_character_by_name(const string &name);

Weapon *find_weapon_by_name(const string &name);

Artifact *find_artifact_by_name(const string &name);

class Config_File
{
public:
    string team_name;

    vector<Combination *> gcsim[4];
    string options;
    string target;
    vector<string> attack_script;

    Team_Config *team_config;

    Config_File(string team_name_, vector<string> file);

    ~Config_File();

    static string generate_sample_config();
};

#endif //GENSHINCAL_CONFIG_FILE_H
