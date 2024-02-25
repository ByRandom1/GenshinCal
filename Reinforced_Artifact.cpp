//
// Created by 陈劭彬 on 2023/9/1.
//

#include "Reinforced_Artifact.h"

#include <utility>

Reinforced_Artifact::Reinforced_Artifact(int level_,
                                         string name_,
                                         const pair<string, double> &main_,
                                         const vector<pair<string, double>> &entry_)
{
    level = level_;
    name = Reinforced_Artifact::suit_name_convert(std::move(name_));
    main = make_pair(Reinforced_Artifact::type_name_convert(main_.first), main_.second);
    for (const auto &i: entry_)
        entry.emplace_back(Reinforced_Artifact::type_name_convert(i.first), i.second);
}

string Reinforced_Artifact::suit_name_convert(string suit_name_)
{
    if (suit_name_ == "wandererTroupe") return "流浪大地的乐团";
    else if (suit_name_ == "gladiatorFinale") return "角斗士的终幕礼";
    else if (suit_name_ == "blizzardStrayer") return "冰风迷途的勇士";
    else if (suit_name_ == "heartOfDepth") return "沉沦之心";
    else if (suit_name_ == "Archaic Petra") return "悠古的磐岩";//?
    else if (suit_name_ == "Retracing Bolide") return "逆飞的流星";//?
    else if (suit_name_ == "Bloodstained Chivalry") return "染血的骑士道";//?
    else if (suit_name_ == "noblesseOblige") return "昔日宗室之仪";
    else if (suit_name_ == "viridescentVenerer") return "翠绿之影";
    else if (suit_name_ == "maidenBeloved") return "被怜爱的少女";
    else if (suit_name_ == "paleFlame") return "苍白之火";
    else if (suit_name_ == "tenacityOfTheMillelith") return "千岩牢固";
    else if (suit_name_ == "crimsonWitch") return "炽烈的炎之魔女";
    else if (suit_name_ == "lavaWalker") return "渡过烈火的贤人";
    else if (suit_name_ == "thunderingFury") return "如雷的盛怒";//?
    else if (suit_name_ == "Thundersoother") return "平息鸣雷的尊者";//?
    else if (suit_name_ == "shimenawaReminiscence") return "追忆之注连";
    else if (suit_name_ == "emblemOfSeveredFate") return "绝缘之旗印";
    else if (suit_name_ == "huskOfOpulentDreams") return "华馆梦醒形骸记";//?
    else if (suit_name_ == "oceanHuedClam") return "海染砗磲";//?
    else if (suit_name_ == "VermillionHereafter") return "辰砂往生录";
    else if (suit_name_ == "EchoesOfAnOffering") return "来歆余响";
    else if (suit_name_ == "DeepwoodMemories") return "深林的记忆";
    else if (suit_name_ == "GildedDreams") return "饰金之梦";
    else if (suit_name_ == "DesertPavilionChronicle") return "沙上楼阁史话";
    else if (suit_name_ == "FlowerOfParadiseLost") return "乐园遗落之花";
    else if (suit_name_ == "NymphsDream") return "水仙之梦";
    else if (suit_name_ == "VourukashasGlow") return "花海甘露之光";
    else if (suit_name_ == "MarechausseeHunter") return "逐影猎人";
    else if (suit_name_ == "GoldenTroupe") return "黄金剧团";
    else if (suit_name_ == "NighttimeWhispersInTheEchoingWoods") return "回声之林夜话";
    else if (suit_name_ == "SongOfDaysPast") return "昔时之歌";
    else
    {
        cout << suit_name_ << endl;
        return suit_name_;
    }
}

string Reinforced_Artifact::type_name_convert(string type_name_)
{
    if (type_name_ == "lifeStatic") return "生命值S";
    else if (type_name_ == "lifePercentage") return "生命值";
    else if (type_name_ == "attackStatic") return "攻击力S";
    else if (type_name_ == "attackPercentage") return "攻击力";
    else if (type_name_ == "defendStatic") return "防御力S";
    else if (type_name_ == "defendPercentage") return "防御力";
    else if (type_name_ == "elementalMastery") return "元素精通";
    else if (type_name_ == "recharge") return "元素充能效率";
    else if (type_name_ == "critical") return "暴击率";
    else if (type_name_ == "criticalDamage") return "暴击伤害";
    else if (type_name_ == "waterBonus") return "水伤害加成";
    else if (type_name_ == "iceBonus") return "冰伤害加成";
    else if (type_name_ == "fireBonus") return "火伤害加成";
    else if (type_name_ == "thunderBonus") return "雷伤害加成";
    else if (type_name_ == "windBonus") return "风伤害加成";
    else if (type_name_ == "rockBonus") return "岩伤害加成";
    else if (type_name_ == "dendroBonus") return "草伤害加成";
    else if (type_name_ == "physicalBonus") return "物理伤害加成";
    else if (type_name_ == "cureEffect") return "治疗加成";
    else
    {
        cout << type_name_ << endl;
        return type_name_;
    }
}

attribute_data<double> Reinforced_Artifact::get_entry_num()
{
    double life_base_value = 14500;
    double atk_base_value = 950;
    double def_base_value = 800;

    attribute_data<double> entry_num;
    for (auto &i: entry)
    {
        if (i.first == "生命值S") entry_num = entry_num + attribute_data("生命值", (i.second / life_base_value) / 0.05);
        else if (i.first == "生命值") entry_num = entry_num + attribute_data("生命值", i.second / 0.05);
        else if (i.first == "攻击力S") entry_num = entry_num + attribute_data("攻击力", (i.second / atk_base_value) / 0.05);
        else if (i.first == "攻击力") entry_num = entry_num + attribute_data("攻击力", i.second / 0.05);
        else if (i.first == "防御力S") entry_num = entry_num + attribute_data("防御力", (i.second / def_base_value) / 0.062);
        else if (i.first == "防御力") entry_num = entry_num + attribute_data("防御力", i.second / 0.062);
        else if (i.first == "元素精通") entry_num = entry_num + attribute_data("元素精通", i.second / 20.0);
        else if (i.first == "元素充能效率") entry_num = entry_num + attribute_data("元素充能效率", i.second / 0.055);
        else if (i.first == "暴击率") entry_num = entry_num + attribute_data("暴击率", i.second / 0.033);
        else if (i.first == "暴击伤害") entry_num = entry_num + attribute_data("暴击伤害", i.second / 0.066);
    }

    return entry_num;
}