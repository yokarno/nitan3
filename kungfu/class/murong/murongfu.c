// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// murongfu.c Ľ�ݸ�

#include <ansi.h>
#include "murong.h"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_GUARDER;
inherit F_COAGENT;

void create()
{
        set_name("Ľ�ݸ�", ({ "murong fu", "murong", "fu" }));
        set("long", @LONG
���ǹ���Ľ�ݵĴ��ˣ���Ľ�ݲ�֮�ӣ���ν��Ľ�ݡ����Ƿ塣
�������Ǻ��Ƿ�������Ľ�ݼҸ��֡�����ò���ţ���ȹ��ˣ�
��ȷ��Ѱ���˿ɱȡ�
LONG );
        set("titile", "����Ľ��");
        set("gender", "����");
        set("age", 25);
        set("shen_type",-1);
        set("attitude", "peaceful");

        set("str", 27);
        set("int", 29);
        set("con", 31);
        set("dex", 28);
        set("per", 28);

        set("qi", 4100);
        set("max_qi", 4100);
        set("jing", 2100);
        set("max_jing", 2100);
        set("neili", 4900);
        set("max_neili", 4900);
        set("jiali", 80);
        set("level", 30);
        set("combat_exp", 1750000);

        set_skill("force", 180);
        set_skill("literate", 140);
        set_skill("cuff", 180);
        set_skill("sword", 180);
        set_skill("blade", 180);
        set_skill("dodge", 180);
        set_skill("strike", 180);
        set_skill("parry", 200);
        
        set_skill("shenyuan-gong", 180);
        set_skill("zihui-xinfa", 200);
        set_skill("xingyi-zhang", 300);
        set_skill("douzhuan-xingyi", 200);
        set_skill("beidou-xianzong", 180);
        set_skill("qixing-quan", 180);
        set_skill("murong-jianfa", 180);
        set_skill("murong-daofa", 180);
        set_skill("martial-cognize", 140);

        map_skill("force", "shenyuan-gong");
        map_skill("dodge", "beidou-xianzong");
        map_skill("cuff",  "qixing-quan");
        map_skill("parry", "douzhuan-xingyi");
        map_skill("strike", "xingyi-zhang");
        map_skill("blade", "murong-daofa");
        map_skill("sword", "murong-jianfa");

        prepare_skill("cuff", "qixing-quan");
        
        set("inquiry", 
        ([
                "name"       : "�Ҿ����Ա�֮������ʩ�����Ĺ���Ľ�ݸ���\n",
                "here"       : "�����Ǵ��������������룬�ѵ���û����˵����\n",
                "rumors"     : "�Ҹ�ͻȾ�񼲣����������˼����һ�涼û���������¶������Σ�\n",
                "����"       : "�ҵĹ���ס����٢��ɽׯ���������������µ������񶴡�\n",
                // "��ʩˮ��"   : (: ask_ge :),
                // "������"     : (: ask_wang :),
                // "��Ԫ��"     : (: ask_dan :),
                // "��¶����ɢ" : (: ask_dan1 :),
                // "��ѧ����"   : (: ask_learn :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "recover" :),
                (: perform_action, "parry.yi" :),
                (: perform_action, "blade.feng" :),
                (: perform_action, "cuff.zhai" :),
        }));

        create_family("Ľ������", 16, "����");

        set("coagents", ({
                ([ "startroom" : "/d/yanziwu/canheju",
                   "id"        : "murong bo" ]),
        }));

        set("master_ob",3);
	setup();
        carry_object("/clone/weapon/gangdao")->wield();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver", 200);
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if ((int)ob->query("shen") > 0)
        {
                command("say ��Ľ��������������������Щ��ν������ʿ������");
                command("say �㻹����ذɣ�");
                return;
        }


        command("nod");
        command("say �����Ҿ����������㣬�պ���̿����䣬�⸴���ࡣ");
        command("recruit " + ob->query("id"));
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "����" :
        case "����" :
        case "����" :
                return QUEST_D->accept_ask(this_object(), me, topic);
                break;

        case "ժ��ʽ" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/qixing-quan/zhai",
                           "name"    : "ժ��ʽ",
                           "sk1"     : "qixing-quan",
                           "lv1"     : 40,
                           "gongxian": 140,
                           "shen"    : -4000, ]));
                break;

        case "��ת����" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/murong-jianfa/xing",
                           "name"    : "��ת����",
                           "sk1"     : "murong-jianfa",
                           "lv1"     :  40,
                           "gongxian":  200,
                           "shen"    : -6000, ]));
                break;

        case "�׺����" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/murong-jianfa/hong",
                           "name"    : "�׺����",
                           "sk1"     : "murong-jianfa",
                           "lv1"     : 80,
                           "force"   : 90,
                           "gongxian": 320,
                           "shen"    : -9000, ]));
                break;

        case "����ͬ��" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/xingyi-zhang/riyue",
                           "name"    : "����ͬ��",
                           "sk1"     : "xingyi-zhang",
                           "lv1"     :  40,
                           "gongxian":  200,
                           "shen"    : -6000, ]));
                break;

        case "�ǹ���" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/xingyi-zhang/xing",
                           "name"    : "�ǹ���",
                           "sk1"     : "xingyi-zhang",
                           "lv1"     : 80,
                           "force"   : 90,
                           "gongxian": 320,
                           "shen"    : -9000, ]));
                break;

        case "��Ӱ��" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/murong-daofa/ying",
                           "name"    : "��Ӱ��",
                           "sk1"     : "murong-daofa",
                           "lv1"     : 80,
                           "force"   : 90,
                           "gongxian": 320,
                           "shen"    : -9000, ]));
                break;
                               
        default:
                return 0;
        }
}

/*
void unconcious()
{
        die();
}

*/