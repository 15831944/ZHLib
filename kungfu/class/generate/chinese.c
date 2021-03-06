// chan_cler 中国挑战者

inherit NPC;

private void from_wudang();
private void from_shaolin();
private void from_huashan();
private void from_emei();
private void from_gaibang();
private void from_taohua();
private void from_xiaoyao();
private void from_gumu();
private void from_quanzhen();
private void from_xueshan();
private void from_mingjiao();
private void from_lingjiu();
private void from_duan();
private void from_hu();
private void from_murong();
private void from_ouyang();

function *init_man_family = ({ 
(: from_wudang :), 
(: from_shaolin :), 
(: from_huashan :),
(: from_gaibang :),
(: from_taohua :), 
(: from_xiaoyao :), 
(: from_gumu :), 
(: from_quanzhen :), 
(: from_xueshan :), 
(: from_mingjiao :), 
(: from_duan :), 
(: from_hu :), 
(: from_murong :), 
(: from_ouyang :)
});

function *init_woman_family = ({ 
(: from_huashan :),
(: from_emei :), 
(: from_taohua :), 
(: from_xiaoyao :), 
(: from_gumu :), 
(: from_mingjiao :), 
(: from_lingjiu :), 
(: from_duan :), 
(: from_hu :), 
(: from_murong :), 
(: from_ouyang :)
});

void create()
{
        if (random(3) == 1)
                set("gender","女性");
        else
                set("gender", "男性");
        NPC_D->generate_cn_name(this_object());
        set("long", "一个人。\n");
        set("age", 20);
        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 20);

        // the follow 5 setting has no use      
        set("max_qi", 100);
        set("max_jing", 100);
        set("neili", 100);
        set("max_neili", 100);
        set("jiali", 100);

        set("combat_exp", 3000000);

        set_skill("force", 1);
        set_skill("dodge", 1);
        set_skill("parry", 1);

        setup();
        if (query("gender") == "男性")
                evaluate(init_man_family[random(sizeof(init_man_family))]);
        else
                evaluate(init_woman_family[random(sizeof(init_woman_family))]);
}

private void from_wudang()
{
        set("scale", 200);
        set("from", ({
                "据说此人出自武当，是武当派的高手，然而修武不修德，可惜啊可惜。",
                "听闻此人本是武当山下一农夫，耳渎目染，居然练就成非凡武功。",
                "据说此人乃武当弃徒，当年犯了杀戒逃至东洋，不想今日返回中原！",
        }));

        set_skill("taiji-shengong", 1);
        set_skill("parry", "taiji-jian");
        set_skill("tiyunzong", 1);
        set_skill("sword", 1);
        set_skill("taiji-jian", 1);
        set_skill("hand", 1);
        set_skill("paiyun-shou", 1);
        set_skill("unarmed", 1);
        set_skill("taiji-quan", 1);

        map_skill("force", "taiji-shengong");
        map_skill("dodge", "tiyunzong");
        map_skill("sword", "taiji-jian");
        map_skill("hand", "paiyun-shou");
        map_skill("unarmed", "taiji-quan");

        prepare_skill("hand", "paiyun-shou");
      prepare_skill("cuff", "taiji-quan");

        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: perform_action, "sword.lian" :),
                (: perform_action, "unarmed.zhen" :),
                (: exert_function, "recover" :),
        }) );

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/wudang/obj/greyrobe")->wear();
}

private void from_shaolin()
{
        set("scale", 150);
        set("from", ({
                "据说此人出自少林，是少林的俗家高手，可却没有半点慈悲之心，唉！",
                "听闻此人偷师于少林，练就了一身超凡脱俗的本领。",
                "据说此人乃少林的火工头陀，偷学武艺后被发现，竟然打死"
                + "达摩院长老出逃西域，想不到今日返回中原！",
                "据说此人当年犯了少林的戒律，被迫离寺，想不到隐居多年"
                + "以后居然重出江湖。"
        }));

        set_skill("hunyuan-yiqi", 1);
        set_skill("parry", "damo-jian");
        set_skill("shaolin-shenfa", 1);
        set_skill("sword", 1);
        set_skill("fumo-jian", 1);
        set_skill("finger", 1);
        set_skill("nianhua-zhi", 1);
        set_skill("strike", 1);
        set_skill("sanhua-zhang", 1);

        map_skill("force", "hunyuan-yiqi");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("sword", "fumo-jian");
        map_skill("finger", "nianhua-zhi");
        map_skill("strike", "sanhua-zhang");

        prepare_skill("finger", "nianhua-zhi");
        prepare_skill("strike", "sanhua-zhang");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "sword.sanjue" :),
                (: perform_action, "strike.san" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
                (: exert_function, "recover" :),
        }) );

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

 private void from_huashan()
{
        set("scale", 130);
        set("from", ({
                "据说此人出自华山，无恶不作，后来行迹忽然不见，想不到今日又出头。",
                "听闻此人本是华山长老，因剑气之争远投异地，不知何故返回中原！",
                "据说此人本是别派卧底到华山去的，偷学本领以后没回本派"
                + "反而觅地苦修，今日终于得出江湖。",
        }));

        set_skill("zixia-shengong", 1);
        set_skill("parry", 1);
        set_skill("feiyan-huixiang", 1);
        set_skill("sword", 1);
        set_skill("huashan-sword", 1);
        set_skill("cuff", 1);
        set_skill("poyu-quan", 1);
        set_skill("strike", 1);
        set_skill("hunyuan-zhang", 1);
        set_skill("force",1);
        set_skill("dodge",1);

        map_skill("force", "zixia-shengong");
        map_skill("dodge", "feiyan-huixiang");
        map_skill("sword", "huashan-sword");
        map_skill("cuff", "poyu-quan");
        map_skill("strike", "hunyuan-zhang");
        map_skill("parry", "huashan-sword");

        prepare_skill("cuff", "poyu-quan");
        prepare_skill("strike", "hunyuan-zhang");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "sword.jianzhang" :),
                (: perform_action, "cuff.leidong" :),
                (: perform_action, "cuff.poshi" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
                (: exert_function, "recover" :),
        }) );

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

private void from_ouyang()
{
        set("scale", 130);
        set("from", ({
                "据说此人原是当今武林宗师欧阳锋的兄长，不知何故失踪，今"
                + "日居然又出现了。",
                "听闻此人偷学了西域白驼山庄欧阳世家的武功，后来被欧阳"
                + "锋发现打成重伤，此人带伤而走，竟然活到今日，不可思议！",
        }));

        set_skill("hamagong", 1);
        set_skill("chanchu-bufa", 1);
        set_skill("staff", 1);
        set_skill("lingshe-zhangfa", 1);
        set_skill("cuff", 1);
        set_skill("lingshe-quan", 1);
        set_skill("finger", 1);
        set_skill("shedu-qiqiao", 1);

        map_skill("force", "hamagong");
        map_skill("parry", "lingshe-zhangfa");
        map_skill("dodge", "chanchu-bufa");
        map_skill("staff", "lingshe-zhangfa");
        map_skill("cuff", "lingshe-quan");
        map_skill("finger", "shedu-qiqiao");

        prepare_skill("cuff", "lingshe-quan");
        prepare_skill("finger", "shedu-qiqiao");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "staff.lingshe" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
                (: exert_function, "recover" :),
        }) );

        carry_object("/clone/weapon/gangzhang")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

private void from_gaibang()
{
        set("scale", 130);
        set("from", ({
                "据说此人原是丐帮长老，武功高绝，后因欺辱良家女子而被"
                + "逐出帮外，今日重现江湖必将又起血雨腥风。"
        }));

        set_skill("huntian-qigong", 1);
        set_skill("feiyan-zoubi", 1);
        set_skill("staff", 1);
        set_skill("dagou-bang", 1);
        set_skill("strike", 1);
        set_skill("dragon-strike", 1);

        map_skill("force", "huntian-qigong");
        map_skill("parry", "dagou-bang");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("staff", "dagou-bang");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
                (: exert_function, "recover" :),
        }) );

        carry_object("/clone/weapon/gangzhang")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

private void from_murong()
{
        set("scale", 130);
        set("from", ({
                "据说此人原是慕容家臣，武功高绝，后因出卖大燕国而被"
                + "通缉追杀，今日燕国覆亡，故又重出江湖。"
        }));

        set_skill("force", 1);
        set_skill("cuff", 1);
        set_skill("finger", 1);
        set_skill("sword", 1);
        set_skill("dodge", 1);
        set_skill("parry", 1);
        set_skill("zihui-xinfa", 1);
        set_skill("douzhuan-xingyi", 1);
        set_skill("beidou-xianzong", 1);
        set_skill("canhe-zhi", 1);
        set_skill("qixing-quan", 1);
        set_skill("murong-sword", 1);

        map_skill("force", "zihui-xinfa");
        map_skill("dodge", "beidou-xianzong");
        map_skill("cuff",  "qixing-quan");
        map_skill("parry", "douzhuan-xingyi");
        map_skill("finger", "canhe-zhi");
        map_skill("sword", "murong-sword");

        prepare_skill("finger", "canhe-zhi");
        prepare_skill("cuff", "qixing-quan");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
                (: exert_function, "recover" :),
        }) );

        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
}

 private void from_duan()
{
        set("scale", 130);
        set("from", ({
                "据说此人原是段氏家臣，武功高绝，后因偷学六脉神剑而被"
                + "处斩，不料让其逃脱，今又重出江湖。"
        }));

        set_skill("force", 1);                // 基本内功
        set_skill("kurong-changong", 1);      // 枯荣禅功
        set_skill("finger", 1);               // 基本指法
        set_skill("six-finger", 1);           // 六脉神剑
        set_skill("dodge", 1);                // 基本躲闪
        set_skill("tiannan-step", 1);         // 天南步法
        set_skill("parry", 1);                // 基本招架

        map_skill("force", "kurong-changong");
        map_skill("dodge", "tiannan-step");
        map_skill("parry", "six-finger");
        map_skill("finger", "six-finger");
        prepare_skill("finger","six-finger");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "kurong" :),
                (: exert_function, "recover" :),
        }) );

        carry_object("/clone/cloth/cloth")->wear();
}

private void from_emei()
{
        set("scale", 130);
        set("from", ({
                "据说此人原是峨嵋护法，武功高绝，后因情缘未绝"
                + "叛离佛门，今又重出江湖，却是心性大变。"
        }));

        set_skill("force", 1);
        set_skill("dodge", 1);
        set_skill("finger", 1);
        set_skill("parry", 1);
        set_skill("strike", 1);
        set_skill("sword", 1);
        set_skill("jinding-zhang", 1);
        set_skill("tiangang-zhi", 1);
        set_skill("huifeng-jian", 1);
        set_skill("zhutian-bu", 1);
        set_skill("linji-zhuang", 1);

        map_skill("force","linji-zhuang");
        map_skill("finger","tiangang-zhi");
        map_skill("dodge","zhutian-bu");
        map_skill("strike","jinding-zhang");
        map_skill("sword","huifeng-jian");
        map_skill("parry","huifeng-jian");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: exert_function, "tiandi" :),
                (: exert_function, "daxiao" :),
                (: exert_function, "fengyun" :),
        }) );

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

private void from_hu()
{
        set("scale", 130);
        set("from", ({
                "据说此人原是关外胡家豪杰，武功高绝，后因被人污蔑"
                + "杀人越货，性格大变，杀人如麻。"
        }));

    set_skill("force", 1);            // 基本内功
    set_skill("lengyue-shengong", 1); // 冷月神功
    set_skill("blade", 1);            // 基本刀法
    set_skill("hujia-daofa", 1);      // 胡家刀法
    set_skill("dodge", 1);            // 基本躲闪
    set_skill("taxue-wuhen", 1);      // 踏雪无痕
    set_skill("parry", 1);            // 基本招架
    set_skill("strike", 1);           // 基本掌法
    set_skill("tianchang-zhang", 1);  // 天长掌法
    set_skill("cuff", 1);             // 基本拳法
    set_skill("hujia-quan", 1);       // 胡家拳法

    map_skill("force", "lengyue-shengong");
    map_skill("blade", "hujia-daofa");
    map_skill("dodge", "taxue-wuhen");
    map_skill("parry", "hujia-daofa");
    map_skill("strike", "tianchang-zhang");
    map_skill("cuff", "hujia-quan");

    prepare_skill("strike", "tianchang-zhang");
    prepare_skill("cuff",   "hujia-quan");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "freeze" :),
                (: exert_function, "recover" :),
        }) );

    carry_object("/clone/weapon/blade")->wield();
    carry_object("/clone/cloth/cloth")->wear();
}

private void from_quanzhen()
{
        set("scale", 130);
        set("from", ({
                "据说此人原是全真元老，武功高绝，后因不耐道家"
                + "清修之苦，叛离道家，做恶江湖。"
        }));

        set_skill("force", 1);
        set_skill("xiantian-gong", 1);
        set_skill("sword", 1);
        set_skill("quanzhen-jian",1);
        set_skill("dodge", 1);
        set_skill("jinyan-gong", 1);
        set_skill("parry", 1);
        set_skill("strike", 1);
        set_skill("haotian-zhang", 1);
        set_skill("finger",1);
        set_skill("zhongnan-zhi", 1);

        map_skill("force", "xiantian-gong");
        map_skill("sword", "quanzhen-jian");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "quanzhen-jian");
        map_skill("finger","zhongnan-zhi");
        map_skill("strike", "haotian-zhang");

        prepare_skill("finger","zhongnan-zhi");
        prepare_skill("strike","haotian-zhang");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: exert_function, "chunyang" :),
                (: exert_function, "recover" :),
                (: exert_function, "recover" :),
        }) );

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/wudang/obj/greyrobe")->wear();
}

private void from_xueshan()
{
        set("scale", 130);
        set("from", ({
                "据说此人原是雪山高僧，武功高绝，后因破了色戒"
                + "被逐出师门，今日又重现江湖，复多了一重杀性。"
        }));

        set_skill("force", 1);
        set_skill("longxiang", 1);
        set_skill("dodge", 1);
        set_skill("shenkong-xing", 1);
        set_skill("parry", 1);
        set_skill("hammer", 1);
        set_skill("riyue-lun", 1);
        set_skill("strike",1);
        set_skill("huoyan-dao",1);

        map_skill("force", "longxiang");
        map_skill("dodge", "shenkong-xing");
        map_skill("parry", "riyue-lun");
        map_skill("hammer", "riyue-lun");
        map_skill("strike","huoyan-dao");

        prepare_skill("strike", "huoyan-dao");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: exert_function, "longxiang" :),
                (: exert_function, "shield" :),
                (: exert_function, "panlong" :),
        }) );

        carry_object("/clone/weapon/falun")->set_amount(4);
        carry_object("/clone/weapon/falun")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}
 private void from_xiaoyao()
{
        set("scale", 130);
        set("from", ({
                "据说此人原是逍遥派护法，武功高绝，后因违反师门"
                + "清规被逐出师门，今日又重现江湖，势必引起一场血雨腥风。"
        }));

        set_skill("force", 1);
        set_skill("xiaowuxiang", 1);
        set_skill("dodge", 1);
        set_skill("lingbo-weibu", 1);
        set_skill("liuyang-zhang", 1);
        set_skill("parry", 1);
        set_skill("zhemei-shou", 1);
        set_skill("hand", 1);
        set_skill("strike", 1);

        map_skill("force", "xiaowuxiang");
        map_skill("dodge", "lingbo-weibu");
        map_skill("hand", "zhemei-shou");
        map_skill("strike", "liuyang-zhang");
        map_skill("parry", "zhemei-shou");

        prepare_skill("hand","zhemei-shou");
        prepare_skill("strike","liuyang-zhang");

        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
                (: exert_function, "recover" :),
        }) );

        carry_object("/clone/misc/cloth")->wear();
}

private void from_gumu()
{
        set("scale", 130);
        set("from", ({
                "据说此人原是古墓派老奴，武功高绝，后因泄露"
                + "古墓派的秘密给驱除出古墓派，今日又重现江湖。"
        }));

        if (query("gender") == "女性")
        {
                set_skill("force", 1);
                set_skill("yunv-xinfa", 1);
                set_skill("sword", 1);
                set_skill("yunv-jian", 1);
                set_skill("quanzhen-jian", 1);
                set_skill("dodge", 1);
                set_skill("yunv-shenfa", 1);
                set_skill("parry", 1);
                set_skill("cuff",1);
                set_skill("meinv-quan", 1);

                map_skill("force", "yunv-xinfa");
                map_skill("sword", "yunv-jian");
                map_skill("dodge", "yunv-shenfa");
                map_skill("parry", "meinv-quan");
                map_skill("cuff", "meinv-quan");

                prepare_skill("cuff", "meinv-quan");

                set("chat_msg_combat", ({
                        (: exert_function, "powerup" :),
                        (: exert_function, "wang" :),
                        (: exert_function, "recover" :),
                }) );

                carry_object("/clone/weapon/changjian")->wield();
                carry_object("/clone/cloth/cloth")->wear();
        } else
        {
                set_skill("force", 1);
                set_skill("nuhai-kuangtao", 1);
                set_skill("sword", 1);
                set_skill("xuantie-jian", 1);
                set_skill("dodge", 1);
                set_skill("yunv-shenfa", 1);
                set_skill("parry", 1);
                set_skill("strike", 1);
                set_skill("sad-strike", 1);

                map_skill("force", "nuhai-kuangtao");
                map_skill("sword", "xuantie-jian");
                map_skill("dodge", "yunv-shenfa");
                map_skill("parry", "xuantie-jian");
                map_skill("strike", "sad-strike");

                prepare_skill("strike", "sad-strike");

                set("chat_msg_combat", ({
                        (: exert_function, "haixiao" :),
                        (: exert_function, "recover" :),
                        (: exert_function, "recover" :),
                }) );

                carry_object("/clone/weapon/gangjian")->wield();
                carry_object("/clone/cloth/cloth")->wear();
        }
}

private void from_taohua()
{
        set("scale", 130);
        set("from", ({
                "据说此人原是桃花岛弟子，武功高绝，后因偷练九阴真经"
                + "被黄药师逐出师门，今日又重现江湖，势必引起一场血雨腥风。"
        }));

        set_skill("force", 1);             // 基本内功
        set_skill("bibo-shengong", 1);     // 碧波神功
        set_skill("finger", 1);            // 基本指法
        set_skill("tanzhi-shentong", 1);   // 弹指神通
        set_skill("hand", 1);           // 基本手法
        set_skill("strike", 1);            // 基本拳脚
        set_skill("dodge", 1);             // 基本躲闪
        set_skill("parry", 1);             // 基本招架
        set_skill("sword", 1);             // 基本剑法
        set_skill("throwing", 1);          // 基本暗器
        set_skill("luoying-shenfa",1);
        set_skill("yuxiao-jian", 1);       // 玉箫剑法
        set_skill("lanhua-shou", 1);       // 兰花拂穴手
        set_skill("qimen-wuxing", 1);      // 奇门五行

        map_skill("force"  , "bibo-shengong");
        map_skill("finger" , "tanzhi-shentong");
        map_skill("hand"   , "lanhua-shou");
        map_skill("dodge"  , "luoying-shenfa");
        map_skill("parry"  , "yuxiao-jian");
        map_skill("sword"  , "yuxiao-jian");
        map_skill("throwing", "tanzhi-shentong");

        prepare_skill("finger" , "tanzhi-shentong");
        prepare_skill("hand"   , "lanhua-shou");

        set("chat_msg_combat", ({
                (: exert_function, "wuzhuan" :),
                (: exert_function, "recover" :),
                (: exert_function, "recover" :),
        }) );

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

private void from_lingjiu()
{
        set("scale", 130);
        set("from", ({
                "据说此人原是灵鹫宫长老，武功高绝，后因出卖天山童姥"
                + "被追杀，今日又重现江湖，势必引起一场血雨腥风。"
        }));

        set_skill("force", 1);
        set_skill("dodge", 1);
        set_skill("parry", 1);
        set_skill("hand", 1);
        set_skill("strike", 1);

        set_skill("zhemei-shou", 1);
        set_skill("liuyang-zhang", 1);
        set_skill("yueying-wubu", 1);
        set_skill("bahuang-gong", 1);

        map_skill("force", "bahuang-gong");
        map_skill("strike", "liuyang-zhang");
        map_skill("dodge", "yueying-wubu");
        map_skill("hand", "zhemei-shou");
        map_skill("parry", "liuyang-zhang");

        prepare_skill("hand","zhemei-shou");
        prepare_skill("strike","liuyang-zhang");        

        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
                (: exert_function, "recover" :),
        }) );

        carry_object("/clone/cloth/cloth")->wear();
}

private void from_mingjiao()
{
        set("scale", 130);
        set("from", ({
                "据说此人原是明教护法，武功高绝，后因偷练乾坤大挪移"
                + "走火入魔，今日又重现江湖，势必引起一场血雨腥风。"
        }));

    set_skill("force", 1);
    set_skill("cuff", 1);
    set_skill("dodge", 1);
    set_skill("parry", 1);
    set_skill("sword", 1);

    set_skill("shenghuo-xuanming", 1);
    set_skill("qiankun-danuoyi", 1);
    set_skill("lingxu-bu", 1);
    set_skill("shenghuo-ling", 1);
    set_skill("qishang-quan", 1);

    map_skill("force", "shenghuo-xuanming");
    map_skill("dodge", "lingxu-bu");
    map_skill("cuff", "qishang-quan");
    map_skill("sword","shenghuo-ling");
    map_skill("parry","qiankun-danuoyi");

    prepare_skill("cuff", "qishang-quan");

        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
                (: exert_function, "recover" :),
        }) );

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}
