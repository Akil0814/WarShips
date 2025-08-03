#pragma once
#include"skill.h"
#include"skill_type.h"

class SkillFactory
{
public:
	static SkillFactory* instance()//实现单例模式
	{
		if (!skill_factory)
			skill_factory = new SkillFactory();//线程不安全

		return skill_factory;
	}

	Skill* get_skill(SkillType type);

private:
	SkillFactory() = default;

private:

	static SkillFactory* skill_factory;
};