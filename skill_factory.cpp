#include"skill_factory.h"

SkillFactory* SkillFactory::skill_factory = nullptr;

Skill* SkillFactory::get_skill(SkillType type)
{
	Skill* new_skill = new Skill;

	switch (type)
	{
	case SkillType::NONE:
		break;
	case SkillType::Detect_3x3:
		break;
	case SkillType::Detect_13C:
		break;
	case SkillType::Attack_5C:
		break;
	case SkillType::Attack_3x3:
		break;
	case SkillType::Repair:
		break;
	default:
		break;
	}

	return new_skill;
}