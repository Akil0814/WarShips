#pragma once
#include"skill.h"
#include"skill_type.h"

class SkillFactory
{
public:
	static SkillFactory* instance()//ʵ�ֵ���ģʽ
	{
		if (!skill_factory)
			skill_factory = new SkillFactory();//�̲߳���ȫ

		return skill_factory;
	}

	Skill* get_skill(SkillType type);

private:
	SkillFactory() = default;

private:

	static SkillFactory* skill_factory;
};