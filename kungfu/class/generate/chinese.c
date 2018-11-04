// chan_cler �й���ս��

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
                set("gender","Ů��");
        else
                set("gender", "����");
        NPC_D->generate_cn_name(this_object());
        set("long", "һ���ˡ�\n");
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
        if (query("gender") == "����")
                evaluate(init_man_family[random(sizeof(init_man_family))]);
        else
                evaluate(init_woman_family[random(sizeof(init_woman_family))]);
}

private void from_wudang()
{
        set("scale", 200);
        set("from", ({
                "��˵���˳����䵱�����䵱�ɵĸ��֣�Ȼ�����䲻�޵£���ϧ����ϧ��",
                "���Ŵ��˱����䵱ɽ��һũ�򣬶���ĿȾ����Ȼ���ͳɷǷ��书��",
                "��˵�������䵱��ͽ�����그��ɱ���������󣬲�����շ�����ԭ��",
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
                "��˵���˳������֣������ֵ��׼Ҹ��֣���ȴû�а��ȱ�֮�ģ�����",
                "���Ŵ���͵ʦ�����֣�������һ�������׵ı��졣",
                "��˵���������ֵĻ�ͷ�ӣ�͵ѧ���պ󱻷��֣���Ȼ����"
                + "��ĦԺ���ϳ��������벻�����շ�����ԭ��",
                "��˵���˵��그�����ֵĽ��ɣ��������£��벻�����Ӷ���"
                + "�Ժ��Ȼ�س�������"
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
                "��˵���˳��Ի�ɽ���޶����������м���Ȼ�������벻�������ֳ�ͷ��",
                "���Ŵ��˱��ǻ�ɽ���ϣ�����֮��ԶͶ��أ���֪�ιʷ�����ԭ��",
                "��˵���˱��Ǳ����Ե׵���ɽȥ�ģ�͵ѧ�����Ժ�û�ر���"
                + "�����ٵؿ��ޣ��������ڵó�������",
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
                "��˵����ԭ�ǵ���������ʦŷ������ֳ�����֪�ι�ʧ�٣���"
                + "�վ�Ȼ�ֳ����ˡ�",
                "���Ŵ���͵ѧ���������ɽׯŷ�����ҵ��书��������ŷ��"
                + "�淢�ִ�����ˣ����˴��˶��ߣ���Ȼ����գ�����˼�飡",
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
                "��˵����ԭ��ؤ�ﳤ�ϣ��书�߾���������������Ů�Ӷ���"
                + "������⣬�������ֽ����ؽ�����Ѫ���ȷ硣"
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
                "��˵����ԭ��Ľ�ݼҳ����书�߾�������������������"
                + "ͨ��׷ɱ��������������������س�������"
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
                "��˵����ԭ�Ƕ��ϼҳ����书�߾�������͵ѧ�����񽣶���"
                + "��ն�������������ѣ������س�������"
        }));

        set_skill("force", 1);                // �����ڹ�
        set_skill("kurong-changong", 1);      // ��������
        set_skill("finger", 1);               // ����ָ��
        set_skill("six-finger", 1);           // ������
        set_skill("dodge", 1);                // ��������
        set_skill("tiannan-step", 1);         // ���ϲ���
        set_skill("parry", 1);                // �����м�

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
                "��˵����ԭ�Ƕ��һ������书�߾���������Եδ��"
                + "������ţ������س�������ȴ�����Դ�䡣"
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
                "��˵����ԭ�ǹ�����Һ��ܣ��书�߾�������������"
                + "ɱ��Խ�����Ը��䣬ɱ�����顣"
        }));

    set_skill("force", 1);            // �����ڹ�
    set_skill("lengyue-shengong", 1); // ������
    set_skill("blade", 1);            // ��������
    set_skill("hujia-daofa", 1);      // ���ҵ���
    set_skill("dodge", 1);            // ��������
    set_skill("taxue-wuhen", 1);      // ̤ѩ�޺�
    set_skill("parry", 1);            // �����м�
    set_skill("strike", 1);           // �����Ʒ�
    set_skill("tianchang-zhang", 1);  // �쳤�Ʒ�
    set_skill("cuff", 1);             // ����ȭ��
    set_skill("hujia-quan", 1);       // ����ȭ��

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
                "��˵����ԭ��ȫ��Ԫ�ϣ��书�߾��������͵���"
                + "����֮�࣬������ң����񽭺���"
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
                "��˵����ԭ��ѩɽ��ɮ���书�߾�����������ɫ��"
                + "�����ʦ�ţ����������ֽ�����������һ��ɱ�ԡ�"
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
                "��˵����ԭ����ң�ɻ������书�߾�������Υ��ʦ��"
                + "��汻���ʦ�ţ����������ֽ������Ʊ�����һ��Ѫ���ȷ硣"
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
                "��˵����ԭ�ǹ�Ĺ����ū���书�߾�������й¶"
                + "��Ĺ�ɵ����ܸ���������Ĺ�ɣ����������ֽ�����"
        }));

        if (query("gender") == "Ů��")
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
                "��˵����ԭ���һ������ӣ��书�߾�������͵�������澭"
                + "����ҩʦ���ʦ�ţ����������ֽ������Ʊ�����һ��Ѫ���ȷ硣"
        }));

        set_skill("force", 1);             // �����ڹ�
        set_skill("bibo-shengong", 1);     // �̲���
        set_skill("finger", 1);            // ����ָ��
        set_skill("tanzhi-shentong", 1);   // ��ָ��ͨ
        set_skill("hand", 1);           // �����ַ�
        set_skill("strike", 1);            // ����ȭ��
        set_skill("dodge", 1);             // ��������
        set_skill("parry", 1);             // �����м�
        set_skill("sword", 1);             // ��������
        set_skill("throwing", 1);          // ��������
        set_skill("luoying-shenfa",1);
        set_skill("yuxiao-jian", 1);       // ���｣��
        set_skill("lanhua-shou", 1);       // ������Ѩ��
        set_skill("qimen-wuxing", 1);      // ��������

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
                "��˵����ԭ�����չ����ϣ��书�߾������������ɽͯ��"
                + "��׷ɱ�����������ֽ������Ʊ�����һ��Ѫ���ȷ硣"
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
                "��˵����ԭ�����̻������书�߾�������͵��Ǭ����Ų��"
                + "�߻���ħ�����������ֽ������Ʊ�����һ��Ѫ���ȷ硣"
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
