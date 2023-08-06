struct weapon_artifact_related_arguments
{
    //weapon
    int sword_wuqie_level = -1;//雾切，普通攻击造成元素伤害时，持续5秒；施放元素爆发时，持续10秒；角色元素能量低于100%时
    int sword_shengxian_level = -1;//圣显之钥，E命中。20s，3层
    int sword_langya_level = -1;//狼牙，EQ命中，10s，4层
    int catalyst_shenle_level = -1;//神乐铃，释放E，16s，3层
    bool catalyst_biluo_enable = false;//碧落之珑，创造护盾，3s
    int catalyst_sifeng_level = -1;//四风，站场4s，4层
    int bow_feilei_level = -1;//飞雷，普通攻击造成伤害时，持续5秒；施放元素战技时，持续10秒；此外，角色元素能量低于100%时
    int bow_dongji_level = -1;//冬极，普通攻击、重击、元素战技或元素爆发命中敌人
    bool bow_pomo_fullenergy = false;//破魔
    bool polearm_humo_halflife = false;//护摩
    int polearm_chisha_level = -1;//赤砂之杖，E命中，10s，3层
    int polearm_shizuo_level = -1;//试作星镰，释放E，12s，2层
    //artifact
    int cangbai_level;//苍白，E命中，7s，2层
    bool qianyan_enable;//千岩，E命中，3s
    int monv_level;//魔女，释放E，10s，3层
    bool chensha_enable;//辰砂
    bool shenlin_enable;//草套，EQ命中，8s
    int shuixian_level;//水仙，A重A下落AEQ命中，8s
    int zhuying_level;//逐影，生命值变动，5s

    weapon_artifact_related_arguments(int cangbai_level_,
                                      bool qianyan_enable_,
                                      int monv_level_,
                                      bool chensha_enable_,
                                      bool shenlin_enable_,
                                      int shuixian_level_,
                                      int zhuying_level_,

                                      string weapon_type,
                                      int wuqie_shenle_feilei_humo,
                                      int shengxian_biluo_dongji_chisha,
                                      int langya_sifeng_pomo_shizuo)
    {
        cangbai_level = cangbai_level_;
        qianyan_enable = qianyan_enable_;
        monv_level = monv_level_;
        chensha_enable = chensha_enable_;
        shenlin_enable = shenlin_enable_;
        shuixian_level = shuixian_level_;
        zhuying_level = zhuying_level_;

        if (weapon_type == "单手剑")
        {
            sword_wuqie_level = wuqie_shenle_feilei_humo;
            sword_shengxian_level = shengxian_biluo_dongji_chisha;
            sword_langya_level = langya_sifeng_pomo_shizuo;
        }
        else if (weapon_type == "法器")
        {
            catalyst_shenle_level = wuqie_shenle_feilei_humo;
            catalyst_biluo_enable = shengxian_biluo_dongji_chisha;
            catalyst_sifeng_level = langya_sifeng_pomo_shizuo;
        }
        else if (weapon_type == "弓")
        {
            bow_feilei_level = wuqie_shenle_feilei_humo;
            bow_dongji_level = shengxian_biluo_dongji_chisha;
            bow_pomo_fullenergy = langya_sifeng_pomo_shizuo;
        }
        else if (weapon_type == "双手剑")
        {

        }
        else if (weapon_type == "长柄武器")
        {
            polearm_humo_halflife = wuqie_shenle_feilei_humo;
            polearm_chisha_level = shengxian_biluo_dongji_chisha;
            polearm_shizuo_level = langya_sifeng_pomo_shizuo;
        }
    }
};

//build new weapon(all)
void init_weapon_data()
{
    vector<Set *> temp;

    //(special)
    temp.push_back(new Set(new Condition("火|水|雷|冰|风|岩|草", "ALL", "ALL"), "伤害加成", 0.12));
    weapon_list.push_back(new Weapon("雾切之回光", "mistsplitterreforged", "单手剑", 674, "暴击伤害", 0.441, 1, temp));
    temp.clear();

    temp.push_back(new Set(new Condition("ALL", "ALL", "ALL"), "攻击力", 0.2));
    weapon_list.push_back(new Weapon("风鹰剑", "aquilafavonia", "单手剑", 674, "伤害加成", 0.413, 1, temp));
    temp.clear();

    temp.push_back(new Set(new Condition("火|水|雷|冰|风|岩|草", "ALL", "ALL"), "伤害加成", 0.12));
    temp.push_back(new Set(new Condition("ALL", "ALL", "平A"), "伤害加成", 0.4));//队友E，2层
    weapon_list.push_back(new Weapon("波乱月白经津", "harangeppakufutsu", "单手剑", 608, "暴击率", 0.331, 1, temp));
    temp.clear();

    //(special)
    temp.push_back(new Set(new Condition("ALL", "ALL", "ALL"), "护盾强效", 0.2));
    weapon_list.push_back(new Weapon("斫峰之刃", "summitshaper", "单手剑", 608, "攻击力", 0.496, 1, temp));
    temp.clear();

    temp.push_back(new Set(new Condition("ALL", "ALL", "ALL"), "暴击率", 0.04));
    temp.push_back(new Set(new Condition("ALL", "ALL", "平A|重A"), "额外倍率", 0.2));//Q后
    weapon_list.push_back(new Weapon("天空之刃", "skywardblade", "单手剑", 608, "元素充能效率", 0.551, 1, temp));
    temp.clear();

    //(special)
    //(get_team)
    temp.push_back(new Set(new Condition("ALL", "ALL", "ALL"), "伤害加成", 0.1));
    weapon_list.push_back(new Weapon("苍古自由之誓", "freedomsworn", "单手剑", 608, "元素精通", 198.0, 1, temp));
    temp.clear();

    //(get_convert)
    temp.push_back(new Set(new Condition("ALL", "ALL", "ALL"), "生命值", 0.2));
    weapon_list.push_back(new Weapon("磐岩结绿", "primordialjadecutter", "单手剑", 542, "暴击率", 0.441, 1, temp));
    temp.clear();

    //(convert)
    temp.push_back(new Set(new Condition("ALL", "ALL", "ALL"), "暴击率", 0.04));
    weapon_list.push_back(new Weapon("裁叶萃光", "lightoffoliarincision", "单手剑", 542, "暴击伤害", 0.882, 1, temp));
    temp.clear();

    //(convert)
    //(get_team)
    temp.push_back(new Set(new Condition("ALL", "ALL", "ALL"), "生命值", 0.2));
    weapon_list.push_back(new Weapon("圣显之钥", "keyofkhajnisut", "单手剑", 542, "生命值", 0.662, 1, temp));
    temp.clear();

    temp.push_back(new Set(new Condition("ALL", "ALL", "ALL"), "伤害加成", 0.12));
    weapon_list.push_back(new Weapon("暗巷闪光", "thealleyflash", "单手剑", 620, "元素精通", 55.0, 1, temp));
    temp.clear();

    //TODO:NEW
    //(convert)
    temp.push_back(new Set(new Condition("ALL", "ALL", "ALL"), "攻击力", 0.12));
    weapon_list.push_back(new Weapon("海渊终曲", "", "单手剑", 565, "攻击力", 0.276, 1, temp));
    temp.clear();

    //(special)
    weapon_list.push_back(new Weapon("试作斩岩", "prototyperancour", "单手剑", 565, "伤害加成", 0.345, 5, temp));
    temp.clear();

    //(get_team)
    weapon_list.push_back(new Weapon("原木刀", "sapwoodblade", "单手剑", 565, "元素充能效率", 0.306, 5, temp));
    temp.clear();

    temp.push_back(new Set(new Condition("ALL", "ALL", "平A|重A"), "伤害加成", 0.2));
    weapon_list.push_back(new Weapon("黑剑", "theblacksword", "单手剑", 510, "暴击率", 0.276, 1, temp));
    temp.clear();

    //TODO:NEW
    //(special)
    temp.push_back(new Set(new Condition("ALL", "ALL", "E|Q"), "伤害加成", 0.16));
    weapon_list.push_back(new Weapon("狼牙", "", "单手剑", 510, "暴击率", 0.276, 1, temp));
    temp.clear();

    //(special)
    weapon_list.push_back(new Weapon("匣里龙吟", "lionsroar", "单手剑", 510, "攻击力", 0.413, 5, temp));
    temp.clear();

    temp.push_back(new Set(new Condition("ALL", "ALL", "ALL"), "攻击力", 0.15));//平A重A下落A
    weapon_list.push_back(new Weapon("笼钓瓶一心", "kagotsurubeisshin", "单手剑", 510, "攻击力", 0.413, 1, temp));
    temp.clear();

    weapon_list.push_back(new Weapon("笛剑", "theflute", "单手剑", 510, "攻击力", 0.413, 5, temp));
    temp.clear();

    temp.push_back(new Set(new Condition("ALL", "ALL", "E"), "伤害加成", 0.16));
    temp.push_back(new Set(new Condition("ALL", "ALL", "E"), "暴击率", 0.06));
    weapon_list.push_back(new Weapon("腐殖之剑", "festeringdesire", "单手剑", 510, "元素充能效率", 0.459, 5, temp));
    temp.clear();

    //TODO:NEW
    temp.push_back(new Set(new Condition("ALL", "ALL", "ALL"), "元素充能效率", 0.16));
    temp.push_back(new Set(new Condition("ALL", "ALL", "E"), "暴击率", 0.08));
    weapon_list.push_back(new Weapon("灰河渡手", "", "单手剑", 510, "元素充能效率", 0.459, 1, temp));
    temp.clear();

    temp.push_back(new Set(new Condition("ALL", "ALL", "ALL"), "伤害加成", 0.12));//元素伤害，2层
    weapon_list.push_back(new Weapon("铁蜂刺", "ironsting", "单手剑", 510, "元素精通", 165.0, 5, temp));
    temp.clear();

    //(convert)
    //(get_team)
    weapon_list.push_back(new Weapon("西福斯的月光", "xiphosmoonlight", "单手剑", 510, "元素精通", 165.0, 1, temp));
    temp.clear();

    temp.push_back(new Set(new Condition("ALL", "ALL", "ALL"), "伤害加成", 0.16));
    weapon_list.push_back(new Weapon("东花坊时雨", "toukaboushigure", "单手剑", 510, "元素精通", 165.0, 5, temp));
    temp.clear();

    //(get_extra_rate)
    weapon_list.push_back(new Weapon("辰砂之纺锤", "cinnabarspindle", "单手剑", 454, "防御力", 0.69, 5, temp));
    temp.clear();

    //(recharge)
    weapon_list.push_back(new Weapon("天目影打刀", "amenomakageuchi", "单手剑", 454, "攻击力", 0.551, 5, temp));
    temp.clear();

    //(recharge)
    weapon_list.push_back(new Weapon("西风剑", "favoniussword", "单手剑", 454, "元素充能效率", 0.613, 5, temp));
    temp.clear();

    //(recharge)
    weapon_list.push_back(new Weapon("祭礼剑", "sacrificialsword", "单手剑", 454, "元素充能效率", 0.613, 5, temp));
    temp.clear();

    weapon_list.push_back(new Weapon("图莱杜拉的回忆", "tulaytullahsremembrance", "法器", 674, "暴击伤害", 0.441, 1, temp));
    temp.clear();

    temp.push_back(new Set(new Condition("火|水|雷|冰|风|岩|草", "ALL", "ALL"), "伤害加成", 0.12));
    weapon_list.push_back(new Weapon("天空之卷", "skywardatlas", "法器", 674, "攻击力", 0.331, 1, temp));
    temp.clear();

    //(special)
    weapon_list.push_back(new Weapon("四风原典", "lostprayertothesacredwinds", "法器", 608, "暴击率", 0.331, 1, temp));
    temp.clear();

    //(special)
    weapon_list.push_back(new Weapon("神乐之真意", "kagurasverity", "法器", 608, "暴击伤害", 0.662, 1, temp));
    temp.clear();

    //(special)
    temp.push_back(new Set(new Condition("ALL", "ALL", "ALL"), "护盾强效", 0.2));
    weapon_list.push_back(new Weapon("尘世之锁", "memoryofdust", "法器", 608, "攻击力", 0.496, 1, temp));
    temp.clear();

    //(get_extra_rate)
    //(recharge)
    temp.push_back(new Set(new Condition("ALL", "ALL", "ALL"), "治疗加成", 0.1));
    weapon_list.push_back(new Weapon("不灭月华", "everlastingmoonglow", "法器", 608, "生命值", 0.496, 1, temp));
    temp.clear();

    //(recharge)
    //(convert)
    weapon_list.push_back(new Weapon("碧落之珑", "jadefallssplendor", "法器", 608, "生命值", 0.496, 1, temp));
    temp.clear();

    //(special)
    //(get_team)
    weapon_list.push_back(new Weapon("千夜浮梦", "athousandfloatingdreams", "法器", 542, "元素精通", 265.0, 1, temp));
    temp.clear();

    temp.push_back(new Set(new Condition("ALL", "ALL", "ALL"), "元素充能效率", 0.24));//E后
    weapon_list.push_back(new Weapon("证誓之明瞳", "oathsworneye", "法器", 565, "攻击力", 0.276, 5, temp));
    temp.clear();

    //TODO:NEW
    //(convert)
    temp.push_back(new Set(new Condition("火|水|雷|冰|风|岩|草", "ALL", "ALL"), "伤害加成", 0.08));
    weapon_list.push_back(new Weapon("纯水流华", "", "法器", 565, "攻击力", 0.276, 1, temp));
    temp.clear();

    temp.push_back(new Set(new Condition("ALL", "ALL", "ALL"), "攻击力", 0.2));//冲刺
    weapon_list.push_back(new Weapon("暗巷的酒与诗", "wineandsong", "法器", 565, "元素充能效率", 0.306, 1, temp));
    temp.clear();

    //(special) (get_team)
    weapon_list.push_back(new Weapon("白辰之环", "hakushinring", "法器", 565, "元素充能效率", 0.306, 5, temp));
    temp.clear();

    //(special)
    weapon_list.push_back(new Weapon("万国诸海图谱", "mappamare", "法器", 565, "元素精通", 110.0, 5, temp));
    temp.clear();

    //(special)
    weapon_list.push_back(new Weapon("匣里日月", "solarpearl", "法器", 510, "暴击率", 0.276, 1, temp));
    temp.clear();

    //(special)
    weapon_list.push_back(new Weapon("流浪乐章", "thewidsith", "法器", 510, "暴击伤害", 0.551, 5, temp));
    temp.clear();

    weapon_list.push_back(new Weapon("忍冬之果", "frostbearer", "法器", 510, "攻击力", 0.413, 5, temp));
    temp.clear();

    //(recharge)
    weapon_list.push_back(new Weapon("试作金珀", "prototypeamber", "法器", 510, "生命值", 0.413, 5, temp));
    temp.clear();

    //(special)
    weapon_list.push_back(new Weapon("盈满之实", "fruitoffulfillment", "法器", 510, "元素充能效率", 0.459, 5, temp));
    temp.clear();

    //(recharge)
    weapon_list.push_back(new Weapon("西风秘典", "favoniuscodex", "法器", 510, "元素充能效率", 0.459, 5, temp));
    temp.clear();

    //(convert)
    //(get_team)
    weapon_list.push_back(new Weapon("流浪的晚星", "wanderingevenstar", "法器", 510, "元素精通", 165.0, 1, temp));
    temp.clear();

    //TODO:NEW
    //(special)
    weapon_list.push_back(new Weapon("遗祀玉珑", "", "法器", 454, "暴击率", 0.368, 1, temp));
    temp.clear();

    weapon_list.push_back(new Weapon("昭心", "eyeofperception", "法器", 454, "攻击力", 0.551, 5, temp));
    temp.clear();

    //(special)
    weapon_list.push_back(new Weapon("嘟嘟可故事集", "dodocotales", "法器", 454, "攻击力", 0.551, 5, temp));
    temp.clear();

    //(recharge)
    weapon_list.push_back(new Weapon("祭礼残章", "sacrificialfragments", "法器", 454, "元素精通", 221.0, 5, temp));
    temp.clear();

    temp.push_back(new Set(new Condition("ALL", "ALL", "ALL"), "暴击伤害", 0.2));
    weapon_list.push_back(new Weapon("天空之翼", "skywardharp", "弓", 674, "暴击率", 0.221, 1, temp));
    temp.clear();

    //(special)
    temp.push_back(new Set(new Condition("ALL", "ALL", "E|Q"), "伤害加成", 0.12));
    weapon_list.push_back(new Weapon("冬极白星", "polarstar", "弓", 608, "暴击率", 0.331, 1, temp));
    temp.clear();

    //(special)
    temp.push_back(new Set(new Condition("ALL", "ALL", "ALL"), "攻击力", 0.2));
    weapon_list.push_back(new Weapon("飞雷之弦振", "thunderingpulse", "弓", 608, "暴击伤害", 0.662, 1, temp));
    temp.clear();

    //TODO:NEW
    //(special)
    temp.push_back(new Set(new Condition("ALL", "ALL", "ALL"), "攻击力", 0.12));
    weapon_list.push_back(new Weapon("最初的大魔术", "", "弓", 608, "暴击伤害", 0.662, 1, temp));
    temp.clear();

    //高估
    temp.push_back(new Set(new Condition("ALL", "ALL", "平A|重A"), "伤害加成", 0.12));
    temp.push_back(new Set(new Condition("ALL", "ALL", "平A"), "伤害加成", 0.16));//2层
    temp.push_back(new Set(new Condition("ALL", "ALL", "重A"), "伤害加成", 0.32));//4层
    weapon_list.push_back(new Weapon("阿莫斯之弓", "amosbow", "弓", 608, "攻击力", 0.496, 1, temp));
    temp.clear();

    //(get_team)
    temp.push_back(new Set(new Condition("ALL", "ALL", "ALL"), "元素精通", 60.0));
    temp.push_back(new Set(new Condition("ALL", "ALL", "ALL"), "元素精通", 100.0));
    temp.push_back(new Set(new Condition("ALL", "ALL", "ALL"), "攻击力", 0.2));
    weapon_list.push_back(new Weapon("终末嗟叹之诗", "elegyfortheend", "弓", 608, "元素充能效率", 0.551, 1, temp));
    temp.clear();

    //(get_extra_rate)
    temp.push_back(new Set(new Condition("火|水|雷|冰|风|岩|草", "ALL", "ALL"), "伤害加成", 0.12));
    weapon_list.push_back(new Weapon("猎人之径", "hunterspath", "弓", 542, "暴击率", 0.441, 1, temp));
    temp.clear();

    temp.push_back(new Set(new Condition("ALL", "ALL", "ALL"), "生命值", 0.16));
    temp.push_back(new Set(new Condition("ALL", "ALL", "ALL"), "伤害加成", 0.2));
    weapon_list.push_back(new Weapon("若水", "aquasimulacra", "弓", 542, "暴击伤害", 0.882, 1, temp));
    temp.clear();

    //TODO:NEW
    temp.push_back(new Set(new Condition("ALL", "ALL", "重A"), "伤害加成", 0.28));
    weapon_list.push_back(new Weapon("烈阳之嗣", "", "弓", 565, "暴击率", 0.184, 1, temp));
    temp.clear();

    //(special)
    weapon_list.push_back(new Weapon("暗巷猎手", "alleyhunter", "弓", 565, "攻击力", 0.276, 1, temp));
    temp.clear();

    //(special)
    weapon_list.push_back(new Weapon("曚云之月", "mouunsmoon", "弓", 565, "攻击力", 0.276, 2, temp));
    temp.clear();

    //(recharge)
    weapon_list.push_back(new Weapon("祭礼弓", "sacrificialbow", "弓", 565, "元素充能效率", 0.306, 5, temp));
    temp.clear();

    temp.push_back(new Set(new Condition("ALL", "ALL", "ALL"), "伤害加成", 0.1));
    weapon_list.push_back(new Weapon("落霞", "fadingtwilight", "弓", 565, "元素充能效率", 0.306, 5, temp));
    temp.clear();

    weapon_list.push_back(new Weapon("苍翠猎弓", "theviridescenthunt", "弓", 510, "暴击率", 0.276, 1, temp));
    temp.clear();

    //(special)
    temp.push_back(new Set(new Condition("ALL", "ALL", "平A"), "伤害加成", 0.4));
    weapon_list.push_back(new Weapon("弓藏", "rust", "弓", 510, "攻击力", 0.413, 5, temp));
    temp.clear();

    //TODO:NEW
    //(special)
    weapon_list.push_back(new Weapon("静谧之曲", "", "弓", 510, "攻击力", 0.413, 1, temp));
    temp.clear();

    weapon_list.push_back(new Weapon("试作澹月", "prototypecrescent", "弓", 510, "攻击力", 0.413, 5, temp));
    temp.clear();

    //(special)
    weapon_list.push_back(new Weapon("幽夜华尔兹", "mitternachtswaltz", "弓", 510, "伤害加成", 0.517, 1, temp));
    temp.clear();

    weapon_list.push_back(new Weapon("竭泽", "endoftheline", "弓", 510, "元素充能效率", 0.459, 5, temp));
    temp.clear();

    temp.push_back(new Set(new Condition("ALL", "ALL", "E|Q"), "伤害加成", 0.24));
    weapon_list.push_back(new Weapon("绝弦", "thestringless", "弓", 510, "元素精通", 165.0, 5, temp));
    temp.clear();

    temp.push_back(new Set(new Condition("ALL", "ALL", "ALL"), "攻击力", 0.16));//E后
    weapon_list.push_back(new Weapon("风花之颂", "windblumeode", "弓", 510, "元素精通", 165.0, 5, temp));
    temp.clear();

    //(special)
    weapon_list.push_back(new Weapon("破魔之弓", "hamayumi", "弓", 454, "攻击力", 0.551, 5, temp));
    temp.clear();

    //(special)
    weapon_list.push_back(new Weapon("王下近侍", "kingssquire", "弓", 454, "攻击力", 0.551, 5, temp));
    temp.clear();

    //(special)
    weapon_list.push_back(new Weapon("钢轮弓", "compoundbow", "弓", 454, "伤害加成", 0.69, 5, temp));
    temp.clear();

    //(recharge)
    weapon_list.push_back(new Weapon("西风猎弓", "favoniuswarbow", "弓", 454, "元素充能效率", 0.613, 5, temp));
    temp.clear();

    temp.push_back(new Set(new Condition("ALL", "ALL", "ALL"), "攻击力", 0.16));
    temp.push_back(new Set(new Condition("ALL", "ALL", "ALL"), "攻击力", 0.2));//平A重A4次 (get_team)
    weapon_list.push_back(new Weapon("松籁响起之时", "songofbrokenpines", "双手剑", 741, "伤害加成", 0.207, 1, temp));
    temp.clear();

    temp.push_back(new Set(new Condition("ALL", "ALL", "ALL"), "伤害加成", 0.08));
    weapon_list.push_back(new Weapon("天空之傲", "skywardpride", "双手剑", 674, "元素充能效率", 0.368, 1, temp));
    temp.clear();

    //(special)
    temp.push_back(new Set(new Condition("ALL", "ALL", "ALL"), "攻击力", 0.2));//E命中
    temp.push_back(new Set(new Condition("ALL", "ALL", "ALL"), "攻击力", 0.2));//受伤
    weapon_list.push_back(new Weapon("苇海信标", "beaconofthereedsea", "双手剑", 608, "暴击率", 0.331, 1, temp));
    temp.clear();

    temp.push_back(new Set(new Condition("ALL", "ALL", "ALL"), "攻击力", 0.2));//默认不触发特效
    weapon_list.push_back(new Weapon("狼的末路", "wolfsgravestone", "双手剑", 608, "攻击力", 0.496, 1, temp));
    temp.clear();

    //(special)
    temp.push_back(new Set(new Condition("ALL", "ALL", "ALL"), "护盾强效", 0.2));
    weapon_list.push_back(new Weapon("无工之剑", "theunforged", "双手剑", 608, "攻击力", 0.496, 1, temp));
    temp.clear();

    //(get_extra_rate)
    temp.push_back(new Set(new Condition("ALL", "ALL", "ALL"), "防御力", 0.28));
    weapon_list.push_back(new Weapon("赤角石溃杵", "redhornstonethresher", "双手剑", 542, "暴击伤害", 0.882, 1, temp));
    temp.clear();

    //TODO:NEW
    //TODO:自身元素附着
    weapon_list.push_back(new Weapon("聊聊棒", "", "双手剑", 565, "暴击率", 0.184, 1, temp));
    temp.clear();

    weapon_list.push_back(new Weapon("试作古华", "prototypearchaic", "双手剑", 565, "攻击力", 0.276, 5, temp));
    temp.clear();

    weapon_list.push_back(new Weapon("雪葬的星银", "snowtombedstarsilver", "双手剑", 565, "伤害加成", 0.345, 5, temp));
    temp.clear();

    //(recharge)
    weapon_list.push_back(new Weapon("祭礼大剑", "sacrificialgreatsword", "双手剑", 565, "元素充能效率", 0.306, 5, temp));
    temp.clear();

    //(special) (get_team)
    weapon_list.push_back(new Weapon("森林王器", "forestregalia", "双手剑", 565, "元素充能效率", 0.306, 5, temp));
    temp.clear();

    temp.push_back(new Set(new Condition("ALL", "ALL", "ALL"), "攻击力", 0.12));//E命中或元素反应
    temp.push_back(new Set(new Condition("ALL", "ALL", "ALL"), "元素精通", 48.0));//E命中或元素反应
    weapon_list.push_back(new Weapon("饰铁之花", "mailedflower", "双手剑", 565, "元素精通", 110.0, 5, temp));
    temp.clear();

    //(special)
    weapon_list.push_back(new Weapon("螭骨剑", "serpentspine", "双手剑", 510, "暴击率", 0.276, 5, temp));
    temp.clear();

    //(special)
    weapon_list.push_back(new Weapon("白影剑", "whiteblind", "双手剑", 510, "防御力", 0.517, 5, temp));
    temp.clear();

    //(special)
    weapon_list.push_back(new Weapon("千岩古剑", "lithicblade", "双手剑", 510, "攻击力", 0.413, 1, temp));
    temp.clear();

    //(special)
    weapon_list.push_back(new Weapon("恶王丸", "akuoumaru", "双手剑", 510, "攻击力", 0.413, 1, temp));
    temp.clear();

    //TODO:NEW
    //(special)
    weapon_list.push_back(new Weapon("浪影阔剑", "", "双手剑", 510, "攻击力", 0.413, 1, temp));
    temp.clear();

    //(special)
    weapon_list.push_back(new Weapon("钟剑", "thebell", "双手剑", 510, "生命值", 0.413, 5, temp));
    temp.clear();

    //(recharge)
    temp.push_back(new Set(new Condition("ALL", "ALL", "E"), "伤害加成", 0.06));
    weapon_list.push_back(new Weapon("桂木斩长正", "katsuragikirinagamasa", "双手剑", 510, "元素充能效率", 0.459, 5, temp));
    temp.clear();

    //(special)
    weapon_list.push_back(new Weapon("雨裁", "rainslasher", "双手剑", 510, "元素精通", 165.0, 5, temp));
    temp.clear();

    //(convert)
    //(get_team)
    weapon_list.push_back(new Weapon("玛海菈的水色", "makhairaaquamarine", "双手剑", 510, "元素精通", 165.0, 1, temp));
    temp.clear();

    //(recharge)
    weapon_list.push_back(new Weapon("西风大剑", "favoniusgreatsword", "双手剑", 454, "元素充能效率", 0.613, 5, temp));
    temp.clear();

    temp.push_back(new Set(new Condition("ALL", "ALL", "Q"), "伤害加成", 0.12));
    weapon_list.push_back(new Weapon("衔珠海皇", "luxurioussealord", "双手剑", 454, "攻击力", 0.551, 5, temp));
    temp.clear();

    //(special)
    temp.push_back(new Set(new Condition("火|水|雷|冰|风|岩|草", "ALL", "ALL"), "伤害加成", 0.12));
    weapon_list.push_back(new Weapon("息灾", "calamityqueller", "长柄武器", 741, "攻击力", 0.165, 1, temp));
    temp.clear();

    //(special)
    weapon_list.push_back(new Weapon("和璞鸢", "primordialjadewingedspear", "长柄武器", 674, "暴击率", 0.221, 1, temp));
    temp.clear();

    temp.push_back(new Set(new Condition("ALL", "ALL", "ALL"), "暴击率", 0.08));
    weapon_list.push_back(new Weapon("天空之脊", "skywardspine", "长柄武器", 674, "元素充能效率", 0.368, 1, temp));
    temp.clear();

    //(get_convert)
    temp.push_back(new Set(new Condition("ALL", "ALL", "ALL"), "生命值", 0.2));
    weapon_list.push_back(new Weapon("护摩之杖", "staffofhoma", "长柄武器", 608, "暴击伤害", 0.662, 1, temp));
    temp.clear();

    //(special)
    temp.push_back(new Set(new Condition("ALL", "ALL", "ALL"), "护盾强效", 0.2));
    weapon_list.push_back(new Weapon("贯虹之槊", "vortexvanquisher", "长柄武器", 608, "攻击力", 0.496, 1, temp));
    temp.clear();

    //(special) (get_convert)
    weapon_list.push_back(new Weapon("薙草之稻光", "engulfinglightning", "长柄武器", 608, "元素充能效率", 0.551, 1, temp));
    temp.clear();

    //(convert)
    //(get_team)
    weapon_list.push_back(new Weapon("赤沙之杖", "staffofthescarletsands", "长柄武器", 542, "暴击率", 0.441, 1, temp));
    temp.clear();

    //(special)
    weapon_list.push_back(new Weapon("断浪长鳍", "wavebreakersfin", "长柄武器", 620, "攻击力", 0.138, 4, temp));
    temp.clear();

    //(special)
    weapon_list.push_back(new Weapon("千岩长枪", "lithicspear", "长柄武器", 565, "攻击力", 0.276, 1, temp));
    temp.clear();

    //TODO:NEW
    //(recharge)
    weapon_list.push_back(new Weapon("公义的酬报", "", "长柄武器", 565, "生命值", 0.276, 1, temp));
    temp.clear();

    temp.push_back(new Set(new Condition("ALL", "ALL", "平A|重A"), "额外倍率", 0.2));
    weapon_list.push_back(new Weapon("流月针", "crescentpike", "长柄武器", 565, "伤害加成", 0.345, 5, temp));
    temp.clear();

    //(recharge)
    weapon_list.push_back(new Weapon("西风长枪", "favoniuslance", "长柄武器", 565, "元素充能效率", 0.306, 5, temp));
    temp.clear();

    //(recharge)
    temp.push_back(new Set(new Condition("ALL", "ALL", "E"), "伤害加成", 0.06));
    weapon_list.push_back(new Weapon("喜多院十文字", "kitaincrossspear", "长柄武器", 565, "元素精通", 110.0, 5, temp));
    temp.clear();

    //(special) (get_team)
    weapon_list.push_back(new Weapon("贯月矢", "moonpiercer", "长柄武器", 565, "元素精通", 110.0, 5, temp));
    temp.clear();

    //(special)
    weapon_list.push_back(new Weapon("试作星镰", "prototypestarglitter", "长柄武器", 510, "元素充能效率", 0.459, 5, temp));
    temp.clear();

    //TODO:NEW
    //(special)
    weapon_list.push_back(new Weapon("峡湾长歌", "", "长柄武器", 510, "暴击率", 0.276, 1, temp));
    temp.clear();

    //(special)
    weapon_list.push_back(new Weapon("风信之锋", "missivewindspear", "长柄武器", 510, "攻击力", 0.413, 5, temp));
    temp.clear();

    temp.push_back(new Set(new Condition("ALL", "ALL", "Q"), "伤害加成", 0.16));
    temp.push_back(new Set(new Condition("ALL", "ALL", "Q"), "暴击率", 0.06));
    weapon_list.push_back(new Weapon("渔获", "thecatch", "长柄武器", 510, "元素充能效率", 0.459, 5, temp));
    temp.clear();

    temp.push_back(new Set(new Condition("ALL", "ALL", "ALL"), "攻击力", 0.24));//单怪条件
    temp.push_back(new Set(new Condition("ALL", "ALL", "ALL"), "防御力", 0.16));//多怪条件
    weapon_list.push_back(new Weapon("决斗之枪", "deathmatch", "长柄武器", 454, "暴击率", 0.368, 3, temp));
    temp.clear();

    weapon_list.push_back(new Weapon("龙脊长枪", "dragonspinespear", "长柄武器", 454, "伤害加成", 0.69, 5, temp));
    temp.clear();

    //(special)
    weapon_list.push_back(new Weapon("匣里灭辰", "dragonsbane", "长柄武器", 454, "元素精通", 221.0, 5, temp));
    temp.clear();

    //(special)
    weapon_list.push_back(new Weapon("讨龙英杰谭", "thrillingtalesofdragonslayers", "法器", 401, "生命值", 0.352, 5, temp));
    temp.clear();
}

//build new weapon(all)
//TODO:important 叠层类圣遗物触发后能快速自动叠层的总取最大层数，否则显式指定层数
bool Weapon::get_extra_special(Deployment *data) const
{
    if (name == "雾切之回光")
    {
        if (data->attack_config->condition->ele_type != "物理")
        {
            if (data->attack_config->args->sword_wuqie_level == 1) data->add_percentage("伤害加成", (0.08 * (0.75 + level * 0.25)), (name + "_extra_special"));
            else if (data->attack_config->args->sword_wuqie_level == 2) data->add_percentage("伤害加成", (0.16 * (0.75 + level * 0.25)), (name + "_extra_special"));
            else if (data->attack_config->args->sword_wuqie_level >= 3) data->add_percentage("伤害加成", (0.28 * (0.75 + level * 0.25)), (name + "_extra_special"));
        }
    }
    else if (name == "斫峰之刃")
    {
        if (!data->attack_config->background)
        {
            data->add_percentage("攻击力", (0.04 * 5 * (0.75 + level * 0.25)), (name + "_extra_special"));
            if (data->c_point->shield_sustain || data->team_config->teammate_1->shield_sustain || data->team_config->teammate_2->shield_sustain || data->team_config->teammate_3->shield_sustain)
                data->add_percentage("攻击力", (0.04 * 5 * (0.75 + level * 0.25)), (name + "_extra_special"));
        }
    }
    else if (name == "苍古自由之誓")
    {
        if (data->attack_config->react_type != "NONE")
        {
            if (data->attack_config->condition->attack_way == "平A" || data->attack_config->condition->attack_way == "重A" || data->attack_config->condition->attack_way == "下落A")
                data->add_percentage("伤害加成", (0.16 * (0.75 + level * 0.25)), (name + "_extra_special"));
            data->add_percentage("攻击力", (0.2 * (0.75 + level * 0.25)), (name + "_extra_special"));
        }
    }
    else if (name == "试作斩岩")
    {
        if (!data->attack_config->background)
        {
            data->add_percentage("攻击力", (0.04 * 4 * (0.75 + level * 0.25)), (name + "_extra_special"));
            data->add_percentage("防御力", (0.04 * 4 * (0.75 + level * 0.25)), (name + "_extra_special"));
        }
    }
        //默认给队友
//    else if (name == "原木刀")
//    {
//        if (data->attack_config->react_type.find("燃烧") != string::npos || data->attack_config->react_type.find("激化") != string::npos || data->attack_config->react_type.find("绽放") != string::npos)
//            data->add_percentage("元素精通", (60.0 * (0.75 + level * 0.25)), (name + "_extra_special"));
//    }
//TODO:NEW
    else if (name == "狼牙")
    {
        if (data->attack_config->condition->attack_way == "E" || data->attack_config->condition->attack_way == "Q")
        {
            if (data->attack_config->args->sword_langya_level >= 4) data->add_percentage("暴击率", (0.08 * (0.75 + level * 0.25)), (name + "_extra_special"));
            else if (data->attack_config->args->sword_langya_level == 3) data->add_percentage("暴击率", (0.06 * (0.75 + level * 0.25)), (name + "_extra_special"));
            else if (data->attack_config->args->sword_langya_level == 2) data->add_percentage("暴击率", (0.04 * (0.75 + level * 0.25)), (name + "_extra_special"));
            else if (data->attack_config->args->sword_langya_level == 1) data->add_percentage("暴击率", (0.02 * (0.75 + level * 0.25)), (name + "_extra_special"));
        }
    }
    else if (name == "匣里龙吟")
    {
        if (data->team_config->ele_attach_type.find("火") != string::npos || data->team_config->ele_attach_type.find("雷") != string::npos)
            data->add_percentage("伤害加成", (0.16 + level * 0.04), (name + "_extra_special"));
    }

    else if (name == "图莱杜拉的回忆")
    {
        if (!data->attack_config->background)
            if (data->attack_config->condition->attack_way == "平A")
                data->add_percentage("伤害加成", (0.48 * (0.75 + level * 0.25)), (name + "_extra_special"));
    }
    else if (name == "四风原典")
    {
        if (!data->attack_config->background)
            if (data->attack_config->condition->ele_type != "物理")
            {
                if (data->attack_config->args->catalyst_sifeng_level >= 4) data->add_percentage("伤害加成", (0.32 * (0.75 + level * 0.25)), (name + "_extra_special"));
                else if (data->attack_config->args->catalyst_sifeng_level == 3) data->add_percentage("伤害加成", (0.24 * (0.75 + level * 0.25)), (name + "_extra_special"));
                else if (data->attack_config->args->catalyst_sifeng_level == 2) data->add_percentage("伤害加成", (0.16 * (0.75 + level * 0.25)), (name + "_extra_special"));
                else if (data->attack_config->args->catalyst_sifeng_level == 1) data->add_percentage("伤害加成", (0.08 * (0.75 + level * 0.25)), (name + "_extra_special"));
            }
    }
    else if (name == "神乐之真意")
    {
        if (data->attack_config->args->catalyst_shenle_level >= 3)
        {
            if (data->attack_config->condition->attack_way == "E")
                data->add_percentage("伤害加成", (0.12 * 3 * (0.75 + level * 0.25)), (name + "_extra_special"));
            if (data->attack_config->condition->ele_type != "物理")
                data->add_percentage("伤害加成", (0.12 * (0.75 + level * 0.25)), (name + "_extra_special"));
        }
        else if (data->attack_config->args->catalyst_shenle_level == 2)
        {
            if (data->attack_config->condition->attack_way == "E")
                data->add_percentage("伤害加成", (0.12 * 2 * (0.75 + level * 0.25)), (name + "_extra_special"));
        }
        else if (data->attack_config->args->catalyst_shenle_level == 1)
        {
            if (data->attack_config->condition->attack_way == "E")
                data->add_percentage("伤害加成", (0.12 * (0.75 + level * 0.25)), (name + "_extra_special"));
        }
    }
    else if (name == "尘世之锁")
    {
        if (!data->attack_config->background)
        {
            data->add_percentage("攻击力", (0.04 * 5 * (0.75 + level * 0.25)), (name + "_extra_special"));
            if (data->c_point->shield_sustain || data->team_config->teammate_1->shield_sustain || data->team_config->teammate_2->shield_sustain || data->team_config->teammate_3->shield_sustain)
                data->add_percentage("攻击力", (0.04 * 5 * (0.75 + level * 0.25)), (name + "_extra_special"));
        }
    }
    else if (name == "千夜浮梦")
    {
        int same = 0;
        int diff = 0;
        if (data->team_config->teammate_1->ele_type == data->c_point->ele_type) same += 1;
        else diff += 1;
        if (data->team_config->teammate_2->ele_type == data->c_point->ele_type) same += 1;
        else diff += 1;
        if (data->team_config->teammate_3->ele_type == data->c_point->ele_type) same += 1;
        else diff += 1;
        data->add_percentage("元素精通", 32.0 * (0.75 + level * 0.25) * same, (name + "_extra_special"));
        data->add_percentage("伤害加成", (0.06 + level * 0.04) * diff, (name + "_extra_special"));
    }
    else if (name == "白辰之环")
    {
        if ((data->attack_config->react_type.find("超载") != string::npos && (data->attack_config->condition->ele_type == "雷" || data->attack_config->condition->ele_type == "火")) ||
            (data->attack_config->react_type.find("感电") != string::npos && (data->attack_config->condition->ele_type == "雷" || data->attack_config->condition->ele_type == "水")) ||
            (data->attack_config->react_type.find("激化") != string::npos && (data->attack_config->condition->ele_type == "雷" || data->attack_config->condition->ele_type == "草")) ||
            (data->attack_config->react_type.find("超导") != string::npos && (data->attack_config->condition->ele_type == "雷" || data->attack_config->condition->ele_type == "冰")) ||
            (data->attack_config->react_type.find("扩散") != string::npos && data->team_config->ele_allow_spread.find("雷") != string::npos && (data->attack_config->condition->ele_type == "雷" || data->attack_config->condition->ele_type == "风")) ||
            (data->attack_config->react_type.find("结晶") != string::npos && data->team_config->ele_allow_spread.find("雷") != string::npos && (data->attack_config->condition->ele_type == "雷" || data->attack_config->condition->ele_type == "岩")))
            data->add_percentage("伤害加成", (0.1 * (0.75 + level * 0.25)), (name + "_extra_special"));
    }
    else if (name == "万国诸海图谱")
    {
        if (data->attack_config->react_type != "NONE")
            if (data->attack_config->condition->ele_type != "物理")
                data->add_percentage("伤害加成", (0.16 * (0.75 + level * 0.25)), (name + "_extra_special"));
    }
    else if (name == "匣里日月")
    {
        if (!data->attack_config->background)
            if (data->attack_config->condition->attack_way == "平A" || data->attack_config->condition->attack_way == "E" || data->attack_config->condition->attack_way == "Q")
                data->add_percentage("伤害加成", (0.2 * (0.75 + level * 0.25)), (name + "_extra_special"));
    }
        //流浪乐章默认无加成
//    else if (name == "流浪乐章")
//    {
//        //每个各取1/4
//        data->add_percentage("攻击力", (0.15 * (0.75 + level * 0.25)), (name + "_extra_special"));
//        data->add_percentage("伤害加成", (0.12 * (0.75 + level * 0.25)), (name + "_extra_special"));
//        data->add_percentage("元素精通", (60.0 * (0.75 + level * 0.25)), (name + "_extra_special"));
//    }
    else if (name == "盈满之实")
    {
        if (data->attack_config->react_type != "NONE")
        {
            data->add_percentage("元素精通", (5 * (21.0 + level * 3.0)), (name + "_extra_special"));//元素反应，5层
            data->add_percentage("攻击力", -0.25, (name + "_extra_special"));//元素反应，5层
        }
    }
        //TODO:NEW
    else if (name == "遗祀玉珑")
    {
        if (data->attack_config->background)
        {
            data->add_percentage("元素精通", (40.0 * (0.75 + level * 0.25)), (name + "_extra_special"));
            data->add_percentage("生命值", (0.32 * (0.75 + level * 0.25)), (name + "_extra_special"));
        }
    }
    else if (name == "嘟嘟可故事集")
    {
        if (!data->attack_config->background)
        {
            if (data->attack_config->condition->attack_way == "重A")
                data->add_percentage("伤害加成", (0.16 * (0.75 + level * 0.25)), (name + "_extra_special"));
            data->add_percentage("攻击力", (0.08 * (0.75 + level * 0.25)), (name + "_extra_special"));
        }
    }

    else if (name == "冬极白星")
    {
        if (data->attack_config->args->bow_dongji_level == 1) data->add_percentage("攻击力", (0.1 * (0.75 + level * 0.25)), (name + "_extra_special"));
        else if (data->attack_config->args->bow_dongji_level == 2) data->add_percentage("攻击力", (0.2 * (0.75 + level * 0.25)), (name + "_extra_special"));
        else if (data->attack_config->args->bow_dongji_level == 3) data->add_percentage("攻击力", (0.3 * (0.75 + level * 0.25)), (name + "_extra_special"));
        else if (data->attack_config->args->bow_dongji_level >= 4) data->add_percentage("攻击力", (0.48 * (0.75 + level * 0.25)), (name + "_extra_special"));
    }
    else if (name == "飞雷之弦振")
    {
        if (data->attack_config->condition->attack_way == "平A")
        {
            if (data->attack_config->args->bow_feilei_level == 1) data->add_percentage("伤害加成", (0.12 * (0.75 + level * 0.25)), (name + "_extra_special"));
            else if (data->attack_config->args->bow_feilei_level == 2) data->add_percentage("伤害加成", (0.24 * (0.75 + level * 0.25)), (name + "_extra_special"));
            else if (data->attack_config->args->bow_feilei_level >= 3) data->add_percentage("伤害加成", (0.40 * (0.75 + level * 0.25)), (name + "_extra_special"));
        }
    }
        //TODO:NEW
    else if (name == "最初的大魔术")
    {
        int same = 1;
        if (data->team_config->teammate_1->ele_type == data->c_point->ele_type) same += 1;
        if (data->team_config->teammate_2->ele_type == data->c_point->ele_type) same += 1;
        if (data->team_config->teammate_3->ele_type == data->c_point->ele_type) same += 1;
        if (same == 1) data->add_percentage("攻击力", (0.08 * (0.75 + level * 0.25)), (name + "_extra_special"));
        else if (same == 2) data->add_percentage("攻击力", (0.16 * (0.75 + level * 0.25)), (name + "_extra_special"));
        else if (same >= 3) data->add_percentage("攻击力", (0.40 * (0.75 + level * 0.25)), (name + "_extra_special"));
    }
    else if (name == "暗巷猎手")
    {
        if (data->attack_config->background)
            data->add_percentage("伤害加成", 0.2 * (0.75 + level * 0.25), (name + "_extra_special"));
    }
    else if (name == "曚云之月")
    {
        if (data->attack_config->condition->attack_way == "Q")
            data->add_percentage("伤害加成", min(334.0, data->c_point->Q_energy + data->team_config->teammate_1->Q_energy + data->team_config->teammate_2->Q_energy + data->team_config->teammate_3->Q_energy)
                                             * 0.0012 * (0.75 + level * 0.25), (name + "_extra_special"));
    }
    else if (name == "弓藏")
    {
        if (data->attack_config->condition->attack_way == "重A")
            data->add_percentage("伤害加成", -0.1, (name + "_extra_special"));
    }
        //TODO:NEW
    else if (name == "静谧之曲")
    {
        if (data->c_point->heal_sustain || data->team_config->teammate_1->heal_sustain || data->team_config->teammate_2->heal_sustain || data->team_config->teammate_3->heal_sustain)
            data->add_percentage("伤害加成", 0.16 * (0.75 + level * 0.25), (name + "_extra_special"));
    }
    else if (name == "幽夜华尔兹")
    {
        if (!data->attack_config->background)
            if (data->attack_config->condition->attack_way == "平A" || data->attack_config->condition->attack_way == "E")
                data->add_percentage("伤害加成", (0.2 * (0.75 + level * 0.25)), (name + "_extra_special"));
    }
    else if (name == "破魔之弓")
    {
        if (data->attack_config->condition->attack_way == "平A")
            data->add_percentage("伤害加成", ((data->attack_config->args->bow_pomo_fullenergy ? 2 : 1) * 0.16 * (0.75 + level * 0.25)), (name + "_extra_special"));
        if (data->attack_config->condition->attack_way == "重A")
            data->add_percentage("伤害加成", ((data->attack_config->args->bow_pomo_fullenergy ? 2 : 1) * 0.12 * (0.75 + level * 0.25)), (name + "_extra_special"));
    }
    else if (name == "王下近侍")
    {
        if (!data->attack_config->background)
            data->add_percentage("元素精通", (40.0 + level * 20.0), (name + "_extra_special"));//EQ后
    }
    else if (name == "钢轮弓")
    {
        if (!data->attack_config->background)
            data->add_percentage("攻击力", (0.04 * 4 * (0.75 + level * 0.25)), (name + "_extra_special"));
    }

    else if (name == "苇海信标")
    {
        if (!data->c_point->shield_sustain && !data->team_config->teammate_1->shield_sustain && !data->team_config->teammate_2->shield_sustain && !data->team_config->teammate_3->shield_sustain)
            data->add_percentage("生命值", (0.32 * (0.75 + level * 0.25)), (name + "_extra_special"));//不处于护盾下，条件弱
    }
    else if (name == "无工之剑")
    {
        if (!data->attack_config->background)
        {
            data->add_percentage("攻击力", (0.04 * 5 * (0.75 + level * 0.25)), (name + "_extra_special"));
            if (data->c_point->shield_sustain || data->team_config->teammate_1->shield_sustain || data->team_config->teammate_2->shield_sustain || data->team_config->teammate_3->shield_sustain)
                data->add_percentage("攻击力", (0.04 * 5 * (0.75 + level * 0.25)), (name + "_extra_special"));
        }
    }
        //默认给队友
//    else if (name == "森林王器")
//    {
//        if (data->attack_config->react_type.find("燃烧") != string::npos || data->attack_config->react_type.find("激化") != string::npos || data->attack_config->react_type.find("绽放") != string::npos)
//            data->add_percentage("元素精通", (60.0 * (0.75 + level * 0.25)), (name + "_extra_special"));
//    }
    else if (name == "螭骨剑")
    {
        data->add_percentage("伤害加成", (0.25 + level * 0.05), (name + "_extra_special"));
    }
    else if (name == "白影剑")
    {
        if (!data->attack_config->background)
        {
            data->add_percentage("攻击力", (0.06 * 4 * (0.75 + level * 0.25)), (name + "_extra_special"));
            data->add_percentage("防御力", (0.06 * 4 * (0.75 + level * 0.25)), (name + "_extra_special"));
        }
    }
    else if (name == "千岩古剑")
    {
        data->add_percentage("攻击力", (0.24 + level * 0.04), (name + "_extra_special"));//默认3层
        data->add_percentage("暴击率", (0.08 + level * 0.04), (name + "_extra_special"));//默认3层
    }
    else if (name == "恶王丸")
    {
        if (data->attack_config->condition->attack_way == "Q")
            data->add_percentage("伤害加成", min(334.0, data->c_point->Q_energy + data->team_config->teammate_1->Q_energy + data->team_config->teammate_2->Q_energy + data->team_config->teammate_3->Q_energy)
                                             * 0.0012 * (0.75 + level * 0.25), (name + "_extra_special"));
    }
        //TODO:NEW
    else if (name == "浪影阔剑")
    {
        if (data->c_point->heal_sustain || data->team_config->teammate_1->heal_sustain || data->team_config->teammate_2->heal_sustain || data->team_config->teammate_3->heal_sustain)
            data->add_percentage("攻击力", 0.24 * (0.75 + level * 0.25), (name + "_extra_special"));
    }
    else if (name == "钟剑")
    {
        if (data->c_point->shield_sustain || data->team_config->teammate_1->shield_sustain || data->team_config->teammate_2->shield_sustain || data->team_config->teammate_3->shield_sustain)
            data->add_percentage("伤害加成", (0.12 * (0.75 + level * 0.25)), (name + "_extra_special"));
    }
    else if (name == "雨裁")
    {
        if (data->team_config->ele_attach_type.find("水") != string::npos || data->team_config->ele_attach_type.find("雷") != string::npos)
            data->add_percentage("伤害加成", (0.16 + level * 0.04), (name + "_extra_special"));
    }

    else if (name == "息灾")
    {
        data->add_percentage("攻击力", (0.192 * (0.75 + level * 0.25)), (name + "_extra_special"));
        if (data->attack_config->background)
            data->add_percentage("攻击力", (0.192 * (0.75 + level * 0.25)), (name + "_extra_special"));
    }
    else if (name == "和璞鸢")
    {
        if (!data->attack_config->background)
        {
            data->add_percentage("攻击力", (0.025 + level * 0.007) * 7, (name + "_extra_special"));//默认满层
            data->add_percentage("伤害加成", (0.75 + level * 0.25) * 0.12, (name + "_extra_special"));//默认满层
        }
    }
    else if (name == "贯虹之槊")
    {
        if (!data->attack_config->background)
        {
            data->add_percentage("攻击力", (0.04 * 5 * (0.75 + level * 0.25)), (name + "_extra_special"));
            if (data->c_point->shield_sustain || data->team_config->teammate_1->shield_sustain || data->team_config->teammate_2->shield_sustain || data->team_config->teammate_3->shield_sustain)
                data->add_percentage("攻击力", (0.04 * 5 * (0.75 + level * 0.25)), (name + "_extra_special"));
        }
    }
    else if (name == "薙草之稻光")
    {
        data->add_percentage("元素充能效率", (0.25 + level * 0.05), (name + "_extra_special"));//Q后
    }
    else if (name == "断浪长鳍")
    {
        if (data->attack_config->condition->attack_way == "Q")
            data->add_percentage("伤害加成", min(334.0, data->c_point->Q_energy + data->team_config->teammate_1->Q_energy + data->team_config->teammate_2->Q_energy + data->team_config->teammate_3->Q_energy)
                                             * 0.0012 * (0.75 + level * 0.25), (name + "_extra_special"));
    }
    else if (name == "千岩长枪")
    {
        data->add_percentage("攻击力", (0.24 + level * 0.04), (name + "_extra_special"));//默认3层
        data->add_percentage("暴击率", (0.08 + level * 0.04), (name + "_extra_special"));//默认3层
    }
        //默认给队友
//    else if (name == "贯月矢")
//    {
//        if (data->attack_config->react_type.find("燃烧") != string::npos || data->attack_config->react_type.find("激化") != string::npos || data->attack_config->react_type.find("绽放") != string::npos)
//            data->add_percentage("攻击力", (0.16 * (0.75 + level * 0.25)), (name + "_extra_special"));
//    }
    else if (name == "试作星镰")
    {
        if (data->attack_config->args->polearm_shizuo_level >= 2)
        {
            if (data->attack_config->condition->attack_way == "平A" || data->attack_config->condition->attack_way == "重A")
                data->add_percentage("伤害加成", (0.08 * 2 * (0.75 + level * 0.25)), (name + "_extra_special"));
        }
        else if (data->attack_config->args->polearm_shizuo_level == 1)
        {
            if (data->attack_config->condition->attack_way == "平A" || data->attack_config->condition->attack_way == "重A")
                data->add_percentage("伤害加成", (0.08 * (0.75 + level * 0.25)), (name + "_extra_special"));
        }
    }
        //TODO:NEW
    else if (name == "峡湾长歌")
    {
        int diff_element_num = 1;
        if (data->team_config->teammate_1->ele_type != data->c_point->ele_type) diff_element_num++;
        if (data->team_config->teammate_2->ele_type != data->team_config->teammate_1->ele_type && data->team_config->teammate_2->ele_type != data->c_point->ele_type) diff_element_num++;
        if (data->team_config->teammate_3->ele_type != data->team_config->teammate_2->ele_type && data->team_config->teammate_3->ele_type != data->team_config->teammate_1->ele_type && data->team_config->teammate_3->ele_type != data->c_point->ele_type) diff_element_num++;
        if (diff_element_num >= 3) data->add_percentage("元素精通", (120.0 * (0.75 + level * 0.25)), (name + "_extra_special"));
    }
    else if (name == "风信之锋")
    {
        if (data->attack_config->react_type != "NONE")
        {
            data->add_percentage("攻击力", (0.12 * (0.75 + level * 0.25)), (name + "_extra_special"));
            data->add_percentage("元素精通", (48.0 * (0.75 + level * 0.25)), (name + "_extra_special"));
        }
    }
    else if (name == "匣里灭辰")
    {
        if (data->team_config->ele_attach_type.find("水") != string::npos || data->team_config->ele_attach_type.find("火") != string::npos)
            data->add_percentage("伤害加成", (0.16 + level * 0.04), (name + "_extra_special"));
    }
    return true;
}

//build new weapon(all) 被转化的属性有效
void Weapon::modify_useful_attribute(Deployment *data)
{
    if (data->w_point->name == "磐岩结绿" && data->data_list[str2index_full("攻击力")]->useful)
        data->data_list[str2index_full("生命值")]->useful = true;
    else if (data->w_point->name == "裁叶萃光" && (data->attack_config->condition->attack_way == "平A" || data->attack_config->condition->attack_way == "E"))
        data->data_list[str2index_full("元素精通")]->useful = true;
    else if (data->w_point->name == "圣显之钥" && data->attack_config->args->sword_shengxian_level > 0 && data->data_list[str2index_full("元素精通")]->useful)
        data->data_list[str2index_full("生命值")]->useful = true;
        //TODO:NEW
    else if (data->w_point->name == "海渊终曲" && data->data_list[str2index_full("攻击力")]->useful && (data->c_point->heal_sustain || data->team_config->teammate_1->heal_sustain || data->team_config->teammate_2->heal_sustain || data->team_config->teammate_3->heal_sustain))
        data->data_list[str2index_full("生命值")]->useful = true;
    else if (data->w_point->name == "辰砂之纺锤" && data->attack_config->condition->attack_way == "E")
        data->data_list[str2index_full("防御力")]->useful = true;
    else if (data->w_point->name == "西福斯的月光" && (data->data_list[str2index_full("元素充能效率")]->useful || data->need_to_satisfy_recharge))
        data->data_list[str2index_full("元素精通")]->useful = true;
    else if (data->w_point->name == "不灭月华" && data->attack_config->condition->attack_way == "平A")
        data->data_list[str2index_full("生命值")]->useful = true;
    else if (data->w_point->name == "碧落之珑" && data->attack_config->args->catalyst_biluo_enable)
        data->data_list[str2index_full("生命值")]->useful = true;
        //TODO:NEW
    else if (data->w_point->name == "纯水流华" && data->data_list[str2index_full("伤害加成")]->useful && (data->c_point->heal_sustain || data->team_config->teammate_1->heal_sustain || data->team_config->teammate_2->heal_sustain || data->team_config->teammate_3->heal_sustain))
        data->data_list[str2index_full("生命值")]->useful = true;
    else if (data->w_point->name == "流浪的晚星" && data->data_list[str2index_full("攻击力")]->useful)
        data->data_list[str2index_full("元素精通")]->useful = true;
    else if (data->w_point->name == "猎人之径" && data->attack_config->condition->attack_way == "重A")
        data->data_list[str2index_full("元素精通")]->useful = true;
    else if (data->w_point->name == "赤角石溃杵" && (data->attack_config->condition->attack_way == "平A" || data->attack_config->condition->attack_way == "重A"))
        data->data_list[str2index_full("防御力")]->useful = true;
    else if (data->w_point->name == "玛海菈的水色" && data->data_list[str2index_full("攻击力")]->useful)
        data->data_list[str2index_full("元素精通")]->useful = true;
    else if (data->w_point->name == "护摩之杖" && data->data_list[str2index_full("攻击力")]->useful)
        data->data_list[str2index_full("生命值")]->useful = true;
    else if (data->w_point->name == "薙草之稻光" && data->data_list[str2index_full("攻击力")]->useful)
        data->data_list[str2index_full("元素充能效率")]->useful = true;
    else if (data->w_point->name == "赤沙之杖" && data->data_list[str2index_full("攻击力")]->useful)
        data->data_list[str2index_full("元素精通")]->useful = true;
}

//build new artifact(all)
void init_artifact_data()
{
    artifact_list.push_back(new Artifact("EMPTY", "EMPTY", nullptr, nullptr));

    artifact_list.push_back(new Artifact("流浪大地的乐团", "wandererstroupe", new Set(new Condition("ALL", "ALL", "ALL"), "元素精通", 80.0),
                                         new Set(new Condition("ALL", "法器|弓", "重A"), "伤害加成", 0.35)));
    artifact_list.push_back(new Artifact("角斗士的终幕礼", "gladiatorsfinale", new Set(new Condition("ALL", "ALL", "ALL"), "攻击力", 0.18),
                                         new Set(new Condition("ALL", "单手剑|双手剑|长柄武器", "平A"), "伤害加成", 0.35)));
    artifact_list.push_back(new Artifact("冰风迷途的勇士", "blizzardstrayer", new Set(new Condition("冰", "ALL", "ALL"), "伤害加成", 0.15),
                                         nullptr));//(special)
    artifact_list.push_back(new Artifact("沉沦之心", "heartofdepth", new Set(new Condition("水", "ALL", "ALL"), "伤害加成", 0.15),
                                         new Set(new Condition("ALL", "ALL", "平A|重A"), "伤害加成", 0.3)));
    artifact_list.push_back(new Artifact("悠古的磐岩", "archaicpetra", new Set(new Condition("岩", "ALL", "ALL"), "伤害加成", 0.15),
                                         nullptr));//(get_team)
    artifact_list.push_back(new Artifact("逆飞的流星", "retracingbolide", new Set(new Condition("ALL", "ALL", "ALL"), "护盾强效", 0.35),
                                         nullptr));//(special)
    artifact_list.push_back(new Artifact("染血的骑士道", "bloodstainedchivalry", new Set(new Condition("物理", "ALL", "ALL"), "伤害加成", 0.25),
                                         nullptr));//new Set(new Condition("ALL", "ALL", "重A"), "伤害加成", 0.5)));//击败敌人
    artifact_list.push_back(new Artifact("昔日宗室之仪", "noblesseoblige", new Set(new Condition("ALL", "ALL", "Q"), "伤害加成", 0.2),
                                         new Set(new Condition("ALL", "ALL", "ALL"), "攻击力", 0.2)));//(get_team) 高估
    artifact_list.push_back(new Artifact("翠绿之影", "viridescentvenerer", new Set(new Condition("风", "ALL", "ALL"), "伤害加成", 0.15),
                                         nullptr));//(react) (get_team)
    artifact_list.push_back(new Artifact("被怜爱的少女", "maidenbeloved", new Set(new Condition("ALL", "ALL", "ALL"), "治疗加成", 0.15),
                                         nullptr));//受治疗加成
    artifact_list.push_back(new Artifact("苍白之火", "paleflame", new Set(new Condition("物理", "ALL", "ALL"), "伤害加成", 0.25),
                                         nullptr));//(special)
    artifact_list.push_back(new Artifact("千岩牢固", "tenacityofthemillelith", new Set(new Condition("ALL", "ALL", "ALL"), "生命值", 0.2),
                                         nullptr));//(special) (get_team)
    artifact_list.push_back(new Artifact("炽烈的炎之魔女", "crimsonwitchofflames", new Set(new Condition("火", "ALL", "ALL"), "伤害加成", 0.15),
                                         nullptr));//(special) (react)
    artifact_list.push_back(new Artifact("渡过烈火的贤人", "lavawalker", nullptr, nullptr));//(special)
    artifact_list.push_back(new Artifact("如雷的盛怒", "thunderingfury", new Set(new Condition("雷", "ALL", "ALL"), "伤害加成", 0.15),
                                         nullptr));//(react) 减CD
    artifact_list.push_back(new Artifact("平息鸣雷的尊者", "thundersoother", nullptr, nullptr));//(special)
    artifact_list.push_back(new Artifact("追忆之注连", "shimenawasreminiscence", new Set(new Condition("ALL", "ALL", "ALL"), "攻击力", 0.18),
                                         nullptr));//new Set(new Condition("ALL", "ALL", "平A|重A|下落A"), "伤害加成", 0.5)));//15能量
    artifact_list.push_back(new Artifact("绝缘之旗印", "emblemofseveredfate", new Set(new Condition("ALL", "ALL", "ALL"), "元素充能效率", 0.2),
                                         nullptr));//(get_convert)
    artifact_list.push_back(new Artifact("华馆梦醒形骸记", "huskofopulentdreams", new Set(new Condition("ALL", "ALL", "ALL"), "防御力", 0.3),
                                         nullptr));//(special)
    artifact_list.push_back(new Artifact("海染砗磲", "oceanhuedclam", new Set(new Condition("ALL", "ALL", "ALL"), "治疗加成", 0.15),
                                         nullptr));//额外物理伤害
    artifact_list.push_back(new Artifact("辰砂往生录", "vermillionhereafter", new Set(new Condition("ALL", "ALL", "ALL"), "攻击力", 0.18),
                                         nullptr));//(special)
    artifact_list.push_back(new Artifact("来歆余响", "echoesofanoffering", new Set(new Condition("ALL", "ALL", "ALL"), "攻击力", 0.18),
                                         new Set(new Condition("ALL", "ALL", "平A"), "额外倍率", 0.35)));
    artifact_list.push_back(new Artifact("深林的记忆", "deepwoodmemories", new Set(new Condition("草", "ALL", "ALL"), "伤害加成", 0.15),
                                         nullptr));//(special) (get_team)
    artifact_list.push_back(new Artifact("饰金之梦", "gildeddreams", new Set(new Condition("ALL", "ALL", "ALL"), "元素精通", 80.0),
                                         nullptr));//(special)
    artifact_list.push_back(new Artifact("沙上楼阁史话", "desertpavilionchronicle", new Set(new Condition("风", "ALL", "ALL"), "伤害加成", 0.15),
                                         nullptr));
    artifact_list.push_back(new Artifact("乐园遗落之花", "flowerofparadiselost", new Set(new Condition("ALL", "ALL", "ALL"), "元素精通", 80.0),
                                         nullptr));//(react)
    artifact_list.push_back(new Artifact("水仙之梦", "nymphsdream", new Set(new Condition("水", "ALL", "ALL"), "伤害加成", 0.15),
                                         nullptr));//(special)
    artifact_list.push_back(new Artifact("花海甘露之光", "dewflowersglow", new Set(new Condition("ALL", "ALL", "ALL"), "生命值", 0.2),
                                         nullptr));//(special)
    //TODO：NEW
    artifact_list.push_back(new Artifact("逐影猎人", "", new Set(new Condition("ALL", "ALL", "平A|重A"), "伤害加成", 0.15),
                                         nullptr));//(special)
    artifact_list.push_back(new Artifact("黄金剧团", "", new Set(new Condition("ALL", "ALL", "E"), "伤害加成", 0.2),
                                         nullptr));//(special)
}

//build new artifact(all) 保证二件套效果和四件套效果分开
//TODO:important 叠层类圣遗物触发后能快速自动叠层的总取最大层数，否则显式指定层数
bool Artifact::get_extra_special(Deployment *data, bool if_4_piece) const
{
    if (if_4_piece && name == "冰风迷途的勇士")
    {
        if (data->team_config->ele_attach_type.find("冰") != string::npos)//冰附着
            data->add_percentage("暴击率", 0.2, (name + "_extra_special"));
        if (data->attack_config->react_type.find("冻结") != string::npos)
            data->add_percentage("暴击率", 0.2, (name + "_extra_special"));//冻结
    }
    else if (if_4_piece && name == "逆飞的流星")
    {
        if (data->c_point->shield_sustain || data->team_config->teammate_1->shield_sustain || data->team_config->teammate_2->shield_sustain || data->team_config->teammate_3->shield_sustain)
            if (data->attack_config->condition->attack_way == "平A" || data->attack_config->condition->attack_way == "重A")
                data->add_percentage("伤害加成", 0.4, (name + "_extra_special"));
    }
    else if (if_4_piece && name == "苍白之火")
    {
        if (data->attack_config->args->cangbai_level >= 2)
        {
            data->add_percentage("攻击力", 0.18, name + "_extra_special");
            if (data->attack_config->condition->ele_type == "物理") data->add_percentage("伤害加成", 0.25, (name + "_extra_special"));
        }
        else if (data->attack_config->args->cangbai_level == 1)
        {
            data->add_percentage("攻击力", 0.09, name + "_extra_special");
        }
    }
    else if (if_4_piece && name == "千岩牢固")
    {
        if (data->attack_config->args->qianyan_enable)
        {
            data->add_percentage("攻击力", 0.2, (name + "_extra_special"));
            data->add_percentage("护盾强效", 0.3, (name + "_extra_special"));
        }
    }
    else if (if_4_piece && name == "炽烈的炎之魔女")
    {
        if (data->attack_config->condition->ele_type == "火")
        {
            if (data->attack_config->args->monv_level >= 3) data->add_percentage("伤害加成", 0.225, (name + "_extra_special"));
            else if (data->attack_config->args->monv_level == 2) data->add_percentage("伤害加成", 0.15, (name + "_extra_special"));
            else if (data->attack_config->args->monv_level == 1) data->add_percentage("伤害加成", 0.075, (name + "_extra_special"));
        }
    }
    else if (if_4_piece && name == "渡过烈火的贤人")
    {
        if (data->team_config->ele_attach_type.find("火") != string::npos)//火附着
            data->add_percentage("伤害加成", 0.35, (name + "_extra_special"));
    }
    else if (if_4_piece && name == "平息鸣雷的尊者")
    {
        if (data->team_config->ele_attach_type.find("雷") != string::npos)//雷附着
            data->add_percentage("伤害加成", 0.35, (name + "_extra_special"));
    }
    else if (if_4_piece && name == "华馆梦醒形骸记")
    {
        if (data->attack_config->background || (!data->attack_config->background && data->c_point->ele_type == "岩"))
        {
            data->add_percentage("防御力", 0.24, (name + "_extra_special"));
            if (data->attack_config->condition->ele_type == "岩") data->add_percentage("伤害加成", 0.24, (name + "_extra_special"));
        }
    }
    else if (if_4_piece && name == "辰砂往生录")
    {
        if (data->attack_config->args->chensha_enable)
            data->add_percentage("攻击力", 0.48, (name + "_extra_special"));
    }
    else if (if_4_piece && name == "深林的记忆")
    {
        if (data->attack_config->args->shenlin_enable)
            if (data->attack_config->condition->ele_type == "草")
                data->add_percentage("抗性削弱", 0.3, (name + "_extra_special"));
    }
    else if (if_4_piece && name == "饰金之梦")
    {
        if (data->attack_config->react_type != "NONE")
        {
            int same = 0;
            int diff = 0;
            if (data->team_config->teammate_1->ele_type == data->c_point->ele_type) same += 1;
            else diff += 1;
            if (data->team_config->teammate_2->ele_type == data->c_point->ele_type) same += 1;
            else diff += 1;
            if (data->team_config->teammate_3->ele_type == data->c_point->ele_type) same += 1;
            else diff += 1;
            data->add_percentage("攻击力", 0.14 * same, (name + "_extra_special"));
            data->add_percentage("元素精通", 50.0 * diff, (name + "_extra_special"));
        }
    }
    else if (if_4_piece && name == "沙上楼阁史话")
    {
        if (!data->attack_config->background)
            if (data->attack_config->condition->attack_way == "平A" || data->attack_config->condition->attack_way == "重A" || data->attack_config->condition->attack_way == "下落A")
                data->add_percentage("伤害加成", 0.4, (name + "_extra_special"));
    }
    else if (if_4_piece && name == "水仙之梦")
    {
        if (data->attack_config->args->shuixian_level == 1)
        {
            data->add_percentage("攻击力", 0.07, (name + "_extra_special"));
            if (data->attack_config->condition->ele_type == "水") data->add_percentage("伤害加成", 0.04, (name + "_extra_special"));
        }
        else if (data->attack_config->args->shuixian_level == 2)
        {
            data->add_percentage("攻击力", 0.16, (name + "_extra_special"));
            if (data->attack_config->condition->ele_type == "水") data->add_percentage("伤害加成", 0.09, (name + "_extra_special"));
        }
        else if (data->attack_config->args->shuixian_level >= 3)
        {
            data->add_percentage("攻击力", 0.25, (name + "_extra_special"));
            if (data->attack_config->condition->ele_type == "水") data->add_percentage("伤害加成", 0.15, (name + "_extra_special"));
        }
    }
    else if (if_4_piece && name == "花海甘露之光")
    {
        if (data->attack_config->condition->attack_way == "E" || data->attack_config->condition->attack_way == "Q")
        {
            if (!data->attack_config->background && !data->c_point->shield_sustain && !data->team_config->teammate_1->shield_sustain && !data->team_config->teammate_2->shield_sustain && !data->team_config->teammate_3->shield_sustain)
                data->add_percentage("伤害加成", 0.5, (name + "_extra_special"));
            else
                data->add_percentage("伤害加成", 0.1, (name + "_extra_special"));
        }
    }
        //TODO:NEW
    else if (if_4_piece && name == "逐影猎人")
    {
        if (data->attack_config->args->zhuying_level == 1) data->add_percentage("暴击率", 0.11, (name + "_extra_special"));
        else if (data->attack_config->args->zhuying_level == 2) data->add_percentage("暴击率", 0.22, (name + "_extra_special"));
        else if (data->attack_config->args->zhuying_level >= 3) data->add_percentage("暴击率", 0.33, (name + "_extra_special"));
    }
    else if (if_4_piece && name == "黄金剧团")
    {
        if (data->attack_config->condition->attack_way == "E")
        {
            data->add_percentage("伤害加成", 0.2, (name + "_extra_special"));
            if (data->attack_config->background) data->add_percentage("伤害加成", 0.2, (name + "_extra_special"));
        }
    }
    return true;
}

//build new artifact(all) 被转化的属性有效
void Artifact::modify_useful_attribute(Deployment *data)
{
    if (data->suit1->name == "绝缘之旗印" && data->suit2->name == "绝缘之旗印" && data->attack_config->condition->attack_way == "Q")
        data->data_list[str2index_full("元素充能效率")]->useful = true;
}

//build new artifact(all) 提供充能、队友加成的有效
void Deployment::check_artifact_special(bool &suit1_valid, bool &suit2_valid, bool if_4_piece)
{
    //特殊判断圣遗物套装，原来肯定-现在肯定；原来否定-现在肯定；原来肯定-现在否定；原来否定-现在否定
    if (if_4_piece)
    {
        if (suit1->name == "悠古的磐岩")
        {
            if (c_point->ele_type == "岩")
                suit1_valid = suit2_valid = true;//原来肯定-现在肯定；原来否定-现在肯定；
        }
        else if (suit1->name == "翠绿之影")
        {
            if (c_point->ele_type == "风")
                suit1_valid = suit2_valid = true;//原来肯定-现在肯定；原来否定-现在肯定；
        }
        else if (suit1->name == "如雷的盛怒")
        {
            if (c_point->ele_type == "雷")
                suit1_valid = suit2_valid = true;//原来肯定-现在肯定；原来否定-现在肯定；
        }
        else if (suit1->name == "绝缘之旗印")
        {
            if (attack_config->condition->attack_way == "Q")
                suit1_valid = suit2_valid = true;//原来肯定-现在肯定；原来否定-现在肯定；
        }
        else if (suit1->name == "海染砗磲" || suit1->name == "被怜爱的少女")
        {
            if (c_point->heal_sustain)
                suit1_valid = suit2_valid = true;//原来肯定-现在肯定；原来否定-现在肯定；
        }
        else if (suit1->name == "乐园遗落之花")
        {
            if (attack_config->react_type.find("绽放") != string::npos)
                suit1_valid = suit2_valid = true;//原来肯定-现在肯定；原来否定-现在肯定；
        }

            //team
        else if (suit1->name == "昔日宗室之仪")
        {
            suit1_valid = suit2_valid = true;//原来肯定-现在肯定；原来否定-现在肯定；
        }
        else if (suit1->name == "千岩牢固")
        {
            if (attack_config->args->qianyan_enable)
                suit1_valid = suit2_valid = true;//原来肯定-现在肯定；原来否定-现在肯定；
        }
        else if (suit1->name == "深林的记忆")
        {
            if (attack_config->args->shenlin_enable)
                suit1_valid = suit2_valid = true;//原来肯定-现在肯定；原来否定-现在肯定；
        }

        //recharge
    }
    else
    {
        //2+2
        //攻击：角斗+（追忆） 物理：染血+（苍白） 治疗：少女+（海染） 精通：乐团+（饰金） 风伤：翠绿+（沙上） 水伤：沉沦+（水仙） 生命：千岩+（花海）
        //suit1
        if ((suit1->name == "追忆之注连" && suit2->name != "角斗士的终幕礼") || suit1->name == "辰砂往生录" || suit1->name == "来歆余响") suit1_valid = false;//原来肯定-现在否定；原来否定-现在否定
        if (suit1->name == "苍白之火" && suit2->name != "染血的骑士道") suit1_valid = false;//原来肯定-现在否定；原来否定-现在否定
        if (suit1->name == "海染砗磲" && suit2->name != "被怜爱的少女") suit1_valid = false;//原来肯定-现在否定；原来否定-现在否定
        if ((suit1->name == "饰金之梦" && suit2->name != "流浪大地的乐团") || suit1->name == "乐园遗落之花") suit1_valid = false;//原来肯定-现在否定；原来否定-现在否定
        if (suit1->name == "沙上楼阁史话" && suit2->name != "翠绿之影") suit1_valid = false;//原来肯定-现在否定；原来否定-现在否定
        if (suit1->name == "水仙之梦" && suit2->name != "沉沦之心") suit1_valid = false;//原来肯定-现在否定；原来否定-现在否定
        if (suit1->name == "花海甘露之光" && suit2->name != "千岩牢固") suit1_valid = false;//原来肯定-现在否定；原来否定-现在否定
        //suit2
        if ((suit2->name == "追忆之注连" && suit1->name != "角斗士的终幕礼") || suit2->name == "辰砂往生录" || suit2->name == "来歆余响") suit2_valid = false;//原来肯定-现在否定；原来否定-现在否定
        if (suit2->name == "苍白之火" && suit1->name != "染血的骑士道") suit2_valid = false;//原来肯定-现在否定；原来否定-现在否定
        if (suit2->name == "海染砗磲" && suit1->name != "被怜爱的少女") suit2_valid = false;//原来肯定-现在否定；原来否定-现在否定
        if ((suit2->name == "饰金之梦" && suit1->name != "流浪大地的乐团") || suit2->name == "乐园遗落之花") suit2_valid = false;//原来肯定-现在否定；原来否定-现在否定
        if (suit2->name == "沙上楼阁史话" && suit1->name != "翠绿之影") suit2_valid = false;//原来肯定-现在否定；原来否定-现在否定
        if (suit2->name == "水仙之梦" && suit1->name != "沉沦之心") suit2_valid = false;//原来肯定-现在否定；原来否定-现在否定
        if (suit2->name == "花海甘露之光" && suit1->name != "千岩牢固") suit2_valid = false;//原来肯定-现在否定；原来否定-现在否定
    }
}

//build new character(needed)||build new weapon(all)||build new artifact(all) 所有转化类属性的有效百分比决定开关
void Deployment::check_useful_attribute()
{
    //实际上应该采用（武器-圣遗物）对的形式考虑还原useful
    //如果useful相对于config没有改变，那不影响；如果useful相对与config改变了，一定是转化类的属性新增了有效词条，那要检查是否值得新增
    //convert:如果转化后的词条值还不如直接堆转化后的属性，那么还原
    //extrarate:1、base_skillrate=0 默认有效
    //          2、base_skillrate!=0 如果攻击词条（一定有效）的收益更大，那么还原
    if (w_point->name == "磐岩结绿")
    {
        if ((data_list[str2index_full("生命值")]->value_per_entry * 0.012 * (0.75 + w_point->level * 0.25) * base_life / base_atk) < data_list[str2index_full("攻击力")]->value_per_entry)
            data_list[str2index_full("生命值")]->useful = attack_config->useful_attributes[str2index_full("生命值")];
    }
    else if (w_point->name == "裁叶萃光")
    {
        if (base_skillrate != 0)
            if ((data_list[str2index_full("元素精通")]->value_per_entry * 1.2 * (0.75 + w_point->level * 0.25) / (base_skillrate * base_atk)) < data_list[str2index_full("攻击力")]->value_per_entry)
                data_list[str2index_full("元素精通")]->useful = attack_config->useful_attributes[str2index_full("元素精通")];
    }
    else if (w_point->name == "圣显之钥")
    {
        if (attack_config->args->sword_shengxian_level >= 3)
        {
            if ((data_list[str2index_full("生命值")]->value_per_entry * 0.0056 * (0.75 + w_point->level * 0.25) * base_life) < data_list[str2index_full("元素精通")]->value_per_entry)
                data_list[str2index_full("生命值")]->useful = attack_config->useful_attributes[str2index_full("生命值")];
        }
        else if (attack_config->args->sword_shengxian_level == 2)
        {
            if ((data_list[str2index_full("生命值")]->value_per_entry * 0.0024 * (0.75 + w_point->level * 0.25) * base_life) < data_list[str2index_full("元素精通")]->value_per_entry)
                data_list[str2index_full("生命值")]->useful = attack_config->useful_attributes[str2index_full("生命值")];
        }
        else if (attack_config->args->sword_shengxian_level == 1)
        {
            if ((data_list[str2index_full("生命值")]->value_per_entry * 0.0012 * (0.75 + w_point->level * 0.25) * base_life) < data_list[str2index_full("元素精通")]->value_per_entry)
                data_list[str2index_full("生命值")]->useful = attack_config->useful_attributes[str2index_full("生命值")];
        }
    }
    else if (w_point->name == "辰砂之纺锤")
    {
        if (base_skillrate != 0)
            if ((data_list[str2index_full("防御力")]->value_per_entry * 0.4 * (0.75 + w_point->level * 0.25) * base_def / (base_skillrate * base_atk)) < data_list[str2index_full("攻击力")]->value_per_entry)
                data_list[str2index_full("防御力")]->useful = attack_config->useful_attributes[str2index_full("防御力")];
    }
        //TODO:NEW
    else if (w_point->name == "海渊终曲")
    {
        if ((data_list[str2index_full("生命值")]->value_per_entry * 0.25 * 0.024 * (0.75 + w_point->level * 0.25) * base_life) < data_list[str2index_full("攻击力")]->value_per_entry * base_atk)
            data_list[str2index_full("生命值")]->useful = attack_config->useful_attributes[str2index_full("生命值")];
    }
    else if (w_point->name == "西福斯的月光")
    {
        if ((data_list[str2index_full("元素精通")]->value_per_entry * 0.00036 * (0.75 + w_point->level * 0.25)) < data_list[str2index_full("元素充能效率")]->value_per_entry)
            data_list[str2index_full("元素精通")]->useful = attack_config->useful_attributes[str2index_full("元素精通")];
    }
    else if (w_point->name == "不灭月华")
    {
        if (base_skillrate != 0)
            if ((data_list[str2index_full("生命值")]->value_per_entry * (0.005 + w_point->level * 0.005) * base_life / (base_skillrate * base_atk)) < data_list[str2index_full("攻击力")]->value_per_entry)
                data_list[str2index_full("生命值")]->useful = attack_config->useful_attributes[str2index_full("生命值")];
    }
    else if (w_point->name == "流浪的晚星")
    {
        if ((data_list[str2index_full("元素精通")]->value_per_entry * 0.24 * (0.75 + w_point->level * 0.25) / base_atk) < data_list[str2index_full("攻击力")]->value_per_entry)
            data_list[str2index_full("元素精通")]->useful = attack_config->useful_attributes[str2index_full("元素精通")];
    }
    else if (w_point->name == "猎人之径")
    {
        if (base_skillrate != 0)
            if ((data_list[str2index_full("元素精通")]->value_per_entry * 1.6 * (0.75 + w_point->level * 0.25) / (base_skillrate * base_atk)) < data_list[str2index_full("攻击力")]->value_per_entry)
                data_list[str2index_full("元素精通")]->useful = attack_config->useful_attributes[str2index_full("元素精通")];
    }
    else if (w_point->name == "赤角石溃杵")
    {
        if (base_skillrate != 0)
            if ((data_list[str2index_full("防御力")]->value_per_entry * 0.4 * (0.75 + w_point->level * 0.25) * base_def / (base_skillrate * base_atk)) < data_list[str2index_full("攻击力")]->value_per_entry)
                data_list[str2index_full("防御力")]->useful = attack_config->useful_attributes[str2index_full("防御力")];
    }
    else if (w_point->name == "玛海菈的水色")
    {
        if ((data_list[str2index_full("元素精通")]->value_per_entry * 0.24 * (0.75 + w_point->level * 0.25) / base_atk) < data_list[str2index_full("攻击力")]->value_per_entry)
            data_list[str2index_full("元素精通")]->useful = attack_config->useful_attributes[str2index_full("元素精通")];
    }
    else if (w_point->name == "护摩之杖")
    {
        if (attack_config->args->polearm_humo_halflife)
        {
            if ((data_list[str2index_full("生命值")]->value_per_entry * (0.008 * (0.75 + w_point->level * 0.25) + (0.008 + w_point->level * 0.002)) * base_life / base_atk) < data_list[str2index_full("攻击力")]->value_per_entry)
                data_list[str2index_full("生命值")]->useful = attack_config->useful_attributes[str2index_full("生命值")];
        }
        else
        {
            if ((data_list[str2index_full("生命值")]->value_per_entry * 0.008 * (0.75 + w_point->level * 0.25) * base_life / base_atk) < data_list[str2index_full("攻击力")]->value_per_entry)
                data_list[str2index_full("生命值")]->useful = attack_config->useful_attributes[str2index_full("生命值")];
        }
    }
    else if (w_point->name == "薙草之稻光")
    {
        if ((data_list[str2index_full("元素充能效率")]->value_per_entry * 0.28 * (0.75 + w_point->level * 0.25)) < data_list[str2index_full("攻击力")]->value_per_entry)
            data_list[str2index_full("元素充能效率")]->useful = attack_config->useful_attributes[str2index_full("元素充能效率")];
    }
    else if (w_point->name == "赤沙之杖")
    {
        if (attack_config->args->polearm_chisha_level >= 3)
        {
            if ((data_list[str2index_full("元素精通")]->value_per_entry * 1.36 * (0.75 + w_point->level * 0.25) / base_atk) < data_list[str2index_full("攻击力")]->value_per_entry)
                data_list[str2index_full("元素精通")]->useful = attack_config->useful_attributes[str2index_full("元素精通")];
        }
        else if (attack_config->args->polearm_chisha_level == 2)
        {
            if ((data_list[str2index_full("元素精通")]->value_per_entry * 1.08 * (0.75 + w_point->level * 0.25) / base_atk) < data_list[str2index_full("攻击力")]->value_per_entry)
                data_list[str2index_full("元素精通")]->useful = attack_config->useful_attributes[str2index_full("元素精通")];
        }
        else if (attack_config->args->polearm_chisha_level == 1)
        {
            if ((data_list[str2index_full("元素精通")]->value_per_entry * 0.8 * (0.75 + w_point->level * 0.25) / base_atk) < data_list[str2index_full("攻击力")]->value_per_entry)
                data_list[str2index_full("元素精通")]->useful = attack_config->useful_attributes[str2index_full("元素精通")];
        }
        else
        {
            if ((data_list[str2index_full("元素精通")]->value_per_entry * 0.52 * (0.75 + w_point->level * 0.25) / base_atk) < data_list[str2index_full("攻击力")]->value_per_entry)
                data_list[str2index_full("元素精通")]->useful = attack_config->useful_attributes[str2index_full("元素精通")];
        }
    }

    //artifact
    //绝缘肯定有效（增伤效益认为无穷）
    if (suit1->name == "绝缘之旗印" && suit2->name == "绝缘之旗印" && attack_config->condition->attack_way == "Q")
        data_list[str2index_full("元素充能效率")]->useful = true;
}

//build new character(needed)||build new weapon(all)||build new artifact(all)
void Deployment::get_team_data()
{
    //默认队友5星0命，技能均为9级，4星6命，技能均为12级

    //weapon
    if ((team_config->team_weapon_artifact.find("终末嗟叹之诗") != string::npos || team_config->team_weapon_artifact.find("苍古自由之誓") != string::npos || team_config->team_weapon_artifact.find("松籁响起之时") != string::npos)
        && (w_point->name != "终末嗟叹之诗" && w_point->name != "苍古自由之誓" && w_point->name != "松籁响起之时"))
    {
        add_percentage("攻击力", 0.2, "team_大乐章");
    }
    if (team_config->team_weapon_artifact.find("终末嗟叹之诗") != string::npos && w_point->name != "终末嗟叹之诗")
    {
        add_percentage("元素精通", 100.0, "team_终末嗟叹之诗");
    }
    if (team_config->team_weapon_artifact.find("苍古自由之誓") != string::npos && w_point->name != "苍古自由之誓")
    {
        if (attack_config->condition->attack_way == "平A" || attack_config->condition->attack_way == "重A" || attack_config->condition->attack_way == "下落A")
            add_percentage("伤害加成", 0.16, "team_苍古自由之誓");
    }
    if (team_config->team_weapon_artifact.find("白辰之环") != string::npos && w_point->name != "白辰之环")
    {
        if ((attack_config->react_type.find("超载") != string::npos && (attack_config->condition->ele_type == "雷" || attack_config->condition->ele_type == "火")) ||
            (attack_config->react_type.find("感电") != string::npos && (attack_config->condition->ele_type == "雷" || attack_config->condition->ele_type == "水")) ||
            (attack_config->react_type.find("激化") != string::npos && (attack_config->condition->ele_type == "雷" || attack_config->condition->ele_type == "草")) ||
            (attack_config->react_type.find("超导") != string::npos && (attack_config->condition->ele_type == "雷" || attack_config->condition->ele_type == "冰")) ||
            (attack_config->react_type.find("扩散") != string::npos && team_config->ele_allow_spread.find("雷") != string::npos && (attack_config->condition->ele_type == "雷" || attack_config->condition->ele_type == "风")) ||
            (attack_config->react_type.find("结晶") != string::npos && team_config->ele_allow_spread.find("雷") != string::npos && (attack_config->condition->ele_type == "雷" || attack_config->condition->ele_type == "岩")))
            add_percentage("伤害加成", 0.2, "team_白辰之环");
    }
    if (team_config->team_weapon_artifact.find("讨龙英杰谭") != string::npos)
    {
        add_percentage("攻击力", 0.48, "team_讨龙");
    }
    if ((team_config->team_weapon_artifact.find("原木刀") != string::npos || team_config->team_weapon_artifact.find("森林王器") != string::npos) && (w_point->name != "原木刀" && w_point->name != "森林王器"))
    {
        add_percentage("元素精通", 120, "team_原木刀/森林王器");
    }
    if (team_config->team_weapon_artifact.find("贯月矢") != string::npos && w_point->name != "贯月矢")
    {
        add_percentage("攻击力", 0.32, "team_贯月矢");
    }
    if (team_config->team_weapon_artifact.find("千夜浮梦") != string::npos)
    {
        add_percentage("元素精通", 40.0, "team_千夜浮梦");
    }
    //转化类
    if (team_config->team_weapon_artifact.find("圣显之钥") != string::npos && w_point->name != "圣显之钥")
    {
        add_converted_percentage("元素精通", 100.0, "team_圣显之钥");//50000HP
    }
    if (team_config->team_weapon_artifact.find("西福斯的月光") != string::npos)
    {
        add_converted_percentage("元素充能效率", 0.054, "team_西福斯的月光");//500EM
    }
    if (team_config->team_weapon_artifact.find("流浪的晚星") != string::npos)
    {
        add_converted_percentage("攻击力", 36.0 / base_atk, "team_流浪的晚星");//500EM
    }
    if (team_config->team_weapon_artifact.find("玛海菈的水色") != string::npos)
    {
        add_converted_percentage("攻击力", 36.0 / base_atk, "team_玛海菈的水色");//500EM
    }

    //artifact
    if (team_config->team_weapon_artifact.find("悠古的磐岩") != string::npos && (suit1->name != "悠古的磐岩" || suit2->name != "悠古的磐岩"))
    {
        if (attack_config->condition->ele_type == "水" || attack_config->condition->ele_type == "火" || attack_config->condition->ele_type == "雷" || attack_config->condition->ele_type == "冰")
            if (team_config->ele_allow_spread.find(attack_config->condition->ele_type) != string::npos)//扩散与元素附着
                add_percentage("伤害加成", 0.35, "team_悠古的磐岩");
    }
    if (team_config->team_weapon_artifact.find("昔日宗室之仪") != string::npos && (suit1->name != "昔日宗室之仪" || suit2->name != "昔日宗室之仪"))
    {
        add_percentage("攻击力", 0.2, "team_昔日宗室之仪");
    }
    if (team_config->team_weapon_artifact.find("翠绿之影") != string::npos && (suit1->name != "翠绿之影" || suit2->name != "翠绿之影"))
    {
        if (attack_config->condition->ele_type == "水" || attack_config->condition->ele_type == "火" || attack_config->condition->ele_type == "雷" || attack_config->condition->ele_type == "冰")
            if (team_config->ele_allow_spread.find(attack_config->condition->ele_type) != string::npos)//扩散与元素附着
                add_percentage("抗性削弱", 0.4, "team_翠绿之影");
    }
    if (team_config->team_weapon_artifact.find("千岩牢固") != string::npos && (suit1->name != "千岩牢固" || suit2->name != "千岩牢固"))
    {
        add_percentage("攻击力", 0.2, "team_千岩牢固");
        add_percentage("护盾强效", 0.3, "team_千岩牢固");
    }
    if (team_config->team_weapon_artifact.find("深林的记忆") != string::npos && (suit1->name != "深林的记忆" || suit2->name != "深林的记忆"))
    {
        if (attack_config->condition->ele_type == "草")
            add_percentage("抗性削弱", 0.3, "team_深林的记忆");
    }
}

//build new character(needed)||build new weapon(all)||build new artifact(all) 有关充能的转化类属性要考虑
void Deployment::satisfy_recharge_requirement()
{
    //能量回复值 = 微粒数 * 系数 * 实时的元素充能效率
    double front = 1;
    double back = 0.6;
    double same = 3;
    double white = 2;
    double diff = 1;
    double monster_drop = 10;

    double Q_energy_modify = c_point->Q_energy;
    double energy = monster_drop;
    double converted_recharge = 0;

    //"天目影打刀" 12/E 不吃充能
    //"西风剑" 3*2/6s
    //"祭礼剑" 1E/16s
    //"西福斯的月光" 充能效率 mastery * 0.00036 * (0.75 + w_point->level * 0.25)

    //"不灭月华" 0.6/A Q后12s内 不吃充能
    //"碧落之珑" 4/Q 4/2.5s
    //"试作金珀" 3*6/Q 不吃充能
    //"西风秘典" 3*2/6s
    //"祭礼残章" 1E/16s

    //"祭礼弓" 1E/16s
    //"西风猎弓" 3*2/6s

    //"祭礼大剑" 1E/16s
    //"桂木斩长正" 3*5-3/E 不吃充能
    //"西风大剑" 3*2/6s

    //"西风长枪" 3*2/6s
    //"喜多院十文字" 3*5-3/E 不吃充能
    //"公义的酬报" 8/10s 不吃充能

    if (c_point->name == "胡桃")
    {
        //Q 60 E 5f 2E/Q
        energy += team_config->E_energy_times_data[0].second * c_point->E_energy * front * same;

        if (w_point->name == "西风长枪") energy += 3 * front * white;
        else if (w_point->name == "喜多院十文字") Q_energy_modify -= 12;
            //TODO:NEW
        else if (w_point->name == "公义的酬报" && (c_point->heal_sustain || team_config->teammate_1->heal_sustain || team_config->teammate_2->heal_sustain || team_config->teammate_3->heal_sustain)) Q_energy_modify -= 8 * (0.75 + w_point->level * 0.25);
    }
    else if (c_point->name == "艾尔海森")
    {
        //Q 70 E 5f 1E/Q
        energy += team_config->E_energy_times_data[0].second * c_point->E_energy * front * same;

        if (w_point->name == "西风剑") energy += 3 * front * white;
        else if (w_point->name == "祭礼剑") energy += 0;
        else if (w_point->name == "天目影打刀") Q_energy_modify -= 12;
        else if (w_point->name == "西福斯的月光") converted_recharge += data_list[str2index_full("元素精通")]->percentage * 0.00036 * (0.75 + w_point->level * 0.25);
    }
    else if (c_point->name == "雷电将军")
    {
        //Q 90-24=66 E 10b 1E/Q
        Q_energy_modify -= 24;
        energy += team_config->E_energy_times_data[0].second * c_point->E_energy * back * same;

        if (w_point->name == "西风长枪") energy += 3 * front * white;
        else if (w_point->name == "喜多院十文字") Q_energy_modify -= 12;
            //TODO:NEW
        else if (w_point->name == "公义的酬报" && (c_point->heal_sustain || team_config->teammate_1->heal_sustain || team_config->teammate_2->heal_sustain || team_config->teammate_3->heal_sustain)) Q_energy_modify -= 8 * (0.75 + w_point->level * 0.25);

        energy = min(energy, Q_energy_modify / 2.4);
    }
    else if (c_point->name == "神里绫华")
    {
        //Q 80 E 4.5f 2E/Q
        energy += team_config->E_energy_times_data[0].second * c_point->E_energy * front * same;

        if (w_point->name == "西风剑") energy += 3 * front * white;
        else if (w_point->name == "祭礼剑") energy += c_point->E_energy * front * same;
        else if (w_point->name == "天目影打刀") Q_energy_modify -= team_config->E_energy_times_data[0].second * 12;
        else if (w_point->name == "西福斯的月光") converted_recharge += data_list[str2index_full("元素精通")]->percentage * 0.00036 * (0.75 + w_point->level * 0.25);
    }
    else if (c_point->name == "甘雨")
    {
        //Q 60 E 2f+2b 2E/Q
        energy += team_config->E_energy_times_data[0].second * c_point->E_energy * (front / 2 + back / 2) * same;

        if (w_point->name == "西风猎弓") energy += 3 * front * white;
        else if (w_point->name == "祭礼弓") energy += c_point->E_energy * (front / 2 + back / 2) * same;
    }
    else if (c_point->name == "纳西妲")
    {
        //Q 50 E 6b 2E/Q
        energy += team_config->E_energy_times_data[0].second * c_point->E_energy * back * same;

        if (w_point->name == "西风秘典") energy += 3 * front * white;
        else if (w_point->name == "祭礼残章") energy += 0;
        else if (w_point->name == "试作金珀") Q_energy_modify -= 18;
        else if (w_point->name == "不灭月华") Q_energy_modify -= 0;
        else if (w_point->name == "碧落之珑") Q_energy_modify -= 4.5;
    }
    else if (c_point->name == "夜兰")
    {
        //Q 70 E 4f 1E/Q
        energy += team_config->E_energy_times_data[0].second * c_point->E_energy * front * same;

        if (w_point->name == "西风猎弓") energy += 3 * front * white;
        else if (w_point->name == "祭礼弓") energy += c_point->E_energy * front * same;
    }
    else if (c_point->name == "八重神子")
    {
        //Q 90-24=66 E 5b 1E/Q
        Q_energy_modify -= 24;
        energy += team_config->E_energy_times_data[0].second * c_point->E_energy * back * same;

        if (w_point->name == "西风秘典") energy += 3 * front * white;
        else if (w_point->name == "祭礼残章") energy += 0;
        else if (w_point->name == "试作金珀") Q_energy_modify -= 18;
        else if (w_point->name == "不灭月华") Q_energy_modify -= 0;
        else if (w_point->name == "碧落之珑") Q_energy_modify -= 4.5;
    }
    else if (c_point->name == "香菱")
    {
        //Q 80 E 4b 1E/Q
        energy += team_config->E_energy_times_data[0].second * c_point->E_energy * back * same;

        if (w_point->name == "西风长枪") energy += 3 * front * white;
        else if (w_point->name == "喜多院十文字") Q_energy_modify -= 12;
            //TODO:NEW
        else if (w_point->name == "公义的酬报" && (c_point->heal_sustain || team_config->teammate_1->heal_sustain || team_config->teammate_2->heal_sustain || team_config->teammate_3->heal_sustain)) Q_energy_modify -= 8 * (0.75 + w_point->level * 0.25);
    }
    else if (c_point->name == "行秋")
    {
        //Q 80-3*5=65 E 5f 1E/Q
        Q_energy_modify -= 12;
        energy += team_config->E_energy_times_data[0].second * c_point->E_energy * front * same;

        if (w_point->name == "西风剑") energy += 3 * front * white;
        else if (w_point->name == "祭礼剑") energy += c_point->E_energy * front * same;
        else if (w_point->name == "天目影打刀") Q_energy_modify -= team_config->E_energy_times_data[0].second * 12;
        else if (w_point->name == "西福斯的月光") converted_recharge += data_list[str2index_full("元素精通")]->percentage * 0.00036 * (0.75 + w_point->level * 0.25);
    }
    else energy = Q_energy_modify;

    min_recharge_num = max(0, (int) ((Q_energy_modify / energy - data_list[str2index_full("元素充能效率")]->percentage - data_list[str2index_full("元素充能效率")]->converted_percentage - converted_recharge) / data_list[str2index_full("元素充能效率")]->value_per_entry));
}

//build new character(needed)||build new weapon(all)||build new artifact(all)
void Deployment::get_convert_value(double &life, double &atk, double &def, double &mastery, double &recharge, double &critrate, double &critdam, double &damplus)
{
    //先计算转化，最后再执行加成，不加到面板上的转化可以吃converted_percentage
    double life_add = 0, atk_add = 0, def_add = 0, mastery_add = 0, recharge_add = 0, critrate_add = 0, critdam_add = 0, damplus_add = 0;
    //weapon
    if (w_point->name == "磐岩结绿")//生命->攻击
        atk_add += life * 0.012 * (0.75 + w_point->level * 0.25) * base_life / base_atk;//生命->攻击
    else if (w_point->name == "圣显之钥")//生命->精通
    {
        if (attack_config->args->sword_shengxian_level >= 3)
        {
            mastery_add += life * 0.0012 * 3 * (0.75 + w_point->level * 0.25) * base_life;//生命->精通
            mastery_add += life * 0.002 * (0.75 + w_point->level * 0.25) * base_life;//生命->精通
        }
        else if (attack_config->args->sword_shengxian_level == 2)
        {
            mastery_add += life * 0.0012 * 2 * (0.75 + w_point->level * 0.25) * base_life;//生命->精通
        }
        else if (attack_config->args->sword_shengxian_level == 1)
        {
            mastery_add += life * 0.0012 * (0.75 + w_point->level * 0.25) * base_life;//生命->精通
        }
    }
        //TODO:NEW
    else if (w_point->name == "海渊终曲")//生命->攻击
    {
        if (c_point->heal_sustain || team_config->teammate_1->heal_sustain || team_config->teammate_2->heal_sustain || team_config->teammate_3->heal_sustain)
            atk_add += min(life * 0.25 * 0.024 * (0.75 + w_point->level * 0.25) * base_life, 150 * (0.75 + w_point->level * 0.25)) / base_atk;//生命->攻击
    }
    else if (w_point->name == "西福斯的月光")//精通->充能
        recharge_add += mastery * 0.00036 * (0.75 + w_point->level * 0.25);//精通->充能
    else if (w_point->name == "碧落之珑" && attack_config->args->catalyst_biluo_enable)//生命->增伤
        damplus_add += min(life * (0.001 + w_point->level * 0.002) * base_life / 1000, 0.04 + w_point->level * 0.08);//生命->增伤
        //TODO:NEW
    else if (w_point->name == "纯水流华")//生命->增伤
    {
        if (c_point->heal_sustain || team_config->teammate_1->heal_sustain || team_config->teammate_2->heal_sustain || team_config->teammate_3->heal_sustain)
            damplus_add += min(life * 0.24 * 0.02 * (0.75 + w_point->level * 0.25) * base_life / 1000, 0.12 * (0.75 + w_point->level * 0.25));//生命->增伤
    }
    else if (w_point->name == "流浪的晚星")//精通->攻击
        atk_add += mastery * 0.24 * (0.75 + w_point->level * 0.25) / base_atk;//精通->攻击
    else if (w_point->name == "玛海菈的水色")//精通->攻击
        atk_add += mastery * 0.24 * (0.75 + w_point->level * 0.25) / base_atk;//精通->攻击
    else if (w_point->name == "护摩之杖")//生命->攻击
    {
        atk_add += life * 0.008 * (0.75 + w_point->level * 0.25) * base_life / base_atk;//生命->攻击
        if (attack_config->args->polearm_humo_halflife)
            atk_add += life * (0.008 + w_point->level * 0.002) * base_life / base_atk;//生命->攻击
    }
    else if (w_point->name == "薙草之稻光")//充能->攻击
        atk_add += min((recharge - 1) * (0.75 + w_point->level * 0.25) * 0.28, (0.7 + w_point->level * 0.1));
    else if (w_point->name == "赤沙之杖")//精通->攻击
    {
        atk_add += mastery * 0.52 * (0.75 + w_point->level * 0.25) / base_atk;//精通->攻击
        if (attack_config->args->polearm_chisha_level >= 3)
            atk_add += mastery * 0.28 * 3 * (0.75 + w_point->level * 0.25) / base_atk;//精通->攻击
        else if (attack_config->args->polearm_chisha_level == 2)
            atk_add += mastery * 0.28 * 2 * (0.75 + w_point->level * 0.25) / base_atk;//精通->攻击
        else if (attack_config->args->polearm_chisha_level == 1)
            atk_add += mastery * 0.28 * (0.75 + w_point->level * 0.25) / base_atk;//精通->攻击
    }

    //artifact
    if (suit1->name == "绝缘之旗印" && suit2->name == "绝缘之旗印" && attack_config->condition->attack_way == "Q")//充能->增伤
        damplus_add += min(recharge * 0.25, 0.75);

    life += life_add;
    atk += atk_add;
    def += def_add;
    mastery += mastery_add;
    recharge += recharge_add;
    critrate += critrate_add;
    critdam += critdam_add;
    damplus += damplus_add;
}

//build new character(needed)||build new weapon(all)||build new artifact(all)
void Deployment::get_extra_rate_value(double life, double atk, double def, double mastery, double recharge, double critrate, double critdam, double damplus, double &extrarate)
{
    //artifact
    //weapon
    if (w_point->name == "裁叶萃光" && (attack_config->condition->attack_way == "平A" || attack_config->condition->attack_way == "E"))
        extrarate += 1.2 * (0.75 + w_point->level * 0.25) * mastery;
    else if (w_point->name == "辰砂之纺锤" && attack_config->condition->attack_way == "E")
        extrarate += 0.4 * (0.75 + w_point->level * 0.25) * def * base_def;
    else if (w_point->name == "不灭月华" && attack_config->condition->attack_way == "平A")
        extrarate += (0.005 + w_point->level * 0.005) * life * base_life;
    else if (w_point->name == "赤角石溃杵" && (attack_config->condition->attack_way == "平A" || attack_config->condition->attack_way == "重A"))
        extrarate += 0.4 * (0.75 + w_point->level * 0.25) * def * base_def;
    else if (w_point->name == "猎人之径" && attack_config->condition->attack_way == "重A")
        extrarate += 1.6 * (0.75 + w_point->level * 0.25) * mastery;
}

//build new character(needed)||build new weapon(all)||build new artifact(all)
void Deployment::get_react_value(double mastery, double &extrarate, double &growrate, double &extra_damage)
{
    //扩散（风+水火雷冰），结晶（岩+水火雷冰），绽放（草水+火雷），激化（草雷），燃烧（草火），蒸发（水火），融化（火冰），冻结（水冰），感电（雷水），超载（雷火），超导（雷冰）
    //默认抗性固定为0.1
    if (attack_config->react_type.find("no_add_damage") != string::npos) return;
    if (attack_config->react_type.find("扩散") != string::npos)
    {
        double extra_damplus = 0;
        if ((suit1->name == suit2->name) && (suit1->name == "翠绿之影")) extra_damplus += 0.6;
        if (team_config->teammate_all.find("莫娜") != string::npos && team_config->ele_allow_spread.find("水") != string::npos) extra_damplus += 0.15;
        extra_damage += 1.2 * 723.4 * (1.0 + (16.0 * mastery) / (mastery + 2000.0) + extra_damplus);
        //1.2 * 723.4 * (1.0 + (16.0 * mastery) / (mastery + 2000.0) + 如雷/魔女等) * resistance;
        //元素伤，吃各元素抗
    }
    if (attack_config->react_type.find("结晶") != string::npos)
    {}
    if (attack_config->react_type.find("绽放") != string::npos)
    {
        //TODO:绽放
//        if (attack_config->react_type.find("烈绽放") != string::npos)
//        {
//            double extra_damplus = 0;
//            if ((suit1->name == suit2->name) && (suit1->name == "炽烈的炎之魔女")) extra_damplus += 0.4;
//            if ((suit1->name == suit2->name) && (suit1->name == "乐园遗落之花")) extra_damplus += 0.8;
//            //extra_damage += 6.0 * 723.4 * (1.0 + (16.0 * mastery) / (mastery + 2000.0) + extra_damplus);
//            extra_damage += 6.0 * 723.4 * (1.0 + (16.0 * mastery) / (mastery + 2000.0) + extra_damplus) * ((team_config->teammate_all.find("纳西妲") != string::npos) ? 1.2 : 1);
//            //6.0 * 723.4 * (1.0 + (16.0 * mastery) / (mastery + 2000.0) + 如雷/魔女等) * resistance;
//            //草伤，吃草抗
//        }
//        else if (attack_config->react_type.find("超绽放") != string::npos)
//        {
//            double extra_damplus = 0;
//            if ((suit1->name == suit2->name) && (suit1->name == "如雷的盛怒")) extra_damplus += 0.4;
//            if ((suit1->name == suit2->name) && (suit1->name == "乐园遗落之花")) extra_damplus += 0.8;
//            //extra_damage += 6.0 * 723.4 * (1.0 + (16.0 * mastery) / (mastery + 2000.0) + extra_damplus);
//            extra_damage += 6.0 * 723.4 * (1.0 + (16.0 * mastery) / (mastery + 2000.0) + extra_damplus) * ((team_config->teammate_all.find("纳西妲") != string::npos) ? 1.2 : 1);
//            //6.0 * 723.4 * (1.0 + (16.0 * mastery) / (mastery + 2000.0) + 如雷/魔女等) * resistance;
//            //草伤，吃草抗
//        }
//        else
//        {
//            double extra_damplus = 0;
//            if ((suit1->name == suit2->name) && (suit1->name == "乐园遗落之花")) extra_damplus += 0.8;
//            //extra_damage += 4.0 * 723.4 * (1.0 + (16.0 * mastery) / (mastery + 2000.0) + extra_damplus);
//            extra_damage += 4.0 * 723.4 * (1.0 + (16.0 * mastery) / (mastery + 2000.0) + extra_damplus) * ((team_config->teammate_all.find("纳西妲") != string::npos) ? 1.2 : 1);
//            //4.0 * 723.4 * (1.0 + (16.0 * mastery) / (mastery + 2000.0) + 如雷/魔女等) * resistance;
//            //草伤，吃草抗
//        }
    }
    if (attack_config->react_type.find("激化") != string::npos)
    {
        double extra_damplus = 0;
        if (this->attack_config->condition->ele_type == "草") extrarate += 1447.0 * 1.25 * (1.0 + (5.0 * mastery) / (mastery + 1200.0) + extra_damplus);
        else if (this->attack_config->condition->ele_type == "雷")
        {
            if ((suit1->name == suit2->name) && (suit1->name == "如雷的盛怒")) extra_damplus += 0.2;
            extrarate += 1447.0 * 1.15 * (1.0 + (5.0 * mastery) / (mastery + 1200.0) + extra_damplus);
        }
    }
    if (attack_config->react_type.find("燃烧") != string::npos)
    {
        double extra_damplus = 0;
        if ((suit1->name == suit2->name) && (suit1->name == "炽烈的炎之魔女")) extra_damplus += 0.4;
        //extra_damage += 4.0 * 723.4 * (1.0 + (16.0 * mastery) / (mastery + 2000.0) + extra_damplus);
        extra_damage += 4.0 * 723.4 * (1.0 + (16.0 * mastery) / (mastery + 2000.0) + extra_damplus) * ((team_config->teammate_all.find("纳西妲") != string::npos) ? 1.2 : 1);
        //0.5 * 723.4 * (1.0 + (16.0 * mastery) / (mastery + 2000.0) + 如雷/魔女等) * resistance;
        //火伤，吃火抗，8段伤害
    }
    if (attack_config->react_type.find("蒸发") != string::npos)
    {
        growrate = 1.0 + (25.0 * mastery) / (9.0 * (mastery + 1401.0));
        if ((suit1->name == suit2->name) && (suit1->name == "炽烈的炎之魔女")) growrate += 0.15;
        if (team_config->teammate_all.find("莫娜") != string::npos) growrate += 0.15;
        if (attack_config->condition->ele_type == "火") growrate *= 1.5;
        else if (attack_config->condition->ele_type == "水") growrate *= 2.0;
    }
    if (attack_config->react_type.find("融化") != string::npos)
    {
        growrate = 1.0 + (25.0 * mastery) / (9.0 * (mastery + 1401.0));
        if ((suit1->name == suit2->name) && (suit1->name == "炽烈的炎之魔女")) growrate += 0.15;
        if (attack_config->condition->ele_type == "火") growrate *= 2.0;
        else if (attack_config->condition->ele_type == "冰") growrate *= 1.5;
    }
    if (attack_config->react_type.find("冻结") != string::npos)
    {}
    //碎冰 //3.0 * 723.4 * (1.0 + (16.0 * mastery) / (mastery + 2000.0) + 如雷/魔女等) * resistance;
    //物理伤，吃物理抗
    if (attack_config->react_type.find("感电") != string::npos)
    {
        double extra_damplus = 0;
        if ((suit1->name == suit2->name) && (suit1->name == "如雷的盛怒")) extra_damplus += 0.4;
        if (team_config->teammate_all.find("莫娜") != string::npos) extra_damplus += 0.15;
        extra_damage += 2.4 * 723.4 * (1.0 + (16.0 * mastery) / (mastery + 2000.0) + extra_damplus);
        //2.4 * 723.4 * (1.0 + (16.0 * mastery) / (mastery + 2000.0) + 如雷/魔女等) * resistance;
        //雷伤，吃雷抗
    }
    if (attack_config->react_type.find("超载") != string::npos)
    {
        double extra_damplus = 0;
        if ((suit1->name == suit2->name) && (suit1->name == "炽烈的炎之魔女")) extra_damplus += 0.4;
        if ((suit1->name == suit2->name) && (suit1->name == "如雷的盛怒")) extra_damplus += 0.4;
        extra_damage += 4.0 * 723.4 * (1.0 + (16.0 * mastery) / (mastery + 2000.0) + extra_damplus);
        //4.0 * 723.4 * (1.0 + (16.0 * mastery) / (mastery + 2000.0) + 如雷/魔女等) * resistance;
        //火伤，吃火抗
    }
    if (attack_config->react_type.find("超导") != string::npos)
    {
        double extra_damplus = 0;
        if ((suit1->name == suit2->name) && (suit1->name == "如雷的盛怒")) extra_damplus += 0.4;
        extra_damage += 1.0 * 723.4 * (1.0 + (16.0 * mastery) / (mastery + 2000.0) + extra_damplus);
        //1.0 * 723.4 * (1.0 + (16.0 * mastery) / (mastery + 2000.0) + 如雷/魔女等) * resistance;
        //冰伤，吃冰抗
    }
}