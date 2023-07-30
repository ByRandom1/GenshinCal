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